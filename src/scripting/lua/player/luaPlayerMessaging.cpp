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

int LuaScriptInterface::luaPlayerShowTextDialog(lua_State* L)
{
	// player:showTextDialog(itemId[, text[, canWrite[, length]]])
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	int32_t length = getNumber<int32_t>(L, 5, -1);
	bool canWrite = getBoolean(L, 4, false);
	std::string text;

	int parameters = lua_gettop(L);
	if (parameters >= 3) {
		text = getString(L, 3);
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

	Item* item = Item::CreateItem(itemId);
	if (!item) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_ITEM_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	if (length < 0) {
		length = Item::items[item->getID()].maxTextLen;
	}

	if (!text.empty()) {
		item->setText(text);
		length = std::max<int32_t>(text.size(), length);
	}

	item->setParent(player);
	player->setWriteItem(item, length);
	player->sendTextWindow(item, length, canWrite);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerSendTextMessage(lua_State* L)
{
	// player:sendTextMessage(type, text[, position, primaryValue = 0, primaryColor = TEXTCOLOR_NONE[, secondaryValue = 0, secondaryColor = TEXTCOLOR_NONE]])
	int parameters = lua_gettop(L);

	TextMessage message(getNumber<MessageClasses>(L, 2), getString(L, 3));
	if (parameters >= 6) {
		message.position = getPosition(L, 4);
		message.primary.value = getNumber<int32_t>(L, 5);
		message.primary.color = getNumber<TextColor_t>(L, 6);
	}

	if (parameters >= 8) {
		message.secondary.value = getNumber<int32_t>(L, 7);
		message.secondary.color = getNumber<TextColor_t>(L, 8);
	}

	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->sendTextMessage(message);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSendChannelMessage(lua_State* L)
{
	// player:sendChannelMessage(author, text, type, channelId)
	uint16_t channelId = getNumber<uint16_t>(L, 5);
	SpeakClasses type = getNumber<SpeakClasses>(L, 4);
	const std::string& text = getString(L, 3);
	const std::string& author = getString(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->sendChannelMessage(author, text, type, channelId);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSendPrivateMessage(lua_State* L)
{
	// player:sendPrivateMessage(speaker, text[, type])
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	const Player* speaker = getUserdata<const Player>(L, 2);
	const std::string& text = getString(L, 3);
	SpeakClasses type = getNumber<SpeakClasses>(L, 4, TALKTYPE_PRIVATE_FROM);
	player->sendPrivateMessage(speaker, type, text);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerChannelSay(lua_State* L)
{
	// player:channelSay(speaker, type, text, channelId)
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	Creature* speaker = getCreature(L, 2);
	SpeakClasses type = getNumber<SpeakClasses>(L, 3);
	const std::string& text = getString(L, 4);
	uint16_t channelId = getNumber<uint16_t>(L, 5);
	player->sendToChannel(speaker, type, text, channelId);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerOpenChannel(lua_State* L)
{
	// player:openChannel(channelId)
	uint16_t channelId = getNumber<uint16_t>(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		g_game.playerOpenChannel(player->getID(), channelId);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


