// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../npc.hpp"

#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern LuaEnvironment g_luaEnvironment;

int NpcScriptInterface::luaActionSay(lua_State* L)
{
	//selfSay(words[, target])
	Npc* npc = getScriptEnv()->getNpc();
	if (!npc) {
		return 0;
	}

	const std::string& text = getString(L, 1);
	if (lua_gettop(L) >= 2) {
		Player* target = getPlayer(L, 2);
		if (target) {
			npc->doSayToPlayer(target, text);
			return 0;
		}
	}

	npc->doSay(text);
	return 0;
}

int NpcScriptInterface::luaActionMove(lua_State* L)
{
	//selfMove(direction)
	Npc* npc = getScriptEnv()->getNpc();
	if (npc) {
		g_game.internalMoveCreature(npc, getNumber<Direction>(L, 1));
	}
	return 0;
}

int NpcScriptInterface::luaActionMoveTo(lua_State* L)
{
	//selfMoveTo(x,y,z)
	Npc* npc = getScriptEnv()->getNpc();
	if (!npc) {
		return 0;
	}

	npc->doMoveTo(Position(
		getNumber<uint16_t>(L, 1),
		getNumber<uint16_t>(L, 2),
		getNumber<uint8_t>(L, 3)
	));
	return 0;
}

int NpcScriptInterface::luaActionTurn(lua_State* L)
{
	//selfTurn(direction)
	Npc* npc = getScriptEnv()->getNpc();
	if (npc) {
		g_game.internalCreatureTurn(npc, getNumber<Direction>(L, 1));
	}
	return 0;
}

int NpcScriptInterface::luaActionFollow(lua_State* L)
{
	//selfFollow(player)
	Npc* npc = getScriptEnv()->getNpc();
	if (!npc) {
		pushBoolean(L, false);
		return 1;
	}

	pushBoolean(L, npc->setFollowCreature(getPlayer(L, 1)));
	return 1;
}

int NpcScriptInterface::luagetDistanceTo(lua_State* L)
{
	//getDistanceTo(uid)
	ScriptEnvironment* env = getScriptEnv();

	Npc* npc = env->getNpc();
	if (!npc) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_THING_NOT_FOUND));
		lua_pushnil(L);
		return 1;
	}

	uint32_t uid = getNumber<uint32_t>(L, -1);

	Thing* thing = env->getThingByUID(uid);
	if (!thing) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_THING_NOT_FOUND));
		lua_pushnil(L);
		return 1;
	}

	const Position& thingPos = thing->getPosition();
	const Position& npcPos = npc->getPosition();
	if (npcPos.z != thingPos.z) {
		lua_pushnumber(L, -1);
	} else {
		int32_t dist = std::max<int32_t>(Position::getDistanceX(npcPos, thingPos), Position::getDistanceY(npcPos, thingPos));
		lua_pushnumber(L, dist);
	}
	return 1;
}

int NpcScriptInterface::luaSetNpcFocus(lua_State* L)
{
	//doNpcSetCreatureFocus(cid)
	Npc* npc = getScriptEnv()->getNpc();
	if (npc) {
		npc->setCreatureFocus(getCreature(L, -1));
	}
	return 0;
}

int NpcScriptInterface::luaGetNpcCid(lua_State* L)
{
	//getNpcCid()
	Npc* npc = getScriptEnv()->getNpc();
	if (npc) {
		lua_pushnumber(L, npc->getID());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int NpcScriptInterface::luaGetNpcParameter(lua_State* L)
{
	//getNpcParameter(paramKey)
	Npc* npc = getScriptEnv()->getNpc();
	if (!npc) {
		lua_pushnil(L);
		return 1;
	}

	std::string paramKey = getString(L, -1);

	auto it = npc->parameters.find(paramKey);
	if (it != npc->parameters.end()) {
		LuaScriptInterface::pushString(L, it->second);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

