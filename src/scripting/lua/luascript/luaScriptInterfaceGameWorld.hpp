// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

// Included inside LuaScriptInterface class declaration by ../luascript.hpp.

		// Game
		static int luaGameGetSpectators(lua_State* L);
		static int luaGameGetPlayers(lua_State* L);
		static int luaGameLoadMap(lua_State* L);

		static int luaGameGetExperienceStage(lua_State* L);
		static int luaGameGetMonsterCount(lua_State* L);
		static int luaGameGetPlayerCount(lua_State* L);
		static int luaGameGetNpcCount(lua_State* L);

		static int luaGameGetTowns(lua_State* L);
		static int luaGameGetHouses(lua_State* L);

		static int luaGameGetGameState(lua_State* L);
		static int luaGameSetGameState(lua_State* L);

		static int luaGameGetWorldType(lua_State* L);
		static int luaGameSetWorldType(lua_State* L);

		static int luaGameGetReturnMessage(lua_State* L);

		static int luaGameCreateItem(lua_State* L);
		static int luaGameCreateContainer(lua_State* L);
		static int luaGameCreateMonster(lua_State* L);
		static int luaGameCreateNpc(lua_State* L);
		static int luaGameCreateTile(lua_State* L);

		static int luaGameStartRaid(lua_State* L);

		static int luaGameSendAnimatedText(lua_State* L); //pota

		// Variant
		static int luaVariantCreate(lua_State* L);

		static int luaVariantGetNumber(lua_State* L);
		static int luaVariantGetString(lua_State* L);
		static int luaVariantGetPosition(lua_State* L);

		// Position
		static int luaPositionCreate(lua_State* L);
		static int luaPositionAdd(lua_State* L);
		static int luaPositionSub(lua_State* L);
		static int luaPositionCompare(lua_State* L);

		static int luaPositionGetDistance(lua_State* L);
		static int luaPositionIsSightClear(lua_State* L);

		static int luaPositionSendMagicEffect(lua_State* L);
		static int luaPositionSendDistanceEffect(lua_State* L);

		// Tile
		static int luaTileCreate(lua_State* L);

		static int luaTileGetPosition(lua_State* L);
		static int luaTileGetGround(lua_State* L);
		static int luaTileGetThing(lua_State* L);
		static int luaTileGetThingCount(lua_State* L);
		static int luaTileGetTopVisibleThing(lua_State* L);

		static int luaTileGetTopTopItem(lua_State* L);
		static int luaTileGetTopDownItem(lua_State* L);
		static int luaTileGetFieldItem(lua_State* L);

		static int luaTileGetItemById(lua_State* L);
		static int luaTileGetItemByType(lua_State* L);
		static int luaTileGetItemByTopOrder(lua_State* L);
		static int luaTileGetItemCountById(lua_State* L);

		static int luaTileGetBottomCreature(lua_State* L);
		static int luaTileGetTopCreature(lua_State* L);
		static int luaTileGetBottomVisibleCreature(lua_State* L);
		static int luaTileGetTopVisibleCreature(lua_State* L);

		static int luaTileGetItems(lua_State* L);
		static int luaTileGetItemCount(lua_State* L);
		static int luaTileGetDownItemCount(lua_State* L);
		static int luaTileGetTopItemCount(lua_State* L);

		static int luaTileGetCreatures(lua_State* L);
		static int luaTileGetCreatureCount(lua_State* L);

		static int luaTileHasProperty(lua_State* L);
		static int luaTileHasFlag(lua_State* L);

		static int luaTileGetThingIndex(lua_State* L);

		static int luaTileQueryAdd(lua_State* L);

		static int luaTileGetHouse(lua_State* L);

		// NetworkMessage
		static int luaNetworkMessageCreate(lua_State* L);
		static int luaNetworkMessageDelete(lua_State* L);

		static int luaNetworkMessageGetByte(lua_State* L);
		static int luaNetworkMessageGetU16(lua_State* L);
		static int luaNetworkMessageGetU32(lua_State* L);
		static int luaNetworkMessageGetU64(lua_State* L);
		static int luaNetworkMessageGetString(lua_State* L);
		static int luaNetworkMessageGetPosition(lua_State* L);

		static int luaNetworkMessageAddByte(lua_State* L);
		static int luaNetworkMessageAddU16(lua_State* L);
		static int luaNetworkMessageAddU32(lua_State* L);
		static int luaNetworkMessageAddU64(lua_State* L);
		static int luaNetworkMessageAddString(lua_State* L);
		static int luaNetworkMessageAddPosition(lua_State* L);
		static int luaNetworkMessageAddDouble(lua_State* L);
		static int luaNetworkMessageAddItem(lua_State* L);
		static int luaNetworkMessageAddItemId(lua_State* L);

		static int luaNetworkMessageReset(lua_State* L);
		static int luaNetworkMessageSkipBytes(lua_State* L);
		static int luaNetworkMessageSendToPlayer(lua_State* L);

		// ModalWindow
		static int luaModalWindowCreate(lua_State* L);
		static int luaModalWindowDelete(lua_State* L);

		static int luaModalWindowGetId(lua_State* L);
		static int luaModalWindowGetTitle(lua_State* L);
		static int luaModalWindowGetMessage(lua_State* L);

		static int luaModalWindowSetTitle(lua_State* L);
		static int luaModalWindowSetMessage(lua_State* L);

		static int luaModalWindowGetButtonCount(lua_State* L);
		static int luaModalWindowGetChoiceCount(lua_State* L);

		static int luaModalWindowAddButton(lua_State* L);
		static int luaModalWindowAddChoice(lua_State* L);

		static int luaModalWindowGetDefaultEnterButton(lua_State* L);
		static int luaModalWindowSetDefaultEnterButton(lua_State* L);

		static int luaModalWindowGetDefaultEscapeButton(lua_State* L);
		static int luaModalWindowSetDefaultEscapeButton(lua_State* L);

		static int luaModalWindowHasPriority(lua_State* L);
		static int luaModalWindowSetPriority(lua_State* L);

		static int luaModalWindowSendToPlayer(lua_State* L);
