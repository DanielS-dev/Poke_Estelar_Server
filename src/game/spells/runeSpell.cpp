// This file is part of The Forgotten Server.

// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../game.hpp"
#include "../../config/configmanager.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/monster.hpp"
#include "../../items/items.hpp"

#include "runeSpell.hpp"

extern Game g_game;
extern ConfigManager g_config;
std::string RuneSpell::getScriptEventName() const
{
	return "onCastSpell";
}

bool RuneSpell::configureEvent(const pugi::xml_node& node)
{
	if (!Spell::configureSpell(node)) {
		return false;
	}

	if (!Action::configureEvent(node)) {
		return false;
	}

	pugi::xml_attribute attr;
	if (!(attr = node.attribute("id"))) {
		std::cout << "[Error - RuneSpell::configureSpell] Rune spell without id." << std::endl;
		return false;
	}
	runeId = pugi::cast<uint16_t>(attr.value());

	uint32_t charges;
	if ((attr = node.attribute("charges"))) {
		charges = pugi::cast<uint32_t>(attr.value());
	} else {
		charges = 0;
	}

	hasCharges = (charges > 0);
	if (magLevel != 0 || level != 0) {
		//Change information in the ItemType to get accurate description
		ItemType& iType = Item::items.getItemType(runeId);
		iType.runeMagLevel = magLevel;
		iType.runeLevel = level;
		iType.charges = charges;
	}

	return true;
}

bool RuneSpell::loadFunction(const pugi::xml_attribute& attr)
{
	const char* functionName = attr.as_string();
	if (strcasecmp(functionName, "chameleon") == 0) {
		runeFunction = Illusion;
	} else if (strcasecmp(functionName, "convince") == 0) {
		runeFunction = Convince;
	} else {
		std::cout << "[Warning - RuneSpell::loadFunction] Function \"" << functionName << "\" does not exist." << std::endl;
		return false;
	}

	scripted = false;
	return true;
}

bool RuneSpell::Illusion(const RuneSpell*, Player* player, const Position& posTo)
{
	Thing* thing = g_game.internalGetThing(player, posTo, 0, 0, STACKPOS_MOVE);
	if (!thing) {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	Item* illusionItem = thing->getItem();
	if (!illusionItem || !illusionItem->isMoveable()) {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	ReturnValue ret = Spell::CreateIllusion(player, illusionItem->getID(), 200000);
	if (ret != RETURNVALUE_NOERROR) {
		player->sendCancelMessage(ret);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	g_game.addMagicEffect(player->getPosition(), CONST_ME_MAGIC_RED);
	return true;
}

bool RuneSpell::Convince(const RuneSpell* spell, Player* player, const Position& posTo)
{
	if (!player->hasFlag(PlayerFlag_CanConvinceAll)) {
		if (player->getSummonCount() >= 2) {
			player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
			g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
			return false;
		}
	}

	Thing* thing = g_game.internalGetThing(player, posTo, 0, 0, STACKPOS_LOOK);
	if (!thing) {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	Creature* convinceCreature = thing->getCreature();
	if (!convinceCreature) {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	uint32_t manaCost = 0;
	if (convinceCreature->getMonster()) {
		manaCost = convinceCreature->getMonster()->getManaCost();
	}

	if (!player->hasFlag(PlayerFlag_HasInfiniteMana) && player->getMana() < manaCost) {
		player->sendCancelMessage(RETURNVALUE_NOTENOUGHMANA);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	if (!convinceCreature->convinceCreature(player)) {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	Spell::postCastSpell(player, manaCost, spell->getSoulCost());
	g_game.updateCreatureType(convinceCreature);
	g_game.addMagicEffect(player->getPosition(), CONST_ME_MAGIC_RED);
	return true;
}

ReturnValue RuneSpell::canExecuteAction(const Player* player, const Position& toPos)
{
	if (player->hasFlag(PlayerFlag_CannotUseSpells)) {
		return RETURNVALUE_CANNOTUSETHISOBJECT;
	}

	ReturnValue ret = Action::canExecuteAction(player, toPos);
	if (ret != RETURNVALUE_NOERROR) {
		return ret;
	}

	if (toPos.x == 0xFFFF) {
		if (needTarget) {
			return RETURNVALUE_CANONLYUSETHISRUNEONCREATURES;
		} else if (!selfTarget) {
			return RETURNVALUE_NOTENOUGHROOM;
		}
	}

	return RETURNVALUE_NOERROR;
}

bool RuneSpell::executeUse(Player* player, Item* item, const Position&, Thing* target, const Position& toPosition, bool isHotkey)
{
	if (!playerRuneSpellCheck(player, toPosition)) {
		return false;
	}

	bool result = false;
	if (scripted) {
		LuaVariant var;

		if (needTarget) {
			var.type = VARIANT_NUMBER;

			if (target == nullptr) {
				Tile* toTile = g_game.map.getTile(toPosition);
				if (toTile) {
					const Creature* visibleCreature = toTile->getBottomVisibleCreature(player);
					if (visibleCreature) {
						var.number = visibleCreature->getID();
					}
				}
			} else {
				var.number = target->getCreature()->getID();
			}
		} else {
			var.type = VARIANT_POSITION;
			var.pos = toPosition;
		}

		result = internalCastSpell(player, var, isHotkey);
	} else if (runeFunction) {
		result = runeFunction(this, player, toPosition);
	}

	if (!result) {
		return false;
	}

	postCastSpell(player);
	if (hasCharges && item && g_config.getBoolean(ConfigManager::REMOVE_RUNE_CHARGES)) {
		int32_t newCount = std::max<int32_t>(0, item->getItemCount() - 1);
		g_game.transformItem(item, item->getID(), newCount);
	}
	return true;
}

bool RuneSpell::castSpell(Creature* creature)
{
	LuaVariant var;
	var.type = VARIANT_NUMBER;
	var.number = creature->getID();
	return internalCastSpell(creature, var, false);
}

bool RuneSpell::castSpell(Creature* creature, Creature* target)
{
	LuaVariant var;
	var.type = VARIANT_NUMBER;
	var.number = target->getID();
	return internalCastSpell(creature, var, false);
}

bool RuneSpell::internalCastSpell(Creature* creature, const LuaVariant& var, bool isHotkey)
{
	bool result;
	if (scripted) {
		result = executeCastSpell(creature, var, isHotkey);
	} else {
		result = false;
	}
	return result;
}

bool RuneSpell::executeCastSpell(Creature* creature, const LuaVariant& var, bool isHotkey)
{
	//onCastSpell(creature, var, isHotkey)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - RuneSpell::executeCastSpell] Call stack overflow" << std::endl;
		return false;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(scriptId, scriptInterface);

	lua_State* L = scriptInterface->getLuaState();

	scriptInterface->pushFunction(scriptId);

	LuaScriptInterface::pushUserdata<Creature>(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);

	LuaScriptInterface::pushVariant(L, var);

	LuaScriptInterface::pushBoolean(L, isHotkey);

	return scriptInterface->callFunction(3);
}
