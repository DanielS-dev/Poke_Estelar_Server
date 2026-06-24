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

bool LuaScriptInterface::getArea(lua_State* L, std::list<uint32_t>& list, uint32_t& rows)
{
	lua_pushnil(L);
	for (rows = 0; lua_next(L, -2) != 0; ++rows) {
		if (!isTable(L, -1)) {
			return false;
		}

		lua_pushnil(L);
		while (lua_next(L, -2) != 0) {
			if (!isNumber(L, -1)) {
				return false;
			}
			list.push_back(getNumber<uint32_t>(L, -1));
			lua_pop(L, 1);
		}

		lua_pop(L, 1);
	}

	lua_pop(L, 1);
	return (rows != 0);
}


int LuaScriptInterface::luaCreateCombatArea(lua_State* L)
{
	//createCombatArea( {area}, <optional> {extArea} )
	ScriptEnvironment* env = getScriptEnv();
	if (env->getScriptId() != EVENT_ID_LOADING) {
		reportErrorFunc("This function can only be used while loading the script.");
		pushBoolean(L, false);
		return 1;
	}

	uint32_t areaId = g_luaEnvironment.createAreaObject(env->getScriptInterface());
	AreaCombat* area = g_luaEnvironment.getAreaObject(areaId);

	int parameters = lua_gettop(L);
	if (parameters >= 2) {
		uint32_t rowsExtArea;
		std::list<uint32_t> listExtArea;
		if (!isTable(L, 2) || !getArea(L, listExtArea, rowsExtArea)) {
			reportErrorFunc("Invalid extended area table.");
			pushBoolean(L, false);
			return 1;
		}
		area->setupExtArea(listExtArea, rowsExtArea);
	}

	uint32_t rowsArea = 0;
	std::list<uint32_t> listArea;
	if (!isTable(L, 1) || !getArea(L, listArea, rowsArea)) {
		reportErrorFunc("Invalid area table.");
		pushBoolean(L, false);
		return 1;
	}

	area->setupArea(listArea, rowsArea);
	lua_pushnumber(L, areaId);
	return 1;
}


