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

int LuaScriptInterface::luaVariantCreate(lua_State* L)
{
	// Variant(number or string or position or thing)
	LuaVariant variant;
	if (isUserdata(L, 2)) {
		if (Thing* thing = getThing(L, 2)) {
			variant.type = VARIANT_TARGETPOSITION;
			variant.pos = thing->getPosition();
		}
	} else if (isTable(L, 2)) {
		variant.type = VARIANT_POSITION;
		variant.pos = getPosition(L, 2);
	} else if (isNumber(L, 2)) {
		variant.type = VARIANT_NUMBER;
		variant.number = getNumber<uint32_t>(L, 2);
	} else if (isString(L, 2)) {
		variant.type = VARIANT_STRING;
		variant.text = getString(L, 2);
	}
	pushVariant(L, variant);
	return 1;
}


int LuaScriptInterface::luaVariantGetNumber(lua_State* L)
{
	// Variant:getNumber()
	const LuaVariant& variant = getVariant(L, 1);
	if (variant.type == VARIANT_NUMBER) {
		lua_pushnumber(L, variant.number);
	} else {
		lua_pushnumber(L, 0);
	}
	return 1;
}


int LuaScriptInterface::luaVariantGetString(lua_State* L)
{
	// Variant:getString()
	const LuaVariant& variant = getVariant(L, 1);
	if (variant.type == VARIANT_STRING) {
		pushString(L, variant.text);
	} else {
		pushString(L, std::string());
	}
	return 1;
}


int LuaScriptInterface::luaVariantGetPosition(lua_State* L)
{
	// Variant:getPosition()
	const LuaVariant& variant = getVariant(L, 1);
	if (variant.type == VARIANT_POSITION || variant.type == VARIANT_TARGETPOSITION) {
		pushPosition(L, variant.pos);
	} else {
		pushPosition(L, Position());
	}
	return 1;
}

// Position


