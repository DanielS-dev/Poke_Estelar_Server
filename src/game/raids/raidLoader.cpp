// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include "raidLoader.hpp"
#include "raids.hpp"

#include "../../core/logger.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/xmlErro.hpp"

bool RaidLoader::loadFromXml(Raids& raids)
{
	if (raids.isLoaded()) {
		return true;
	}

	uint32_t loadedRaids = 0;

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
			LOG_ERROR("Scripts", "Missing raid name in data/raids/raids.xml");
			continue;
		}

		if ((attr = raidNode.attribute("file"))) {
			file = attr.as_string();
		} else {
			std::ostringstream ss;
			ss << "raids/" << name << ".xml";
			file = ss.str();
			LOG_WARN("Scripts", "Missing file tag for raid " + name + ". Using default: " + file);
		}

		interval = pugi::cast<uint32_t>(raidNode.attribute("interval2").value()) * 60;
		if (interval == 0) {
			LOG_ERROR("Scripts", "Missing or zero interval2 for raid " + name);
			continue;
		}

		if ((attr = raidNode.attribute("margin"))) {
			margin = pugi::cast<uint32_t>(attr.value()) * 60 * 1000;
		} else {
			LOG_WARN("Scripts", "Missing margin for raid " + name + ". Using 0.");
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
			++loadedRaids;
		} else {
			LOG_ERROR("Scripts", "Failed to load raid " + name);
			delete newRaid;
		}
	}

	raids.loaded = true;
	LOG_INFO("Scripts", "Loaded " + std::to_string(loadedRaids) + " raids from data/raids/raids.xml");
	return true;
}
