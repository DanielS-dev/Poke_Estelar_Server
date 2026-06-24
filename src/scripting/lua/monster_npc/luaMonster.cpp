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

int LuaScriptInterface::luaMonsterGetExperience(lua_State* L) //pota
{
	// monster:getExperience()
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		lua_pushnumber(L, monster->getExperience());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterSetExperience(lua_State* L) //pota
{
	// monster:setExperience(experience)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		monster->setExperience(getNumber<uint64_t>(L, 2));
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterGetLevel(lua_State* L) //pota
{
	// monster:getMonsterLevel()
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		lua_pushnumber(L, monster->getLevel());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterGetBoost(lua_State* L) //pota
{
	// monster:getMonsterLevel()
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		lua_pushnumber(L, monster->getBoost());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterCreate(lua_State* L)
{
	// Monster(id or userdata)
	Monster* monster;
	if (isNumber(L, 2)) {
		monster = g_game.getMonsterByID(getNumber<uint32_t>(L, 2));
	} else if (isUserdata(L, 2)) {
		if (getUserdataType(L, 2) != LuaData_Monster) {
			lua_pushnil(L);
			return 1;
		}
		monster = getUserdata<Monster>(L, 2);
	} else {
		monster = nullptr;
	}

	if (monster) {
		pushUserdata<Monster>(L, monster);
		setMetatable(L, -1, "Monster");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterIsMonster(lua_State* L)
{
	// monster:isMonster()
	pushBoolean(L, getUserdata<const Monster>(L, 1) != nullptr);
	return 1;
}


int LuaScriptInterface::luaMonsterGetType(lua_State* L)
{
	// monster:getType()
	const Monster* monster = getUserdata<const Monster>(L, 1);
	if (monster) {
		pushUserdata<MonsterType>(L, monster->mType);
		setMetatable(L, -1, "MonsterType");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterGetSpawnPosition(lua_State* L)
{
	// monster:getSpawnPosition()
	const Monster* monster = getUserdata<const Monster>(L, 1);
	if (monster) {
		pushPosition(L, monster->getMasterPos());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterIsInSpawnRange(lua_State* L)
{
	// monster:isInSpawnRange([position])
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		pushBoolean(L, monster->isInSpawnRange(lua_gettop(L) >= 2 ? getPosition(L, 2) : monster->getPosition()));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterIsIdle(lua_State* L)
{
	// monster:isIdle()
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		pushBoolean(L, monster->getIdleStatus());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterSetIdle(lua_State* L)
{
	// monster:setIdle(idle)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (!monster) {
		lua_pushnil(L);
		return 1;
	}

	monster->setIdle(getBoolean(L, 2));
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaMonsterIsTarget(lua_State* L)
{
	// monster:isTarget(creature)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		const Creature* creature = getCreature(L, 2);
		pushBoolean(L, monster->isTarget(creature));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterIsOpponent(lua_State* L)
{
	// monster:isOpponent(creature)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		const Creature* creature = getCreature(L, 2);
		pushBoolean(L, monster->isOpponent(creature));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterIsFriend(lua_State* L)
{
	// monster:isFriend(creature)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		const Creature* creature = getCreature(L, 2);
		pushBoolean(L, monster->isFriend(creature));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterAddFriend(lua_State* L)
{
	// monster:addFriend(creature)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		Creature* creature = getCreature(L, 2);
		monster->addFriend(creature);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterRemoveFriend(lua_State* L)
{
	// monster:removeFriend(creature)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		Creature* creature = getCreature(L, 2);
		monster->removeFriend(creature);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterGetFriendList(lua_State* L)
{
	// monster:getFriendList()
	Monster* monster = getUserdata<Monster>(L, 1);
	if (!monster) {
		lua_pushnil(L);
		return 1;
	}

	const auto& friendList = monster->getFriendList();
	lua_createtable(L, friendList.size(), 0);

	int index = 0;
	for (Creature* creature : friendList) {
		pushUserdata<Creature>(L, creature);
		setCreatureMetatable(L, -1, creature);
		lua_rawseti(L, -2, ++index);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterGetFriendCount(lua_State* L)
{
	// monster:getFriendCount()
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		lua_pushnumber(L, monster->getFriendList().size());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterAddTarget(lua_State* L)
{
	// monster:addTarget(creature[, pushFront = false])
	Monster* monster = getUserdata<Monster>(L, 1);
	if (!monster) {
		lua_pushnil(L);
		return 1;
	}

	Creature* creature = getCreature(L, 2);
	bool pushFront = getBoolean(L, 3, false);
	monster->addTarget(creature, pushFront);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaMonsterRemoveTarget(lua_State* L)
{
	// monster:removeTarget(creature)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (!monster) {
		lua_pushnil(L);
		return 1;
	}

	monster->removeTarget(getCreature(L, 2));
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaMonsterGetTargetList(lua_State* L)
{
	// monster:getTargetList()
	Monster* monster = getUserdata<Monster>(L, 1);
	if (!monster) {
		lua_pushnil(L);
		return 1;
	}

	const auto& targetList = monster->getTargetList();
	lua_createtable(L, targetList.size(), 0);

	int index = 0;
	for (Creature* creature : targetList) {
		pushUserdata<Creature>(L, creature);
		setCreatureMetatable(L, -1, creature);
		lua_rawseti(L, -2, ++index);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterGetTargetCount(lua_State* L)
{
	// monster:getTargetCount()
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		lua_pushnumber(L, monster->getTargetList().size());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterSelectTarget(lua_State* L)
{
	// monster:selectTarget(creature)
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		Creature* creature = getCreature(L, 2);
		pushBoolean(L, monster->selectTarget(creature));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaMonsterSearchTarget(lua_State* L)
{
	// monster:searchTarget([searchType = TARGETSEARCH_DEFAULT])
	Monster* monster = getUserdata<Monster>(L, 1);
	if (monster) {
		TargetSearchType_t searchType = getNumber<TargetSearchType_t>(L, 2, TARGETSEARCH_DEFAULT);
		pushBoolean(L, monster->searchTarget(searchType));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

// Npc


