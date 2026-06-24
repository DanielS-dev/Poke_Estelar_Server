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

int LuaScriptInterface::luaPlayerAddOutfit(lua_State* L)
{
	// player:addOutfit(lookType)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->addOutfit(getNumber<uint16_t>(L, 2), 0);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddOutfitAddon(lua_State* L)
{
	// player:addOutfitAddon(lookType, addon)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		uint16_t lookType = getNumber<uint16_t>(L, 2);
		uint8_t addon = getNumber<uint8_t>(L, 3);
		player->addOutfit(lookType, addon);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerRemoveOutfit(lua_State* L)
{
	// player:removeOutfit(lookType)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		uint16_t lookType = getNumber<uint16_t>(L, 2);
		pushBoolean(L, player->removeOutfit(lookType));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerRemoveOutfitAddon(lua_State* L)
{
	// player:removeOutfitAddon(lookType, addon)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		uint16_t lookType = getNumber<uint16_t>(L, 2);
		uint8_t addon = getNumber<uint8_t>(L, 3);
		pushBoolean(L, player->removeOutfitAddon(lookType, addon));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerHasOutfit(lua_State* L)
{
	// player:hasOutfit(lookType[, addon = 0])
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		uint16_t lookType = getNumber<uint16_t>(L, 2);
		uint8_t addon = getNumber<uint8_t>(L, 3, 0);
		pushBoolean(L, player->canWear(lookType, addon));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSendOutfitWindow(lua_State* L)
{
	// player:sendOutfitWindow()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->sendOutfitWindow();
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddMount(lua_State* L)
{
	// player:addMount(mountId)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		uint8_t mountId = getNumber<uint8_t>(L, 2);
		pushBoolean(L, player->tameMount(mountId));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerRemoveMount(lua_State* L)
{
	// player:removeMount(mountId)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		uint8_t mountId = getNumber<uint8_t>(L, 2);
		pushBoolean(L, player->untameMount(mountId));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerHasMount(lua_State* L)
{
	// player:hasMount(mountId)
	const Player* player = getUserdata<const Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	uint8_t mountId = getNumber<uint8_t>(L, 2);
	Mount* mount = g_game.mounts.getMountByID(mountId);
	if (mount) {
		pushBoolean(L, player->hasMount(mount));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


