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

int LuaScriptInterface::luaContainerCreate(lua_State* L)
{
	// Container(uid)
	uint32_t id = getNumber<uint32_t>(L, 2);

	Container* container = getScriptEnv()->getContainerByUID(id);
	if (container) {
		pushUserdata(L, container);
		setMetatable(L, -1, "Container");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaContainerGetSize(lua_State* L)
{
	// container:getSize()
	Container* container = getUserdata<Container>(L, 1);
	if (container) {
		lua_pushnumber(L, container->size());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaContainerGetCapacity(lua_State* L)
{
	// container:getCapacity()
	Container* container = getUserdata<Container>(L, 1);
	if (container) {
		lua_pushnumber(L, container->capacity());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaContainerGetEmptySlots(lua_State* L)
{
	// container:getEmptySlots([recursive = false])
	Container* container = getUserdata<Container>(L, 1);
	if (!container) {
		lua_pushnil(L);
		return 1;
	}

	uint32_t slots = container->capacity() - container->size();
	bool recursive = getBoolean(L, 2, false);
	if (recursive) {
		for (ContainerIterator it = container->iterator(); it.hasNext(); it.advance()) {
			if (Container* tmpContainer = (*it)->getContainer()) {
				slots += tmpContainer->capacity() - tmpContainer->size();
			}
		}
	}
	lua_pushnumber(L, slots);
	return 1;
}


int LuaScriptInterface::luaContainerGetItemHoldingCount(lua_State* L)
{
	// container:getItemHoldingCount()
	Container* container = getUserdata<Container>(L, 1);
	if (container) {
		lua_pushnumber(L, container->getItemHoldingCount());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaContainerGetItem(lua_State* L)
{
	// container:getItem(index)
	Container* container = getUserdata<Container>(L, 1);
	if (!container) {
		lua_pushnil(L);
		return 1;
	}

	uint32_t index = getNumber<uint32_t>(L, 2);
	Item* item = container->getItemByIndex(index);
	if (item) {
		pushUserdata<Item>(L, item);
		setItemMetatable(L, -1, item);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaContainerHasItem(lua_State* L)
{
	// container:hasItem(item)
	Item* item = getUserdata<Item>(L, 2);
	Container* container = getUserdata<Container>(L, 1);
	if (container) {
		pushBoolean(L, container->isHoldingItem(item));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaContainerAddItem(lua_State* L)
{
	// container:addItem(itemId[, count/subType = 1[, index = INDEX_WHEREEVER[, flags = 0]]])
	Container* container = getUserdata<Container>(L, 1);
	if (!container) {
		lua_pushnil(L);
		return 1;
	}

	uint16_t itemId;
	if (isNumber(L, 2)) {
		itemId = getNumber<uint16_t>(L, 2);
	} else {
		itemId = Item::items.getItemIdByName(getString(L, 2));
		if (itemId == 0) {
			lua_pushnil(L);
			return 1;
		}
	}

	uint32_t subType = getNumber<uint32_t>(L, 3, 1);

	Item* item = Item::CreateItem(itemId, std::min<uint32_t>(subType, 100));
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	int32_t index = getNumber<int32_t>(L, 4, INDEX_WHEREEVER);
	uint32_t flags = getNumber<uint32_t>(L, 5, 0);

	ReturnValue ret = g_game.internalAddItem(container, item, index, flags);
	if (ret == RETURNVALUE_NOERROR) {
		pushUserdata<Item>(L, item);
		setItemMetatable(L, -1, item);
	} else {
		delete item;
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaContainerAddItemEx(lua_State* L)
{
	// container:addItemEx(item[, index = INDEX_WHEREEVER[, flags = 0]])
	Item* item = getUserdata<Item>(L, 2);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	Container* container = getUserdata<Container>(L, 1);
	if (!container) {
		lua_pushnil(L);
		return 1;
	}

	if (item->getParent() != VirtualCylinder::virtualCylinder) {
		reportErrorFunc("Item already has a parent");
		lua_pushnil(L);
		return 1;
	}

	int32_t index = getNumber<int32_t>(L, 3, INDEX_WHEREEVER);
	uint32_t flags = getNumber<uint32_t>(L, 4, 0);
	ReturnValue ret = g_game.internalAddItem(container, item, index, flags);
	if (ret == RETURNVALUE_NOERROR) {
		ScriptEnvironment::removeTempItem(item);
	}
	lua_pushnumber(L, ret);
	return 1;
}


int LuaScriptInterface::luaContainerGetItemCountById(lua_State* L)
{
	// container:getItemCountById(itemId[, subType = -1])
	Container* container = getUserdata<Container>(L, 1);
	if (!container) {
		lua_pushnil(L);
		return 1;
	}

	uint16_t itemId;
	if (isNumber(L, 2)) {
		itemId = getNumber<uint16_t>(L, 2);
	} else {
		itemId = Item::items.getItemIdByName(getString(L, 2));
		if (itemId == 0) {
			lua_pushnil(L);
			return 1;
		}
	}

	int32_t subType = getNumber<int32_t>(L, 3, -1);
	lua_pushnumber(L, container->getItemTypeCount(itemId, subType));
	return 1;
}

// Teleport


