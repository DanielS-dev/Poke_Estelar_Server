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
ReturnValue Tile::queryAdd(int32_t, const Thing& thing, uint32_t, uint32_t flags, Creature*) const
{
	if (const Creature* creature = thing.getCreature()) {
		if (hasBitSet(FLAG_NOLIMIT, flags)) {
			return RETURNVALUE_NOERROR;
		}

		if (hasBitSet(FLAG_PATHFINDING, flags) && hasFlag(TILESTATE_FLOORCHANGE | TILESTATE_TELEPORT)) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		if (ground == nullptr) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		if (const Monster* monster = creature->getMonster()) {
			if (hasFlag(TILESTATE_PROTECTIONZONE | TILESTATE_FLOORCHANGE | TILESTATE_TELEPORT)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			const CreatureVector* creatures = getCreatures();
			if (monster->canPushCreatures() && !monster->isSummon()) {
				if (creatures) {
					for (Creature* tileCreature : *creatures) {
						if (tileCreature->getPlayer() && tileCreature->getPlayer()->isInGhostMode()) {
							continue;
						}

						const Monster* creatureMonster = tileCreature->getMonster();
						if (!creatureMonster || !tileCreature->isPushable() ||
						        (creatureMonster->isSummon() && creatureMonster->getMaster()->getPlayer())) {
							return RETURNVALUE_NOTPOSSIBLE;
						}
					}
				}
			} else if (creatures && !creatures->empty()) {
				for (const Creature* tileCreature : *creatures) {
					if (!tileCreature->isInGhostMode()) {
						return RETURNVALUE_NOTENOUGHROOM;
					}
				}
			}

			if (hasFlag(TILESTATE_IMMOVABLEBLOCKSOLID)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasBitSet(FLAG_PATHFINDING, flags) && hasFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasFlag(TILESTATE_BLOCKSOLID) || (hasBitSet(FLAG_PATHFINDING, flags) && hasFlag(TILESTATE_NOFIELDBLOCKPATH))) {
				if (!(monster->canPushItems() || hasBitSet(FLAG_IGNOREBLOCKITEM, flags))) {
					return RETURNVALUE_NOTPOSSIBLE;
				}
			}

			MagicField* field = getFieldItem();
			if (field && !field->isBlocking()) {
				CombatType_t combatType = field->getCombatType();

				//There is 3 options for a monster to enter a magic field
				//1) Monster is immune
				if (!monster->isImmune(combatType)) {
					//1) Monster is "strong" enough to handle the damage
					//2) Monster is already afflicated by this type of condition
					if (hasBitSet(FLAG_IGNOREFIELDDAMAGE, flags)) {
						if (!(monster->canPushItems() || monster->hasCondition(Combat::DamageToConditionType(combatType)))) {
							return RETURNVALUE_NOTPOSSIBLE;
						}
					} else {
						return RETURNVALUE_NOTPOSSIBLE;
					}
				}
			}

			return RETURNVALUE_NOERROR;
		}

		const CreatureVector* creatures = getCreatures();
		if (const Player* player = creature->getPlayer()) {
			if (creatures && !creatures->empty() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, flags) && !player->isAccessPlayer()) {
				for (const Creature* tileCreature : *creatures) {
					if (!player->canWalkthrough(tileCreature)) {
						return RETURNVALUE_NOTPOSSIBLE;
					}
				}
			}

			if (player->getParent() == nullptr && hasFlag(TILESTATE_NOLOGOUT)) {
				//player is trying to login to a "no logout" tile
				return RETURNVALUE_NOTPOSSIBLE;
			}

			const Tile* playerTile = player->getTile();
			if (playerTile && player->isPzLocked()) {
				if (!playerTile->hasFlag(TILESTATE_PVPZONE)) {
					//player is trying to enter a pvp zone while being pz-locked
					if (hasFlag(TILESTATE_PVPZONE)) {
						return RETURNVALUE_PLAYERISPZLOCKEDENTERPVPZONE;
					}
				} else if (!hasFlag(TILESTATE_PVPZONE)) {
					// player is trying to leave a pvp zone while being pz-locked
					return RETURNVALUE_PLAYERISPZLOCKEDLEAVEPVPZONE;
				}

				if ((!playerTile->hasFlag(TILESTATE_NOPVPZONE) && hasFlag(TILESTATE_NOPVPZONE)) ||
					(!playerTile->hasFlag(TILESTATE_PROTECTIONZONE) && hasFlag(TILESTATE_PROTECTIONZONE))) {
					// player is trying to enter a non-pvp/protection zone while being pz-locked
					return RETURNVALUE_PLAYERISPZLOCKED;
				}
			}
		} else if (creatures && !creatures->empty() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, flags)) {
			for (const Creature* tileCreature : *creatures) {
				if (!tileCreature->isInGhostMode()) {
					return RETURNVALUE_NOTENOUGHROOM;
				}
			}
		}

		if (!hasBitSet(FLAG_IGNOREBLOCKITEM, flags)) {
			//If the FLAG_IGNOREBLOCKITEM bit isn't set we dont have to iterate every single item
			if (hasFlag(TILESTATE_BLOCKSOLID)) {
				return RETURNVALUE_NOTENOUGHROOM;
			}
		} else {
			//FLAG_IGNOREBLOCKITEM is set
			if (ground) {
				const ItemType& iiType = Item::items[ground->getID()];
				if (iiType.blockSolid && (!iiType.moveable || ground->hasAttribute(ITEM_ATTRIBUTE_UNIQUEID))) {
					return RETURNVALUE_NOTPOSSIBLE;
				}
			}

			if (const auto items = getItemList()) {
				for (const Item* item : *items) {
					const ItemType& iiType = Item::items[item->getID()];
					if (iiType.blockSolid && (!iiType.moveable || item->hasAttribute(ITEM_ATTRIBUTE_UNIQUEID))) {
						return RETURNVALUE_NOTPOSSIBLE;
					}
				}
			}
		}
	} else if (const Item* item = thing.getItem()) {
		const TileItemVector* items = getItemList();
		if (items && items->size() >= 0xFFFF) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		if (hasBitSet(FLAG_NOLIMIT, flags)) {
			return RETURNVALUE_NOERROR;
		}

		bool itemIsHangable = item->isHangable();
		if (ground == nullptr && !itemIsHangable) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		const CreatureVector* creatures = getCreatures();
		if (creatures && !creatures->empty() && item->isBlocking() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, flags)) {
			for (const Creature* tileCreature : *creatures) {
				if (!tileCreature->isInGhostMode()) {
					return RETURNVALUE_NOTENOUGHROOM;
				}
			}
		}

		if (itemIsHangable && hasFlag(TILESTATE_SUPPORTS_HANGABLE)) {
			if (items) {
				for (const Item* tileItem : *items) {
					if (tileItem->isHangable()) {
						return RETURNVALUE_NEEDEXCHANGE;
					}
				}
			}
		} else {
			if (ground) {
				const ItemType& iiType = Item::items[ground->getID()];
				if (iiType.blockSolid) {
					if (!iiType.allowPickupable || item->isMagicField() || item->isBlocking()) {
						if (!item->isPickupable()) {
							return RETURNVALUE_NOTENOUGHROOM;
						}

						if (!iiType.hasHeight || iiType.pickupable || iiType.isBed()) {
							return RETURNVALUE_NOTENOUGHROOM;
						}
					}
				}
			}

			if (items) {
				for (const Item* tileItem : *items) {
					const ItemType& iiType = Item::items[tileItem->getID()];
					if (!iiType.blockSolid) {
						continue;
					}

					if (iiType.allowPickupable && !item->isMagicField() && !item->isBlocking()) {
						continue;
					}

					if (!item->isPickupable()) {
						return RETURNVALUE_NOTENOUGHROOM;
					}

					if (!iiType.hasHeight || iiType.pickupable || iiType.isBed()) {
						return RETURNVALUE_NOTENOUGHROOM;
					}
				}
			}
		}
	}
	return RETURNVALUE_NOERROR;
}

