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

int NpcScriptInterface::luaOpenShopWindow(lua_State* L)
{
	//openShopWindow(cid, items, onBuy callback, onSell callback)
	int32_t sellCallback;
	if (lua_isfunction(L, -1) == 0) {
		sellCallback = -1;
		lua_pop(L, 1); // skip it - use default value
	} else {
		sellCallback = popCallback(L);
	}

	int32_t buyCallback;
	if (lua_isfunction(L, -1) == 0) {
		buyCallback = -1;
		lua_pop(L, 1); // skip it - use default value
	} else {
		buyCallback = popCallback(L);
	}

	if (lua_istable(L, -1) == 0) {
		reportError(__FUNCTION__, "item list is not a table.");
		pushBoolean(L, false);
		return 1;
	}

	std::list<ShopInfo> items;
	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		const auto tableIndex = lua_gettop(L);
		ShopInfo item;

		item.itemId = getField<uint32_t>(L, tableIndex, "id");
		item.subType = getField<int32_t>(L, tableIndex, "subType");
		if (item.subType == 0) {
			item.subType = getField<int32_t>(L, tableIndex, "subtype");
			lua_pop(L, 1);
		}

		item.buyPrice = getField<uint32_t>(L, tableIndex, "buy");
		item.sellPrice = getField<uint32_t>(L, tableIndex, "sell");
		item.realName = getFieldString(L, tableIndex, "name");

		items.push_back(item);
		lua_pop(L, 6);
	}
	lua_pop(L, 1);

	Player* player = getPlayer(L, -1);
	if (!player) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	//Close any eventual other shop window currently open.
	player->closeShopWindow(false);

	Npc* npc = getScriptEnv()->getNpc();
	if (!npc) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	npc->addShopPlayer(player);
	player->setShopOwner(npc, buyCallback, sellCallback);
	player->openShopWindow(npc, items);

	pushBoolean(L, true);
	return 1;
}

int NpcScriptInterface::luaCloseShopWindow(lua_State* L)
{
	//closeShopWindow(cid)
	Npc* npc = getScriptEnv()->getNpc();
	if (!npc) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Player* player = getPlayer(L, 1);
	if (!player) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	int32_t buyCallback;
	int32_t sellCallback;

	Npc* merchant = player->getShopOwner(buyCallback, sellCallback);

	//Check if we actually have a shop window with this player.
	if (merchant == npc) {
		player->sendCloseShop();

		if (buyCallback != -1) {
			luaL_unref(L, LUA_REGISTRYINDEX, buyCallback);
		}

		if (sellCallback != -1) {
			luaL_unref(L, LUA_REGISTRYINDEX, sellCallback);
		}

		player->setShopOwner(nullptr, -1, -1);
		npc->removeShopPlayer(player);
	}

	pushBoolean(L, true);
	return 1;
}

int NpcScriptInterface::luaDoSellItem(lua_State* L)
{
	//doSellItem(cid, itemid, amount, <optional> subtype, <optional> actionid, <optional: default: 1> canDropOnMap)
	Player* player = getPlayer(L, 1);
	if (!player) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	uint32_t sellCount = 0;

	uint32_t itemId = getNumber<uint32_t>(L, 2);
	uint32_t amount = getNumber<uint32_t>(L, 3);
	uint32_t subType;

	int32_t n = getNumber<int32_t>(L, 4, -1);
	if (n != -1) {
		subType = n;
	} else {
		subType = 1;
	}

	uint32_t actionId = getNumber<uint32_t>(L, 5, 0);
	bool canDropOnMap = getBoolean(L, 6, true);

	const ItemType& it = Item::items[itemId];
	if (it.stackable) {
		while (amount > 0) {
			int32_t stackCount = std::min<int32_t>(100, amount);
			Item* item = Item::CreateItem(it.id, stackCount);
			if (item && actionId != 0) {
				item->setActionId(actionId);
			}

			if (g_game.internalPlayerAddItem(player, item, canDropOnMap) != RETURNVALUE_NOERROR) {
				delete item;
				lua_pushnumber(L, sellCount);
				return 1;
			}

			amount -= stackCount;
			sellCount += stackCount;
		}
	} else {
		for (uint32_t i = 0; i < amount; ++i) {
			Item* item = Item::CreateItem(it.id, subType);
			if (item && actionId != 0) {
				item->setActionId(actionId);
			}

			if (g_game.internalPlayerAddItem(player, item, canDropOnMap) != RETURNVALUE_NOERROR) {
				delete item;
				lua_pushnumber(L, sellCount);
				return 1;
			}

			++sellCount;
		}
	}

	lua_pushnumber(L, sellCount);
	return 1;
}

