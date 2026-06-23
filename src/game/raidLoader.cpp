// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include "raidLoader.hpp"
#include "raids.hpp"

#include "../core/pugicast.hpp"
#include "../core/tools/stringsTools.hpp"
#include "../core/tools/xmlErro.hpp"

bool RaidLoader::loadFromXml(Raids& raids)
{
	if (raids.isLoaded()) {
		return true;
	}

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/raids/raids.xml");
	if (!result) {
		printXMLError("Error - Raids::loadFromXml", "data/raids/raids.xml", result);
		return false;
	}

	for (auto raidNode : doc.child("raids").children()) {
		std::string name, file;
		uint32_t interval, margin;

		pugi::xml_attribute attr;
		if ((attr = raidNode.attribute("name"))) {
			name = attr.as_string();
		} else {
			std::cout << "[Error - Raids::loadFromXml] Name tag missing for raid" << std::endl;
			continue;
		}

		if ((attr = raidNode.attribute("file"))) {
			file = attr.as_string();
		} else {
			std::ostringstream ss;
			ss << "raids/" << name << ".xml";
			file = ss.str();
			std::cout << "[Warning - Raids::loadFromXml] File tag missing for raid " << name << ". Using default: " << file << std::endl;
		}

		interval = pugi::cast<uint32_t>(raidNode.attribute("interval2").value()) * 60;
		if (interval == 0) {
			std::cout << "[Error - Raids::loadFromXml] interval2 tag missing or zero (would divide by 0) for raid: " << name << std::endl;
			continue;
		}

		if ((attr = raidNode.attribute("margin"))) {
			margin = pugi::cast<uint32_t>(attr.value()) * 60 * 1000;
		} else {
			std::cout << "[Warning - Raids::loadFromXml] margin tag missing for raid: " << name << std::endl;
			margin = 0;
		}

		bool repeat;
		if ((attr = raidNode.attribute("repeat"))) {
			repeat = booleanString(attr.as_string());
		} else {
			repeat = false;
		}

		Raid* newRaid = new Raid(name, interval, margin, repeat);
		if (newRaid->loadFromXml("data/raids/" + file)) {
			raids.raidList.push_back(newRaid);
		} else {
			std::cout << "[Error - Raids::loadFromXml] Failed to load raid: " << name << std::endl;
			delete newRaid;
		}
	}

	raids.loaded = true;
	return true;
}
