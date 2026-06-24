// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "creatureevent.hpp"
#include "../../core/tools/systemTools.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/player.hpp"

void CreatureEvent::executeHealthChange(Creature* creature, Creature* attacker, CombatDamage& damage)
{
	//onHealthChange(creature, attacker, primaryDamage, primaryType, secondaryDamage, secondaryType, origin)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - CreatureEvent::executeHealthChange] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(scriptId, scriptInterface);

	lua_State* L = scriptInterface->getLuaState();
	scriptInterface->pushFunction(scriptId);

	LuaScriptInterface::pushUserdata(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	if (attacker) {
		LuaScriptInterface::pushUserdata(L, attacker);
		LuaScriptInterface::setCreatureMetatable(L, -1, attacker);
	} else {
		lua_pushnil(L);
	}

	lua_pushnumber(L, damage.primary.value);
	lua_pushnumber(L, damage.primary.type);
	lua_pushnumber(L, damage.secondary.value);
	lua_pushnumber(L, damage.secondary.type);
	lua_pushnumber(L, damage.origin);

	if (scriptInterface->protectedCall(L, 7, 4) != 0) {
		LuaScriptInterface::reportError(nullptr, LuaScriptInterface::popString(L));
	} else {
		damage.primary.value = std::abs(LuaScriptInterface::getNumber<int32_t>(L, -4));
		damage.primary.type = LuaScriptInterface::getNumber<CombatType_t>(L, -3);
		damage.secondary.value = std::abs(LuaScriptInterface::getNumber<int32_t>(L, -2));
		damage.secondary.type = LuaScriptInterface::getNumber<CombatType_t>(L, -1);

		lua_pop(L, 4);
		if (damage.primary.type != COMBAT_HEALING) {
			damage.primary.value = -damage.primary.value;
			damage.secondary.value = -damage.secondary.value;
		}
	}

	scriptInterface->resetScriptEnv();
}

void CreatureEvent::executeManaChange(Creature* creature, Creature* attacker, int32_t& manaChange, CombatOrigin origin)
{
	//onManaChange(creature, attacker, manaChange, origin)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - CreatureEvent::executeManaChange] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(scriptId, scriptInterface);

	lua_State* L = scriptInterface->getLuaState();
	scriptInterface->pushFunction(scriptId);

	LuaScriptInterface::pushUserdata(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	if (attacker) {
		LuaScriptInterface::pushUserdata(L, attacker);
		LuaScriptInterface::setCreatureMetatable(L, -1, attacker);
	} else {
		lua_pushnil(L);
	}

	lua_pushnumber(L, manaChange);
	lua_pushnumber(L, origin);

	if (scriptInterface->protectedCall(L, 4, 1) != 0) {
		LuaScriptInterface::reportError(nullptr, LuaScriptInterface::getString(L, -1));
	} else {
		manaChange = LuaScriptInterface::getNumber<int32_t>(L, -1);
	}
	lua_pop(L, 1);

	scriptInterface->resetScriptEnv();
}

