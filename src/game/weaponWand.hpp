// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_WEAPON_WAND_H_69D1993478AA42948E24C0B90B8F5BF5
#define FS_WEAPON_WAND_H_69D1993478AA42948E24C0B90B8F5BF5

#include "weapon.hpp"

class WeaponWand final : public Weapon
{
	public:
		explicit WeaponWand(LuaScriptInterface* interface) : Weapon(interface) {}

		bool configureEvent(const pugi::xml_node& node) final;
		void configureWeapon(const ItemType& it) final;

		int32_t getWeaponDamage(const Player* player, const Creature* target, const Item* item, bool maxDamage = false) const final;
		int32_t getElementDamage(const Player*, const Creature*, const Item*) const final { return 0; }
		CombatType_t getElementType() const final { return COMBAT_NONE; }

	protected:
		bool getSkillType(const Player*, const Item*, skills_t&, uint32_t&) const final {
			return false;
		}

		int32_t minChange = 0;
		int32_t maxChange = 0;
};

#endif
