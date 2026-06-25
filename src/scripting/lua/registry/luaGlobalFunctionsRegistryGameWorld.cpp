// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"

void LuaScriptInterface::registerGameWorldBindings()
{
	// Game
	registerTable("Game");

	registerMethod("Game", "getSpectators", LuaScriptInterface::luaGameGetSpectators);
	registerMethod("Game", "getPlayers", LuaScriptInterface::luaGameGetPlayers);
	registerMethod("Game", "loadMap", LuaScriptInterface::luaGameLoadMap);

	registerMethod("Game", "getExperienceStage", LuaScriptInterface::luaGameGetExperienceStage);
	registerMethod("Game", "getMonsterCount", LuaScriptInterface::luaGameGetMonsterCount);
	registerMethod("Game", "getPlayerCount", LuaScriptInterface::luaGameGetPlayerCount);
	registerMethod("Game", "getNpcCount", LuaScriptInterface::luaGameGetNpcCount);

	registerMethod("Game", "getTowns", LuaScriptInterface::luaGameGetTowns);
	registerMethod("Game", "getHouses", LuaScriptInterface::luaGameGetHouses);

	registerMethod("Game", "getGameState", LuaScriptInterface::luaGameGetGameState);
	registerMethod("Game", "setGameState", LuaScriptInterface::luaGameSetGameState);

	registerMethod("Game", "getWorldType", LuaScriptInterface::luaGameGetWorldType);
	registerMethod("Game", "setWorldType", LuaScriptInterface::luaGameSetWorldType);

	registerMethod("Game", "getReturnMessage", LuaScriptInterface::luaGameGetReturnMessage);

	registerMethod("Game", "createItem", LuaScriptInterface::luaGameCreateItem);
	registerMethod("Game", "createContainer", LuaScriptInterface::luaGameCreateContainer);
	registerMethod("Game", "createMonster", LuaScriptInterface::luaGameCreateMonster);
	registerMethod("Game", "createNpc", LuaScriptInterface::luaGameCreateNpc);
	registerMethod("Game", "createTile", LuaScriptInterface::luaGameCreateTile);

	registerMethod("Game", "startRaid", LuaScriptInterface::luaGameStartRaid);
	registerMethod("Game", "sendAnimatedText", LuaScriptInterface::luaGameSendAnimatedText); //pota

	// Variant
	registerClass("Variant", "", LuaScriptInterface::luaVariantCreate);

	registerMethod("Variant", "getNumber", LuaScriptInterface::luaVariantGetNumber);
	registerMethod("Variant", "getString", LuaScriptInterface::luaVariantGetString);
	registerMethod("Variant", "getPosition", LuaScriptInterface::luaVariantGetPosition);

	// Position
	registerClass("Position", "", LuaScriptInterface::luaPositionCreate);
	registerMetaMethod("Position", "__add", LuaScriptInterface::luaPositionAdd);
	registerMetaMethod("Position", "__sub", LuaScriptInterface::luaPositionSub);
	registerMetaMethod("Position", "__eq", LuaScriptInterface::luaPositionCompare);

	registerMethod("Position", "getDistance", LuaScriptInterface::luaPositionGetDistance);
	registerMethod("Position", "isSightClear", LuaScriptInterface::luaPositionIsSightClear);

	registerMethod("Position", "sendMagicEffect", LuaScriptInterface::luaPositionSendMagicEffect);
	registerMethod("Position", "sendDistanceEffect", LuaScriptInterface::luaPositionSendDistanceEffect);

	// Tile
	registerClass("Tile", "", LuaScriptInterface::luaTileCreate);
	registerMetaMethod("Tile", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Tile", "getPosition", LuaScriptInterface::luaTileGetPosition);
	registerMethod("Tile", "getGround", LuaScriptInterface::luaTileGetGround);
	registerMethod("Tile", "getThing", LuaScriptInterface::luaTileGetThing);
	registerMethod("Tile", "getThingCount", LuaScriptInterface::luaTileGetThingCount);
	registerMethod("Tile", "getTopVisibleThing", LuaScriptInterface::luaTileGetTopVisibleThing);

	registerMethod("Tile", "getTopTopItem", LuaScriptInterface::luaTileGetTopTopItem);
	registerMethod("Tile", "getTopDownItem", LuaScriptInterface::luaTileGetTopDownItem);
	registerMethod("Tile", "getFieldItem", LuaScriptInterface::luaTileGetFieldItem);

	registerMethod("Tile", "getItemById", LuaScriptInterface::luaTileGetItemById);
	registerMethod("Tile", "getItemByType", LuaScriptInterface::luaTileGetItemByType);
	registerMethod("Tile", "getItemByTopOrder", LuaScriptInterface::luaTileGetItemByTopOrder);
	registerMethod("Tile", "getItemCountById", LuaScriptInterface::luaTileGetItemCountById);

	registerMethod("Tile", "getBottomCreature", LuaScriptInterface::luaTileGetBottomCreature);
	registerMethod("Tile", "getTopCreature", LuaScriptInterface::luaTileGetTopCreature);
	registerMethod("Tile", "getBottomVisibleCreature", LuaScriptInterface::luaTileGetBottomVisibleCreature);
	registerMethod("Tile", "getTopVisibleCreature", LuaScriptInterface::luaTileGetTopVisibleCreature);

	registerMethod("Tile", "getItems", LuaScriptInterface::luaTileGetItems);
	registerMethod("Tile", "getItemCount", LuaScriptInterface::luaTileGetItemCount);
	registerMethod("Tile", "getDownItemCount", LuaScriptInterface::luaTileGetDownItemCount);
	registerMethod("Tile", "getTopItemCount", LuaScriptInterface::luaTileGetTopItemCount);

	registerMethod("Tile", "getCreatures", LuaScriptInterface::luaTileGetCreatures);
	registerMethod("Tile", "getCreatureCount", LuaScriptInterface::luaTileGetCreatureCount);

	registerMethod("Tile", "getThingIndex", LuaScriptInterface::luaTileGetThingIndex);

	registerMethod("Tile", "hasProperty", LuaScriptInterface::luaTileHasProperty);
	registerMethod("Tile", "hasFlag", LuaScriptInterface::luaTileHasFlag);

	registerMethod("Tile", "queryAdd", LuaScriptInterface::luaTileQueryAdd);

	registerMethod("Tile", "getHouse", LuaScriptInterface::luaTileGetHouse);

	// NetworkMessage
	registerClass("NetworkMessage", "", LuaScriptInterface::luaNetworkMessageCreate);
	registerMetaMethod("NetworkMessage", "__eq", LuaScriptInterface::luaUserdataCompare);
	registerMetaMethod("NetworkMessage", "__gc", LuaScriptInterface::luaNetworkMessageDelete);
	registerMethod("NetworkMessage", "delete", LuaScriptInterface::luaNetworkMessageDelete);

	registerMethod("NetworkMessage", "getByte", LuaScriptInterface::luaNetworkMessageGetByte);
	registerMethod("NetworkMessage", "getU16", LuaScriptInterface::luaNetworkMessageGetU16);
	registerMethod("NetworkMessage", "getU32", LuaScriptInterface::luaNetworkMessageGetU32);
	registerMethod("NetworkMessage", "getU64", LuaScriptInterface::luaNetworkMessageGetU64);
	registerMethod("NetworkMessage", "getString", LuaScriptInterface::luaNetworkMessageGetString);
	registerMethod("NetworkMessage", "getPosition", LuaScriptInterface::luaNetworkMessageGetPosition);

	registerMethod("NetworkMessage", "addByte", LuaScriptInterface::luaNetworkMessageAddByte);
	registerMethod("NetworkMessage", "addU16", LuaScriptInterface::luaNetworkMessageAddU16);
	registerMethod("NetworkMessage", "addU32", LuaScriptInterface::luaNetworkMessageAddU32);
	registerMethod("NetworkMessage", "addU64", LuaScriptInterface::luaNetworkMessageAddU64);
	registerMethod("NetworkMessage", "addString", LuaScriptInterface::luaNetworkMessageAddString);
	registerMethod("NetworkMessage", "addPosition", LuaScriptInterface::luaNetworkMessageAddPosition);
	registerMethod("NetworkMessage", "addDouble", LuaScriptInterface::luaNetworkMessageAddDouble);
	registerMethod("NetworkMessage", "addItem", LuaScriptInterface::luaNetworkMessageAddItem);
	registerMethod("NetworkMessage", "addItemId", LuaScriptInterface::luaNetworkMessageAddItemId);

	registerMethod("NetworkMessage", "reset", LuaScriptInterface::luaNetworkMessageReset);
	registerMethod("NetworkMessage", "skipBytes", LuaScriptInterface::luaNetworkMessageSkipBytes);
	registerMethod("NetworkMessage", "sendToPlayer", LuaScriptInterface::luaNetworkMessageSendToPlayer);

	// ModalWindow
	registerClass("ModalWindow", "", LuaScriptInterface::luaModalWindowCreate);
	registerMetaMethod("ModalWindow", "__eq", LuaScriptInterface::luaUserdataCompare);
	registerMetaMethod("ModalWindow", "__gc", LuaScriptInterface::luaModalWindowDelete);
	registerMethod("ModalWindow", "delete", LuaScriptInterface::luaModalWindowDelete);

	registerMethod("ModalWindow", "getId", LuaScriptInterface::luaModalWindowGetId);
	registerMethod("ModalWindow", "getTitle", LuaScriptInterface::luaModalWindowGetTitle);
	registerMethod("ModalWindow", "getMessage", LuaScriptInterface::luaModalWindowGetMessage);

	registerMethod("ModalWindow", "setTitle", LuaScriptInterface::luaModalWindowSetTitle);
	registerMethod("ModalWindow", "setMessage", LuaScriptInterface::luaModalWindowSetMessage);

	registerMethod("ModalWindow", "getButtonCount", LuaScriptInterface::luaModalWindowGetButtonCount);
	registerMethod("ModalWindow", "getChoiceCount", LuaScriptInterface::luaModalWindowGetChoiceCount);

	registerMethod("ModalWindow", "addButton", LuaScriptInterface::luaModalWindowAddButton);
	registerMethod("ModalWindow", "addChoice", LuaScriptInterface::luaModalWindowAddChoice);

	registerMethod("ModalWindow", "getDefaultEnterButton", LuaScriptInterface::luaModalWindowGetDefaultEnterButton);
	registerMethod("ModalWindow", "setDefaultEnterButton", LuaScriptInterface::luaModalWindowSetDefaultEnterButton);

	registerMethod("ModalWindow", "getDefaultEscapeButton", LuaScriptInterface::luaModalWindowGetDefaultEscapeButton);
	registerMethod("ModalWindow", "setDefaultEscapeButton", LuaScriptInterface::luaModalWindowSetDefaultEscapeButton);

	registerMethod("ModalWindow", "hasPriority", LuaScriptInterface::luaModalWindowHasPriority);
	registerMethod("ModalWindow", "setPriority", LuaScriptInterface::luaModalWindowSetPriority);

	registerMethod("ModalWindow", "sendToPlayer", LuaScriptInterface::luaModalWindowSendToPlayer);
}
