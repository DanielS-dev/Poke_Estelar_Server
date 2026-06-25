// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

// Included inside LuaScriptInterface class declaration by ../luascript.hpp.

		//lua functions
		static int luaDoCreatureCastSpell(lua_State* L); //pota

		static int luaDoCreateItem(lua_State* L);
		static int luaDoCreateItemEx(lua_State* L);
		static int luaDoMoveCreature(lua_State* L);

		static int luaDoPlayerAddItem(lua_State* L);
		static int luaDoTileAddItemEx(lua_State* L);
		static int luaDoSetCreatureLight(lua_State* L);

		static int luaGetCombatName(lua_State* L); //pota

		//get item info
		static int luaGetDepotId(lua_State* L);

		//get creature info functions
		static int luaGetPlayerFlagValue(lua_State* L);
		static int luaGetCreatureCondition(lua_State* L);

		static int luaGetPlayerInstantSpellInfo(lua_State* L);
		static int luaGetPlayerInstantSpellCount(lua_State* L);

		static int luaGetWorldTime(lua_State* L);
		static int luaGetWorldLight(lua_State* L);
		static int luaGetWorldUpTime(lua_State* L);

		//type validation
		static int luaIsDepot(lua_State* L);
		static int luaGetMonstersName(lua_State* L); //pota

		static int luaIsMoveable(lua_State* L);
		static int luaIsValidUID(lua_State* L);

		//container
		static int luaDoAddContainerItem(lua_State* L);

		//
		static int luaCreateCombatArea(lua_State* L);

		static int luaDoAreaCombatHealth(lua_State* L);
		static int luaDoTargetCombatHealth(lua_State* L);

		//
		static int luaDoAreaCombatMana(lua_State* L);
		static int luaDoTargetCombatMana(lua_State* L);

		static int luaDoAreaCombatCondition(lua_State* L);
		static int luaDoTargetCombatCondition(lua_State* L);

		static int luaDoAreaCombatDispel(lua_State* L);
		static int luaDoTargetCombatDispel(lua_State* L);

		static int luaDoChallengeCreature(lua_State* L);

		static int luaSetCreatureOutfit(lua_State* L);
		static int luaSetMonsterOutfit(lua_State* L);
		static int luaSetItemOutfit(lua_State* L);

		static int luaDebugPrint(lua_State* L);
		static int luaIsInArray(lua_State* L);
		static int luaAddEvent(lua_State* L);
		static int luaStopEvent(lua_State* L);

		static int luaSaveServer(lua_State* L);
		static int luaCleanMap(lua_State* L);

		static int luaIsInWar(lua_State* L);

		static int luaGetWaypointPositionByName(lua_State* L);

		static int luaSendChannelMessage(lua_State* L);
		static int luaSendGuildChannelMessage(lua_State* L);

#ifndef LUAJIT_VERSION
		static int luaBitNot(lua_State* L);
		static int luaBitAnd(lua_State* L);
		static int luaBitOr(lua_State* L);
		static int luaBitXor(lua_State* L);
		static int luaBitLeftShift(lua_State* L);
		static int luaBitRightShift(lua_State* L);
#endif

		static int luaConfigManagerGetString(lua_State* L);
		static int luaConfigManagerGetNumber(lua_State* L);
		static int luaConfigManagerGetBoolean(lua_State* L);

		static int luaDatabaseExecute(lua_State* L);
		static int luaDatabaseAsyncExecute(lua_State* L);
		static int luaDatabaseStoreQuery(lua_State* L);
		static int luaDatabaseAsyncStoreQuery(lua_State* L);
		static int luaDatabaseEscapeString(lua_State* L);
		static int luaDatabaseEscapeBlob(lua_State* L);
		static int luaDatabaseLastInsertId(lua_State* L);
		static int luaDatabaseTableExists(lua_State* L);

		static int luaResultGetNumber(lua_State* L);
		static int luaResultGetString(lua_State* L);
		static int luaResultGetStream(lua_State* L);
		static int luaResultNext(lua_State* L);
		static int luaResultFree(lua_State* L);

		// Userdata
		static int luaUserdataCompare(lua_State* L);

		// _G
		static int luaIsType(lua_State* L);
		static int luaRawGetMetatable(lua_State* L);

		// os
		static int luaSystemTime(lua_State* L);

		// table
		static int luaTableCreate(lua_State* L);

