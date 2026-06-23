// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_SPELLS_H_D78A7CCB7080406E8CAA6B1D31D3DA71
#define FS_SPELLS_H_D78A7CCB7080406E8CAA6B1D31D3DA71

#include <map>
#include <string>

#include "combatSpell.hpp"
#include "conjureSpell.hpp"
#include "instantSpell.hpp"
#include "runeSpell.hpp"
#include "spell.hpp"
#include "../../scripting/baseevents.hpp"

class Spells final : public BaseEvents
{
	public:
		Spells();
		~Spells();

		// non-copyable
		Spells(const Spells&) = delete;
		Spells& operator=(const Spells&) = delete;

		Spell* getSpellByName(const std::string& name);
		RuneSpell* getRuneSpell(uint32_t id);
		RuneSpell* getRuneSpellByName(const std::string& name);

		InstantSpell* getInstantSpell(const std::string& words);
		InstantSpell* getInstantSpellByName(const std::string& name);

		uint32_t getInstantSpellCount(const Player* player) const;
		InstantSpell* getInstantSpellByIndex(const Player* player, uint32_t index);

		TalkActionResult_t playerSaySpell(Player* player, std::string& words);

		static Position getCasterPosition(Creature* creature, Direction dir);
		std::string getScriptBaseName() const final;

	protected:
		void clear() final;
		LuaScriptInterface& getScriptInterface() final;
		Event* getEvent(const std::string& nodeName) final;
		bool registerEvent(Event* event, const pugi::xml_node& node) final;

		std::map<uint16_t, RuneSpell*> runes;
		std::map<std::string, InstantSpell*> instants;

		friend class CombatSpell;
		LuaScriptInterface scriptInterface { "Spell Interface" };
};

#endif
