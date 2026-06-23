// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <iostream>
#include <string>

#include "weaponWand.hpp"

#include "../core/pugicast.hpp"
#include "../core/tools/random.hpp"
#include "../core/tools/stringsTools.hpp"
#include "../items/items.hpp"

bool WeaponWand::configureEvent(const pugi::xml_node& node)
{
	if (!Weapon::configureEvent(node)) {
		return false;
	}

	pugi::xml_attribute attr;
	if ((attr = node.attribute("min"))) {
		minChange = pugi::cast<int32_t>(attr.value());
	}

	if ((attr = node.attribute("max"))) {
		maxChange = pugi::cast<int32_t>(attr.value());
	}

	if ((attr = node.attribute("type"))) {
		std::string tmpStrValue = asLowerCaseString(attr.as_string());
		if (tmpStrValue == "earth") {
			params.combatType = COMBAT_EARTHDAMAGE;
		} else if (tmpStrValue == "ice") {
			params.combatType = COMBAT_ICEDAMAGE;
		} else if (tmpStrValue == "energy") {
			params.combatType = COMBAT_ENERGYDAMAGE;
		} else if (tmpStrValue == "fire") {
			params.combatType = COMBAT_FIREDAMAGE;
		} else if (tmpStrValue == "death") {
			params.combatType = COMBAT_DEATHDAMAGE;
		} else if (tmpStrValue == "holy") {
			params.combatType = COMBAT_HOLYDAMAGE;
		} else if (tmpStrValue == "none") {
			params.combatType = COMBAT_NONE;
		} else {
			std::cout << "[Warning - WeaponWand::configureEvent] Type \"" << attr.as_string() << "\" does not exist." << std::endl;
		}
	}
	return true;
}

void WeaponWand::configureWeapon(const ItemType& it)
{
	params.distanceEffect = it.shootType;

	Weapon::configureWeapon(it);
}

int32_t WeaponWand::getWeaponDamage(const Player*, const Creature*, const Item*, bool maxDamage /*= false*/) const
{
	if (maxDamage) {
		return -maxChange;
	}
	return -normal_random(minChange, maxChange);
}
