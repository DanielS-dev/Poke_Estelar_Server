// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_COMBATSPELL_H_89BC92CB8922469D9F0DF33B7069248B
#define FS_COMBATSPELL_H_89BC92CB8922469D9F0DF33B7069248B

#include "spell.hpp"
#include "../../scripting/baseevents.hpp"

class Combat;

class CombatSpell final : public Event, public BaseSpell
{
	public:
		CombatSpell(Combat* combat, bool needTarget, bool needDirection);
		~CombatSpell();

		// non-copyable
		CombatSpell(const CombatSpell&) = delete;
		CombatSpell& operator=(const CombatSpell&) = delete;

		bool castSpell(Creature* creature) final;
		bool castSpell(Creature* creature, Creature* target) final;
		bool configureEvent(const pugi::xml_node&) final {
			return true;
		}

		//scripting
		bool executeCastSpell(Creature* creature, const LuaVariant& var);

		bool loadScriptCombat();
		Combat* getCombat() {
			return combat;
		}

	protected:
		std::string getScriptEventName() const final {
			return "onCastSpell";
		}

		Combat* combat;

		bool needDirection;
		bool needTarget;
};

#endif
