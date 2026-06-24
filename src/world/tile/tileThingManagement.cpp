// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <boost/range/adaptor/reversed.hpp>

#include "../tile.hpp"

#include "../../entities/creature.hpp"
#include "../../entities/monster.hpp"
#include "../../game/combat/combat.hpp"
#include "../../game/game.hpp"
#include "../../game/movement/movement.hpp"
#include "../../items/mailbox.hpp"
#include "../../items/trashholder.hpp"
#include "../teleport.hpp"

extern Game g_game;
extern MoveEvents* g_moveEvents;
void Tile::addThing(Thing* thing)
{
	addThing(0, thing);
}

void Tile::addThing(int32_t, Thing* thing)
{
	Creature* creature = thing->getCreature();
	if (creature) {
		g_game.map.clearSpectatorCache();
		creature->setParent(this);
		CreatureVector* creatures = makeCreatures();
		creatures->insert(creatures->begin(), creature);
	} else {
		Item* item = thing->getItem();
		if (item == nullptr) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		TileItemVector* items = getItemList();
		if (items && items->size() >= 0xFFFF) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		item->setParent(this);

		const ItemType& itemType = Item::items[item->getID()];
		if (itemType.isGroundTile()) {
			if (ground == nullptr) {
				ground = item;
				onAddTileItem(item);
			} else {
				const ItemType& oldType = Item::items[ground->getID()];

				Item* oldGround = ground;
				ground->setParent(nullptr);
				g_game.ReleaseItem(ground);
				ground = item;
				resetTileFlags(oldGround);
				setTileFlags(item);
				onUpdateTileItem(oldGround, oldType, item, itemType);
				postRemoveNotification(oldGround, nullptr, 0);
			}
		} else if (itemType.alwaysOnTop) {
			if (itemType.isSplash() && items) {
				//remove old splash if exists
				for (ItemVector::const_iterator it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
					Item* oldSplash = *it;
					if (!Item::items[oldSplash->getID()].isSplash()) {
						continue;
					}

					removeThing(oldSplash, 1);
					oldSplash->setParent(nullptr);
					g_game.ReleaseItem(oldSplash);
					postRemoveNotification(oldSplash, nullptr, 0);
					break;
				}
			}

			bool isInserted = false;

			if (items) {
				for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
					//Note: this is different from internalAddThing
					if (itemType.alwaysOnTopOrder <= Item::items[(*it)->getID()].alwaysOnTopOrder) {
						items->insert(it, item);
						isInserted = true;
						break;
					}
				}
			} else {
				items = makeItemList();
			}

			if (!isInserted) {
				items->push_back(item);
			}

			onAddTileItem(item);
		} else {
			if (itemType.isMagicField()) {
				//remove old field item if exists
				if (items) {
					for (ItemVector::const_iterator it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
						MagicField* oldField = (*it)->getMagicField();
						if (oldField) {
							if (oldField->isReplaceable()) {
								removeThing(oldField, 1);

								oldField->setParent(nullptr);
								g_game.ReleaseItem(oldField);
								postRemoveNotification(oldField, nullptr, 0);
								break;
							} else {
								//This magic field cannot be replaced.
								item->setParent(nullptr);
								g_game.ReleaseItem(item);
								return;
							}
						}
					}
				}
			}

			items = makeItemList();
			items->insert(items->getBeginDownItem(), item);
			items->addDownItemCount(1);
			onAddTileItem(item);
		}
	}
}

void Tile::updateThing(Thing* thing, uint16_t itemId, uint32_t count)
{
	int32_t index = getThingIndex(thing);
	if (index == -1) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	Item* item = thing->getItem();
	if (item == nullptr) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	const ItemType& oldType = Item::items[item->getID()];
	const ItemType& newType = Item::items[itemId];
	resetTileFlags(item);
	item->setID(itemId);
	item->setSubType(count);
	setTileFlags(item);
	onUpdateTileItem(item, oldType, item, newType);
}

void Tile::replaceThing(uint32_t index, Thing* thing)
{
	int32_t pos = index;

	Item* item = thing->getItem();
	if (item == nullptr) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	Item* oldItem = nullptr;
	bool isInserted = false;

	if (ground) {
		if (pos == 0) {
			oldItem = ground;
			ground = item;
			isInserted = true;
		}

		--pos;
	}

	TileItemVector* items = getItemList();
	if (items && !isInserted) {
		int32_t topItemSize = getTopItemCount();
		if (pos < topItemSize) {
			auto it = items->getBeginTopItem();
			it += pos;

			oldItem = (*it);
			it = items->erase(it);
			items->insert(it, item);
			isInserted = true;
		}

		pos -= topItemSize;
	}

	CreatureVector* creatures = getCreatures();
	if (creatures) {
		if (!isInserted && pos < static_cast<int32_t>(creatures->size())) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		pos -= static_cast<uint32_t>(creatures->size());
	}

	if (items && !isInserted) {
		int32_t downItemSize = getDownItemCount();
		if (pos < downItemSize) {
			auto it = items->getBeginDownItem() + pos;
			oldItem = *it;
			it = items->erase(it);
			items->insert(it, item);
			isInserted = true;
		}
	}

	if (isInserted) {
		item->setParent(this);

		resetTileFlags(oldItem);
		setTileFlags(item);
		const ItemType& oldType = Item::items[oldItem->getID()];
		const ItemType& newType = Item::items[item->getID()];
		onUpdateTileItem(oldItem, oldType, item, newType);

		oldItem->setParent(nullptr);
		return /*RETURNVALUE_NOERROR*/;
	}
}

