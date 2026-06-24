// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <boost/range/adaptor/reversed.hpp>

#include "../luascript.hpp"
#include "../../events/events.hpp"
#include "../../../game/chat/chat.hpp"
#include "../../../entities/player.hpp"
#include "../../../game/game.hpp"
#include "../../../network/protocolstatus.hpp"
#include "../../../game/spells/spells.hpp"
#include "../../../persistence/login/iologindata.hpp"
#include "../../../config/configmanager.hpp"
#include "../../../world/teleport.hpp"
#include "../../../persistence/databasemanager.hpp"
#include "../../../world/bed.hpp"
#include "../../../entities/monster.hpp"
#include "../../../core/scheduler.hpp"
#include "../../../persistence/databasetasks.hpp"
#include "../../../core/tools/random.hpp"
#include "../../../core/tools/gameEnumTools.hpp"
#include "../../../core/tools/returnMessageTools.hpp"
#include "../../../core/tools/stringsTools.hpp"

extern Chat* g_chat;
extern Game g_game;
extern Monsters g_monsters;
extern ConfigManager g_config;
extern Vocations g_vocations;
extern Spells* g_spells;
extern Events* g_events;

int LuaScriptInterface::luaConditionCreate(lua_State* L)
{
	// Condition(conditionType[, conditionId = CONDITIONID_COMBAT])
	ConditionType_t conditionType = getNumber<ConditionType_t>(L, 2);
	ConditionId_t conditionId = getNumber<ConditionId_t>(L, 3, CONDITIONID_COMBAT);

	Condition* condition = Condition::createCondition(conditionId, conditionType, 0, 0);
	if (condition) {
		pushUserdata<Condition>(L, condition);
		setMetatable(L, -1, "Condition");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionDelete(lua_State* L)
{
	// condition:delete()
	Condition** conditionPtr = getRawUserdata<Condition>(L, 1);
	if (conditionPtr && *conditionPtr) {
		delete *conditionPtr;
		*conditionPtr = nullptr;
	}
	return 0;
}


int LuaScriptInterface::luaConditionGetId(lua_State* L)
{
	// condition:getId()
	Condition* condition = getUserdata<Condition>(L, 1);
	if (condition) {
		lua_pushnumber(L, condition->getId());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionGetSubId(lua_State* L)
{
	// condition:getSubId()
	Condition* condition = getUserdata<Condition>(L, 1);
	if (condition) {
		lua_pushnumber(L, condition->getSubId());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionGetType(lua_State* L)
{
	// condition:getType()
	Condition* condition = getUserdata<Condition>(L, 1);
	if (condition) {
		lua_pushnumber(L, condition->getType());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionGetIcons(lua_State* L)
{
	// condition:getIcons()
	Condition* condition = getUserdata<Condition>(L, 1);
	if (condition) {
		lua_pushnumber(L, condition->getIcons());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionGetEndTime(lua_State* L)
{
	// condition:getEndTime()
	Condition* condition = getUserdata<Condition>(L, 1);
	if (condition) {
		lua_pushnumber(L, condition->getEndTime());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionClone(lua_State* L)
{
	// condition:clone()
	Condition* condition = getUserdata<Condition>(L, 1);
	if (condition) {
		pushUserdata<Condition>(L, condition->clone());
		setMetatable(L, -1, "Condition");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionGetTicks(lua_State* L)
{
	// condition:getTicks()
	Condition* condition = getUserdata<Condition>(L, 1);
	if (condition) {
		lua_pushnumber(L, condition->getTicks());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionSetTicks(lua_State* L)
{
	// condition:setTicks(ticks)
	int32_t ticks = getNumber<int32_t>(L, 2);
	Condition* condition = getUserdata<Condition>(L, 1);
	if (condition) {
		condition->setTicks(ticks);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionSetParameter(lua_State* L)
{
	// condition:setParameter(key, value)
	Condition* condition = getUserdata<Condition>(L, 1);
	if (!condition) {
		lua_pushnil(L);
		return 1;
	}

	ConditionParam_t key = getNumber<ConditionParam_t>(L, 2);
	int32_t value;
	if (isBoolean(L, 3)) {
		value = getBoolean(L, 3) ? 1 : 0;
	} else {
		value = getNumber<int32_t>(L, 3);
	}
	condition->setParam(key, value);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaConditionSetFormula(lua_State* L)
{
	// condition:setFormula(mina, minb, maxa, maxb)
	double maxb = getNumber<double>(L, 5);
	double maxa = getNumber<double>(L, 4);
	double minb = getNumber<double>(L, 3);
	double mina = getNumber<double>(L, 2);
	ConditionSpeed* condition = dynamic_cast<ConditionSpeed*>(getUserdata<Condition>(L, 1));
	if (condition) {
		condition->setFormulaVars(mina, minb, maxa, maxb);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionSetOutfit(lua_State* L)
{
	// condition:setOutfit(outfit)
	// condition:setOutfit(lookTypeEx, lookType, lookHead, lookBody, lookLegs, lookFeet[, lookAddons[, lookMount]])
	Outfit_t outfit;
	if (isTable(L, 2)) {
		outfit = getOutfit(L, 2);
	} else {
		outfit.lookMount = getNumber<uint16_t>(L, 9, outfit.lookMount);
		outfit.lookAddons = getNumber<uint8_t>(L, 8, outfit.lookAddons);
		outfit.lookFeet = getNumber<uint8_t>(L, 7);
		outfit.lookLegs = getNumber<uint8_t>(L, 6);
		outfit.lookBody = getNumber<uint8_t>(L, 5);
		outfit.lookHead = getNumber<uint8_t>(L, 4);
		outfit.lookType = getNumber<uint16_t>(L, 3);
		outfit.lookTypeEx = getNumber<uint16_t>(L, 2);
	}

	ConditionOutfit* condition = dynamic_cast<ConditionOutfit*>(getUserdata<Condition>(L, 1));
	if (condition) {
		condition->setOutfit(outfit);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaConditionAddDamage(lua_State* L)
{
	// condition:addDamage(rounds, time, value)
	int32_t value = getNumber<int32_t>(L, 4);
	int32_t time = getNumber<int32_t>(L, 3);
	int32_t rounds = getNumber<int32_t>(L, 2);
	ConditionDamage* condition = dynamic_cast<ConditionDamage*>(getUserdata<Condition>(L, 1));
	if (condition) {
		pushBoolean(L, condition->addDamage(rounds, time, value));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

// MonsterType


int LuaScriptInterface::luaMonsterTypeGetCombatImmunities(lua_State* L)
{
	// monsterType:getCombatImmunities()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.damageImmunities);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetConditionImmunities(lua_State* L)
{
	// monsterType:getConditionImmunities()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.conditionImmunities);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


