// This file is part of The Forgotten Server.

// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <sstream>

#include "../game.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/monster.hpp"

#include "instantSpell.hpp"
#include "spells.hpp"

extern Game g_game;

std::string InstantSpell::getScriptEventName() const
{
	return "onCastSpell";
}

bool InstantSpell::configureEvent(const pugi::xml_node& node)
{
	if (!Spell::configureSpell(node)) {
		return false;
	}

	if (!TalkAction::configureEvent(node)) {
		return false;
	}

	pugi::xml_attribute attr;
	if ((attr = node.attribute("params"))) {
		hasParam = attr.as_bool();
	}

	if ((attr = node.attribute("playernameparam"))) {
		hasPlayerNameParam = attr.as_bool();
	}

	if ((attr = node.attribute("direction"))) {
		needDirection = attr.as_bool();
	} else if ((attr = node.attribute("casterTargetOrDirection"))) {
		casterTargetOrDirection = attr.as_bool();
	}

	if ((attr = node.attribute("blockwalls"))) {
		checkLineOfSight = attr.as_bool();
	}
	return true;
}

bool InstantSpell::loadFunction(const pugi::xml_attribute& attr)
{
	const char* functionName = attr.as_string();
	if (strcasecmp(functionName, "edithouseguest") == 0) {
		function = HouseGuestList;
	} else if (strcasecmp(functionName, "edithousesubowner") == 0) {
		function = HouseSubOwnerList;
	} else if (strcasecmp(functionName, "edithousedoor") == 0) {
		function = HouseDoorList;
	} else if (strcasecmp(functionName, "housekick") == 0) {
		function = HouseKick;
	} else if (strcasecmp(functionName, "searchplayer") == 0) {
		function = SearchPlayer;
	} else if (strcasecmp(functionName, "levitate") == 0) {
		function = Levitate;
	} else if (strcasecmp(functionName, "illusion") == 0) {
		function = Illusion;
	} else if (strcasecmp(functionName, "summonmonster") == 0) {
		function = SummonMonster;
	} else {
		std::cout << "[Warning - InstantSpell::loadFunction] Function \"" << functionName << "\" does not exist." << std::endl;
		return false;
	}

	scripted = false;
	return true;
}

bool InstantSpell::playerCastInstant(Player* player, std::string& param)
{
	if (!playerSpellCheck(player)) {
		return false;
	}

	LuaVariant var;

	if (selfTarget) {
		var.type = VARIANT_NUMBER;
		var.number = player->getID();
	} else if (needTarget || casterTargetOrDirection) {
		Creature* target = nullptr;
		bool useDirection = false;

		if (hasParam) {
			Player* playerTarget = nullptr;
			ReturnValue ret = g_game.getPlayerByNameWildcard(param, playerTarget);

			if (playerTarget && playerTarget->isAccessPlayer() && !player->isAccessPlayer()) {
				playerTarget = nullptr;
			}

			target = playerTarget;
			if (!target || target->getHealth() <= 0) {
				if (!casterTargetOrDirection) {
					if (cooldown > 0) {
						Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLCOOLDOWN, cooldown, 0, false, spellId);
						player->addCondition(condition);
					}

					if (groupCooldown > 0) {
						Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLGROUPCOOLDOWN, groupCooldown, 0, false, group);
						player->addCondition(condition);
					}

					if (secondaryGroupCooldown > 0) {
						Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLGROUPCOOLDOWN, secondaryGroupCooldown, 0, false, secondaryGroup);
						player->addCondition(condition);
					}

					player->sendCancelMessage(ret);
					g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
					return false;
				}

				useDirection = true;
			}

			if (playerTarget) {
				param = playerTarget->getName();
			}
		} else {
			target = player->getAttackedCreature();
			if (!target || target->getHealth() <= 0) {
				if (!casterTargetOrDirection) {
					player->sendCancelMessage(RETURNVALUE_YOUCANONLYUSEITONCREATURES);
					g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
					return false;
				}

				useDirection = true;
			}
		}

		if (!useDirection) {
			if (!canThrowSpell(player, target)) {
				player->sendCancelMessage(RETURNVALUE_CREATUREISNOTREACHABLE);
				g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
				return false;
			}

			var.type = VARIANT_NUMBER;
			var.number = target->getID();
		} else {
			var.type = VARIANT_POSITION;
			var.pos = Spells::getCasterPosition(player, player->getDirection());

			if (!playerInstantSpellCheck(player, var.pos)) {
				return false;
			}
		}
	} else if (hasParam) {
		var.type = VARIANT_STRING;

		if (getHasPlayerNameParam()) {
			Player* playerTarget = nullptr;
			ReturnValue ret = g_game.getPlayerByNameWildcard(param, playerTarget);

			if (ret != RETURNVALUE_NOERROR) {
				if (cooldown > 0) {
					Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLCOOLDOWN, cooldown, 0, false, spellId);
					player->addCondition(condition);
				}

				if (groupCooldown > 0) {
					Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLGROUPCOOLDOWN, groupCooldown, 0, false, group);
					player->addCondition(condition);
				}

				if (secondaryGroupCooldown > 0) {
					Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLGROUPCOOLDOWN, secondaryGroupCooldown, 0, false, secondaryGroup);
					player->addCondition(condition);
				}

				player->sendCancelMessage(ret);
				g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
				return false;
			}

			if (playerTarget && (!playerTarget->isAccessPlayer() || player->isAccessPlayer())) {
				param = playerTarget->getName();
			}
		}

		var.text = param;
	} else {
		var.type = VARIANT_POSITION;

		if (needDirection) {
			var.pos = Spells::getCasterPosition(player, player->getDirection());
		} else {
			var.pos = player->getPosition();
		}

		if (!playerInstantSpellCheck(player, var.pos)) {
			return false;
		}
	}

	bool result = internalCastSpell(player, var);
	if (result) {
		postCastSpell(player);
	}

	return result;
}

