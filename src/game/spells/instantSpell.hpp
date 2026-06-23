// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_INSTANTSPELL_H_FD451972554341E19D1193C4B0E2869A
#define FS_INSTANTSPELL_H_FD451972554341E19D1193C4B0E2869A

#include "spell.hpp"
#include "../../scripting/talkaction.hpp"

class House;

class InstantSpell;

typedef bool (InstantSpellFunction)(const InstantSpell* spell, Creature* creature, const std::string& param);

class InstantSpell : public TalkAction, public Spell
{
	public:
		explicit InstantSpell(LuaScriptInterface* interface) : TalkAction(interface) {}

		bool configureEvent(const pugi::xml_node& node) override;
		bool loadFunction(const pugi::xml_attribute& attr) override;

		virtual bool playerCastInstant(Player* player, std::string& param);

		bool castSpell(Creature* creature) override;
		bool castSpell(Creature* creature, Creature* target) override;

		//scripting
		bool executeCastSpell(Creature* creature, const LuaVariant& var);

		bool isInstant() const final {
			return true;
		}
		bool getHasParam() const {
			return hasParam;
		}
		bool getHasPlayerNameParam() const {
			return hasPlayerNameParam;
		}
		bool canCast(const Player* player) const;
		bool canThrowSpell(const Creature* creature, const Creature* target) const;

	protected:
		std::string getScriptEventName() const override;

		static InstantSpellFunction HouseGuestList;
		static InstantSpellFunction HouseSubOwnerList;
		static InstantSpellFunction HouseDoorList;
		static InstantSpellFunction HouseKick;
		static InstantSpellFunction SearchPlayer;
		static InstantSpellFunction SummonMonster;
		static InstantSpellFunction Levitate;
		static InstantSpellFunction Illusion;

		static House* getHouseFromPos(Creature* creature);

		bool internalCastSpell(Creature* creature, const LuaVariant& var);

		InstantSpellFunction* function = nullptr;

		bool needDirection = false;
		bool hasParam = false;
		bool hasPlayerNameParam = false;
		bool checkLineOfSight = true;
		bool casterTargetOrDirection = false;
};

#endif
