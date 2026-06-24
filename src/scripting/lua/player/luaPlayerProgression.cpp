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

int LuaScriptInterface::luaPlayerGetPremiumDays(lua_State* L)
{
	// player:getPremiumDays()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->premiumDays);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddPremiumDays(lua_State* L)
{
	// player:addPremiumDays(days)
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	if (player->premiumDays != std::numeric_limits<uint16_t>::max()) {
		uint16_t days = getNumber<uint16_t>(L, 2);
		int32_t addDays = std::min<int32_t>(0xFFFE - player->premiumDays, days);
		if (addDays > 0) {
			player->setPremiumDays(player->premiumDays + addDays);
			IOLoginData::addPremiumDays(player->getAccount(), addDays);
		}
	}
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerRemovePremiumDays(lua_State* L)
{
	// player:removePremiumDays(days)
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	if (player->premiumDays != std::numeric_limits<uint16_t>::max()) {
		uint16_t days = getNumber<uint16_t>(L, 2);
		int32_t removeDays = std::min<int32_t>(player->premiumDays, days);
		if (removeDays > 0) {
			player->setPremiumDays(player->premiumDays - removeDays);
			IOLoginData::removePremiumDays(player->getAccount(), removeDays);
		}
	}
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerHasBlessing(lua_State* L)
{
	// player:hasBlessing(blessing)
	uint8_t blessing = getNumber<uint8_t>(L, 2) - 1;
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		pushBoolean(L, player->hasBlessing(blessing));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddBlessing(lua_State* L)
{
	// player:addBlessing(blessing)
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	uint8_t blessing = getNumber<uint8_t>(L, 2) - 1;
	if (player->hasBlessing(blessing)) {
		pushBoolean(L, false);
		return 1;
	}

	player->addBlessing(1 << blessing);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerRemoveBlessing(lua_State* L)
{
	// player:removeBlessing(blessing)
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	uint8_t blessing = getNumber<uint8_t>(L, 2) - 1;
	if (!player->hasBlessing(blessing)) {
		pushBoolean(L, false);
		return 1;
	}

	player->removeBlessing(1 << blessing);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaPlayerCanLearnSpell(lua_State* L)
{
	// player:canLearnSpell(spellName)
	const Player* player = getUserdata<const Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	const std::string& spellName = getString(L, 2);
	InstantSpell* spell = g_spells->getInstantSpellByName(spellName);
	if (!spell) {
		reportErrorFunc("Spell \"" + spellName + "\" not found");
		pushBoolean(L, false);
		return 1;
	}

	if (player->hasFlag(PlayerFlag_IgnoreSpellCheck)) {
		pushBoolean(L, true);
		return 1;
	}

	const auto& vocMap = spell->getVocMap();
	if (vocMap.count(player->getVocationId()) == 0) {
		pushBoolean(L, false);
	} else if (player->getLevel() < spell->getLevel()) {
		pushBoolean(L, false);
	} else if (player->getMagicLevel() < spell->getMagicLevel()) {
		pushBoolean(L, false);
	} else {
		pushBoolean(L, true);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerLearnSpell(lua_State* L)
{
	// player:learnSpell(spellName)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		const std::string& spellName = getString(L, 2);
		player->learnInstantSpell(spellName);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerForgetSpell(lua_State* L)
{
	// player:forgetSpell(spellName)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		const std::string& spellName = getString(L, 2);
		player->forgetInstantSpell(spellName);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerHasLearnedSpell(lua_State* L)
{
	// player:hasLearnedSpell(spellName)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		const std::string& spellName = getString(L, 2);
		pushBoolean(L, player->hasLearnedInstantSpell(spellName));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


