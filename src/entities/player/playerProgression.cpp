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

void Player::addManaSpent(uint64_t amount)
{
	if (hasFlag(PlayerFlag_NotGainMana)) {
		return;
	}

	uint64_t currReqMana = vocation->getReqMana(magLevel);
	uint64_t nextReqMana = vocation->getReqMana(magLevel + 1);
	if (currReqMana >= nextReqMana) {
		//player has reached max magic level
		return;
	}

	g_events->eventPlayerOnGainSkillTries(this, SKILL_MAGLEVEL, amount);
	if (amount == 0) {
		return;
	}

	bool sendUpdateStats = false;
	while ((manaSpent + amount) >= nextReqMana) {
		amount -= nextReqMana - manaSpent;

		magLevel++;
		manaSpent = 0;

		std::ostringstream ss;
		ss << "You advanced to magic level " << magLevel << '.';
		sendTextMessage(MESSAGE_EVENT_ADVANCE, ss.str());

		g_creatureEvents->playerAdvance(this, SKILL_MAGLEVEL, magLevel - 1, magLevel);

		sendUpdateStats = true;
		currReqMana = nextReqMana;
		nextReqMana = vocation->getReqMana(magLevel + 1);
		if (currReqMana >= nextReqMana) {
			return;
		}
	}

	manaSpent += amount;

	uint8_t oldPercent = magLevelPercent;
	if (nextReqMana > currReqMana) {
		magLevelPercent = Player::getPercentLevel(manaSpent, nextReqMana);
	} else {
		magLevelPercent = 0;
	}

	if (oldPercent != magLevelPercent) {
		sendUpdateStats = true;
	}

	if (sendUpdateStats) {
		sendStats();
	}
}


void Player::addExperience(Creature* source, uint64_t exp, bool sendText/* = false*/)
{
	uint64_t currLevelExp = Player::getExpForLevel(level);
	uint64_t nextLevelExp = Player::getExpForLevel(level + 1);
	uint64_t rawExp = exp;
	if (currLevelExp >= nextLevelExp) {
		//player has reached max level
		levelPercent = 0;
		sendStats();
		return;
	}

	Monster* monster = source ? source->getMonster() : nullptr; //pota
	if (monster) {
		double factor = (g_config.getDouble(ConfigManager::MONSTERLEVEL_BONUSEXP) * monster->getLevel());
		exp += (exp * factor);
	}

	g_events->eventPlayerOnGainExperience(this, source, exp, rawExp);
	if (exp == 0) {
		return;
	}

	experience += exp;

	if (sendText) {
		std::string expString = std::to_string(exp) + (exp != 1 ? " experience points." : " experience point.");

		TextMessage message(MESSAGE_EXPERIENCE, "You gained " + expString);
		message.position = position;
		message.primary.value = exp;
		message.primary.color = TEXTCOLOR_WHITE_EXP;
		sendTextMessage(message);

		SpectatorVec list;
		g_game.map.getSpectators(list, position, false, true);
		list.erase(this);
		if (!list.empty()) {
			message.type = MESSAGE_EXPERIENCE_OTHERS;
			message.text = getName() + " gained " + expString;
			for (Creature* spectator : list) {
				spectator->getPlayer()->sendTextMessage(message);
			}
		}
	}

	uint32_t prevLevel = level;
	while (experience >= nextLevelExp) {
		++level;
		healthMax += vocation->getHPGain();
		health += vocation->getHPGain();
		manaMax += vocation->getManaGain();
		mana += vocation->getManaGain();
		capacity += vocation->getCapGain();

		currLevelExp = nextLevelExp;
		nextLevelExp = Player::getExpForLevel(level + 1);
		if (currLevelExp >= nextLevelExp) {
			//player has reached max level
			break;
		}
	}

	if (prevLevel != level) {
		health = healthMax;
		mana = manaMax;

		updateBaseSpeed();
		setBaseSpeed(getBaseSpeed());

		g_game.changeSpeed(this, 0);
		g_game.addCreatureHealth(this);

		if (party) {
			party->updateSharedExperience();
		}

		g_creatureEvents->playerAdvance(this, SKILL_LEVEL, prevLevel, level);

		std::ostringstream ss;
		ss << "You advanced from Level " << prevLevel << " to Level " << level << '.';
		sendTextMessage(MESSAGE_EVENT_ADVANCE, ss.str());
	}

	if (nextLevelExp > currLevelExp) {
		levelPercent = Player::getPercentLevel(experience - currLevelExp, nextLevelExp - currLevelExp);
	} else {
		levelPercent = 0;
	}
	sendStats();
}