ReturnValue Tile::queryMaxCount(int32_t, const Thing&, uint32_t count, uint32_t& maxQueryCount, uint32_t) const
{
	maxQueryCount = std::max<uint32_t>(1, count);
	return RETURNVALUE_NOERROR;
}

ReturnValue Tile::queryRemove(const Thing& thing, uint32_t count, uint32_t flags) const
{
	int32_t index = getThingIndex(&thing);
	if (index == -1) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	const Item* item = thing.getItem();
	if (item == nullptr) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (count == 0 || (item->isStackable() && count > item->getItemCount())) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (!item->isMoveable() && !hasBitSet(FLAG_IGNORENOTMOVEABLE, flags)) {
		return RETURNVALUE_NOTMOVEABLE;
	}

	return RETURNVALUE_NOERROR;
}

Tile* Tile::queryDestination(int32_t&, const Thing&, Item** destItem, uint32_t& flags)
{
	Tile* destTile = nullptr;
	*destItem = nullptr;

	if (hasFlag(TILESTATE_FLOORCHANGE_DOWN)) {
		uint16_t dx = tilePos.x;
		uint16_t dy = tilePos.y;
		uint8_t dz = tilePos.z + 1;

		Tile* southDownTile = g_game.map.getTile(dx, dy - 1, dz);
		if (southDownTile && southDownTile->hasFlag(TILESTATE_FLOORCHANGE_SOUTH_ALT)) {
			dy -= 2;
			destTile = g_game.map.getTile(dx, dy, dz);
		} else {
			Tile* eastDownTile = g_game.map.getTile(dx - 1, dy, dz);
			if (eastDownTile && eastDownTile->hasFlag(TILESTATE_FLOORCHANGE_EAST_ALT)) {
				dx -= 2;
				destTile = g_game.map.getTile(dx, dy, dz);
			} else {
				Tile* downTile = g_game.map.getTile(dx, dy, dz);
				if (downTile) {
					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_NORTH)) {
						++dy;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_SOUTH)) {
						--dy;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_SOUTH_ALT)) {
						dy -= 2;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_EAST)) {
						--dx;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_EAST_ALT)) {
						dx -= 2;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_WEST)) {
						++dx;
					}

					destTile = g_game.map.getTile(dx, dy, dz);
				}
			}
		}
	} else if (hasFlag(TILESTATE_FLOORCHANGE)) {
		uint16_t dx = tilePos.x;
		uint16_t dy = tilePos.y;
		uint8_t dz = tilePos.z - 1;

		if (hasFlag(TILESTATE_FLOORCHANGE_NORTH)) {
			--dy;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_SOUTH)) {
			++dy;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_EAST)) {
			++dx;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_WEST)) {
			--dx;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_SOUTH_ALT)) {
			dy += 2;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_EAST_ALT)) {
			dx += 2;
		}

		destTile = g_game.map.getTile(dx, dy, dz);
	}

	if (destTile == nullptr) {
		destTile = this;
	} else {
		flags |= FLAG_NOLIMIT;    //Will ignore that there is blocking items/creatures
	}

	if (destTile) {
		Thing* destThing = destTile->getTopDownItem();
		if (destThing) {
			*destItem = destThing->getItem();
		}
	}
	return destTile;
}

