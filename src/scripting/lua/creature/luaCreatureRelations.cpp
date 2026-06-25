// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"
#include "../../../game/game.hpp"

extern Game g_game;

int LuaScriptInterface::luaCreatureGetTarget(lua_State* L)
{
	// creature:getTarget()
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	Creature* target = creature->getAttackedCreature();
	if (target) {
		pushUserdata<Creature>(L, target);
		setCreatureMetatable(L, -1, target);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureSetTarget(lua_State* L)
{
	// creature:setTarget(target)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (creature) {
		Creature* target = getCreature(L, 2);
		pushBoolean(L, creature->setAttackedCreature(target));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureGetFollowCreature(lua_State* L)
{
	// creature:getFollowCreature()
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	Creature* followCreature = creature->getFollowCreature();
	if (followCreature) {
		pushUserdata<Creature>(L, followCreature);
		setCreatureMetatable(L, -1, followCreature);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureSetFollowCreature(lua_State* L)
{
	// creature:setFollowCreature(followedCreature)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (creature) {
		Creature* followCreature = getCreature(L, 2);
		pushBoolean(L, creature->setFollowCreature(followCreature));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureGetMaster(lua_State* L)
{
	// creature:getMaster()
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	Creature* master = creature->getMaster();
	if (!master) {
		lua_pushnil(L);
		return 1;
	}

	pushUserdata<Creature>(L, master);
	setCreatureMetatable(L, -1, master);
	return 1;
}

int LuaScriptInterface::luaCreatureSetMaster(lua_State* L)
{
	// creature:setMaster(master)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	Creature* master = getCreature(L, 2);
	if (master) {
		pushBoolean(L, creature->convinceCreature(master));
	} else {
		master = creature->getMaster();
		if (master) {
			master->removeSummon(creature);
			creature->incrementReferenceCounter();
			creature->setDropLoot(true);
		}
		pushBoolean(L, true);
	}
	g_game.updateCreatureType(creature);
	return 1;
}

