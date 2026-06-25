// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_LUA_SCRIPT_TYPES_HPP
#define FS_LUA_SCRIPT_TYPES_HPP

class Thing;
class Creature;
class Player;
class Item;
class Container;
class AreaCombat;
class Combat;
class Condition;
class Npc;
class Monster;

enum {
	EVENT_ID_LOADING = 1,
	EVENT_ID_USER = 1000,
};

enum LuaVariantType_t {
	VARIANT_NONE,

	VARIANT_NUMBER,
	VARIANT_POSITION,
	VARIANT_TARGETPOSITION,
	VARIANT_STRING,
};

enum LuaDataType {
	LuaData_Unknown,

	LuaData_Item,
	LuaData_Container,
	LuaData_Teleport,
	LuaData_Player,
	LuaData_Monster,
	LuaData_Npc,
	LuaData_Tile,
};

struct LuaVariant {
	LuaVariantType_t type = VARIANT_NONE;
	std::string text;
	Position pos;
	uint32_t number = 0;
};

struct LuaTimerEventDesc {
	int32_t scriptId = -1;
	int32_t function = -1;
	std::list<int32_t> parameters;
	uint32_t eventId = 0;

	LuaTimerEventDesc() = default;
	LuaTimerEventDesc(LuaTimerEventDesc&& other) = default;
};

class LuaScriptInterface;
class Cylinder;
class Game;
class Npc;

#endif
