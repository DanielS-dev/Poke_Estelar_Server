// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.h"

#include "groups.h"

#include "../core/pugicast.h"
#include "../core/tools.h"

bool Groups::load()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/groups.xml");
	if (!result) {
		printXMLError("Error - Groups::load", "data/XML/groups.xml", result);
		return false;
	}

	for (auto groupNode : doc.child("groups").children()) {
		Group group;
		group.id = pugi::cast<uint32_t>(groupNode.attribute("id").value());
		group.name = groupNode.attribute("name").as_string();
		group.flags = pugi::cast<uint64_t>(groupNode.attribute("flags").value());
		group.access = groupNode.attribute("access").as_bool();
		group.maxDepotItems = pugi::cast<uint32_t>(groupNode.attribute("maxdepotitems").value());
		group.maxVipEntries = pugi::cast<uint32_t>(groupNode.attribute("maxvipentries").value());
		groups.push_back(group);
	}
	return true;
}

Group* Groups::getGroup(uint16_t id)
{
	for (Group& group : groups) {
		if (group.id == id) {
			return &group;
		}
	}
	return nullptr;
}
