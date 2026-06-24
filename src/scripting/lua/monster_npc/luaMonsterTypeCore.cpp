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

int LuaScriptInterface::luaMonsterTypeCreate(lua_State* L)
{
	// MonsterType(name)
	MonsterType* monsterType = g_monsters.getMonsterType(getString(L, 2));
	if (monsterType) {
		pushUserdata<MonsterType>(L, monsterType);
		setMetatable(L, -1, "MonsterType");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsAttackable(lua_State* L)
{
	// monsterType:isAttackable()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.isAttackable);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsConvinceable(lua_State* L)
{
	// monsterType:isConvinceable()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.isConvinceable);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsSummonable(lua_State* L)
{
	// monsterType:isSummonable()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.isSummonable);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsIllusionable(lua_State* L)
{
	// monsterType:isIllusionable()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.isIllusionable);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsHostile(lua_State* L)
{
	// monsterType:isHostile()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.isHostile);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsPassive(lua_State* L) //pota
{
	// monsterType:isPassive()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.isPassive);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsFlyable(lua_State* L) //pota
{
	// monsterType:isFlyable()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.isFlyable);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsRideable(lua_State* L)
{
	// monsterType:isRideable()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.isRideable);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsSurfable(lua_State* L)
{
	// monsterType:isSurfable()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.isSurfable);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeCanTeleport(lua_State* L)
{
	// monsterType:canTeleport()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.canTeleport);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeCatchChance(lua_State* L)
{
	// monsterType:catchChance()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.catchChance);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetMoveMagicAttackBase(lua_State* L)
{
	// monsterType:getMoveMagicAttackBase()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.moveMagicAttackBase);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetMoveMagicDefenseBase(lua_State* L) //pota
{
	// monsterType:getMoveMagicDefenseBase()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.moveMagicDefenseBase);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeHasShiny(lua_State* L)
{
	// monsterType:hasShiny()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.hasShiny);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeHasMega(lua_State* L)
{
	// monsterType:hasMega()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.hasMega);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeDexEntry(lua_State* L)
{
	// monsterType:dexEntry()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.dexEntry);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypePortraitId(lua_State* L)
{
	// monsterType:portraitId()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.portraitId);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsPushable(lua_State* L)
{
	// monsterType:isPushable()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.pushable);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeIsHealthShown(lua_State* L)
{
	// monsterType:isHealthShown()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, !monsterType->info.hiddenHealth);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeCanPushItems(lua_State* L)
{
	// monsterType:canPushItems()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.canPushItems);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeCanPushCreatures(lua_State* L)
{
	// monsterType:canPushCreatures()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushBoolean(L, monsterType->info.canPushCreatures);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetName(lua_State* L)
{
	// monsterType:getName()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushString(L, monsterType->name);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetNameDescription(lua_State* L)
{
	// monsterType:getNameDescription()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		pushString(L, monsterType->nameDescription);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetHealth(lua_State* L)
{
	// monsterType:getHealth()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.health);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetMaxHealth(lua_State* L)
{
	// monsterType:getMaxHealth()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.healthMax);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetRunHealth(lua_State* L)
{
	// monsterType:getRunHealth()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.runAwayHealth);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterTypeGetExperience(lua_State* L)
{
	// monsterType:getExperience()
	MonsterType* monsterType = getUserdata<MonsterType>(L, 1);
	if (monsterType) {
		lua_pushnumber(L, monsterType->info.experience);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


