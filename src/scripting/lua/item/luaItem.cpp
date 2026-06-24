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

int LuaScriptInterface::luaItemCreate(lua_State* L)
{
	// Item(uid)
	uint32_t id = getNumber<uint32_t>(L, 2);

	Item* item = getScriptEnv()->getItemByUID(id);
	if (item) {
		pushUserdata<Item>(L, item);
		setItemMetatable(L, -1, item);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemIsItem(lua_State* L)
{
	// item:isItem()
	pushBoolean(L, getUserdata<const Item>(L, 1) != nullptr);
	return 1;
}


int LuaScriptInterface::luaItemGetParent(lua_State* L)
{
	// item:getParent()
	Item* item = getUserdata<Item>(L, 1);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	Cylinder* parent = item->getParent();
	if (!parent) {
		lua_pushnil(L);
		return 1;
	}

	pushCylinder(L, parent);
	return 1;
}


int LuaScriptInterface::luaItemGetTopParent(lua_State* L)
{
	// item:getTopParent()
	Item* item = getUserdata<Item>(L, 1);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	Cylinder* topParent = item->getTopParent();
	if (!topParent) {
		lua_pushnil(L);
		return 1;
	}

	pushCylinder(L, topParent);
	return 1;
}


int LuaScriptInterface::luaItemGetId(lua_State* L)
{
	// item:getId()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		lua_pushnumber(L, item->getID());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemClone(lua_State* L)
{
	// item:clone()
	Item* item = getUserdata<Item>(L, 1);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	Item* clone = item->clone();
	if (!clone) {
		lua_pushnil(L);
		return 1;
	}

	getScriptEnv()->addTempItem(clone);
	clone->setParent(VirtualCylinder::virtualCylinder);

	pushUserdata<Item>(L, clone);
	setItemMetatable(L, -1, clone);
	return 1;
}


int LuaScriptInterface::luaItemSplit(lua_State* L)
{
	// item:split([count = 1])
	Item** itemPtr = getRawUserdata<Item>(L, 1);
	if (!itemPtr) {
		lua_pushnil(L);
		return 1;
	}

	Item* item = *itemPtr;
	if (!item || !item->isStackable()) {
		lua_pushnil(L);
		return 1;
	}

	uint16_t count = std::min<uint16_t>(getNumber<uint16_t>(L, 2, 1), item->getItemCount());
	uint16_t diff = item->getItemCount() - count;

	Item* splitItem = item->clone();
	if (!splitItem) {
		lua_pushnil(L);
		return 1;
	}

	ScriptEnvironment* env = getScriptEnv();
	uint32_t uid = env->addThing(item);

	Item* newItem = g_game.transformItem(item, item->getID(), diff);
	if (item->isRemoved()) {
		env->removeItemByUID(uid);
	}

	if (newItem && newItem != item) {
		env->insertItem(uid, newItem);
	}

	*itemPtr = newItem;

	splitItem->setParent(VirtualCylinder::virtualCylinder);
	env->addTempItem(splitItem);

	pushUserdata<Item>(L, splitItem);
	setItemMetatable(L, -1, splitItem);
	return 1;
}


int LuaScriptInterface::luaItemRemove(lua_State* L)
{
	// item:remove([count = -1])
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		int32_t count = getNumber<int32_t>(L, 2, -1);
		pushBoolean(L, g_game.internalRemoveItem(item, count) == RETURNVALUE_NOERROR);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetUniqueId(lua_State* L)
{
	// item:getUniqueId()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		uint32_t uniqueId = item->getUniqueId();
		if (uniqueId == 0) {
			uniqueId = getScriptEnv()->addThing(item);
		}
		lua_pushnumber(L, uniqueId);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetActionId(lua_State* L)
{
	// item:getActionId()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		lua_pushnumber(L, item->getActionId());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemSetActionId(lua_State* L)
{
	// item:setActionId(actionId)
	uint16_t actionId = getNumber<uint16_t>(L, 2);
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		item->setActionId(actionId);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetCount(lua_State* L)
{
	// item:getCount()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		lua_pushnumber(L, item->getItemCount());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetCharges(lua_State* L)
{
	// item:getCharges()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		lua_pushnumber(L, item->getCharges());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetFluidType(lua_State* L)
{
	// item:getFluidType()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		lua_pushnumber(L, item->getFluidType());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetWeight(lua_State* L)
{
	// item:getWeight()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		lua_pushnumber(L, item->getWeight());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetSubType(lua_State* L)
{
	// item:getSubType()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		lua_pushnumber(L, item->getSubType());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetName(lua_State* L)
{
	// item:getName()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		pushString(L, item->getName());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetPluralName(lua_State* L)
{
	// item:getPluralName()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		pushString(L, item->getPluralName());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetArticle(lua_State* L)
{
	// item:getArticle()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		pushString(L, item->getArticle());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetPosition(lua_State* L)
{
	// item:getPosition()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		pushPosition(L, item->getPosition());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetTile(lua_State* L)
{
	// item:getTile()
	Item* item = getUserdata<Item>(L, 1);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	Tile* tile = item->getTile();
	if (tile) {
		pushUserdata<Tile>(L, tile);
		setMetatable(L, -1, "Tile");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemHasAttribute(lua_State* L)
{
	// item:hasAttribute(key)
	Item* item = getUserdata<Item>(L, 1);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	itemAttrTypes attribute;
	if (isNumber(L, 2)) {
		attribute = getNumber<itemAttrTypes>(L, 2);
	} else if (isString(L, 2)) {
		attribute = stringToItemAttribute(getString(L, 2));
	} else {
		attribute = ITEM_ATTRIBUTE_NONE;
	}

	pushBoolean(L, item->hasAttribute(attribute));
	return 1;
}


int LuaScriptInterface::luaItemGetAttribute(lua_State* L)
{
	// item:getAttribute(key)
	Item* item = getUserdata<Item>(L, 1);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	itemAttrTypes attribute;
	if (isNumber(L, 2)) {
		attribute = getNumber<itemAttrTypes>(L, 2);
	} else if (isString(L, 2)) {
		attribute = stringToItemAttribute(getString(L, 2));
	} else {
		attribute = ITEM_ATTRIBUTE_NONE;
	}

	if (ItemAttributes::isIntAttrType(attribute)) {
		lua_pushnumber(L, item->getIntAttr(attribute));
	} else if (ItemAttributes::isStrAttrType(attribute)) {
		pushString(L, item->getStrAttr(attribute));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemSetAttribute(lua_State* L)
{
	// item:setAttribute(key, value)
	Item* item = getUserdata<Item>(L, 1);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	itemAttrTypes attribute;
	if (isNumber(L, 2)) {
		attribute = getNumber<itemAttrTypes>(L, 2);
	} else if (isString(L, 2)) {
		attribute = stringToItemAttribute(getString(L, 2));
	} else {
		attribute = ITEM_ATTRIBUTE_NONE;
	}

	if (ItemAttributes::isIntAttrType(attribute)) {
		if (attribute == ITEM_ATTRIBUTE_UNIQUEID) {
			reportErrorFunc("Attempt to set protected key \"uid\"");
			pushBoolean(L, false);
			return 1;
		}

		item->setIntAttr(attribute, getNumber<int32_t>(L, 3));
		pushBoolean(L, true);
	} else if (ItemAttributes::isStrAttrType(attribute)) {
		item->setStrAttr(attribute, getString(L, 3));
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemRemoveAttribute(lua_State* L)
{
	// item:removeAttribute(key)
	Item* item = getUserdata<Item>(L, 1);
	if (!item) {
		lua_pushnil(L);
		return 1;
	}

	itemAttrTypes attribute;
	if (isNumber(L, 2)) {
		attribute = getNumber<itemAttrTypes>(L, 2);
	} else if (isString(L, 2)) {
		attribute = stringToItemAttribute(getString(L, 2));
	} else {
		attribute = ITEM_ATTRIBUTE_NONE;
	}

	bool ret = attribute != ITEM_ATTRIBUTE_UNIQUEID;
	if (ret) {
		item->removeAttribute(attribute);
	} else {
		reportErrorFunc("Attempt to erase protected key \"uid\"");
	}
	pushBoolean(L, ret);
	return 1;
}


int LuaScriptInterface::luaItemMoveTo(lua_State* L)
{
	// item:moveTo(position or cylinder)
	Item** itemPtr = getRawUserdata<Item>(L, 1);
	if (!itemPtr) {
		lua_pushnil(L);
		return 1;
	}

	Item* item = *itemPtr;
	if (!item || item->isRemoved()) {
		lua_pushnil(L);
		return 1;
	}

	Cylinder* toCylinder;
	if (isUserdata(L, 2)) {
		const LuaDataType type = getUserdataType(L, 2);
		switch (type) {
			case LuaData_Container:
				toCylinder = getUserdata<Container>(L, 2);
				break;
			case LuaData_Player:
				toCylinder = getUserdata<Player>(L, 2);
				break;
			case LuaData_Tile:
				toCylinder = getUserdata<Tile>(L, 2);
				break;
			default:
				toCylinder = nullptr;
				break;
		}
	} else {
		toCylinder = g_game.map.getTile(getPosition(L, 2));
	}

	if (!toCylinder) {
		lua_pushnil(L);
		return 1;
	}

	if (item->getParent() == toCylinder) {
		pushBoolean(L, true);
		return 1;
	}

	if (item->getParent() == VirtualCylinder::virtualCylinder) {
		pushBoolean(L, g_game.internalAddItem(toCylinder, item) == RETURNVALUE_NOERROR);
	} else {
		Item* moveItem = nullptr;
		ReturnValue ret = g_game.internalMoveItem(item->getParent(), toCylinder, INDEX_WHEREEVER, item, item->getItemCount(), &moveItem, FLAG_NOLIMIT | FLAG_IGNOREBLOCKITEM | FLAG_IGNOREBLOCKCREATURE | FLAG_IGNORENOTMOVEABLE);
		if (moveItem) {
			*itemPtr = moveItem;
		}
		pushBoolean(L, ret == RETURNVALUE_NOERROR);
	}
	return 1;
}


int LuaScriptInterface::luaItemTransform(lua_State* L)
{
	// item:transform(itemId[, count/subType = -1])
	Item** itemPtr = getRawUserdata<Item>(L, 1);
	if (!itemPtr) {
		lua_pushnil(L);
		return 1;
	}

	Item*& item = *itemPtr;
	if (!item) {
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
	if (item->getID() == itemId && (subType == -1 || subType == item->getSubType())) {
		pushBoolean(L, true);
		return 1;
	}

	const ItemType& it = Item::items[itemId];
	if (it.stackable) {
		subType = std::min<int32_t>(subType, 100);
	}

	ScriptEnvironment* env = getScriptEnv();
	uint32_t uid = env->addThing(item);

	Item* newItem = g_game.transformItem(item, itemId, subType);
	if (item->isRemoved()) {
		env->removeItemByUID(uid);
	}

	if (newItem && newItem != item) {
		env->insertItem(uid, newItem);
	}

	item = newItem;
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaItemDecay(lua_State* L)
{
	// item:decay()
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		g_game.startDecay(item);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemGetDescription(lua_State* L)
{
	// item:getDescription(distance)
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		int32_t distance = getNumber<int32_t>(L, 2);
		pushString(L, item->getDescription(distance));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaItemHasProperty(lua_State* L)
{
	// item:hasProperty(property)
	Item* item = getUserdata<Item>(L, 1);
	if (item) {
		ITEMPROPERTY property = getNumber<ITEMPROPERTY>(L, 2);
		pushBoolean(L, item->hasProperty(property));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

// Container


