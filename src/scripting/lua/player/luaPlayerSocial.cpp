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

int LuaScriptInterface::luaPlayerGetGuild(lua_State* L)
{
	// player:getGuild()
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	Guild* guild = player->getGuild();
	if (!guild) {
		lua_pushnil(L);
		return 1;
	}

	pushUserdata<Guild>(L, guild);
	setMetatable(L, -1, "Guild");
	return 1;
}


int LuaScriptInterface::luaPlayerSetGuild(lua_State* L)
{
	// player:setGuild(guild)
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	player->setGuild(getUserdata<Guild>(L, 2));
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerGetGuildLevel(lua_State* L)
{
	// player:getGuildLevel()
	Player* player = getUserdata<Player>(L, 1);
	if (player && player->getGuild()) {
		lua_pushnumber(L, player->getGuildRank()->level);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetGuildLevel(lua_State* L)
{
	// player:setGuildLevel(level)
	uint8_t level = getNumber<uint8_t>(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (!player || !player->getGuild()) {
		lua_pushnil(L);
		return 1;
	}

	const GuildRank* rank = player->getGuild()->getRankByLevel(level);
	if (!rank) {
		pushBoolean(L, false);
	} else {
		player->setGuildRank(rank);
		pushBoolean(L, true);
	}

	return 1;
}


int LuaScriptInterface::luaPlayerGetGuildNick(lua_State* L)
{
	// player:getGuildNick()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		pushString(L, player->getGuildNick());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetGuildNick(lua_State* L)
{
	// player:setGuildNick(nick)
	const std::string& nick = getString(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->setGuildNick(nick);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetGroup(lua_State* L)
{
	// player:getGroup()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		pushUserdata<Group>(L, player->getGroup());
		setMetatable(L, -1, "Group");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetGroup(lua_State* L)
{
	// player:setGroup(group)
	Group* group = getUserdata<Group>(L, 2);
	if (!group) {
		pushBoolean(L, false);
		return 1;
	}

	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->setGroup(group);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetParty(lua_State* L)
{
	// player:getParty()
	const Player* player = getUserdata<const Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	Party* party = player->getParty();
	if (party) {
		pushUserdata<Party>(L, party);
		setMetatable(L, -1, "Party");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


