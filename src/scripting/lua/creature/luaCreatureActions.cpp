// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"
#include "../../../game/game.hpp"
#include "../../../entities/player.hpp"

extern Game g_game;

int LuaScriptInterface::luaCreatureRemove(lua_State* L)
{
	// creature:remove()
	Creature** creaturePtr = getRawUserdata<Creature>(L, 1);
	if (!creaturePtr) {
		lua_pushnil(L);
		return 1;
	}

	Creature* creature = *creaturePtr;
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	Player* player = creature->getPlayer();
	if (player) {
		player->kickPlayer(true);
	} else {
		g_game.removeCreature(creature);
	}

	*creaturePtr = nullptr;
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaCreatureSay(lua_State* L)
{
	// creature:say(text, type[, ghost = false[, target = nullptr[, position]]])
	int parameters = lua_gettop(L);

	Position position;
	if (parameters >= 6) {
		position = getPosition(L, 6);
		if (!position.x || !position.y) {
			reportErrorFunc("Invalid position specified.");
			pushBoolean(L, false);
			return 1;
		}
	}

	Creature* target = nullptr;
	if (parameters >= 5) {
		target = getCreature(L, 5);
	}

	bool ghost = getBoolean(L, 4, false);

	SpeakClasses type = getNumber<SpeakClasses>(L, 3);
	const std::string& text = getString(L, 2);
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	SpectatorVec list;
	if (target) {
		list.insert(target);
	}

	if (position.x != 0) {
		pushBoolean(L, g_game.internalCreatureSay(creature, type, text, ghost, &list, &position));
	} else {
		pushBoolean(L, g_game.internalCreatureSay(creature, type, text, ghost, &list));
	}
	return 1;
}
