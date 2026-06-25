// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

// Included inside LuaScriptInterface class declaration by ../luascript.hpp.

		// Item
		static int luaItemCreate(lua_State* L);

		static int luaItemIsItem(lua_State* L);

		static int luaItemGetParent(lua_State* L);
		static int luaItemGetTopParent(lua_State* L);

		static int luaItemGetId(lua_State* L);

		static int luaItemClone(lua_State* L);
		static int luaItemSplit(lua_State* L);
		static int luaItemRemove(lua_State* L);

		static int luaItemGetUniqueId(lua_State* L);
		static int luaItemGetActionId(lua_State* L);
		static int luaItemSetActionId(lua_State* L);

		static int luaItemGetCount(lua_State* L);
		static int luaItemGetCharges(lua_State* L);
		static int luaItemGetFluidType(lua_State* L);
		static int luaItemGetWeight(lua_State* L);

		static int luaItemGetSubType(lua_State* L);

		static int luaItemGetName(lua_State* L);
		static int luaItemGetPluralName(lua_State* L);
		static int luaItemGetArticle(lua_State* L);

		static int luaItemGetPosition(lua_State* L);
		static int luaItemGetTile(lua_State* L);

		static int luaItemHasAttribute(lua_State* L);
		static int luaItemGetAttribute(lua_State* L);
		static int luaItemSetAttribute(lua_State* L);
		static int luaItemRemoveAttribute(lua_State* L);

		static int luaItemMoveTo(lua_State* L);
		static int luaItemTransform(lua_State* L);
		static int luaItemDecay(lua_State* L);

		static int luaItemGetDescription(lua_State* L);

		static int luaItemHasProperty(lua_State* L);

		// Container
		static int luaContainerCreate(lua_State* L);

		static int luaContainerGetSize(lua_State* L);
		static int luaContainerGetCapacity(lua_State* L);
		static int luaContainerGetEmptySlots(lua_State* L);

		static int luaContainerGetItemHoldingCount(lua_State* L);
		static int luaContainerGetItemCountById(lua_State* L);

		static int luaContainerGetItem(lua_State* L);
		static int luaContainerHasItem(lua_State* L);
		static int luaContainerAddItem(lua_State* L);
		static int luaContainerAddItemEx(lua_State* L);

		// Teleport
		static int luaTeleportCreate(lua_State* L);

		static int luaTeleportGetDestination(lua_State* L);
		static int luaTeleportSetDestination(lua_State* L);

		// Creature
		static int luaCreatureCreate(lua_State* L);

		static int luaCreatureGetEvents(lua_State* L);
		static int luaCreatureRegisterEvent(lua_State* L);
		static int luaCreatureUnregisterEvent(lua_State* L);

		static int luaCreatureIsRemoved(lua_State* L);
		static int luaCreatureIsCreature(lua_State* L);
		static int luaCreatureIsInGhostMode(lua_State* L);
		static int luaCreatureIsHealthHidden(lua_State* L);

		static int luaCreatureCanSee(lua_State* L);
		static int luaCreatureCanSeeCreature(lua_State* L);

		static int luaCreatureGetParent(lua_State* L);

		static int luaCreatureGetId(lua_State* L);
		static int luaCreatureGetName(lua_State* L);

		static int luaCreatureGetTarget(lua_State* L);
		static int luaCreatureSetTarget(lua_State* L);

		static int luaCreatureGetFollowCreature(lua_State* L);
		static int luaCreatureSetFollowCreature(lua_State* L);

		static int luaCreatureGetMaster(lua_State* L);
		static int luaCreatureSetMaster(lua_State* L);

		static int luaCreatureGetLight(lua_State* L);
		static int luaCreatureSetLight(lua_State* L);

		static int luaCreatureGetSpeed(lua_State* L);
		static int luaCreatureGetBaseSpeed(lua_State* L);
		static int luaCreatureChangeSpeed(lua_State* L);

		static int luaCreatureSetDropLoot(lua_State* L);

		static int luaCreatureGetPosition(lua_State* L);
		static int luaCreatureGetTile(lua_State* L);
		static int luaCreatureGetDirection(lua_State* L);
		static int luaCreatureSetDirection(lua_State* L);

		static int luaCreatureGetHealth(lua_State* L);
		static int luaCreatureSetHealth(lua_State* L);
		static int luaCreatureAddHealth(lua_State* L);
		static int luaCreatureGetMaxHealth(lua_State* L);
		static int luaCreatureSetMaxHealth(lua_State* L);
		static int luaCreatureSetHiddenHealth(lua_State* L);

		static int luaCreatureGetMana(lua_State* L);
		static int luaCreatureAddMana(lua_State* L);
		static int luaCreatureGetMaxMana(lua_State* L);

		static int luaCreatureGetSkull(lua_State* L);
		static int luaCreatureSetSkull(lua_State* L);

		static int luaCreatureGetOutfit(lua_State* L);
		static int luaCreatureSetOutfit(lua_State* L);

		static int luaCreatureGetCondition(lua_State* L);
		static int luaCreatureAddCondition(lua_State* L);
		static int luaCreatureRemoveCondition(lua_State* L);

		static int luaCreatureRemove(lua_State* L);
		static int luaCreatureTeleportTo(lua_State* L);
		static int luaCreatureSay(lua_State* L);

		static int luaCreatureGetDamageMap(lua_State* L);

		static int luaCreatureGetSummons(lua_State* L);

		static int luaCreatureGetDescription(lua_State* L);

		static int luaCreatureGetPathTo(lua_State* L);
		static int luaCreatureMove(lua_State* L);
		static int luaCreatureGetWalkDelay(lua_State* L);
