// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_WEAPON_H_69D1993478AA42948E24C0B90B8F5BF5
#define FS_WEAPON_H_69D1993478AA42948E24C0B90B8F5BF5

#include <cstdint>
#include <map>
#include <string>

#include "../../core/const.hpp"
#include "../../entities/player.hpp"
#include "../../scripting/baseevents.hpp"
#include "../combat.hpp"

class ItemType;

class Weapon : public Event
{
	public:
		explicit Weapon(LuaScriptInterface* interface) : Event(interface) {}

		bool configureEvent(const pugi::xml_node& node) override;
		bool loadFunction(const pugi::xml_attribute&) final {
			return true;
		}
		virtual void configureWeapon(const ItemType& it);
		virtual bool interruptSwing() const {
			return false;
		}

		int32_t playerWeaponCheck(Player* player, Creature* target, uint8_t shootRange) const;
		static bool useFist(Player* player, Creature* target);
		virtual bool useWeapon(Player* player, Item* item, Creature* target) const;

		virtual int32_t getWeaponDamage(const Player* player, const Creature* target, const Item* item, bool maxDamage = false) const = 0;
		virtual int32_t getElementDamage(const Player* player, const Creature* target, const Item* item) const = 0;
		virtual CombatType_t getElementType() const = 0;

		uint16_t getID() const {
			return id;
		}

		uint32_t getReqLevel() const {
			return level;
		}
		uint32_t getReqMagLv() const {
			return magLevel;
		}
		bool isPremium() const {
			return premium;
		}
		bool isWieldedUnproperly() const {
			return wieldUnproperly;
		}

	protected:
		std::string getScriptEventName() const final;

		bool executeUseWeapon(Player* player, const LuaVariant& var) const;
		void internalUseWeapon(Player* player, Item* item, Creature* target, int32_t damageModifier) const;
		void internalUseWeapon(Player* player, Item* item, Tile* tile) const;

		void onUsedWeapon(Player* player, Item* item, Tile* destTile) const;
		virtual bool getSkillType(const Player*, const Item*, skills_t&, uint32_t&) const {
			return false;
		}

		uint32_t getManaCost(const Player* player) const;

		CombatParams params;

		uint32_t level = 0;
		uint32_t magLevel = 0;
		uint32_t mana = 0;
		uint32_t manaPercent = 0;
		uint32_t soul = 0;
		uint16_t id = 0;
		WeaponAction_t action = WEAPONACTION_NONE;
		uint8_t breakChance = 0;
		bool enabled = true;
		bool premium = false;
		bool wieldUnproperly = false;

	private:
		static void decrementItemCount(Item* item);

		std::map<uint16_t, bool> vocWeaponMap;
		friend class Combat;
};

#endif