int LuaScriptInterface::luaDoAreaCombatHealth(lua_State* L)
{
	//doAreaCombatHealth(cid, type, pos, area, min, max, effect[, type2, origin = ORIGIN_SPELL])
	Creature* creature = getCreature(L, 1);
	if (!creature && (!isNumber(L, 1) || getNumber<uint32_t>(L, 1) != 0)) {
		// reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	uint32_t areaId = getNumber<uint32_t>(L, 4);
	const AreaCombat* area = g_luaEnvironment.getAreaObject(areaId);
	if (area || areaId == 0) {
		CombatType_t combatType = getNumber<CombatType_t>(L, 2);

		CombatParams params;
		params.combatType = combatType;
		params.impactEffect = getNumber<uint16_t>(L, 7); //pota

		CombatDamage damage;
		damage.origin = getNumber<CombatOrigin>(L, 9, ORIGIN_SPELL); //pota
		damage.primary.type = combatType;
		damage.primary.value = normal_random(getNumber<int32_t>(L, 6), getNumber<int32_t>(L, 5));

		CombatType_t combatType2 = getNumber<CombatType_t>(L, 8); //pota
		damage.secondary.type = combatType2; //pota
		damage.secondary.value = 0; //pota

		Combat::doCombatHealth(creature, getPosition(L, 3), area, damage, params);
		pushBoolean(L, true);
	} else {
		reportErrorFunc(getErrorDesc(LUA_ERROR_AREA_NOT_FOUND));
		pushBoolean(L, false);
	}
	return 1;
}


int LuaScriptInterface::luaDoTargetCombatHealth(lua_State* L)
{
	//doTargetCombatHealth(cid, target, type, min, max, effect[, type2, origin = ORIGIN_SPELL])
	Creature* creature = getCreature(L, 1);
	if (!creature && (!isNumber(L, 1) || getNumber<uint32_t>(L, 1) != 0)) {
		// reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Creature* target = getCreature(L, 2);
	if (!target) {
		// reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	CombatType_t combatType = getNumber<CombatType_t>(L, 3);

	CombatParams params;
	params.combatType = combatType;
	params.impactEffect = getNumber<uint16_t>(L, 6);

	CombatDamage damage;
	damage.origin = getNumber<CombatOrigin>(L, 8, ORIGIN_SPELL); //pota
	damage.primary.type = combatType;
	damage.primary.value = normal_random(getNumber<int32_t>(L, 4), getNumber<int32_t>(L, 5));

	CombatType_t combatType2 = getNumber<CombatType_t>(L, 7); //pota
	damage.secondary.type = combatType2; //pota
	damage.secondary.value = 0; //pota

	Combat::doCombatHealth(creature, target, damage, params);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaDoAreaCombatMana(lua_State* L)
{
	//doAreaCombatMana(cid, pos, area, min, max, effect[, origin = ORIGIN_SPELL])
	Creature* creature = getCreature(L, 1);
	if (!creature && (!isNumber(L, 1) || getNumber<uint32_t>(L, 1) != 0)) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	uint32_t areaId = getNumber<uint32_t>(L, 3);
	const AreaCombat* area = g_luaEnvironment.getAreaObject(areaId);
	if (area || areaId == 0) {
		CombatParams params;
		params.impactEffect = getNumber<uint8_t>(L, 6);

		CombatDamage damage;
		damage.origin = getNumber<CombatOrigin>(L, 7, ORIGIN_SPELL);
		damage.primary.type = COMBAT_MANADRAIN;
		damage.primary.value = normal_random(getNumber<int32_t>(L, 4), getNumber<int32_t>(L, 5));

		Position pos = getPosition(L, 2);
		Combat::doCombatMana(creature, pos, area, damage, params);
		pushBoolean(L, true);
	} else {
		reportErrorFunc(getErrorDesc(LUA_ERROR_AREA_NOT_FOUND));
		pushBoolean(L, false);
	}
	return 1;
}


int LuaScriptInterface::luaDoTargetCombatMana(lua_State* L)
{
	//doTargetCombatMana(cid, target, min, max, effect[, origin = ORIGIN_SPELL)
	Creature* creature = getCreature(L, 1);
	if (!creature && (!isNumber(L, 1) || getNumber<uint32_t>(L, 1) != 0)) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Creature* target = getCreature(L, 2);
	if (!target) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	CombatParams params;
	params.impactEffect = getNumber<uint8_t>(L, 5);

	CombatDamage damage;
	damage.origin = getNumber<CombatOrigin>(L, 6, ORIGIN_SPELL);
	damage.primary.type = COMBAT_MANADRAIN;
	damage.primary.value = normal_random(getNumber<int32_t>(L, 3), getNumber<int32_t>(L, 4));

	Combat::doCombatMana(creature, target, damage, params);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaDoAreaCombatCondition(lua_State* L)
{
	//doAreaCombatCondition(cid, pos, area, condition, effect)
	Creature* creature = getCreature(L, 1);
	if (!creature && (!isNumber(L, 1) || getNumber<uint32_t>(L, 1) != 0)) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	const Condition* condition = getUserdata<Condition>(L, 4);
	if (!condition) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CONDITION_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	uint32_t areaId = getNumber<uint32_t>(L, 3);
	const AreaCombat* area = g_luaEnvironment.getAreaObject(areaId);
	if (area || areaId == 0) {
		CombatParams params;
		params.impactEffect = getNumber<uint8_t>(L, 5);
		params.conditionList.emplace_front(condition);
		Combat::doCombatCondition(creature, getPosition(L, 2), area, params);
		pushBoolean(L, true);
	} else {
		reportErrorFunc(getErrorDesc(LUA_ERROR_AREA_NOT_FOUND));
		pushBoolean(L, false);
	}
	return 1;
}


int LuaScriptInterface::luaDoTargetCombatCondition(lua_State* L)
{
	//doTargetCombatCondition(cid, target, condition, effect)
	Creature* creature = getCreature(L, 1);
	if (!creature && (!isNumber(L, 1) || getNumber<uint32_t>(L, 1) != 0)) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Creature* target = getCreature(L, 2);
	if (!target) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	const Condition* condition = getUserdata<Condition>(L, 3);
	if (!condition) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CONDITION_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	CombatParams params;
	params.impactEffect = getNumber<uint8_t>(L, 4);
	params.conditionList.emplace_front(condition);
	Combat::doCombatCondition(creature, target, params);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaDoAreaCombatDispel(lua_State* L)
{
	//doAreaCombatDispel(cid, pos, area, type, effect)
	Creature* creature = getCreature(L, 1);
	if (!creature && (!isNumber(L, 1) || getNumber<uint32_t>(L, 1) != 0)) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	uint32_t areaId = getNumber<uint32_t>(L, 3);
	const AreaCombat* area = g_luaEnvironment.getAreaObject(areaId);
	if (area || areaId == 0) {
		CombatParams params;
		params.impactEffect = getNumber<uint8_t>(L, 5);
		params.dispelType = getNumber<ConditionType_t>(L, 4);
		Combat::doCombatDispel(creature, getPosition(L, 2), area, params);

		pushBoolean(L, true);
	} else {
		reportErrorFunc(getErrorDesc(LUA_ERROR_AREA_NOT_FOUND));
		pushBoolean(L, false);
	}
	return 1;
}


int LuaScriptInterface::luaDoTargetCombatDispel(lua_State* L)
{
	//doTargetCombatDispel(cid, target, type, effect)
	Creature* creature = getCreature(L, 1);
	if (!creature && (!isNumber(L, 1) || getNumber<uint32_t>(L, 1) != 0)) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Creature* target = getCreature(L, 2);
	if (!target) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	CombatParams params;
	params.dispelType = getNumber<ConditionType_t>(L, 3);
	params.impactEffect = getNumber<uint8_t>(L, 4);
	Combat::doCombatDispel(creature, target, params);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaDoChallengeCreature(lua_State* L)
{
	//doChallengeCreature(cid, target)
	Creature* creature = getCreature(L, 1);
	if (!creature) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Creature* target = getCreature(L, 2);
	if (!target) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	target->challengeCreature(creature);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaSetCreatureOutfit(lua_State* L)
{
	//doSetCreatureOutfit(cid, outfit, time)
	Creature* creature = getCreature(L, 1);
	if (!creature) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Outfit_t outfit = getOutfit(L, 2);
	int32_t time = getNumber<int32_t>(L, 3);
	pushBoolean(L, Spell::CreateIllusion(creature, outfit, time) == RETURNVALUE_NOERROR);
	return 1;
}


int LuaScriptInterface::luaSetMonsterOutfit(lua_State* L)
{
	//doSetMonsterOutfit(cid, name, time)
	Creature* creature = getCreature(L, 1);
	if (!creature) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	std::string name = getString(L, 2);
	int32_t time = getNumber<int32_t>(L, 3);
	pushBoolean(L, Spell::CreateIllusion(creature, name, time) == RETURNVALUE_NOERROR);
	return 1;
}


int LuaScriptInterface::luaSetItemOutfit(lua_State* L)
{
	//doSetItemOutfit(cid, item, time)
	Creature* creature = getCreature(L, 1);
	if (!creature) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	uint32_t item = getNumber<uint32_t>(L, 2);
	int32_t time = getNumber<int32_t>(L, 3);
	pushBoolean(L, Spell::CreateIllusion(creature, item, time) == RETURNVALUE_NOERROR);
	return 1;
}


int LuaScriptInterface::luaDoMoveCreature(lua_State* L)
{
	//doMoveCreature(cid, direction)
	Creature* creature = getCreature(L, 1);
	if (!creature) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	Direction direction = getNumber<Direction>(L, 2);
	if (direction > DIRECTION_LAST) {
		reportErrorFunc("No valid direction");
		pushBoolean(L, false);
		return 1;
	}

	ReturnValue ret = g_game.internalMoveCreature(creature, direction, FLAG_NOLIMIT);
	lua_pushnumber(L, ret);
	return 1;
}


int LuaScriptInterface::luaGetCombatName(lua_State* L) //pota
{
	//getCombatName(COMBAT_TYPE)
	CombatType_t combatType = getNumber<CombatType_t>(L, 1);
	pushString(L, getCombatName(combatType));
	return 1;
}


int LuaScriptInterface::luaDoSetCreatureLight(lua_State* L)
{
	//doSetCreatureLight(cid, lightLevel, lightColor, time)
	Creature* creature = getCreature(L, 1);
	if (!creature) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_PLAYER_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	uint16_t level = getNumber<uint16_t>(L, 2);
	uint16_t color = getNumber<uint16_t>(L, 3);
	uint32_t time = getNumber<uint32_t>(L, 4);
	Condition* condition = Condition::createCondition(CONDITIONID_COMBAT, CONDITION_LIGHT, time, level | (color << 8));
	creature->addCondition(condition);
	pushBoolean(L, true);
	return 1;
}


int LuaScriptInterface::luaGetCreatureCondition(lua_State* L)
{
	Creature* creature = getCreature(L, 1);
	if (!creature) {
		reportErrorFunc(getErrorDesc(LUA_ERROR_CREATURE_NOT_FOUND));
		pushBoolean(L, false);
		return 1;
	}

	ConditionType_t condition = getNumber<ConditionType_t>(L, 2);
	uint32_t subId = getNumber<uint32_t>(L, 3, 0);
	pushBoolean(L, creature->hasCondition(condition, subId));
	return 1;
}


int LuaScriptInterface::luaCreatureGetCondition(lua_State* L)
{
	// creature:getCondition(conditionType[, conditionId = CONDITIONID_COMBAT[, subId = 0]])
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	ConditionType_t conditionType = getNumber<ConditionType_t>(L, 2);
	ConditionId_t conditionId = getNumber<ConditionId_t>(L, 3, CONDITIONID_COMBAT);
	uint32_t subId = getNumber<uint32_t>(L, 4, 0);

	Condition* condition = creature->getCondition(conditionType, conditionId, subId);
	if (condition) {
		pushUserdata<Condition>(L, condition);
		setWeakMetatable(L, -1, "Condition");
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaCreatureAddCondition(lua_State* L)
{
	// creature:addCondition(condition[, force = false])
	Creature* creature = getUserdata<Creature>(L, 1);
	Condition* condition = getUserdata<Condition>(L, 2);
	if (creature && condition) {
		bool force = getBoolean(L, 3, false);
		pushBoolean(L, creature->addCondition(condition->clone(), force));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaCreatureRemoveCondition(lua_State* L)
{
	// creature:removeCondition(conditionType[, conditionId = CONDITIONID_COMBAT[, subId = 0[, force = false]]])
	Creature* creature = getUserdata<Creature>(L, 1);
	if (!creature) {
		lua_pushnil(L);
		return 1;
	}

	ConditionType_t conditionType = getNumber<ConditionType_t>(L, 2);
	ConditionId_t conditionId = getNumber<ConditionId_t>(L, 3, CONDITIONID_COMBAT);
	uint32_t subId = getNumber<uint32_t>(L, 4, 0);
	Condition* condition = creature->getCondition(conditionType, conditionId, subId);
	if (condition) {
		bool force = getBoolean(L, 5, false);
		creature->removeCondition(condition, force);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


