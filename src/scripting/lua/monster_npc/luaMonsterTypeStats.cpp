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

int LuaScriptInterface::luaMonsterTypeGetMaxSummons(lua_State* L)
{
	// monsterType:getMaxSummons()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.maxSummons);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetArmor(lua_State* L)
{
	// monsterType:getArmor()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.armor);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetDefense(lua_State* L)
{
	// monsterType:getDefense()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.defense);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetOutfit(lua_State* L)
{
	// monsterType:getOutfit()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushOutfit(L, monsterType->info.outfit);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetRace(lua_State* L)
{
	// monsterType:getRace()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.race);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetRace2(lua_State* L) //pota
{
	// monsterType:getRace2()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.race2);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetMinLevel(lua_State* L) //pota
{
	// monsterType:getMinLevel()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.minLevel);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetMaxLevel(lua_State* L) //pota
{
	// monsterType:getMaxLevel()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.maxLevel);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetCorpseId(lua_State* L)
{
	// monsterType:getCorpseId()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.lookcorpse);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetManaCost(lua_State* L)
{
	// monsterType:getManaCost()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.manaCost);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetBaseSpeed(lua_State* L)
{
	// monsterType:getBaseSpeed()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.baseSpeed);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetLight(lua_State* L)
{
	// monsterType:getLight()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (!monsterType) {
		lua_pushnil(L);
		return 1;
	}

	lua_pushnumber(L, monsterType->info.light.level);
	lua_pushnumber(L, monsterType->info.light.color);
	return 2;
}


int LuaScriptInterface::luaMonsterTypeGetStaticAttackChance(lua_State* L)
{
	// monsterType:getStaticAttackChance()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.staticAttackChance);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetTargetDistance(lua_State* L)
{
	// monsterType:getTargetDistance()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.targetDistance);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetYellChance(lua_State* L)
{
	// monsterType:getYellChance()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.yellChance);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetYellSpeedTicks(lua_State* L)
{
	// monsterType:getYellSpeedTicks()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.yellSpeedTicks);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetChangeTargetChance(lua_State* L)
{
	// monsterType:getChangeTargetChance()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.changeTargetChance);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetChangeTargetSpeed(lua_State* L)
{
	// monsterType:getChangeTargetSpeed()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.changeTargetSpeed);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

// Party


