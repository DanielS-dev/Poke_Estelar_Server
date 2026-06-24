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

bool Events::eventPlayerOnBrowseField(Player* player, const Position& position)
{
	// Player:onBrowseField(position) or Player.onBrowseField(self, position)
	if (info.playerOnBrowseField == -1) {
		return true;
	}

	if (!scriptInterface.reserveScriptEnv()) {
		std::cout << "[Error - Events::eventPlayerOnBrowseField] Call stack overflow" << std::endl;
		return false;
	}

	ScriptEnvironment* env = scriptInterface.getScriptEnv();
	env->setScriptId(info.playerOnBrowseField, &scriptInterface);

	lua_State* L = scriptInterface.getLuaState();
	scriptInterface.pushFunction(info.playerOnBrowseField);

	LuaScriptInterface::pushUserdata<Player>(L, player);
	LuaScriptInterface::setMetatable(L, -1, "Player");

	LuaScriptInterface::pushPosition(L, position);

	return scriptInterface.callFunction(2);
}

