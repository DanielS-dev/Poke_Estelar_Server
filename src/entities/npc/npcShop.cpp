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

void Npc::onPlayerTrade(Player* player, int32_t callback, uint16_t itemId, uint8_t count,
                        uint8_t amount, bool ignore/* = false*/, bool inBackpacks/* = false*/)
{
	if (npcEventHandler) {
		npcEventHandler->onPlayerTrade(player, callback, itemId, count, amount, ignore, inBackpacks);
	}
	player->sendSaleItemList();
}

void Npc::onPlayerEndTrade(Player* player, int32_t buyCallback, int32_t sellCallback)
{
	lua_State* L = getScriptInterface()->getLuaState();

	if (buyCallback != -1) {
		luaL_unref(L, LUA_REGISTRYINDEX, buyCallback);
	}

	if (sellCallback != -1) {
		luaL_unref(L, LUA_REGISTRYINDEX, sellCallback);
	}

	removeShopPlayer(player);

	if (npcEventHandler) {
		npcEventHandler->onPlayerEndTrade(player);
	}
}

void Npc::addShopPlayer(Player* player)
{
	shopPlayerSet.insert(player);
}

void Npc::removeShopPlayer(Player* player)
{
	shopPlayerSet.erase(player);
}

void Npc::closeAllShopWindows()
{
	while (!shopPlayerSet.empty()) {
		Player* player = *shopPlayerSet.begin();
		if (!player->closeShopWindow()) {
			removeShopPlayer(player);
		}
	}
}

