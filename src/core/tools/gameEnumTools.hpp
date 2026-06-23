// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_GAME_ENUM_TOOLS_H_5F9A9742DA194628830AA1C64909AE43
#define FS_GAME_ENUM_TOOLS_H_5F9A9742DA194628830AA1C64909AE43

#include <cstddef>
#include <cstdint>
#include <string>

#include "../const.hpp"
#include "../enums.hpp"

MagicEffectClasses getMagicEffect(const std::string& strValue);
ShootType_t getShootType(const std::string& strValue);
Ammo_t getAmmoType(const std::string& strValue);
WeaponAction_t getWeaponAction(const std::string& strValue);
CombatType_t getCombatType(const std::string& strValue);
Skulls_t getSkullType(const std::string& strValue);
std::string getCombatName(CombatType_t combatType);
std::string getSkillName(uint8_t skillid);
std::string getWeaponName(WeaponType_t weaponType);
size_t combatTypeToIndex(CombatType_t combatType);
CombatType_t indexToCombatType(size_t v);
itemAttrTypes stringToItemAttribute(const std::string& str);

#endif