int NpcScriptInterface::luaNpcGetParameter(lua_State* L)
{
	// npc:getParameter(key)
	const std::string& key = getString(L, 2);
	Npc* npc = getUserdata<Npc>(L, 1);
	if (npc) {
		auto it = npc->parameters.find(key);
		if (it != npc->parameters.end()) {
			pushString(L, it->second);
		} else {
			lua_pushnil(L);
		}
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int NpcScriptInterface::luaNpcSetFocus(lua_State* L)
{
	// npc:setFocus(creature)
	Creature* creature = getCreature(L, 2);
	Npc* npc = getUserdata<Npc>(L, 1);
	if (npc) {
		npc->setCreatureFocus(creature);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int NpcScriptInterface::luaNpcOpenShopWindow(lua_State* L)
{
	// npc:openShopWindow(cid, items, buyCallback, sellCallback)
	if (!isTable(L, 3)) {
		reportErrorFunc("item list is not a table.");
		pushBoolean(L, false);
		return 1;
	}

	Player* player = getPlayer(L, 2);
	if (!player) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Npc* npc = getUserdata<Npc>(L, 1);
	if (!npc) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	int32_t sellCallback = -1;
	if (LuaScriptInterface::isFunction(L, 5)) {
		sellCallback = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	int32_t buyCallback = -1;
	if (LuaScriptInterface::isFunction(L, 4)) {
		buyCallback = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	std::list<ShopInfo> items;

	lua_pushnil(L);
	while (lua_next(L, 3) != 0) {
		const auto tableIndex = lua_gettop(L);
		ShopInfo item;

		item.itemId = getField<uint32_t>(L, tableIndex, "id");
		item.subType = getField<int32_t>(L, tableIndex, "subType");
		if (item.subType == 0) {
			item.subType = getField<int32_t>(L, tableIndex, "subtype");
			lua_pop(L, 1);
		}

		item.buyPrice = getField<uint32_t>(L, tableIndex, "buy");
		item.sellPrice = getField<uint32_t>(L, tableIndex, "sell");
		item.realName = getFieldString(L, tableIndex, "name");

		items.push_back(item);
		lua_pop(L, 6);
	}
	lua_pop(L, 1);

	player->closeShopWindow(false);
	npc->addShopPlayer(player);

	player->setShopOwner(npc, buyCallback, sellCallback);
	player->openShopWindow(npc, items);

	pushBoolean(L, true);
	return 1;
}

int NpcScriptInterface::luaNpcCloseShopWindow(lua_State* L)
{
	// npc:closeShopWindow(player)
	Player* player = getPlayer(L, 2);
	if (!player) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Npc* npc = getUserdata<Npc>(L, 1);
	if (!npc) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	int32_t buyCallback;
	int32_t sellCallback;

	Npc* merchant = player->getShopOwner(buyCallback, sellCallback);
	if (merchant == npc) {
		player->sendCloseShop();
		if (buyCallback != -1) {
			luaL_unref(L, LUA_REGISTRYINDEX, buyCallback);
		}

		if (sellCallback != -1) {
			luaL_unref(L, LUA_REGISTRYINDEX, sellCallback);
		}

		player->setShopOwner(nullptr, -1, -1);
		npc->removeShopPlayer(player);
	}

	pushBoolean(L, true);
	return 1;
}

