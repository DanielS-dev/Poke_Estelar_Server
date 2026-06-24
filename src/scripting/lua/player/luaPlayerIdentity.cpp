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

int LuaScriptInterface::luaPlayerGetVocation(lua_State* L)
{
	// player:getVocation()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		pushUserdata<Vocation>(L, player->getVocation());
		setMetatable(L, -1, "Vocation");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetVocation(lua_State* L)
{
	// player:setVocation(id or name or userdata)
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	Vocation* vocation;
	if (isNumber(L, 2)) {
		vocation = g_vocations.getVocation(getNumber<uint16_t>(L, 2));
	} else if (isString(L, 2)) {
		vocation = g_vocations.getVocation(g_vocations.getVocationId(getString(L, 2)));
	} else if (isUserdata(L, 2)) {
		vocation = getUserdata<Vocation>(L, 2);
	} else {
		vocation = nullptr;
	}

	if (!vocation) {
		pushBoolean(L, false);
		return 1;
	}

	player->setVocation(vocation->getId());
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerGetSex(lua_State* L)
{
	// player:getSex()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getSex());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetSex(lua_State* L)
{
	// player:setSex(newSex)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		PlayerSex_t newSex = getNumber<PlayerSex_t>(L, 2);
		player->setSex(newSex);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetTown(lua_State* L)
{
	// player:getTown()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		pushUserdata<Town>(L, player->getTown());
		setMetatable(L, -1, "Town");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetTown(lua_State* L)
{
	// player:setTown(town)
	Town* town = getUserdata<Town>(L, 2);
	if (!town) {
		pushBoolean(L, false);
		return 1;
	}

	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->setTown(town);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


