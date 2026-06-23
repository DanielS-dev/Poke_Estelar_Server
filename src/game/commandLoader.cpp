// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "commandLoader.hpp"
#include "commands.hpp"
#include "game.hpp"
#include "../core/pugicast.hpp"
#include "../core/tools/stringsTools.hpp"
#include "../core/tools/xmlErro.hpp"

extern Game g_game;

bool CommandLoader::loadFromXml(Commands& commands)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/commands.xml");
	if (!result) {
		printXMLError("Error - Commands::loadFromXml", "data/XML/commands.xml", result);
		return false;
	}

	for (auto commandNode : doc.child("commands").children()) {
		pugi::xml_attribute cmdAttribute = commandNode.attribute("cmd");
		if (!cmdAttribute) {
			std::cout << "[Warning - Commands::loadFromXml] Missing cmd" << std::endl;
			continue;
		}

		auto it = commands.commandMap.find(cmdAttribute.as_string());
		if (it == commands.commandMap.end()) {
			std::cout << "[Warning - Commands::loadFromXml] Unknown command " << cmdAttribute.as_string() << std::endl;
			continue;
		}

		Command* command = it->second;

		pugi::xml_attribute groupAttribute = commandNode.attribute("group");
		if (groupAttribute) {
			command->groupId = pugi::cast<uint32_t>(groupAttribute.value());
		} else {
			std::cout << "[Warning - Commands::loadFromXml] Missing group for command " << it->first << std::endl;
		}

		pugi::xml_attribute acctypeAttribute = commandNode.attribute("acctype");
		if (acctypeAttribute) {
			command->accountType = static_cast<AccountType_t>(pugi::cast<uint32_t>(acctypeAttribute.value()));
		} else {
			std::cout << "[Warning - Commands::loadFromXml] Missing acctype for command " << it->first << std::endl;
		}

		pugi::xml_attribute logAttribute = commandNode.attribute("log");
		if (logAttribute) {
			command->log = booleanString(logAttribute.as_string());
		} else {
			std::cout << "[Warning - Commands::loadFromXml] Missing log for command " << it->first << std::endl;
		}
		g_game.addCommandTag(it->first.front());
	}
	return true;
}
