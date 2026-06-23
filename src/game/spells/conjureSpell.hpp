// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_CONJURESPELL_H_C8393CE45576410DB2E79E4F559960E7
#define FS_CONJURESPELL_H_C8393CE45576410DB2E79E4F559960E7

#include "instantSpell.hpp"

class ConjureSpell final : public InstantSpell
{
	public:
		explicit ConjureSpell(LuaScriptInterface* interface) : InstantSpell(interface) {}

		bool configureEvent(const pugi::xml_node& node) final;
		bool loadFunction(const pugi::xml_attribute& attr) final;

		bool playerCastInstant(Player* player, std::string& param) final;

		bool castSpell(Creature*) final {
			return false;
		}
		bool castSpell(Creature*, Creature*) final {
			return false;
		}

	protected:
		std::string getScriptEventName() const final;

		bool conjureItem(Creature* creature) const;

		uint32_t conjureId = 0;
		uint32_t conjureCount = 1;
		uint32_t reagentId = 0;
};

#endif
