// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"

void LuaScriptInterface::registerItemCreatureBindings()
{
	// Item
	registerClass("Item", "", LuaScriptInterface::luaItemCreate);
	registerMetaMethod("Item", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Item", "isItem", LuaScriptInterface::luaItemIsItem);

	registerMethod("Item", "getParent", LuaScriptInterface::luaItemGetParent);
	registerMethod("Item", "getTopParent", LuaScriptInterface::luaItemGetTopParent);

	registerMethod("Item", "getId", LuaScriptInterface::luaItemGetId);

	registerMethod("Item", "clone", LuaScriptInterface::luaItemClone);
	registerMethod("Item", "split", LuaScriptInterface::luaItemSplit);
	registerMethod("Item", "remove", LuaScriptInterface::luaItemRemove);

	registerMethod("Item", "getUniqueId", LuaScriptInterface::luaItemGetUniqueId);
	registerMethod("Item", "getActionId", LuaScriptInterface::luaItemGetActionId);
	registerMethod("Item", "setActionId", LuaScriptInterface::luaItemSetActionId);

	registerMethod("Item", "getCount", LuaScriptInterface::luaItemGetCount);
	registerMethod("Item", "getCharges", LuaScriptInterface::luaItemGetCharges);
	registerMethod("Item", "getFluidType", LuaScriptInterface::luaItemGetFluidType);
	registerMethod("Item", "getWeight", LuaScriptInterface::luaItemGetWeight);

	registerMethod("Item", "getSubType", LuaScriptInterface::luaItemGetSubType);

	registerMethod("Item", "getName", LuaScriptInterface::luaItemGetName);
	registerMethod("Item", "getPluralName", LuaScriptInterface::luaItemGetPluralName);
	registerMethod("Item", "getArticle", LuaScriptInterface::luaItemGetArticle);

	registerMethod("Item", "getPosition", LuaScriptInterface::luaItemGetPosition);
	registerMethod("Item", "getTile", LuaScriptInterface::luaItemGetTile);

	registerMethod("Item", "hasAttribute", LuaScriptInterface::luaItemHasAttribute);
	registerMethod("Item", "getAttribute", LuaScriptInterface::luaItemGetAttribute);
	registerMethod("Item", "setAttribute", LuaScriptInterface::luaItemSetAttribute);
	registerMethod("Item", "removeAttribute", LuaScriptInterface::luaItemRemoveAttribute);

	registerMethod("Item", "moveTo", LuaScriptInterface::luaItemMoveTo);
	registerMethod("Item", "transform", LuaScriptInterface::luaItemTransform);
	registerMethod("Item", "decay", LuaScriptInterface::luaItemDecay);

	registerMethod("Item", "getDescription", LuaScriptInterface::luaItemGetDescription);

	registerMethod("Item", "hasProperty", LuaScriptInterface::luaItemHasProperty);

	// Container
	registerClass("Container", "Item", LuaScriptInterface::luaContainerCreate);
	registerMetaMethod("Container", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Container", "getSize", LuaScriptInterface::luaContainerGetSize);
	registerMethod("Container", "getCapacity", LuaScriptInterface::luaContainerGetCapacity);
	registerMethod("Container", "getEmptySlots", LuaScriptInterface::luaContainerGetEmptySlots);

	registerMethod("Container", "getItemHoldingCount", LuaScriptInterface::luaContainerGetItemHoldingCount);
	registerMethod("Container", "getItemCountById", LuaScriptInterface::luaContainerGetItemCountById);

	registerMethod("Container", "getItem", LuaScriptInterface::luaContainerGetItem);
	registerMethod("Container", "hasItem", LuaScriptInterface::luaContainerHasItem);
	registerMethod("Container", "addItem", LuaScriptInterface::luaContainerAddItem);
	registerMethod("Container", "addItemEx", LuaScriptInterface::luaContainerAddItemEx);

	// Teleport
	registerClass("Teleport", "Item", LuaScriptInterface::luaTeleportCreate);
	registerMetaMethod("Teleport", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Teleport", "getDestination", LuaScriptInterface::luaTeleportGetDestination);
	registerMethod("Teleport", "setDestination", LuaScriptInterface::luaTeleportSetDestination);

	// Creature
	registerClass("Creature", "", LuaScriptInterface::luaCreatureCreate);
	registerMetaMethod("Creature", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Creature", "getEvents", LuaScriptInterface::luaCreatureGetEvents);
	registerMethod("Creature", "registerEvent", LuaScriptInterface::luaCreatureRegisterEvent);
	registerMethod("Creature", "unregisterEvent", LuaScriptInterface::luaCreatureUnregisterEvent);

	registerMethod("Creature", "isRemoved", LuaScriptInterface::luaCreatureIsRemoved);
	registerMethod("Creature", "isCreature", LuaScriptInterface::luaCreatureIsCreature);
	registerMethod("Creature", "isInGhostMode", LuaScriptInterface::luaCreatureIsInGhostMode);
	registerMethod("Creature", "isHealthHidden", LuaScriptInterface::luaCreatureIsHealthHidden);

	registerMethod("Creature", "canSee", LuaScriptInterface::luaCreatureCanSee);
	registerMethod("Creature", "canSeeCreature", LuaScriptInterface::luaCreatureCanSeeCreature);

	registerMethod("Creature", "getParent", LuaScriptInterface::luaCreatureGetParent);

	registerMethod("Creature", "getId", LuaScriptInterface::luaCreatureGetId);
	registerMethod("Creature", "getName", LuaScriptInterface::luaCreatureGetName);

	registerMethod("Creature", "getTarget", LuaScriptInterface::luaCreatureGetTarget);
	registerMethod("Creature", "setTarget", LuaScriptInterface::luaCreatureSetTarget);

	registerMethod("Creature", "getFollowCreature", LuaScriptInterface::luaCreatureGetFollowCreature);
	registerMethod("Creature", "setFollowCreature", LuaScriptInterface::luaCreatureSetFollowCreature);

	registerMethod("Creature", "getMaster", LuaScriptInterface::luaCreatureGetMaster);
	registerMethod("Creature", "setMaster", LuaScriptInterface::luaCreatureSetMaster);

	registerMethod("Creature", "getLight", LuaScriptInterface::luaCreatureGetLight);
	registerMethod("Creature", "setLight", LuaScriptInterface::luaCreatureSetLight);

	registerMethod("Creature", "getSpeed", LuaScriptInterface::luaCreatureGetSpeed);
	registerMethod("Creature", "getBaseSpeed", LuaScriptInterface::luaCreatureGetBaseSpeed);
	registerMethod("Creature", "changeSpeed", LuaScriptInterface::luaCreatureChangeSpeed);

	registerMethod("Creature", "setDropLoot", LuaScriptInterface::luaCreatureSetDropLoot);

	registerMethod("Creature", "getPosition", LuaScriptInterface::luaCreatureGetPosition);
	registerMethod("Creature", "getTile", LuaScriptInterface::luaCreatureGetTile);
	registerMethod("Creature", "getDirection", LuaScriptInterface::luaCreatureGetDirection);
	registerMethod("Creature", "setDirection", LuaScriptInterface::luaCreatureSetDirection);

	registerMethod("Creature", "getHealth", LuaScriptInterface::luaCreatureGetHealth);
	registerMethod("Creature", "setHealth", LuaScriptInterface::luaCreatureSetHealth);
	registerMethod("Creature", "addHealth", LuaScriptInterface::luaCreatureAddHealth);
	registerMethod("Creature", "getMaxHealth", LuaScriptInterface::luaCreatureGetMaxHealth);

	registerMethod("Creature", "setMaxHealth", LuaScriptInterface::luaCreatureSetMaxHealth);
	registerMethod("Creature", "setHiddenHealth", LuaScriptInterface::luaCreatureSetHiddenHealth);

	registerMethod("Creature", "getMana", LuaScriptInterface::luaCreatureGetMana);
	registerMethod("Creature", "addMana", LuaScriptInterface::luaCreatureAddMana);
	registerMethod("Creature", "getMaxMana", LuaScriptInterface::luaCreatureGetMaxMana);

	registerMethod("Creature", "getSkull", LuaScriptInterface::luaCreatureGetSkull);
	registerMethod("Creature", "setSkull", LuaScriptInterface::luaCreatureSetSkull);

	registerMethod("Creature", "getOutfit", LuaScriptInterface::luaCreatureGetOutfit);
	registerMethod("Creature", "setOutfit", LuaScriptInterface::luaCreatureSetOutfit);

	registerMethod("Creature", "getCondition", LuaScriptInterface::luaCreatureGetCondition);
	registerMethod("Creature", "addCondition", LuaScriptInterface::luaCreatureAddCondition);
	registerMethod("Creature", "removeCondition", LuaScriptInterface::luaCreatureRemoveCondition);

	registerMethod("Creature", "remove", LuaScriptInterface::luaCreatureRemove);
	registerMethod("Creature", "teleportTo", LuaScriptInterface::luaCreatureTeleportTo);
	registerMethod("Creature", "say", LuaScriptInterface::luaCreatureSay);

	registerMethod("Creature", "getDamageMap", LuaScriptInterface::luaCreatureGetDamageMap);

	registerMethod("Creature", "getSummons", LuaScriptInterface::luaCreatureGetSummons);

	registerMethod("Creature", "getDescription", LuaScriptInterface::luaCreatureGetDescription);

	registerMethod("Creature", "getPathTo", LuaScriptInterface::luaCreatureGetPathTo);
	registerMethod("Creature", "move", LuaScriptInterface::luaCreatureMove);
	registerMethod("Creature", "getWalkDelay", LuaScriptInterface::luaCreatureGetWalkDelay);
}
