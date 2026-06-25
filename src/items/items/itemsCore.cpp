// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../items.hpp"
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
	loadFromOtb("data/items/items.otb");

	if (!loadFromXml()) {
		return false;
	}

	g_moveEvents->reload();
	g_weapons->reload();
	g_weapons->loadDefaults();
	return true;
}

