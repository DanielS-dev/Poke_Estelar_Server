// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../items.hpp"
#include "../../core/logger.hpp"
#include "../../game/condition/condition.hpp"
#include "../../game/movement/movement.hpp"
#include "../../game/weapons/weapons.hpp"

extern MoveEvents* g_moveEvents;
extern Weapons* g_weapons;

ItemType::ItemType() = default;

ItemType::ItemType(ItemType&& other) noexcept = default;

ItemType& ItemType::operator=(ItemType&& other) noexcept = default;

ItemType::~ItemType() = default;

Items::Items()
{
	items.reserve(30000);
	nameToItems.reserve(30000);
}

Items::~Items() = default;

void Items::clear()
{
	items.clear();
	reverseItemMap.clear();
	nameToItems.clear();
}

bool Items::reload()
{
	clear();
	FILELOADER_ERRORS otbResult = loadFromOtb("data/items/items.otb");
	if (otbResult != ERROR_NONE) {
		LOG_ERROR("Items", "Failed to reload data/items/items.otb. Error code: " + std::to_string(static_cast<int32_t>(otbResult)));
	}

	if (!loadFromXml()) {
		return false;
	}

	g_moveEvents->reload();
	g_weapons->reload();
	g_weapons->loadDefaults();
	LOG_INFO("Items", "Items reload completed.");
	return true;
}

