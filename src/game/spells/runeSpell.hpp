// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_RUNESPELL_H_D8852D21136044FDBD5EC9840264CD86
#define FS_RUNESPELL_H_D8852D21136044FDBD5EC9840264CD86

#include "spell.hpp"
#include "../../scripting/actions.hpp"

class RuneSpell;

typedef bool (RuneSpellFunction)(const RuneSpell* spell, Player* player, const Position& posTo);

class RuneSpell final : public Action, public Spell
{
	public:
		explicit RuneSpell(LuaScriptInterface* interface) : Action(interface) {}

		bool configureEvent(const pugi::xml_node& node) final;
		bool loadFunction(const pugi::xml_attribute& attr) final;

		ReturnValue canExecuteAction(const Player* player, const Position& toPos) final;
		bool hasOwnErrorHandler() final {
			return true;
		}
		Thing* getTarget(Player*, Creature* targetCreature, const Position&, uint8_t) const final {
			return targetCreature;
		}

		bool executeUse(Player* player, Item* item, const Position& fromPosition, Thing* target, const Position& toPosition, bool isHotkey) final;

		bool castSpell(Creature* creature) final;
		bool castSpell(Creature* creature, Creature* target) final;

		//scripting
		bool executeCastSpell(Creature* creature, const LuaVariant& var, bool isHotkey);

		bool isInstant() const final {
			return false;
		}
		uint16_t getRuneItemId() const {
			return runeId;
		}

	protected:
		std::string getScriptEventName() const final;

		static RuneSpellFunction Illusion;
		static RuneSpellFunction Convince;

		bool internalCastSpell(Creature* creature, const LuaVariant& var, bool isHotkey);

		RuneSpellFunction* runeFunction = nullptr;
		uint16_t runeId = 0;
		bool hasCharges = true;
};

#endif
