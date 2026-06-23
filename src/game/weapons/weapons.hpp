// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_WEAPONS_H_69D1993478AA42948E24C0B90B8F5BF5
#define FS_WEAPONS_H_69D1993478AA42948E24C0B90B8F5BF5

#include <cstdint>
#include <map>
#include <string>

#include "../../scripting/baseevents.hpp"
#include "weapon.hpp"
#include "weaponDistance.hpp"
#include "weaponMelee.hpp"
#include "weaponWand.hpp"

class Weapons final : public BaseEvents
{
	public:
		Weapons();
		~Weapons();

		Weapons(const Weapons&) = delete;
		Weapons& operator=(const Weapons&) = delete;

		void loadDefaults();
		const Weapon* getWeapon(const Item* item) const;

		static int32_t getMaxMeleeDamage(int32_t attackSkill, int32_t attackValue);
		static int32_t getMaxWeaponDamage(uint32_t level, int32_t attackSkill, int32_t attackValue, float attackFactor);

	protected:
		void clear() final;
		LuaScriptInterface& getScriptInterface() final;
		std::string getScriptBaseName() const final;
		Event* getEvent(const std::string& nodeName) final;
		bool registerEvent(Event* event, const pugi::xml_node& node) final;

		std::map<uint32_t, Weapon*> weapons;

		LuaScriptInterface scriptInterface { "Weapon Interface" };
};

#endif
