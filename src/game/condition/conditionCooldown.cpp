// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "condition.hpp"
#include "../game.hpp"
#include "../../core/tools/random.hpp"

extern Game g_game;
void ConditionSpellCooldown::addCondition(Creature* creature, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());

		if (subId != 0 && ticks > 0) {
			Player* player = creature->getPlayer();
			if (player) {
				player->sendSpellCooldown(subId, ticks);
			}
		}
	}
}

bool ConditionSpellCooldown::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	if (subId != 0 && ticks > 0) {
		Player* player = creature->getPlayer();
		if (player) {
			player->sendSpellCooldown(subId, ticks);
		}
	}
	return true;
}

void ConditionStatus::addCondition(Creature* creature, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());

	}
}

bool ConditionStatus::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	return true;
}

void ConditionSpellGroupCooldown::addCondition(Creature* creature, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());

		if (subId != 0 && ticks > 0) {
			Player* player = creature->getPlayer();
			if (player) {
				player->sendSpellGroupCooldown(static_cast<SpellGroup_t>(subId), ticks);
			}
		}
	}
}

bool ConditionSpellGroupCooldown::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	if (subId != 0 && ticks > 0) {
		Player* player = creature->getPlayer();
		if (player) {
			player->sendSpellGroupCooldown(static_cast<SpellGroup_t>(subId), ticks);
		}
	}
	return true;
}
