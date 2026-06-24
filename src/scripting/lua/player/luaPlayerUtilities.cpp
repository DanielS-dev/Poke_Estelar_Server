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

int LuaScriptInterface::luaPlayerSendTutorial(lua_State* L)
{
	// player:sendTutorial(tutorialId)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		uint8_t tutorialId = getNumber<uint8_t>(L, 2);
		player->sendTutorial(tutorialId);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddMapMark(lua_State* L)
{
	// player:addMapMark(position, type, description)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		const Position& position = getPosition(L, 2);
		uint8_t type = getNumber<uint8_t>(L, 3);
		const std::string& description = getString(L, 4);
		player->sendAddMarker(position, type, description);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSave(lua_State* L)
{
	// player:save()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->loginPosition = player->getPosition();
		pushBoolean(L, IOLoginData::savePlayer(player));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerPopupFYI(lua_State* L)
{
	// player:popupFYI(message)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		const std::string& message = getString(L, 2);
		player->sendFYIBox(message);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerIsPzLocked(lua_State* L)
{
	// player:isPzLocked()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		pushBoolean(L, player->isPzLocked());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetClient(lua_State* L)
{
	// player:getClient()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_createtable(L, 0, 2);
		setField(L, "version", player->getProtocolVersion());
		setField(L, "os", player->getOperatingSystem());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetHouse(lua_State* L)
{
	// player:getHouse()
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	House* house = g_game.map.houses.getHouseByPlayerId(player->getGUID());
	if (house) {
		pushUserdata<House>(L, house);
		setMetatable(L, -1, "House");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetGhostMode(lua_State* L)
{
	// player:setGhostMode(enabled)
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	bool enabled = getBoolean(L, 2);
	if (player->isInGhostMode() == enabled) {
		pushBoolean(L, true);
		return 1;
	}

	player->switchGhostMode();

	Tile* tile = player->getTile();
	const Position& position = player->getPosition();

	SpectatorVec list;
	g_game.map.getSpectators(list, position, true, true);
	for (Creature* spectator : list) {
		Player* tmpPlayer = spectator->getPlayer();
		if (tmpPlayer != player && !tmpPlayer->isAccessPlayer()) {
			if (enabled) {
				tmpPlayer->sendRemoveTileThing(position, tile->getStackposOfCreature(tmpPlayer, player));
			} else {
				tmpPlayer->sendCreatureAppear(player, position, true);
			}
		} else {
			tmpPlayer->sendCreatureChangeVisible(player, !enabled);
		}
	}

	if (player->isInGhostMode()) {
		for (const auto& it : g_game.getPlayers()) {
			if (!it.second->isAccessPlayer()) {
				it.second->notifyStatusChange(player, VIPSTATUS_OFFLINE);
			}
		}
		IOLoginData::updateOnlineStatus(player->getGUID(), false);
	} else {
		for (const auto& it : g_game.getPlayers()) {
			if (!it.second->isAccessPlayer()) {
				it.second->notifyStatusChange(player, VIPSTATUS_ONLINE);
			}
		}
		IOLoginData::updateOnlineStatus(player->getGUID(), true);
	}
	pushBoolean(L, true);
	return 1;
}


