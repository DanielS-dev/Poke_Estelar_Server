// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "events.hpp"
#include "../../core/tools/systemTools.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../items/item.hpp"
#include "../../entities/player.hpp"

#include <set>

bool Events::eventMonsterOnSpawn(Monster* monster, const Position& position, bool startup, bool artificial) //pota
{
	// Monster:onSpawn(position)
	if (info.monsterOnSpawn == -1) {
		return true;
	}
 
	if (!scriptInterface.reserveScriptEnv()) {
		std::cout << "[Error - Events::monsterOnSpawn] Call stack overflow" << std::endl;
		return false;
	}
 
	ScriptEnvironment* env = scriptInterface.getScriptEnv();
	env->setScriptId(info.monsterOnSpawn, &scriptInterface);
 
	lua_State* L = scriptInterface.getLuaState();
	scriptInterface.pushFunction(info.monsterOnSpawn);
 
	LuaScriptInterface::pushUserdata<Monster>(L, monster);
	LuaScriptInterface::setMetatable(L, -1, "Monster");
	LuaScriptInterface::pushPosition(L, position);
	LuaScriptInterface::pushBoolean(L, startup);
	LuaScriptInterface::pushBoolean(L, artificial);
 
	return scriptInterface.callFunction(4);
}

// Creature

