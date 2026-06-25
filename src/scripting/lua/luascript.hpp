// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_LUASCRIPT_H_5344B2BC907E46E3943EA78574A212D8
#define FS_LUASCRIPT_H_5344B2BC907E46E3943EA78574A212D8

#include <lua.hpp>

#if LUA_VERSION_NUM >= 502
#ifndef LUA_COMPAT_ALL
#ifndef LUA_COMPAT_MODULE
#define luaL_register(L, libname, l) (luaL_newlib(L, l), lua_pushvalue(L, -1), lua_setglobal(L, libname))
#endif
#undef lua_equal
#define lua_equal(L, i1, i2) lua_compare(L, (i1), (i2), LUA_OPEQ)
#endif
#endif

#include "../../persistence/database.hpp"
#include "../../core/enums.hpp"
#include "../../core/position.hpp"

#include "luascript/luaScriptTypes.hpp"
#include "luascript/scriptEnvironment.hpp"

#define reportErrorFunc(a)  reportError(__FUNCTION__, a, true)

enum ErrorCode_t {
	LUA_ERROR_PLAYER_NOT_FOUND,
	LUA_ERROR_CREATURE_NOT_FOUND,
	LUA_ERROR_ITEM_NOT_FOUND,
	LUA_ERROR_THING_NOT_FOUND,
	LUA_ERROR_TILE_NOT_FOUND,
	LUA_ERROR_HOUSE_NOT_FOUND,
	LUA_ERROR_COMBAT_NOT_FOUND,
	LUA_ERROR_CONDITION_NOT_FOUND,
	LUA_ERROR_AREA_NOT_FOUND,
	LUA_ERROR_CONTAINER_NOT_FOUND,
	LUA_ERROR_VARIANT_NOT_FOUND,
	LUA_ERROR_VARIANT_UNKNOWN,
	LUA_ERROR_SPELL_NOT_FOUND,
};

class LuaScriptInterface
{
	public:
#include "luascript/luaScriptInterfacePublic.hpp"

	protected:
#include "luascript/luaScriptInterfaceCore.hpp"
#include "luascript/luaScriptInterfaceLegacy.hpp"
#include "luascript/luaScriptInterfaceGameWorld.hpp"
#include "luascript/luaScriptInterfaceItemCreature.hpp"
#include "luascript/luaScriptInterfacePlayerMonsterNpc.hpp"
#include "luascript/luaScriptInterfaceSocialCombat.hpp"
#include "luascript/luaScriptInterfaceParty.hpp"
#include "luascript/luaScriptInterfacePrivate.hpp"
};

#include "luascript/luaEnvironment.hpp"

extern LuaEnvironment g_luaEnvironment;

#endif
