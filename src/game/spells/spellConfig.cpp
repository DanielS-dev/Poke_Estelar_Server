// This file is part of The Forgotten Server.

// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../combat/combat.hpp"
#include "../game.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/vocation.hpp"
#include "../../items/items.hpp"

#include "spell.hpp"

extern Game g_game;
extern Vocations g_vocations;
bool Spell::configureSpell(const pugi::xml_node& node)
{
	pugi::xml_attribute nameAttribute = node.attribute("name");
	if (!nameAttribute) {
		std::cout << "[Error - Spell::configureSpell] Spell without name" << std::endl;
		return false;
	}

	name = nameAttribute.as_string();

	static const char* reservedList[] = {
		"melee",
		"physical",
		"poison",
		"fire",
		"energy",
		"drown",
		"lifedrain",
		"manadrain",
		"healing",
		"speed",
		"outfit",
		"invisible",
		"drunk",
		"firefield",
		"poisonfield",
		"energyfield",
		"firecondition",
		"poisoncondition",
		"energycondition",
		"drowncondition",
		"freezecondition",
		"cursecondition",
		"dazzlecondition"
	};

	//static size_t size = sizeof(reservedList) / sizeof(const char*);
	//for (size_t i = 0; i < size; ++i) {
	for (const char* reserved : reservedList) {
		if (strcasecmp(reserved, name.c_str()) == 0) {
			std::cout << "[Error - Spell::configureSpell] Spell is using a reserved name: " << reserved << std::endl;
			return false;
		}
	}

	pugi::xml_attribute attr;
	if ((attr = node.attribute("spellid"))) {
		spellId = pugi::cast<uint16_t>(attr.value());
	}

	if ((attr = node.attribute("group"))) {
		std::string tmpStr = asLowerCaseString(attr.as_string());
		if (tmpStr == "none" || tmpStr == "0") {
			group = SPELLGROUP_NONE;
		} else if (tmpStr == "attack" || tmpStr == "1") {
			group = SPELLGROUP_ATTACK;
		} else if (tmpStr == "healing" || tmpStr == "2") {
			group = SPELLGROUP_HEALING;
		} else if (tmpStr == "support" || tmpStr == "3") {
			group = SPELLGROUP_SUPPORT;
		} else if (tmpStr == "special" || tmpStr == "4") {
			group = SPELLGROUP_SPECIAL;
		} else {
			std::cout << "[Warning - Spell::configureSpell] Unknown group: " << attr.as_string() << std::endl;
		}
	}

	if ((attr = node.attribute("groupcooldown"))) {
		groupCooldown = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("secondarygroup"))) {
		std::string tmpStr = asLowerCaseString(attr.as_string());
		if (tmpStr == "none" || tmpStr == "0") {
			secondaryGroup = SPELLGROUP_NONE;
		} else if (tmpStr == "attack" || tmpStr == "1") {
			secondaryGroup = SPELLGROUP_ATTACK;
		} else if (tmpStr == "healing" || tmpStr == "2") {
			secondaryGroup = SPELLGROUP_HEALING;
		} else if (tmpStr == "support" || tmpStr == "3") {
			secondaryGroup = SPELLGROUP_SUPPORT;
		} else if (tmpStr == "special" || tmpStr == "4") {
			secondaryGroup = SPELLGROUP_SPECIAL;
		} else {
			std::cout << "[Warning - Spell::configureSpell] Unknown secondarygroup: " << attr.as_string() << std::endl;
		}
	}

	if ((attr = node.attribute("secondarygroupcooldown"))) {
		secondaryGroupCooldown = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("lvl"))) {
		level = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("maglv"))) {
		magLevel = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("mana"))) {
		mana = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("manapercent"))) {
		manaPercent = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("soul"))) {
		soul = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("range"))) {
		range = pugi::cast<int32_t>(attr.value());
	}

	if ((attr = node.attribute("exhaustion")) || (attr = node.attribute("cooldown"))) {
		cooldown = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("prem"))) {
		premium = attr.as_bool();
	}

	if ((attr = node.attribute("enabled"))) {
		enabled = attr.as_bool();
	}

	if ((attr = node.attribute("needtarget"))) {
		needTarget = attr.as_bool();
	}

	if ((attr = node.attribute("needweapon"))) {
		needWeapon = attr.as_bool();
	}

	if ((attr = node.attribute("selftarget"))) {
		selfTarget = attr.as_bool();
	}

	if ((attr = node.attribute("needlearn"))) {
		learnable = attr.as_bool();
	}

	if ((attr = node.attribute("blocking"))) {
		blockingSolid = attr.as_bool();
		blockingCreature = blockingSolid;
	}

	if ((attr = node.attribute("blocktype"))) {
		std::string tmpStrValue = asLowerCaseString(attr.as_string());
		if (tmpStrValue == "all") {
			blockingSolid = true;
			blockingCreature = true;
		} else if (tmpStrValue == "solid") {
			blockingSolid = true;
		} else if (tmpStrValue == "creature") {
			blockingCreature = true;
		} else {
			std::cout << "[Warning - Spell::configureSpell] Blocktype \"" << attr.as_string() << "\" does not exist." << std::endl;
		}
	}

	if ((attr = node.attribute("aggressive"))) {
		aggressive = booleanString(attr.as_string());
	}

	if (group == SPELLGROUP_NONE) {
		group = (aggressive ? SPELLGROUP_ATTACK : SPELLGROUP_HEALING);
	}

	for (auto vocationNode : node.children()) {
		if (!(attr = vocationNode.attribute("name"))) {
			continue;
		}

		int32_t vocationId = g_vocations.getVocationId(attr.as_string());
		if (vocationId != -1) {
			attr = vocationNode.attribute("showInDescription");
			vocSpellMap[vocationId] = !attr || attr.as_bool();
		} else {
			std::cout << "[Warning - Spell::configureSpell] Wrong vocation name: " << attr.as_string() << std::endl;
		}
	}
	return true;
}
