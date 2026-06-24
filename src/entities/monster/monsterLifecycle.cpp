// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../monster.hpp"

#include "../../config/configmanager.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../game/game.hpp"
#include "../../game/spells/spells.hpp"

extern Game g_game;
extern Monsters g_monsters;
extern ConfigManager g_config;

void Monster::death(Creature*)
{
	setAttackedCreature(nullptr);

	for (Creature* summon : summons) {
		summon->changeHealth(-summon->getHealth());
		summon->setMaster(nullptr);
		summon->decrementReferenceCounter();
	}
	summons.clear();

	clearTargetList();
	clearFriendList();
	onIdleStatus();
}

Item* Monster::getCorpse(Creature* lastHitCreature, Creature* mostDamageCreature)
{
	Item* corpse = Creature::getCorpse(lastHitCreature, mostDamageCreature);
	if (corpse) {
		if (mostDamageCreature) {
			if (mostDamageCreature->getPlayer()) {
				corpse->setCorpseOwner(mostDamageCreature->getID());
			} else {
				const Creature* mostDamageCreatureMaster = mostDamageCreature->getMaster();
				if (mostDamageCreatureMaster && mostDamageCreatureMaster->getPlayer()) {
					corpse->setCorpseOwner(mostDamageCreatureMaster->getID());
				}
			}
		}
	}
	return corpse;
}

bool Monster::isInSpawnRange(const Position& pos) const
{
	if (!spawn) {
		return true;
	}

	if (Monster::despawnRadius == 0) {
		return true;
	}

	if (!Spawns::isInZone(masterPos, Monster::despawnRadius, pos)) {
		return false;
	}

	if (Monster::despawnRange == 0) {
		return true;
	}

	if (Position::getDistanceZ(pos, masterPos) > Monster::despawnRange) {
		return false;
	}

	return true;
}

bool Monster::getCombatValues(int32_t& min, int32_t& max)
{
	if (minCombatValue == 0 && maxCombatValue == 0) {
		return false;
	}

	min = minCombatValue;
	max = maxCombatValue;
	return true;
}

void Monster::updateLookDirection()
{
	Direction newDir = getDirection();

	if (attackedCreature) {
		const Position& pos = getPosition();
		const Position& attackedCreaturePos = attackedCreature->getPosition();
		int_fast32_t offsetx = Position::getOffsetX(attackedCreaturePos, pos);
		int_fast32_t offsety = Position::getOffsetY(attackedCreaturePos, pos);

		int32_t dx = std::abs(offsetx);
		int32_t dy = std::abs(offsety);
		if (dx > dy) {
			//look EAST/WEST
			if (offsetx < 0) {
				newDir = DIRECTION_WEST;
			} else {
				newDir = DIRECTION_EAST;
			}
		} else if (dx < dy) {
			//look NORTH/SOUTH
			if (offsety < 0) {
				newDir = DIRECTION_NORTH;
			} else {
				newDir = DIRECTION_SOUTH;
			}
		} else {
			Direction dir = getDirection();
			if (offsetx < 0 && offsety < 0) {
				if (dir == DIRECTION_SOUTH) {
					newDir = DIRECTION_WEST;
				} else if (dir == DIRECTION_EAST) {
					newDir = DIRECTION_NORTH;
				}
			} else if (offsetx < 0 && offsety > 0) {
				if (dir == DIRECTION_NORTH) {
					newDir = DIRECTION_WEST;
				} else if (dir == DIRECTION_EAST) {
					newDir = DIRECTION_SOUTH;
				}
			} else if (offsetx > 0 && offsety < 0) {
				if (dir == DIRECTION_SOUTH) {
					newDir = DIRECTION_EAST;
				} else if (dir == DIRECTION_WEST) {
					newDir = DIRECTION_NORTH;
				}
			} else {
				if (dir == DIRECTION_NORTH) {
					newDir = DIRECTION_EAST;
				} else if (dir == DIRECTION_WEST) {
					newDir = DIRECTION_SOUTH;
				}
			}
		}
	}

	g_game.internalCreatureTurn(this, newDir);
}

