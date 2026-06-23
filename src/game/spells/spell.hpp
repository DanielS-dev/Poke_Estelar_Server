// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_SPELL_H_0D5788E0E9414F6DA74917145418A0F4
#define FS_SPELL_H_0D5788E0E9414F6DA74917145418A0F4

#include <map>
#include <string>

#include "../../entities/player.hpp"
#include "../../scripting/luascript.hpp"

typedef std::map<uint16_t, bool> VocSpellMap;

class BaseSpell
{
	public:
		constexpr BaseSpell() = default;
		virtual ~BaseSpell() = default;

		virtual bool castSpell(Creature* creature) = 0;
		virtual bool castSpell(Creature* creature, Creature* target) = 0;
};

class Spell : public BaseSpell
{
	public:
		Spell() = default;

		bool configureSpell(const pugi::xml_node& node);
		const std::string& getName() const {
			return name;
		}

		void postCastSpell(Player* player, bool finishedSpell = true, bool payCost = true) const;
		static void postCastSpell(Player* player, uint32_t manaCost, uint32_t soulCost);

		uint32_t getManaCost(const Player* player) const;
		uint32_t getSoulCost() const {
			return soul;
		}
		uint32_t getLevel() const {
			return level;
		}
		uint32_t getMagicLevel() const {
			return magLevel;
		}
		uint32_t getManaPercent() const {
			return manaPercent;
		}
		bool isPremium() const {
			return premium;
		}

		virtual bool isInstant() const = 0;
		bool isLearnable() const {
			return learnable;
		}

		static ReturnValue CreateIllusion(Creature* creature, const Outfit_t& outfit, int32_t time);
		static ReturnValue CreateIllusion(Creature* creature, const std::string& name, int32_t time);
		static ReturnValue CreateIllusion(Creature* creature, uint32_t itemId, int32_t time);

		const VocSpellMap& getVocMap() const {
			return vocSpellMap;
		}

	protected:
		bool playerSpellCheck(Player* player) const;
		bool playerInstantSpellCheck(Player* player, const Position& toPos);
		bool playerRuneSpellCheck(Player* player, const Position& toPos);

		uint8_t spellId = 0;
		SpellGroup_t group = SPELLGROUP_NONE;
		uint32_t groupCooldown = 1000;
		SpellGroup_t secondaryGroup = SPELLGROUP_NONE;
		uint32_t secondaryGroupCooldown = 0;

		uint32_t mana = 0;
		uint32_t manaPercent = 0;
		uint32_t soul = 0;
		uint32_t cooldown = 1000;
		uint32_t level = 0;
		uint32_t magLevel = 0;
		int32_t range = -1;

		bool needTarget = false;
		bool needWeapon = false;
		bool selfTarget = false;
		bool blockingSolid = false;
		bool blockingCreature = false;
		bool aggressive = true;
		bool learnable = false;
		bool enabled = true;
		bool premium = false;

		VocSpellMap vocSpellMap;

	private:
		std::string name;
};

#endif
