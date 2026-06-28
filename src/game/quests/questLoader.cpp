// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <cstdint>
#include <string>

#include "questLoader.hpp"
#include "quests.hpp"

#include "../../core/logger.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/xmlErro.hpp"

bool QuestLoader::loadFromXml(Quests& quests)
{
	uint32_t loadedQuests = 0;
	uint32_t loadedMissions = 0;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/quests.xml");
	if (!result) {
		printXMLError("Error - Quests::loadFromXml", "data/XML/quests.xml", result);
		return false;
	}

	uint16_t id = 0;
	for (auto questNode : doc.child("quests").children()) {
		quests.quests.emplace_back(
			questNode.attribute("name").as_string(),
			++id,
			pugi::cast<int32_t>(questNode.attribute("startstorageid").value()),
			pugi::cast<int32_t>(questNode.attribute("startstoragevalue").value())
		);
		Quest& quest = quests.quests.back();
		++loadedQuests;

		for (auto missionNode : questNode.children()) {
			std::string mainDescription = missionNode.attribute("description").as_string();

			quest.missions.emplace_back(
				missionNode.attribute("name").as_string(),
				pugi::cast<int32_t>(missionNode.attribute("storageid").value()),
				pugi::cast<int32_t>(missionNode.attribute("startvalue").value()),
				pugi::cast<int32_t>(missionNode.attribute("endvalue").value()),
				missionNode.attribute("ignoreendvalue").as_bool()
			);
			Mission& mission = quest.missions.back();
			++loadedMissions;

			if (mainDescription.empty()) {
				for (auto missionStateNode : missionNode.children()) {
					int32_t missionId = pugi::cast<int32_t>(missionStateNode.attribute("id").value());
					mission.descriptions.emplace(missionId, missionStateNode.attribute("description").as_string());
				}
			} else {
				mission.mainDescription = mainDescription;
			}
		}
	}
	LOG_INFO("Scripts", "Loaded " + std::to_string(loadedQuests) + " quests and " + std::to_string(loadedMissions) + " missions from data/XML/quests.xml");
	return true;
}
