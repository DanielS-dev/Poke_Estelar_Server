// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <cmath>
#include <iostream>

#include "../weapons/weapons.hpp"

#include "../../items/items.hpp"

Weapons::Weapons()
{
	scriptInterface.initState();
}

Weapons::~Weapons()
{
	clear();
}

const Weapon* Weapons::getWeapon(const Item* item) const
{
	if (!item) {
		return nullptr;
	}

	auto it = weapons.find(item->getID());
	if (it == weapons.end()) {
		return nullptr;
	}
	return it->second;
}

void Weapons::clear()
{
	for (const auto& it : weapons) {
		delete it.second;
	}
	weapons.clear();

	scriptInterface.reInitState();
}

LuaScriptInterface& Weapons::getScriptInterface()
{
	return scriptInterface;
}

std::string Weapons::getScriptBaseName() const
{
	return "weapons";
}

void Weapons::loadDefaults()
{
	for (size_t i = 100, size = Item::items.size(); i < size; ++i) {
		const ItemType& it = Item::items.getItemType(i);
		if (it.id == 0 || weapons.find(i) != weapons.end()) {
			continue;
		}

		switch (it.weaponType) {
			case WEAPON_AXE:
			case WEAPON_SWORD:
			case WEAPON_CLUB: {
				WeaponMelee* weapon = new WeaponMelee(&scriptInterface);
				weapon->configureWeapon(it);
				weapons[i] = weapon;
				break;
			}

			case WEAPON_AMMO:
			case WEAPON_DISTANCE: {
				if (it.weaponType == WEAPON_DISTANCE && it.ammoType != AMMO_NONE) {
					continue;
				}

				WeaponDistance* weapon = new WeaponDistance(&scriptInterface);
				weapon->configureWeapon(it);
				weapons[i] = weapon;
				break;
			}

			default:
				break;
		}
	}
}

Event* Weapons::getEvent(const std::string& nodeName)
{
	if (strcasecmp(nodeName.c_str(), "melee") == 0) {
		return new WeaponMelee(&scriptInterface);
	} else if (strcasecmp(nodeName.c_str(), "distance") == 0) {
		return new WeaponDistance(&scriptInterface);
	} else if (strcasecmp(nodeName.c_str(), "wand") == 0) {
		return new WeaponWand(&scriptInterface);
	}
	return nullptr;
}

bool Weapons::registerEvent(Event* event, const pugi::xml_node&)
{
	Weapon* weapon = static_cast<Weapon*>(event);

	auto result = weapons.emplace(weapon->getID(), weapon);
	if (!result.second) {
		std::cout << "[Warning - Weapons::registerEvent] Duplicate registered item with id: " << weapon->getID() << std::endl;
	}
	return result.second;
}

int32_t Weapons::getMaxMeleeDamage(int32_t attackSkill, int32_t attackValue)
{
	return static_cast<int32_t>(std::ceil((attackSkill * (attackValue * 0.05)) + (attackValue * 0.5)));
}

int32_t Weapons::getMaxWeaponDamage(uint32_t level, int32_t attackSkill, int32_t attackValue, float attackFactor)
{
	return static_cast<int32_t>(std::round((level / 5) + (((((attackSkill / 4.) + 1) * (attackValue / 3.)) * 1.03) / attackFactor)));
}
