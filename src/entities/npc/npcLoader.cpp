// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../npc.hpp"

#include "../../core/logger.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern LuaEnvironment g_luaEnvironment;

bool Npc::loadFromXml()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.c_str());
	if (!result) {
		printXMLError("Error - Npc::loadFromXml", filename, result);
		return false;
	}

	pugi::xml_node npcNode = doc.child("npc");
	if (!npcNode) {
		LOG_ERROR("Scripts", "Missing npc tag in " + filename);
		return false;
	}

	name = npcNode.attribute("name").as_string();
	attackable = npcNode.attribute("attackable").as_bool();
	floorChange = npcNode.attribute("floorchange").as_bool();

	pugi::xml_attribute attr;
	if ((attr = npcNode.attribute("speed"))) {
		baseSpeed = pugi::cast<uint32_t>(attr.value());
	} else {
		baseSpeed = 100;
	}

	if ((attr = npcNode.attribute("walkinterval"))) {
		walkTicks = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = npcNode.attribute("walkradius"))) {
		masterRadius = pugi::cast<int32_t>(attr.value());
	}

	if ((attr = npcNode.attribute("ignoreheight"))) {
		ignoreHeight = attr.as_bool();
	}

	if ((attr = npcNode.attribute("speechbubble"))) {
		speechBubble = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = npcNode.attribute("skull"))) {
		setSkull(getSkullType(attr.as_string()));
	}

	pugi::xml_node healthNode = npcNode.child("health");
	if (healthNode) {
		if ((attr = healthNode.attribute("now"))) {
			health = pugi::cast<int32_t>(attr.value());
		} else {
			health = 100;
		}

		if ((attr = healthNode.attribute("max"))) {
			healthMax = pugi::cast<int32_t>(attr.value());
		} else {
			healthMax = 100;
		}
	}

	pugi::xml_node lookNode = npcNode.child("look");
	if (lookNode) {
		pugi::xml_attribute lookTypeAttribute = lookNode.attribute("type");
		if (lookTypeAttribute) {
			defaultOutfit.lookType = pugi::cast<uint16_t>(lookTypeAttribute.value());
			defaultOutfit.lookHead = pugi::cast<uint16_t>(lookNode.attribute("head").value());
			defaultOutfit.lookBody = pugi::cast<uint16_t>(lookNode.attribute("body").value());
			defaultOutfit.lookLegs = pugi::cast<uint16_t>(lookNode.attribute("legs").value());
			defaultOutfit.lookFeet = pugi::cast<uint16_t>(lookNode.attribute("feet").value());
			defaultOutfit.lookAddons = pugi::cast<uint16_t>(lookNode.attribute("addons").value());
		} else if ((attr = lookNode.attribute("typeex"))) {
			defaultOutfit.lookTypeEx = pugi::cast<uint16_t>(attr.value());
		}
		defaultOutfit.lookMount = pugi::cast<uint16_t>(lookNode.attribute("mount").value());

		currentOutfit = defaultOutfit;
	}

	for (auto parameterNode : npcNode.child("parameters").children()) {
		parameters[parameterNode.attribute("key").as_string()] = parameterNode.attribute("value").as_string();
	}

	pugi::xml_attribute scriptFile = npcNode.attribute("script");
	if (scriptFile) {
		npcEventHandler = new NpcEventsHandler(scriptFile.as_string(), this);
		if (!npcEventHandler->isLoaded()) {
			delete npcEventHandler;
			npcEventHandler = nullptr;
			return false;
		}
	}
	return true;
}

