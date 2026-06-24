// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"

void LuaScriptInterface::registerClass(const std::string& className, const std::string& baseClass, lua_CFunction newFunction/* = nullptr*/)
{
	// className = {}
	lua_newtable(luaState);
	lua_pushvalue(luaState, -1);
	lua_setglobal(luaState, className.c_str());
	int methods = lua_gettop(luaState);

	// methodsTable = {}
	lua_newtable(luaState);
	int methodsTable = lua_gettop(luaState);

	if (newFunction) {
		// className.__call = newFunction
		lua_pushcfunction(luaState, newFunction);
		lua_setfield(luaState, methodsTable, "__call");
	}

	uint32_t parents = 0;
	if (!baseClass.empty()) {
		lua_getglobal(luaState, baseClass.c_str());
		lua_rawgeti(luaState, -1, 'p');
		parents = getNumber<uint32_t>(luaState, -1) + 1;
		lua_pop(luaState, 1);
		lua_setfield(luaState, methodsTable, "__index");
	}

	// setmetatable(className, methodsTable)
	lua_setmetatable(luaState, methods);

	// className.metatable = {}
	luaL_newmetatable(luaState, className.c_str());
	int metatable = lua_gettop(luaState);

	// className.metatable.__metatable = className
	lua_pushvalue(luaState, methods);
	lua_setfield(luaState, metatable, "__metatable");

	// className.metatable.__index = className
	lua_pushvalue(luaState, methods);
	lua_setfield(luaState, metatable, "__index");

	// className.metatable['h'] = hash
	lua_pushnumber(luaState, std::hash<std::string>()(className));
	lua_rawseti(luaState, metatable, 'h');

	// className.metatable['p'] = parents
	lua_pushnumber(luaState, parents);
	lua_rawseti(luaState, metatable, 'p');

	// className.metatable['t'] = type
	if (className == "Item") {
		lua_pushnumber(luaState, LuaData_Item);
	} else if (className == "Container") {
		lua_pushnumber(luaState, LuaData_Container);
	} else if (className == "Teleport") {
		lua_pushnumber(luaState, LuaData_Teleport);
	} else if (className == "Player") {
		lua_pushnumber(luaState, LuaData_Player);
	} else if (className == "Monster") {
		lua_pushnumber(luaState, LuaData_Monster);
	} else if (className == "Npc") {
		lua_pushnumber(luaState, LuaData_Npc);
	} else if (className == "Tile") {
		lua_pushnumber(luaState, LuaData_Tile);
	} else {
		lua_pushnumber(luaState, LuaData_Unknown);
	}
	lua_rawseti(luaState, metatable, 't');

	// pop className, className.metatable
	lua_pop(luaState, 2);
}

void LuaScriptInterface::registerTable(const std::string& tableName)
{
	// _G[tableName] = {}
	lua_newtable(luaState);
	lua_setglobal(luaState, tableName.c_str());
}

void LuaScriptInterface::registerMethod(const std::string& globalName, const std::string& methodName, lua_CFunction func)
{
	// globalName.methodName = func
	lua_getglobal(luaState, globalName.c_str());
	lua_pushcfunction(luaState, func);
	lua_setfield(luaState, -2, methodName.c_str());

	// pop globalName
	lua_pop(luaState, 1);
}

void LuaScriptInterface::registerMetaMethod(const std::string& className, const std::string& methodName, lua_CFunction func)
{
	// className.metatable.methodName = func
	luaL_getmetatable(luaState, className.c_str());
	lua_pushcfunction(luaState, func);
	lua_setfield(luaState, -2, methodName.c_str());

	// pop className.metatable
	lua_pop(luaState, 1);
}

void LuaScriptInterface::registerGlobalMethod(const std::string& functionName, lua_CFunction func)
{
	// _G[functionName] = func
	lua_pushcfunction(luaState, func);
	lua_setglobal(luaState, functionName.c_str());
}

void LuaScriptInterface::registerVariable(const std::string& tableName, const std::string& name, lua_Number value)
{
	// tableName.name = value
	lua_getglobal(luaState, tableName.c_str());
	setField(luaState, name.c_str(), value);

	// pop tableName
	lua_pop(luaState, 1);
}

void LuaScriptInterface::registerGlobalVariable(const std::string& name, lua_Number value)
{
	// _G[name] = value
	lua_pushnumber(luaState, value);
	lua_setglobal(luaState, name.c_str());
}

void LuaScriptInterface::registerGlobalBoolean(const std::string& name, bool value)
{
	// _G[name] = value
	pushBoolean(luaState, value);
	lua_setglobal(luaState, name.c_str());
}