void Player::removeExperience(uint64_t exp, bool sendText/* = false*/)
{
	if (experience == 0 || exp == 0) {
		return;
	}

	g_events->eventPlayerOnLoseExperience(this, exp);
	if (exp == 0) {
		return;
	}

	uint64_t lostExp = experience;
	experience = std::max<int64_t>(0, experience - exp);

	if (sendText) {
		lostExp -= experience;

		std::string expString = std::to_string(lostExp) + (lostExp != 1 ? " experience points." : " experience point.");

		TextMessage message(MESSAGE_EXPERIENCE, "You lost " + expString);
		message.position = position;
		message.primary.value = lostExp;
		message.primary.color = TEXTCOLOR_RED;
		sendTextMessage(message);

		SpectatorVec list;
		g_game.map.getSpectators(list, position, false, true);
		list.erase(this);
		if (!list.empty()) {
			message.type = MESSAGE_EXPERIENCE_OTHERS;
			message.text = getName() + " lost " + expString;
			for (Creature* spectator : list) {
				spectator->getPlayer()->sendTextMessage(message);
			}
		}
	}

	uint32_t oldLevel = level;
	uint64_t currLevelExp = Player::getExpForLevel(level);

	while (level > 1 && experience < currLevelExp) {
		--level;
		healthMax = std::max<int32_t>(0, healthMax - vocation->getHPGain());
		manaMax = std::max<int32_t>(0, manaMax - vocation->getManaGain());
		capacity = std::max<int32_t>(0, capacity - vocation->getCapGain());
		currLevelExp = Player::getExpForLevel(level);
	}

	if (oldLevel != level) {
		health = healthMax;
		mana = manaMax;

		updateBaseSpeed();
		setBaseSpeed(getBaseSpeed());

		g_game.changeSpeed(this, 0);
		g_game.addCreatureHealth(this);

		if (party) {
			party->updateSharedExperience();
		}

		std::ostringstream ss;
		ss << "You were downgraded from Level " << oldLevel << " to Level " << level << '.';
		sendTextMessage(MESSAGE_EVENT_ADVANCE, ss.str());
	}

	uint64_t nextLevelExp = Player::getExpForLevel(level + 1);
	if (nextLevelExp > currLevelExp) {
		levelPercent = Player::getPercentLevel(experience - currLevelExp, nextLevelExp - currLevelExp);
	} else {
		levelPercent = 0;
	}
	sendStats();
}

uint8_t Player::getPercentLevel(uint64_t count, uint64_t nextLevelCount)
{
	if (nextLevelCount == 0) {
		return 0;
	}

	uint8_t result = (count * 100) / nextLevelCount;
	if (result > 100) {
		return 0;
	}
	return result;
}


