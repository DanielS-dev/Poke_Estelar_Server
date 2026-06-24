// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <bitset>

#include "../player.hpp"
#include "../../world/bed.hpp"
#include "../../game/chat/chat.hpp"
#include "../../game/combat/combat.hpp"
#include "../../config/configmanager.hpp"
#include "../../scripting/creatureevent/creatureevent.hpp"
#include "../../scripting/events/events.hpp"
#include "../../game/game.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../monster.hpp"
#include "../../game/movement/movement.hpp"
#include "../../core/scheduler.hpp"
#include "../../game/weapons/weapons.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/returnMessageTools.hpp"
#include "../../core/tools/stringsTools.hpp"

extern ConfigManager g_config;
extern Game g_game;
extern Chat* g_chat;
extern Vocations g_vocations;
extern MoveEvents* g_moveEvents;
extern Weapons* g_weapons;
extern CreatureEvents* g_creatureEvents;
extern Events* g_events;

void Player::death(Creature* lastHitCreature)
{
	loginPosition = town->getTemplePosition();

	if (skillLoss) {
		uint8_t unfairFightReduction = 100;
		bool lastHitPlayer = Player::lastHitIsPlayer(lastHitCreature);

		if (lastHitPlayer) {
			uint32_t sumLevels = 0;
			uint32_t inFightTicks = g_config.getNumber(ConfigManager::PZ_LOCKED);
			for (const auto& it : damageMap) {
				CountBlock_t cb = it.second;
				if ((OTSYS_TIME() - cb.ticks) <= inFightTicks) {
					Player* damageDealer = g_game.getPlayerByID(it.first);
					if (damageDealer) {
						sumLevels += damageDealer->getLevel();
					}
				}
			}

			if (sumLevels > level) {
				double reduce = level / static_cast<double>(sumLevels);
				unfairFightReduction = std::max<uint8_t>(20, std::floor((reduce * 100) + 0.5));
			}
		}

		//Magic level loss
		uint64_t sumMana = 0;
		uint64_t lostMana = 0;

		//sum up all the mana
		for (uint32_t i = 1; i <= magLevel; ++i) {
			sumMana += vocation->getReqMana(i);
		}

		sumMana += manaSpent;

		double deathLossPercent = getLostPercent() * (unfairFightReduction / 100.);

		lostMana = static_cast<uint64_t>(sumMana * deathLossPercent);

		while (lostMana > manaSpent && magLevel > 0) {
			lostMana -= manaSpent;
			manaSpent = vocation->getReqMana(magLevel);
			magLevel--;
		}

		manaSpent -= lostMana;

		uint64_t nextReqMana = vocation->getReqMana(magLevel + 1);
		if (nextReqMana > vocation->getReqMana(magLevel)) {
			magLevelPercent = Player::getPercentLevel(manaSpent, nextReqMana);
		} else {
			magLevelPercent = 0;
		}

		//Skill loss
		for (uint8_t i = SKILL_FIRST; i <= SKILL_LAST; ++i) { //for each skill
			uint64_t sumSkillTries = 0;
			for (uint16_t c = 11; c <= skills[i].level; ++c) { //sum up all required tries for all skill levels
				sumSkillTries += vocation->getReqSkillTries(i, c);
			}

			sumSkillTries += skills[i].tries;

			uint32_t lostSkillTries = static_cast<uint32_t>(sumSkillTries * deathLossPercent);
			while (lostSkillTries > skills[i].tries) {
				lostSkillTries -= skills[i].tries;

				if (skills[i].level <= 10) {
					skills[i].level = 10;
					skills[i].tries = 0;
					lostSkillTries = 0;
					break;
				}

				skills[i].tries = vocation->getReqSkillTries(i, skills[i].level);
				skills[i].level--;
			}

			skills[i].tries = std::max<int32_t>(0, skills[i].tries - lostSkillTries);
			skills[i].percent = Player::getPercentLevel(skills[i].tries, vocation->getReqSkillTries(i, skills[i].level));
		}

		//Level loss
		uint64_t expLoss = static_cast<uint64_t>(experience * deathLossPercent);
		g_events->eventPlayerOnLoseExperience(this, expLoss);

		if (expLoss != 0) {
			uint32_t oldLevel = level;

			if (vocation->getId() == VOCATION_NONE || level > 7) {
				experience -= expLoss;
			}

			while (level > 1 && experience < Player::getExpForLevel(level)) {
				--level;
				healthMax = std::max<int32_t>(0, healthMax - vocation->getHPGain());
				manaMax = std::max<int32_t>(0, manaMax - vocation->getManaGain());
				capacity = std::max<int32_t>(0, capacity - vocation->getCapGain());
			}

			if (oldLevel != level) {
				std::ostringstream ss;
				ss << "You were downgraded from Level " << oldLevel << " to Level " << level << '.';
				sendTextMessage(MESSAGE_EVENT_ADVANCE, ss.str());
			}

			uint64_t currLevelExp = Player::getExpForLevel(level);
			uint64_t nextLevelExp = Player::getExpForLevel(level + 1);
			if (nextLevelExp > currLevelExp) {
				levelPercent = Player::getPercentLevel(experience - currLevelExp, nextLevelExp - currLevelExp);
			} else {
				levelPercent = 0;
			}
		}

		std::bitset<6> bitset(blessings);
		if (bitset[5]) {
			if (lastHitPlayer) {
				bitset.reset(5);
				blessings = bitset.to_ulong();
			} else {
				blessings = 32;
			}
		} else {
			blessings = 0;
		}

		sendStats();
		sendSkills();
		sendReLoginWindow(unfairFightReduction);

		if (getSkull() == SKULL_BLACK) {
			health = 40;
			mana = 0;
		} else {
			health = healthMax;
			mana = manaMax;
		}

		auto it = conditions.begin(), end = conditions.end();
		while (it != end) {
			Condition* condition = *it;
			if (condition->isPersistent()) {
				it = conditions.erase(it);

				condition->endCondition(this);
				onEndCondition(condition->getType());
				delete condition;
			} else {
				++it;
			}
		}
	} else {
		setLossSkill(true);

		auto it = conditions.begin(), end = conditions.end();
		while (it != end) {
			Condition* condition = *it;
			if (condition->isPersistent()) {
				it = conditions.erase(it);

				condition->endCondition(this);
				onEndCondition(condition->getType());
				delete condition;
			} else {
				++it;
			}
		}

		health = healthMax;
		g_game.internalTeleport(this, getTemplePosition(), true);
		g_game.addCreatureHealth(this);
		onThink(EVENT_CREATURE_THINK_INTERVAL);
		onIdleStatus();
		sendStats();
	}
}


bool Player::dropCorpse(Creature* lastHitCreature, Creature* mostDamageCreature, bool lastHitUnjustified, bool mostDamageUnjustified)
{
	if (getZone() != ZONE_PVP || !Player::lastHitIsPlayer(lastHitCreature)) {
		return Creature::dropCorpse(lastHitCreature, mostDamageCreature, lastHitUnjustified, mostDamageUnjustified);
	}

	setDropLoot(true);
	return false;
}


Item* Player::getCorpse(Creature* lastHitCreature, Creature* mostDamageCreature)
{
	Item* corpse = Creature::getCorpse(lastHitCreature, mostDamageCreature);
	if (corpse && corpse->getContainer()) {
		std::ostringstream ss;
		if (lastHitCreature) {
			ss << "You recognize " << getNameDescription() << ". " << (getSex() == PLAYERSEX_FEMALE ? "She" : "He") << " was killed by " << lastHitCreature->getNameDescription() << '.';
		} else {
			ss << "You recognize " << getNameDescription() << '.';
		}

		corpse->setSpecialDescription(ss.str());
	}
	return corpse;
}


