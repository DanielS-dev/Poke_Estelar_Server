// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "outfit.hpp"

#include "../core/logger.hpp"
#include "../core/pugicast.hpp"
#include "../core/tools/systemTools.hpp"
#include "../core/tools/xmlErro.hpp"

bool Outfits::loadFromXml()
{
	uint32_t loadedOutfits = 0;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/outfits.xml");
	if (!result) {
		printXMLError("Error - Outfits::loadFromXml", "data/XML/outfits.xml", result);
		return false;
	}

	for (auto outfitNode : doc.child("outfits").children()) {
		pugi::xml_attribute attr;
		if ((attr = outfitNode.attribute("enabled")) && !attr.as_bool()) {
			continue;
		}

		if (!(attr = outfitNode.attribute("type"))) {
			LOG_WARN("Scripts", "Missing outfit type in data/XML/outfits.xml");
			continue;
		}

		uint16_t type = pugi::cast<uint16_t>(attr.value());
		if (type > PLAYERSEX_LAST) {
			LOG_WARN("Scripts", "Invalid outfit type " + std::to_string(type) + " in data/XML/outfits.xml");
			continue;
		}

		pugi::xml_attribute lookTypeAttribute = outfitNode.attribute("looktype");
		if (!lookTypeAttribute) {
			LOG_WARN("Scripts", "Missing looktype on outfit in data/XML/outfits.xml");
			continue;
		}

		outfits[type].emplace_back(
			outfitNode.attribute("name").as_string(),
			pugi::cast<uint16_t>(lookTypeAttribute.value()),
			outfitNode.attribute("premium").as_bool(),
			outfitNode.attribute("unlocked").as_bool(true)
		);
		++loadedOutfits;
	}
	LOG_INFO("Scripts", "Loaded " + std::to_string(loadedOutfits) + " outfits from data/XML/outfits.xml");
	return true;
}

const Outfit* Outfits::getOutfitByLookType(PlayerSex_t sex, uint16_t lookType) const
{
	for (const Outfit& outfit : outfits[sex]) {
		if (outfit.lookType == lookType) {
			return &outfit;
		}
	}
	return nullptr;
}
