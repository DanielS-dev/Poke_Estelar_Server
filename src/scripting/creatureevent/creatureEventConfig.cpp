// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "creatureevent.hpp"
#include "../../core/tools/systemTools.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/player.hpp"

bool CreatureEvent::configureEvent(const pugi::xml_node& node)
{
	// Name that will be used in monster xml files and
	// lua function to register events to reference this event
	pugi::xml_attribute nameAttribute = node.attribute("name");
	if (!nameAttribute) {
		std::cout << "[Error - CreatureEvent::configureEvent] Missing name for creature event" << std::endl;
		return false;
	}

	eventName = nameAttribute.as_string();

	pugi::xml_attribute typeAttribute = node.attribute("type");
	if (!typeAttribute) {
		std::cout << "[Error - CreatureEvent::configureEvent] Missing type for creature event: " << eventName << std::endl;
		return false;
	}

	std::string tmpStr = asLowerCaseString(typeAttribute.as_string());
	if (tmpStr == "login") {
		type = CREATURE_EVENT_LOGIN;
	} else if (tmpStr == "logout") {
		type = CREATURE_EVENT_LOGOUT;
	} else if (tmpStr == "think") {
		type = CREATURE_EVENT_THINK;
	} else if (tmpStr == "preparedeath") {
		type = CREATURE_EVENT_PREPAREDEATH;
	} else if (tmpStr == "death") {
		type = CREATURE_EVENT_DEATH;
	} else if (tmpStr == "postdeath") { //pota
		type = CREATURE_EVENT_POSTDEATH;
	} else if (tmpStr == "kill") {
		type = CREATURE_EVENT_KILL;
	} else if (tmpStr == "advance") {
		type = CREATURE_EVENT_ADVANCE;
	} else if (tmpStr == "modalwindow") {
		type = CREATURE_EVENT_MODALWINDOW;
	} else if (tmpStr == "textedit") {
		type = CREATURE_EVENT_TEXTEDIT;
	} else if (tmpStr == "healthchange") {
		type = CREATURE_EVENT_HEALTHCHANGE;
	} else if (tmpStr == "manachange") {
		type = CREATURE_EVENT_MANACHANGE;
	} else if (tmpStr == "extendedopcode") {
		type = CREATURE_EVENT_EXTENDED_OPCODE;
	} else if (tmpStr == "move") {
		type = CREATURE_EVENT_MOVE;
	} else {
		std::cout << "[Error - CreatureEvent::configureEvent] Invalid type for creature event: " << eventName << std::endl;
		return false;
	}

	loaded = true;
	return true;
}

std::string CreatureEvent::getScriptEventName() const
{
	//Depending on the type script event name is different
	switch (type) {
		case CREATURE_EVENT_LOGIN:
			return "onLogin";

		case CREATURE_EVENT_LOGOUT:
			return "onLogout";

		case CREATURE_EVENT_THINK:
			return "onThink";

		case CREATURE_EVENT_PREPAREDEATH:
			return "onPrepareDeath";

		case CREATURE_EVENT_DEATH:
			return "onDeath";

		case CREATURE_EVENT_POSTDEATH:
			return "onPostDeath";

		case CREATURE_EVENT_KILL:
			return "onKill";

		case CREATURE_EVENT_ADVANCE:
			return "onAdvance";

		case CREATURE_EVENT_MODALWINDOW:
			return "onModalWindow";

		case CREATURE_EVENT_TEXTEDIT:
			return "onTextEdit";

		case CREATURE_EVENT_HEALTHCHANGE:
			return "onHealthChange";

		case CREATURE_EVENT_MANACHANGE:
			return "onManaChange";

		case CREATURE_EVENT_EXTENDED_OPCODE:
			return "onExtendedOpcode";

		case CREATURE_EVENT_MOVE:
			return "onMove";

		case CREATURE_EVENT_NONE:
		default:
			return std::string();
	}
}

void CreatureEvent::copyEvent(CreatureEvent* creatureEvent)
{
	scriptId = creatureEvent->scriptId;
	scriptInterface = creatureEvent->scriptInterface;
	scripted = creatureEvent->scripted;
	loaded = creatureEvent->loaded;
}

void CreatureEvent::clearEvent()
{
	scriptId = 0;
	scriptInterface = nullptr;
	scripted = false;
	loaded = false;
}