void Tile::removeThing(Thing* thing, uint32_t count)
{
	Creature* creature = thing->getCreature();
	if (creature) {
		CreatureVector* creatures = getCreatures();
		if (creatures) {
			auto it = std::find(creatures->begin(), creatures->end(), thing);
			if (it != creatures->end()) {
				g_game.map.clearSpectatorCache();
				creatures->erase(it);
			}
		}
		return;
	}

	Item* item = thing->getItem();
	if (!item) {
		return;
	}

	int32_t index = getThingIndex(item);
	if (index == -1) {
		return;
	}

	if (item == ground) {
		ground->setParent(nullptr);
		ground = nullptr;

		SpectatorVec list;
		g_game.map.getSpectators(list, getPosition(), true);
		onRemoveTileItem(list, std::vector<int32_t>(list.size(), 0), item);
		return;
	}

	TileItemVector* items = getItemList();
	if (!items) {
		return;
	}

	const ItemType& itemType = Item::items[item->getID()];
	if (itemType.alwaysOnTop) {
		auto it = std::find(items->getBeginTopItem(), items->getEndTopItem(), item);
		if (it == items->getEndTopItem()) {
			return;
		}

		std::vector<int32_t> oldStackPosVector;

		SpectatorVec list;
		g_game.map.getSpectators(list, getPosition(), true);
		for (Creature* spectator : list) {
			if (Player* tmpPlayer = spectator->getPlayer()) {
				oldStackPosVector.push_back(getStackposOfItem(tmpPlayer, item));
			}
		}

		item->setParent(nullptr);
		items->erase(it);
		onRemoveTileItem(list, oldStackPosVector, item);
	} else {
		auto it = std::find(items->getBeginDownItem(), items->getEndDownItem(), item);
		if (it == items->getEndDownItem()) {
			return;
		}

		if (itemType.stackable && count != item->getItemCount()) {
			uint8_t newCount = static_cast<uint8_t>(std::max<int32_t>(0, static_cast<int32_t>(item->getItemCount() - count)));
			item->setItemCount(newCount);
			onUpdateTileItem(item, itemType, item, itemType);
		} else {
			std::vector<int32_t> oldStackPosVector;

			SpectatorVec list;
			g_game.map.getSpectators(list, getPosition(), true);
			for (Creature* spectator : list) {
				if (Player* tmpPlayer = spectator->getPlayer()) {
					oldStackPosVector.push_back(getStackposOfItem(tmpPlayer, item));
				}
			}

			item->setParent(nullptr);
			items->erase(it);
			items->addDownItemCount(-1);
			onRemoveTileItem(list, oldStackPosVector, item);
		}
	}
}

void Tile::removeCreature(Creature* creature)
{
	g_game.map.getQTNode(tilePos.x, tilePos.y)->removeCreature(creature);
	removeThing(creature, 0);
}

void Tile::internalAddThing(Thing* thing)
{
	internalAddThing(0, thing);
}

void Tile::internalAddThing(uint32_t, Thing* thing)
{
	thing->setParent(this);

	Creature* creature = thing->getCreature();
	if (creature) {
		g_game.map.clearSpectatorCache();
		CreatureVector* creatures = makeCreatures();
		creatures->insert(creatures->begin(), creature);
	} else {
		Item* item = thing->getItem();
		if (item == nullptr) {
			return;
		}

		const ItemType& itemType = Item::items[item->getID()];
		if (itemType.isGroundTile()) {
			if (ground == nullptr) {
				ground = item;
				setTileFlags(item);
			}
			return;
		}

		TileItemVector* items = makeItemList();
		if (items->size() >= 0xFFFF) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		if (itemType.alwaysOnTop) {
			bool isInserted = false;
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				if (Item::items[(*it)->getID()].alwaysOnTopOrder > itemType.alwaysOnTopOrder) {
					items->insert(it, item);
					isInserted = true;
					break;
				}
			}

			if (!isInserted) {
				items->push_back(item);
			}
		} else {
			items->insert(items->getBeginDownItem(), item);
			items->addDownItemCount(1);
		}

		setTileFlags(item);
	}
}