bool InstantSpell::canThrowSpell(const Creature* creature, const Creature* target) const
{
	const Position& fromPos = creature->getPosition();
	const Position& toPos = target->getPosition();
	if (fromPos.z != toPos.z ||
	        (range == -1 && !g_game.canThrowObjectTo(fromPos, toPos, checkLineOfSight)) ||
	        (range != -1 && !g_game.canThrowObjectTo(fromPos, toPos, checkLineOfSight, range, range))) {
		return false;
	}
	return true;
}

bool InstantSpell::castSpell(Creature* creature)
{
	LuaVariant var;

	if (casterTargetOrDirection) {
		Creature* target = creature->getAttackedCreature();
		if (target && target->getHealth() > 0) {
			if (!canThrowSpell(creature, target)) {
				return false;
			}

			var.type = VARIANT_NUMBER;
			var.number = target->getID();
			return internalCastSpell(creature, var);
		}

		return false;
	} else if (needDirection) {
		var.type = VARIANT_POSITION;
		var.pos = Spells::getCasterPosition(creature, creature->getDirection());
	} else {
		var.type = VARIANT_POSITION;
		var.pos = creature->getPosition();
	}

	return internalCastSpell(creature, var);
}

bool InstantSpell::castSpell(Creature* creature, Creature* target)
{
	if (needTarget) {
		LuaVariant var;
		var.type = VARIANT_NUMBER;
		var.number = target->getID();
		return internalCastSpell(creature, var);
	} else {
		return castSpell(creature);
	}
}

bool InstantSpell::internalCastSpell(Creature* creature, const LuaVariant& var)
{
	if (scripted) {
		return executeCastSpell(creature, var);
	} else if (function) {
		return function(this, creature, var.text);
	}

	return false;
}

bool InstantSpell::executeCastSpell(Creature* creature, const LuaVariant& var)
{
	//onCastSpell(creature, var)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - InstantSpell::executeCastSpell] Call stack overflow" << std::endl;
		return false;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(scriptId, scriptInterface);

	lua_State* L = scriptInterface->getLuaState();

	scriptInterface->pushFunction(scriptId);

	LuaScriptInterface::pushUserdata<Creature>(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);

	LuaScriptInterface::pushVariant(L, var);

	return scriptInterface->callFunction(2);
}

bool InstantSpell::canCast(const Player* player) const
{
	if (player->hasFlag(PlayerFlag_CannotUseSpells)) {
		return false;
	}

	if (player->hasFlag(PlayerFlag_IgnoreSpellCheck)) {
		return true;
	}

	if (isLearnable()) {
		if (player->hasLearnedInstantSpell(getName())) {
			return true;
		}
	} else {
		if (vocSpellMap.empty() || vocSpellMap.find(player->getVocationId()) != vocSpellMap.end()) {
			return true;
		}
	}

	return false;
}
