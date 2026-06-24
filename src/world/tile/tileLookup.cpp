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
size_t Tile::getCreatureCount() const
{
	if (const CreatureVector* creatures = getCreatures()) {
		return creatures->size();
	}
	return 0;
}

size_t Tile::getItemCount() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->size();
	}
	return 0;
}

uint32_t Tile::getTopItemCount() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->getTopItemCount();
	}
	return 0;
}

uint32_t Tile::getDownItemCount() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->getDownItemCount();
	}
	return 0;
}

Teleport* Tile::getTeleportItem() const
{
	if (!hasFlag(TILESTATE_TELEPORT)) {
		return nullptr;
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getTeleport()) {
				return (*it)->getTeleport();
			}
		}
	}
	return nullptr;
}

MagicField* Tile::getFieldItem() const
{
	if (!hasFlag(TILESTATE_MAGICFIELD)) {
		return nullptr;
	}

	if (ground && ground->getMagicField()) {
		return ground->getMagicField();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getMagicField()) {
				return (*it)->getMagicField();
			}
		}
	}
	return nullptr;
}

TrashHolder* Tile::getTrashHolder() const
{
	if (!hasFlag(TILESTATE_TRASHHOLDER)) {
		return nullptr;
	}

	if (ground && ground->getTrashHolder()) {
		return ground->getTrashHolder();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getTrashHolder()) {
				return (*it)->getTrashHolder();
			}
		}
	}
	return nullptr;
}

Mailbox* Tile::getMailbox() const
{
	if (!hasFlag(TILESTATE_MAILBOX)) {
		return nullptr;
	}

	if (ground && ground->getMailbox()) {
		return ground->getMailbox();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getMailbox()) {
				return (*it)->getMailbox();
			}
		}
	}
	return nullptr;
}

BedItem* Tile::getBedItem() const
{
	if (!hasFlag(TILESTATE_BED)) {
		return nullptr;
	}

	if (ground && ground->getBed()) {
		return ground->getBed();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getBed()) {
				return (*it)->getBed();
			}
		}
	}
	return nullptr;
}

Creature* Tile::getTopCreature() const
{
	if (const CreatureVector* creatures = getCreatures()) {
		if (!creatures->empty()) {
			return *creatures->begin();
		}
	}
	return nullptr;
}

const Creature* Tile::getBottomCreature() const
{
	if (const CreatureVector* creatures = getCreatures()) {
		if (!creatures->empty()) {
			return *creatures->rbegin();
		}
	}
	return nullptr;
}

Creature* Tile::getTopVisibleCreature(const Creature* creature) const
{
	if (const CreatureVector* creatures = getCreatures()) {
		if (creature) {
			const Player* player = creature->getPlayer();
			if (player && player->isAccessPlayer()) {
				return getTopCreature();
			}

			for (Creature* tileCreature : *creatures) {
				if (creature->canSeeCreature(tileCreature)) {
					return tileCreature;
				}
			}
		} else {
			for (Creature* tileCreature : *creatures) {
				if (!tileCreature->isInvisible()) {
					const Player* player = tileCreature->getPlayer();
					if (!player || !player->isInGhostMode()) {
						return tileCreature;
					}
				}
			}
		}
	}
	return nullptr;
}

const Creature* Tile::getBottomVisibleCreature(const Creature* creature) const
{
	if (const CreatureVector* creatures = getCreatures()) {
		if (creature) {
			const Player* player = creature->getPlayer();
			if (player && player->isAccessPlayer()) {
				return getBottomCreature();
			}

			for (auto it = creatures->rbegin(), end = creatures->rend(); it != end; ++it) {
				if (creature->canSeeCreature(*it)) {
					return *it;
				}
			}
		} else {
			for (auto it = creatures->rbegin(), end = creatures->rend(); it != end; ++it) {
				if (!(*it)->isInvisible()) {
					const Player* player = (*it)->getPlayer();
					if (!player || !player->isInGhostMode()) {
						return *it;
					}
				}
			}
		}
	}
	return nullptr;
}

Item* Tile::getTopDownItem() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->getTopDownItem();
	}
	return nullptr;
}

Item* Tile::getTopTopItem() const
{
	if (const TileItemVector* items = getItemList()) {
		return items->getTopTopItem();
	}
	return nullptr;
}

Item* Tile::getItemByTopOrder(int32_t topOrder)
{
	//topOrder:
	//1: borders
	//2: ladders, signs, splashes
	//3: doors etc
	//4: creatures
	if (TileItemVector* items = getItemList()) {
		for (auto it = ItemVector::const_reverse_iterator(items->getEndTopItem()), end = ItemVector::const_reverse_iterator(items->getBeginTopItem()); it != end; ++it) {
			if (Item::items[(*it)->getID()].alwaysOnTopOrder == topOrder) {
				return (*it);
			}
		}
	}
	return nullptr;
}

