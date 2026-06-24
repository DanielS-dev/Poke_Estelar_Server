// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "actions.hpp"
#include "../../world/bed.hpp"
#include "../../config/configmanager.hpp"
#include "../../items/container.hpp"
#include "../../game/game.hpp"
#include "../../core/pugicast.hpp"
#include "../../game/spells/spells.hpp"

extern Game g_game;
extern Spells* g_spells;
extern Actions* g_actions;
extern ConfigManager g_config;

Action::Action(LuaScriptInterface* interface) :
	Event(interface), function(nullptr), allowFarUse(false), checkFloor(true), checkLineOfSight(true) {}

Action::Action(const Action* copy) :
	Event(copy), function(copy->function), allowFarUse(copy->allowFarUse), checkFloor(copy->checkFloor), checkLineOfSight(copy->checkLineOfSight) {}

bool Action::configureEvent(const pugi::xml_node& node)
{
	pugi::xml_attribute allowFarUseAttr = node.attribute("allowfaruse");
	if (allowFarUseAttr) {
		setAllowFarUse(allowFarUseAttr.as_bool());
	}

	pugi::xml_attribute blockWallsAttr = node.attribute("blockwalls");
	if (blockWallsAttr) {
		setCheckLineOfSight(blockWallsAttr.as_bool());
	}

	pugi::xml_attribute checkFloorAttr = node.attribute("checkfloor");
	if (checkFloorAttr) {
		setCheckFloor(checkFloorAttr.as_bool());
	}

	return true;
}

bool Action::loadFunction(const pugi::xml_attribute& attr)
{
	const char* functionName = attr.as_string();
	if (strcasecmp(functionName, "increaseitemid") == 0) {
		function = increaseItemId;
	} else if (strcasecmp(functionName, "decreaseitemid") == 0) {
		function = decreaseItemId;
	} else if (strcasecmp(functionName, "market") == 0) {
		function = enterMarket;
	} else {
		std::cout << "[Warning - Action::loadFunction] Function \"" << functionName << "\" does not exist." << std::endl;
		return false;
	}

	scripted = false;
	return true;
}

std::string Action::getScriptEventName() const
{
	return "onUse";
}

