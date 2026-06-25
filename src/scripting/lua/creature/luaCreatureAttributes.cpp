// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"
#include "../../../game/game.hpp"
#include "../../../entities/player.hpp"

extern Game g_game;

int LuaScriptInterface::luaCreatureGetLight(lua_State* L)
{
	// creature:getLight()
	const Creature* creature = getUserdata<const Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	LightInfo light;
	creature->getCreatureLight(light);
	lua_pushnumber(L, light.level);
	lua_pushnumber(L, light.color);
	return 2;
}

int LuaScriptInterface::luaCreatureSetLight(lua_State* L)
{
	// creature:setLight(color, level)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	LightInfo light;
	light.color = getNumber<uint8_t>(L, 2);
	light.level = getNumber<uint8_t>(L, 3);
	creature->setCreatureLight(light);
	g_game.changeLight(creature);
	pushBoolean(L, true);
	return 1;
}

int LuaScriptInterface::luaCreatureGetSpeed(lua_State* L)
{
	// creature:getSpeed()
	const Creature* creature = getUserdata<const Creature>(L, 1);
	if (creature) {
		lua_pushnumber(L, creature->getSpeed());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureGetBaseSpeed(lua_State* L)
{
	// creature:getBaseSpeed()
	const Creature* creature = getUserdata<const Creature>(L, 1);
	if (creature) {
		lua_pushnumber(L, creature->getBaseSpeed());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

//get exp from monsters

int LuaScriptInterface::luaCreatureChangeSpeed(lua_State* L)
{
	// creature:changeSpeed(delta)
	Creature* creature = getCreature(L, 1);
	if (!creature) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	int32_t delta = getNumber<int32_t>(L, 2);
	g_game.changeSpeed(creature, delta);
	pushBoolean(L, true);
	return 1;
}

int LuaScriptInterface::luaCreatureSetDropLoot(lua_State* L)
{
	// creature:setDropLoot(doDrop)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (creature) {
		creature->setDropLoot(getBoolean(L, 2));
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaCreatureGetHealth(lua_State* L)
{
	// creature:getHealth()
	const Creature* creature = getUserdata<const Creature>(L, 1);
	if (creature) {
		lua_pushnumber(L, creature->getHealth());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureSetHealth(lua_State* L)
{
 	// creature:setHealth(health)
 	Creature* creature = getUserdata<Creature>(L, 1);
 	if (!creature) {
 		lua_pushnil(L);
 		return 1;
 	}
 
 	creature->health = std::min<int32_t>(getNumber<uint32_t>(L, 2), creature->healthMax);
 	g_game.addCreatureHealth(creature);
 
 	Player* player = creature->getPlayer();
 	if (player) {
 		player->sendStats();
 	}
 	pushBoolean(L, true);
 	return 1;
}

int LuaScriptInterface::luaCreatureAddHealth(lua_State* L)
{
	// creature:addHealth(healthChange)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	CombatDamage damage;
	damage.primary.value = getNumber<int32_t>(L, 2);
	if (damage.primary.value >= 0) {
		damage.primary.type = COMBAT_HEALING;
	} else {
		damage.primary.type = COMBAT_UNDEFINEDDAMAGE;
	}
	pushBoolean(L, g_game.combatChangeHealth(nullptr, creature, damage));
	return 1;
}

int LuaScriptInterface::luaCreatureGetMaxHealth(lua_State* L)
{
	// creature:getMaxHealth()
	const Creature* creature = getUserdata<const Creature>(L, 1);
	if (creature) {
		lua_pushnumber(L, creature->getMaxHealth());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureSetMaxHealth(lua_State* L)
{
	// creature:setMaxHealth(maxHealth)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	creature->healthMax = getNumber<uint32_t>(L, 2);
	creature->health = std::min<int32_t>(creature->health, creature->healthMax);
	g_game.addCreatureHealth(creature);

	Player* player = creature->getPlayer();
	if (player) {
		player->sendStats();
	}
	pushBoolean(L, true);
	return 1;
}

int LuaScriptInterface::luaCreatureSetHiddenHealth(lua_State* L)
{
	// creature:setHiddenHealth(hide)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (creature) {
		creature->setHiddenHealth(getBoolean(L, 2));
		g_game.addCreatureHealth(creature);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureGetMana(lua_State* L)
{
	// creature:getMana()
	const Creature* creature = getUserdata<const Creature>(L, 1);
	if (creature) {
		lua_pushnumber(L, creature->getMana());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureAddMana(lua_State* L)
{
	// creature:addMana(manaChange[, animationOnLoss = false])
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	int32_t manaChange = getNumber<int32_t>(L, 2);
	bool animationOnLoss = getBoolean(L, 3, false);
	if (!animationOnLoss && manaChange < 0) {
		creature->changeMana(manaChange);
	} else {
		g_game.combatChangeMana(nullptr, creature, manaChange, ORIGIN_NONE);
	}
	pushBoolean(L, true);
	return 1;
}

int LuaScriptInterface::luaCreatureGetMaxMana(lua_State* L)
{
	// creature:getMaxMana()
	const Creature* creature = getUserdata<const Creature>(L, 1);
	if (creature) {
		lua_pushnumber(L, creature->getMaxMana());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureGetSkull(lua_State* L)
{
	// creature:getSkull()
	Creature* creature = getUserdata<Creature>(L, 1);
	if (creature) {
		lua_pushnumber(L, creature->getSkull());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureSetSkull(lua_State* L)
{
	// creature:setSkull(skull)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (creature) {
		creature->setSkull(getNumber<Skulls_t>(L, 2));
		pushBoolean(L, true);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureGetOutfit(lua_State* L)
{
	// creature:getOutfit()
	const Creature* creature = getUserdata<const Creature>(L, 1);
	if (creature) {
		pushOutfit(L, creature->getCurrentOutfit());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaScriptInterface::luaCreatureSetOutfit(lua_State* L)
{
	// creature:setOutfit(outfit)
	Creature* creature = getUserdata<Creature>(L, 1);
	if (creature) {
		creature->defaultOutfit = getOutfit(L, 2);
		g_game.internalCreatureChangeOutfit(creature, creature->defaultOutfit);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