Thing* Tile::getTopVisibleThing(const Creature* creature)
{
	Thing* thing = getTopVisibleCreature(creature);
	if (thing) {
		return thing;
	}

	TileItemVector* items = getItemList();
	if (items) {
		for (ItemVector::const_iterator it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
			const ItemType& iit = Item::items[(*it)->getID()];
			if (!iit.lookThrough) {
				return (*it);
			}
		}

		for (auto it = ItemVector::const_reverse_iterator(items->getEndTopItem()), end = ItemVector::const_reverse_iterator(items->getBeginTopItem()); it != end; ++it) {
			const ItemType& iit = Item::items[(*it)->getID()];
			if (!iit.lookThrough) {
				return (*it);
			}
		}
	}

	return ground;
}

int32_t Tile::getThingIndex(const Thing* thing) const
{
	int32_t n = -1;
	if (ground) {
		if (ground == thing) {
			return 0;
		}
		++n;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		const Item* item = thing->getItem();
		if (item && item->isAlwaysOnTop()) {
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				++n;
				if (*it == item) {
					return n;
				}
			}
		} else {
			n += items->getTopItemCount();
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		if (thing->getCreature()) {
			for (Creature* creature : *creatures) {
				++n;
				if (creature == thing) {
					return n;
				}
			}
		} else {
			n += creatures->size();
		}
	}

	if (items) {
		const Item* item = thing->getItem();
		if (item && !item->isAlwaysOnTop()) {
			for (auto it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
				++n;
				if (*it == item) {
					return n;
				}
			}
		}
	}
	return -1;
}

int32_t Tile::getClientIndexOfCreature(const Player* player, const Creature* creature) const
{
	int32_t n;
	if (ground) {
		n = 1;
	} else {
		n = 0;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		n += items->getTopItemCount();
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (const Creature* c : boost::adaptors::reverse(*creatures)) {
			if (c == creature) {
				return n;
			} else if (player->canSeeCreature(c)) {
				++n;
			}
		}
	}
	return -1;
}

int32_t Tile::getStackposOfCreature(const Player* player, const Creature* creature) const
{
	int32_t n;
	if (ground) {
		n = 1;
	} else {
		n = 0;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		n += items->getTopItemCount();
		if (n >= 10) {
			return -1;
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (const Creature* c : boost::adaptors::reverse(*creatures)) {
			if (c == creature) {
				return n;
			} else if (player->canSeeCreature(c)) {
				if (++n >= 10) {
					return -1;
				}
			}
		}
	}
	return -1;
}

int32_t Tile::getStackposOfItem(const Player* player, const Item* item) const
{
	int32_t n = 0;
	if (ground) {
		if (ground == item) {
			return n;
		}
		++n;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		if (item->isAlwaysOnTop()) {
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				if (*it == item) {
					return n;
				} else if (++n == 10) {
					return -1;
				}
			}
		} else {
			n += items->getTopItemCount();
			if (n >= 10) {
				return -1;
			}
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (const Creature* creature : *creatures) {
			if (player->canSeeCreature(creature)) {
				if (++n >= 10) {
					return -1;
				}
			}
		}
	}

	if (items && !item->isAlwaysOnTop()) {
		for (auto it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
			if (*it == item) {
				return n;
			} else if (++n >= 10) {
				return -1;
			}
		}
	}
	return -1;
}

size_t Tile::getFirstIndex() const
{
	return 0;
}

size_t Tile::getLastIndex() const
{
	return getThingCount();
}

uint32_t Tile::getItemTypeCount(uint16_t itemId, int32_t subType /*= -1*/) const
{
	uint32_t count = 0;
	if (ground && ground->getID() == itemId) {
		count += Item::countByType(ground, subType);
	}

	const TileItemVector* items = getItemList();
	if (items) {
		for (const Item* item : *items) {
			if (item->getID() == itemId) {
				count += Item::countByType(item, subType);
			}
		}
	}
	return count;
}

Thing* Tile::getThing(size_t index) const
{
	if (ground) {
		if (index == 0) {
			return ground;
		}

		--index;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		uint32_t topItemSize = items->getTopItemCount();
		if (index < topItemSize) {
			return items->at(items->getDownItemCount() + index);
		}
		index -= topItemSize;
	}

	if (const CreatureVector* creatures = getCreatures()) {
		if (index < creatures->size()) {
			return (*creatures)[index];
		}
		index -= creatures->size();
	}

	if (items && index < items->getDownItemCount()) {
		return items->at(index);
	}
	return nullptr;
}

Item* Tile::getUseItem() const
{
	const TileItemVector* items = getItemList();
	if (!items || items->size() == 0) {
		return ground;
	}

	for (Item* item : boost::adaptors::reverse(*items)) {
		if (Item::items[item->getID()].forceUse) {
			return item;
		}
	}

	Item* item = items->getTopDownItem();
	if (!item) {
		item = items->getTopTopItem();
	}
	return item;
}