void Monster::dropLoot(Container* corpse, Creature*)
{
	if (corpse && lootDrop) {
//		mType->createLoot(corpse);
		mType->createLoot(corpse, g_config.getDouble(ConfigManager::MONSTERLEVEL_BONUSLOOT) * level); //pota
	}
}

void Monster::setNormalCreatureLight()
{
	internalLight = mType->info.light;
}

void Monster::drainHealth(Creature* attacker, int32_t damage)
{
	Creature::drainHealth(attacker, damage);
	if (isInvisible()) {
		removeCondition(CONDITION_INVISIBLE);
	}
}

void Monster::changeHealth(int32_t healthChange, bool sendHealthChange/* = true*/)
{
	//In case a player with ignore flag set attacks the monster
	setIdle(false);
	Creature::changeHealth(healthChange, sendHealthChange);
}

bool Monster::challengeCreature(Creature* creature)
{
	if (isSummon()) {
		return false;
	}

	bool result = selectTarget(creature);
	if (result) {
		targetChangeCooldown = 8000;
		targetChangeTicks = 0;
	}
	return result;
}

bool Monster::convinceCreature(Creature* creature)
{
	Player* player = creature->getPlayer();
	if (player && !player->hasFlag(PlayerFlag_CanConvinceAll)) {
		if (!mType->info.isConvinceable) {
			return false;
		}
	}

	if (isSummon()) {
		if (getMaster()->getPlayer()) {
			return false;
		} else if (getMaster() == creature) {
			return false;
		}

		Creature* oldMaster = getMaster();
		oldMaster->removeSummon(this);
	}

	creature->addSummon(this);

	setFollowCreature(nullptr);
	setAttackedCreature(nullptr);

	//destroy summons
	for (Creature* summon : summons) {
		summon->changeHealth(-summon->getHealth());
		summon->setMaster(nullptr);
		summon->decrementReferenceCounter();
	}
	summons.clear();

	isMasterInRange = true;
	updateTargetList();
	updateIdleStatus();

	//Notify surrounding about the change
	SpectatorVec list;
	g_game.map.getSpectators(list, getPosition(), true);
	g_game.map.getSpectators(list, creature->getPosition(), true);
	for (Creature* spectator : list) {
		spectator->onCreatureConvinced(creature, this);
	}

	if (spawn) {
		spawn->removeMonster(this);
		spawn = nullptr;
	}
	return true;
}

void Monster::onCreatureConvinced(const Creature* convincer, const Creature* creature)
{
	if (convincer != this && (isFriend(creature) || isOpponent(creature))) {
		updateTargetList();
		updateIdleStatus();
	}
}

void Monster::getPathSearchParams(const Creature* creature, FindPathParams& fpp) const
{
	Creature::getPathSearchParams(creature, fpp);

	fpp.minTargetDist = 1;
	fpp.maxTargetDist = mType->info.targetDistance;

	if (isSummon()) {
		if (getMaster() == creature) {
			fpp.maxTargetDist = 2;
			fpp.fullPathSearch = true;
		} else if (mType->info.targetDistance <= 1) {
			fpp.fullPathSearch = true;
		} else {
			fpp.fullPathSearch = !canUseAttack(getPosition(), creature);
		}
	} else if (isFleeing()) {
		//Distance should be higher than the client view range (Map::maxClientViewportX/Map::maxClientViewportY)
		fpp.maxTargetDist = Map::maxViewportX;
		fpp.clearSight = false;
		fpp.keepDistance = true;
		fpp.fullPathSearch = false;
	} else if (mType->info.targetDistance <= 1) {
		fpp.fullPathSearch = true;
	} else {
		fpp.fullPathSearch = !canUseAttack(getPosition(), creature);
	}
}
