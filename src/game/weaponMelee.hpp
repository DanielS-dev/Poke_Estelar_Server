// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_WEAPON_MELEE_H_69D1993478AA42948E24C0B90B8F5BF5
#define FS_WEAPON_MELEE_H_69D1993478AA42948E24C0B90B8F5BF5

#include "weapon.hpp"

class WeaponMelee final : public Weapon
{
	public:
		explicit WeaponMelee(LuaScriptInterface* interface);

		void configureWeapon(const ItemType& it) final;

		bool useWeapon(Player* player, Item* item, Creature* target) const final;

		int32_t getWeaponDamage(const Player* player, const Creature* target, const Item* item, bool maxDamage = false) const final;
		int32_t getElementDamage(const Player* player, const Creature* target, const Item* item) const final;
		CombatType_t getElementType() const final { return elementType; }

	protected:
		bool getSkillType(const Player* player, const Item* item, skills_t& skill, uint32_t& skillpoint) const final;

		CombatType_t elementType = COMBAT_NONE;
		uint16_t elementDamage = 0;
};

#endif
