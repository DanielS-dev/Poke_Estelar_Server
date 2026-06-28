// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../npc.hpp"

#include "../../core/logger.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern LuaEnvironment g_luaEnvironment;

NpcScriptInterface::NpcScriptInterface() :
	LuaScriptInterface("Npc interface")
{
	libLoaded = false;
	initState();
}

bool NpcScriptInterface::initState()
{
	luaState = g_luaEnvironment.getLuaState();
	if (!luaState) {
		return false;
	}

	registerFunctions();

	lua_newtable(luaState);
	eventTableRef = luaL_ref(luaState, LUA_REGISTRYINDEX);
	runningEventId = EVENT_ID_USER;
	return true;
}

bool NpcScriptInterface::closeState()
{
	libLoaded = false;
	LuaScriptInterface::closeState();
	return true;
}

bool NpcScriptInterface::loadNpcLib(const std::string& file)
{
	if (libLoaded) {
		return true;
	}

	if (loadFile(file) == -1) {
		LOG_WARN("Scripts", "Could not load NPC lib " + file);
		return false;
	}

	libLoaded = true;
	return true;
}

void NpcScriptInterface::registerFunctions()
{
	//npc exclusive functions
	lua_register(luaState, "selfSay", NpcScriptInterface::luaActionSay);
	lua_register(luaState, "selfMove", NpcScriptInterface::luaActionMove);
	lua_register(luaState, "selfMoveTo", NpcScriptInterface::luaActionMoveTo);
	lua_register(luaState, "selfTurn", NpcScriptInterface::luaActionTurn);
	lua_register(luaState, "selfFollow", NpcScriptInterface::luaActionFollow);
	lua_register(luaState, "getDistanceTo", NpcScriptInterface::luagetDistanceTo);
	lua_register(luaState, "doNpcSetCreatureFocus", NpcScriptInterface::luaSetNpcFocus);
	lua_register(luaState, "getNpcCid", NpcScriptInterface::luaGetNpcCid);
	lua_register(luaState, "getNpcParameter", NpcScriptInterface::luaGetNpcParameter);
	lua_register(luaState, "openShopWindow", NpcScriptInterface::luaOpenShopWindow);
	lua_register(luaState, "closeShopWindow", NpcScriptInterface::luaCloseShopWindow);
	lua_register(luaState, "doSellItem", NpcScriptInterface::luaDoSellItem);

	// metatable
	registerMethod("Npc", "getParameter", NpcScriptInterface::luaNpcGetParameter);
	registerMethod("Npc", "setFocus", NpcScriptInterface::luaNpcSetFocus);

	registerMethod("Npc", "openShopWindow", NpcScriptInterface::luaNpcOpenShopWindow);
	registerMethod("Npc", "closeShopWindow", NpcScriptInterface::luaNpcCloseShopWindow);
}

