// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <boost/range/adaptor/reversed.hpp>

#include "luascript.hpp"
#include "../events/events.hpp" //pota
#include "../../game/chat/chat.hpp"
#include "../../entities/player.hpp"
#include "../../game/game.hpp"
#include "../../network/protocolstatus.hpp"
#include "../../game/spells/spells.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../../config/configmanager.hpp"
#include "../../world/teleport.hpp"
#include "../../persistence/databasemanager.hpp"
#include "../../world/bed.hpp"
#include "../../entities/monster.hpp"
#include "../../core/scheduler.hpp"
#include "../../persistence/databasetasks.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/returnMessageTools.hpp"
#include "../../core/tools/stringsTools.hpp"

extern Chat* g_chat;
extern Game g_game;
extern Monsters g_monsters;
extern ConfigManager g_config;
extern Vocations g_vocations;
extern Spells* g_spells;
extern Events* g_events; //pota

int LuaScriptInterface::protectedCall(lua_State* L, int nargs, int nresults)
{
	int error_index = lua_gettop(L) - nargs;
	lua_pushcfunction(L, luaErrorHandler);
	lua_insert(L, error_index);

	int ret = lua_pcall(L, nargs, nresults, error_index);
	lua_remove(L, error_index);
	return ret;
}

int LuaScriptInterface::luaDoCreatureCastSpell(lua_State* L) //pota
{
	//doCreatureCastSpell(cid, spellname)
	Creature* creature = getCreature(L, 1);
	std::string spellName = getString(L, 2);
	if(creature){
		InstantSpell* spell = g_spells->getInstantSpellByName(spellName);
		if(!spell){
			lua_pushboolean(L, false);
			return 1;
		}
		Creature* target = creature->getAttackedCreature();
		if(target){
			spell->castSpell(creature, target);
		} else {
			spell->castSpell(creature);
		}
		lua_pushboolean(L, true);
	} else {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		lua_pushboolean(L, false);
	}
	return 1;
}

int LuaScriptInterface::luaGetPlayerFlagValue(lua_State* L)
{
	//getPlayerFlagValue(cid, flag)
	Player* player = getPlayer(L, 1);
	if (player) {
		PlayerFlags flag = getNumber<PlayerFlags>(L, 2);
		pushBoolean(L, player->hasFlag(flag));
	} else {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
	}
	return 1;
}

int LuaScriptInterface::luaGetPlayerInstantSpellCount(lua_State* L)
{
	//getPlayerInstantSpellCount(cid)
	Player* player = getPlayer(L, 1);
	if (player) {
		lua_pushnumber(L, g_spells->getInstantSpellCount(player));
	} else {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
	}
	return 1;
}

int LuaScriptInterface::luaGetPlayerInstantSpellInfo(lua_State* L)
{
	//getPlayerInstantSpellInfo(cid, index)
	Player* player = getPlayer(L, 1);
	if (!player) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	uint32_t index = getNumber<uint32_t>(L, 2);
	InstantSpell* spell = g_spells->getInstantSpellByIndex(player, index);
	if (!spell) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_SPELL_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	lua_createtable(L, 0, 6);
	setField(L, "name", spell->getName());
	setField(L, "words", spell->getWords());
	setField(L, "level", spell->getLevel());
	setField(L, "mlevel", spell->getMagicLevel());
	setField(L, "mana", spell->getManaCost(player));
	setField(L, "manapercent", spell->getManaPercent());
	return 1;
}