bool Player::addOfflineTrainingTries(skills_t skill, uint64_t tries)
{
	if (tries == 0 || skill == SKILL_LEVEL) {
		return false;
	}

	bool sendUpdate = false;
	uint32_t oldSkillValue, newSkillValue;
	long double oldPercentToNextLevel, newPercentToNextLevel;

	if (skill == SKILL_MAGLEVEL) {
		uint64_t currReqMana = vocation->getReqMana(magLevel);
		uint64_t nextReqMana = vocation->getReqMana(magLevel + 1);

		if (currReqMana >= nextReqMana) {
			return false;
		}

		oldSkillValue = magLevel;
		oldPercentToNextLevel = static_cast<long double>(manaSpent * 100) / nextReqMana;

		g_events->eventPlayerOnGainSkillTries(this, SKILL_MAGLEVEL, tries);
		uint32_t currMagLevel = magLevel;

		while ((manaSpent + tries) >= nextReqMana) {
			tries -= nextReqMana - manaSpent;

			magLevel++;
			manaSpent = 0;

			g_creatureEvents->playerAdvance(this, SKILL_MAGLEVEL, magLevel - 1, magLevel);

			sendUpdate = true;
			currReqMana = nextReqMana;
			nextReqMana = vocation->getReqMana(magLevel + 1);

			if (currReqMana >= nextReqMana) {
				tries = 0;
				break;
			}
		}

		manaSpent += tries;

		if (magLevel != currMagLevel) {
			std::ostringstream ss;
			ss << "You advanced to magic level " << magLevel << '.';
			sendTextMessage(MESSAGE_EVENT_ADVANCE, ss.str());
		}

		uint8_t newPercent;
		if (nextReqMana > currReqMana) {
			newPercent = Player::getPercentLevel(manaSpent, nextReqMana);
			newPercentToNextLevel = static_cast<long double>(manaSpent * 100) / nextReqMana;
		} else {
			newPercent = 0;
			newPercentToNextLevel = 0;
		}

		if (newPercent != magLevelPercent) {
			magLevelPercent = newPercent;
			sendUpdate = true;
		}

		newSkillValue = magLevel;
	} else {
		uint64_t currReqTries = vocation->getReqSkillTries(skill, skills[skill].level);
		uint64_t nextReqTries = vocation->getReqSkillTries(skill, skills[skill].level + 1);
		if (currReqTries >= nextReqTries) {
			return false;
		}

		oldSkillValue = skills[skill].level;
		oldPercentToNextLevel = static_cast<long double>(skills[skill].tries * 100) / nextReqTries;

		g_events->eventPlayerOnGainSkillTries(this, skill, tries);
		uint32_t currSkillLevel = skills[skill].level;

		while ((skills[skill].tries + tries) >= nextReqTries) {
			tries -= nextReqTries - skills[skill].tries;

			skills[skill].level++;
			skills[skill].tries = 0;
			skills[skill].percent = 0;

			g_creatureEvents->playerAdvance(this, skill, (skills[skill].level - 1), skills[skill].level);

			sendUpdate = true;
			currReqTries = nextReqTries;
			nextReqTries = vocation->getReqSkillTries(skill, skills[skill].level + 1);

			if (currReqTries >= nextReqTries) {
				tries = 0;
				break;
			}
		}

		skills[skill].tries += tries;

		if (currSkillLevel != skills[skill].level) {
			std::ostringstream ss;
			ss << "You advanced to " << getSkillName(skill) << " level " << skills[skill].level << '.';
			sendTextMessage(MESSAGE_EVENT_ADVANCE, ss.str());
		}

		uint8_t newPercent;
		if (nextReqTries > currReqTries) {
			newPercent = Player::getPercentLevel(skills[skill].tries, nextReqTries);
			newPercentToNextLevel = static_cast<long double>(skills[skill].tries * 100) / nextReqTries;
		} else {
			newPercent = 0;
			newPercentToNextLevel = 0;
		}

		if (skills[skill].percent != newPercent) {
			skills[skill].percent = newPercent;
			sendUpdate = true;
		}

		newSkillValue = skills[skill].level;
	}

	if (sendUpdate) {
		sendSkills();
	}

	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << "Your " << ucwords(getSkillName(skill)) << " skill changed from level " << oldSkillValue << " (with " << oldPercentToNextLevel << "% progress towards level " << (oldSkillValue + 1) << ") to level " << newSkillValue << " (with " << newPercentToNextLevel << "% progress towards level " << (newSkillValue + 1) << ')';
	sendTextMessage(MESSAGE_EVENT_ADVANCE, ss.str());
	return sendUpdate;
}


