// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../creature.hpp"

#include "../monster.hpp"
#include "../../config/configmanager.hpp"
#include "../../core/scheduler.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern ConfigManager g_config;
extern CreatureEvents* g_creatureEvents;

void Creature::changeHealth(int32_t healthChange, bool sendHealthChange/* = true*/)
{
	int32_t oldHealth = health;

	if (healthChange > 0) {
		health += std::min<int32_t>(healthChange, getMaxHealth() - health);
	} else {
		health = std::max<int32_t>(0, health + healthChange);
	}

	if (sendHealthChange && oldHealth != health) {
		g_game.addCreatureHealth(this);
	}
}

void Creature::changeMana(int32_t manaChange)
{
	if (manaChange > 0) {
		mana += std::min<int32_t>(manaChange, getMaxMana() - mana);
	} else {
		mana = std::max<int32_t>(0, mana + manaChange);
	}
}

void Creature::gainHealth(Creature* healer, int32_t healthGain)
{
	changeHealth(healthGain);
	if (healer) {
		healer->onTargetCreatureGainHealth(this, healthGain);
	}
}

void Creature::drainHealth(Creature* attacker, int32_t damage)
{
	changeHealth(-damage, false);

	if (attacker) {
		attacker->onAttackedCreatureDrainHealth(this, damage);
	}
}

void Creature::drainMana(Creature* attacker, int32_t manaLoss)
{
	onAttacked();
	changeMana(-manaLoss);

	if (attacker) {
		addDamagePoints(attacker, manaLoss);
	}
}

BlockType_t Creature::blockHit(Creature* attacker, CombatType_t combatType, int32_t& damage,
                               bool checkDefense /* = false */, bool checkArmor /* = false */, bool /* field  = false */)
{
	BlockType_t blockType = BLOCK_NONE;

	if (isImmune(combatType)) {
		damage = 0;
		blockType = BLOCK_IMMUNITY;
	} else if (checkDefense || checkArmor) {
		bool hasDefense = false;

		if (blockCount > 0) {
			--blockCount;
			hasDefense = true;
		}

		if (checkDefense && hasDefense) {
			int32_t defense = getDefense();
			damage -= uniform_random(defense / 2, defense);
			if (damage <= 0) {
				damage = 0;
				blockType = BLOCK_DEFENSE;
				checkArmor = false;
			}
		}

		if (checkArmor) {
			int32_t armor = getArmor();
			if (armor > 3) {
				damage -= uniform_random(armor / 2, armor - (armor % 2 + 1));
			} else if (armor > 0) {
				--damage;
			}

			if (damage <= 0) {
				damage = 0;
				blockType = BLOCK_ARMOR;
			}
		}

		if (hasDefense && blockType != BLOCK_NONE) {
			onBlockHit();
		}
	}

	if (attacker) {
		attacker->onAttackedCreature(this);
		attacker->onAttackedCreatureBlockHit(blockType);
	}

	onAttacked();
	return blockType;
}

bool Creature::setAttackedCreature(Creature* creature)
{
	if (creature) {
		const Position& creaturePos = creature->getPosition();
		if (creaturePos.z != getPosition().z || !canSee(creaturePos)) {
			attackedCreature = nullptr;
			return false;
		}

		attackedCreature = creature;
		onAttackedCreature(attackedCreature);
		attackedCreature->onAttacked();
	} else {
		attackedCreature = nullptr;
	}

	for (Creature* summon : summons) {
		summon->setAttackedCreature(creature);
	}
	return true;
}

void Creature::getPathSearchParams(const Creature*, FindPathParams& fpp) const
{
	fpp.fullPathSearch = !hasFollowPath;
	fpp.clearSight = true;
	fpp.maxSearchDist = 12;
	fpp.minTargetDist = 1;
	fpp.maxTargetDist = 1;
}

void Creature::goToFollowCreature()
{
	if (followCreature) {
		FindPathParams fpp;
		getPathSearchParams(followCreature, fpp);

		Monster* monster = getMonster();
		if (monster && !monster->getMaster() && (monster->isFleeing() || fpp.maxTargetDist > 1)) {
			Direction dir = DIRECTION_NONE;

			if (monster->isFleeing()) {
				monster->getDistanceStep(followCreature->getPosition(), dir, true);
			} else { //maxTargetDist > 1
				if (!monster->getDistanceStep(followCreature->getPosition(), dir)) {
					// if we can't get anything then let the A* calculate
					listWalkDir.clear();
					if (getPathTo(followCreature->getPosition(), listWalkDir, fpp)) {
						hasFollowPath = true;
						startAutoWalk(listWalkDir);
					} else {
						hasFollowPath = false;
					}
					return;
				}
			}

			if (dir != DIRECTION_NONE) {
				listWalkDir.clear();
				listWalkDir.push_front(dir);

				hasFollowPath = true;
				startAutoWalk(listWalkDir);
			}
		} else {
			listWalkDir.clear();
			if (getPathTo(followCreature->getPosition(), listWalkDir, fpp)) {
				hasFollowPath = true;
				startAutoWalk(listWalkDir);
			} else {
				hasFollowPath = false;
			}
		}
	}

	onFollowCreatureComplete(followCreature);
}

bool Creature::setFollowCreature(Creature* creature)
{
	if (creature) {
		if (followCreature == creature) {
			return true;
		}

		const Position& creaturePos = creature->getPosition();
		if (creaturePos.z != getPosition().z || !canSee(creaturePos)) {
			followCreature = nullptr;
			return false;
		}

		if (!listWalkDir.empty()) {
			listWalkDir.clear();
			onWalkAborted();
		}

		hasFollowPath = false;
		forceUpdateFollowPath = false;
		followCreature = creature;
		isUpdatingPath = true;
	} else {
		isUpdatingPath = false;
		followCreature = nullptr;
	}

	onFollowCreature(creature);
	return true;
}

double Creature::getDamageRatio(Creature* attacker) const
{
	uint32_t totalDamage = 0;
	uint32_t attackerDamage = 0;

	for (const auto& it : damageMap) {
		const CountBlock_t& cb = it.second;
		totalDamage += cb.total;
		if (it.first == attacker->getID()) {
			attackerDamage += cb.total;
		}
	}

	if (totalDamage == 0) {
		return 0;
	}

	return (static_cast<double>(attackerDamage) / totalDamage);
}

uint64_t Creature::getGainedExperience(Creature* attacker) const
{
	return std::floor(getDamageRatio(attacker) * getLostExperience());
}

void Creature::addDamagePoints(Creature* attacker, int32_t damagePoints)
{
	if (damagePoints <= 0) {
		return;
	}

	uint32_t attackerId = attacker->id;

	if (attacker->isSummon()) { //pota		
		Creature* master = attacker->getMaster();
		if (Player* player = master->getPlayer()) {
			attackerId = player->id;
		}
	}

	auto it = damageMap.find(attackerId);
	if (it == damageMap.end()) {
		CountBlock_t cb;
		cb.ticks = OTSYS_TIME();
		cb.total = damagePoints;
		damageMap[attackerId] = cb;
	} else {
		it->second.total += damagePoints;
		it->second.ticks = OTSYS_TIME();
	}

	lastHitCreatureId = attackerId;
}

