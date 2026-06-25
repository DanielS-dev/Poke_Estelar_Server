// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_PLAYER_TYPES_HPP_4F64609BFD6D46C9B258219A20B4F9E6
#define FS_PLAYER_TYPES_HPP_4F64609BFD6D46C9B258219A20B4F9E6

#include <cstdint>
#include <map>
#include <string>
#include <utility>

class Container;

enum skillsid_t {
	SKILLVALUE_LEVEL = 0,
	SKILLVALUE_TRIES = 1,
	SKILLVALUE_PERCENT = 2,
};

enum playerinfo_t {
	PLAYERINFO_LEVELPERCENT,
	PLAYERINFO_HEALTH,
	PLAYERINFO_MAXHEALTH,
	PLAYERINFO_MANA,
	PLAYERINFO_MAXMANA,
	PLAYERINFO_MAGICLEVEL,
	PLAYERINFO_MAGICLEVELPERCENT,
};

enum chaseMode_t : uint8_t {
	CHASEMODE_STANDSTILL = 0,
	CHASEMODE_FOLLOW = 1,
};

enum fightMode_t : uint8_t {
	FIGHTMODE_ATTACK = 1,
	FIGHTMODE_BALANCED = 2,
	FIGHTMODE_DEFENSE = 3,
};

enum pvpMode_t : uint8_t {
	PVP_MODE_DOVE = 0,
	PVP_MODE_WHITE_HAND = 1,
	PVP_MODE_YELLOW_HAND = 2,
	PVP_MODE_RED_FIST = 3,
};

enum tradestate_t : uint8_t {
	TRADE_NONE,
	TRADE_INITIATED,
	TRADE_ACCEPT,
	TRADE_ACKNOWLEDGE,
	TRADE_TRANSFER,
};

struct VIPEntry {
	VIPEntry(uint32_t guid, std::string name, std::string description, uint32_t icon, bool notify) :
		guid(guid), name(std::move(name)), description(std::move(description)), icon(icon), notify(notify) {}

	uint32_t guid;
	std::string name;
	std::string description;
	uint32_t icon;
	bool notify;
};

struct OpenContainer {
	Container* container;
	uint16_t index;
};

struct OutfitEntry {
	constexpr OutfitEntry(uint16_t lookType, uint8_t addons) : lookType(lookType), addons(addons) {}

	uint16_t lookType;
	uint8_t addons;
};

struct Skill {
	uint64_t tries = 0;
	uint16_t level = 10;
	uint8_t percent = 0;
};

using MuteCountMap = std::map<uint32_t, uint32_t>;

static constexpr int32_t PLAYER_MAX_SPEED = 1500;
static constexpr int32_t PLAYER_MIN_SPEED = 10;

#endif
