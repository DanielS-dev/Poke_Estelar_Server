// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <algorithm>
#include <iostream>
#include <string>

#include "raidEvent.hpp"

#include "../core/pugicast.hpp"
#include "../core/tools/random.hpp"
#include "../core/tools/stringsTools.hpp"
#include "../entities/monster.hpp"
#include "game.hpp"

extern Game g_game;

bool RaidEvent::configureRaidEvent(const pugi::xml_node& eventNode)
{
	pugi::xml_attribute delayAttribute = eventNode.attribute("delay");
	if (!delayAttribute) {
		std::cout << "[Error] Raid: delay tag missing." << std::endl;
		return false;
	}

	delay = std::max<uint32_t>(RAID_MINTICKS, pugi::cast<uint32_t>(delayAttribute.value()));
	return true;
}

bool AnnounceEvent::configureRaidEvent(const pugi::xml_node& eventNode)
{
	if (!RaidEvent::configureRaidEvent(eventNode)) {
		return false;
	}

	pugi::xml_attribute messageAttribute = eventNode.attribute("message");
	if (!messageAttribute) {
		std::cout << "[Error] Raid: message tag missing for announce event." << std::endl;
		return false;
	}
	message = messageAttribute.as_string();

	pugi::xml_attribute typeAttribute = eventNode.attribute("type");
	if (typeAttribute) {
		std::string tmpStrValue = asLowerCaseString(typeAttribute.as_string());
		if (tmpStrValue == "warning") {
			messageType = MESSAGE_STATUS_WARNING;
		} else if (tmpStrValue == "event") {
			messageType = MESSAGE_EVENT_ADVANCE;
		} else if (tmpStrValue == "default") {
			messageType = MESSAGE_EVENT_DEFAULT;
		} else if (tmpStrValue == "description") {
			messageType = MESSAGE_INFO_DESCR;
		} else if (tmpStrValue == "smallstatus") {
			messageType = MESSAGE_STATUS_SMALL;
		} else if (tmpStrValue == "blueconsole") {
			messageType = MESSAGE_STATUS_CONSOLE_BLUE;
		} else if (tmpStrValue == "redconsole") {
			messageType = MESSAGE_STATUS_CONSOLE_RED;
		} else {
			std::cout << "[Notice] Raid: Unknown type tag missing for announce event. Using default: " << static_cast<uint32_t>(messageType) << std::endl;
		}
	} else {
		messageType = MESSAGE_EVENT_ADVANCE;
		std::cout << "[Notice] Raid: type tag missing for announce event. Using default: " << static_cast<uint32_t>(messageType) << std::endl;
	}
	return true;
}

bool AnnounceEvent::executeEvent()
{
	g_game.broadcastMessage(message, messageType);
	return true;
}

bool SingleSpawnEvent::configureRaidEvent(const pugi::xml_node& eventNode)
{
	if (!RaidEvent::configureRaidEvent(eventNode)) {
		return false;
	}

	pugi::xml_attribute attr;
	if ((attr = eventNode.attribute("name"))) {
		monsterName = attr.as_string();
	} else {
		std::cout << "[Error] Raid: name tag missing for singlespawn event." << std::endl;
		return false;
	}

	if ((attr = eventNode.attribute("x"))) {
		position.x = pugi::cast<uint16_t>(attr.value());
	} else {
		std::cout << "[Error] Raid: x tag missing for singlespawn event." << std::endl;
		return false;
	}

	if ((attr = eventNode.attribute("y"))) {
		position.y = pugi::cast<uint16_t>(attr.value());
	} else {
		std::cout << "[Error] Raid: y tag missing for singlespawn event." << std::endl;
		return false;
	}

	if ((attr = eventNode.attribute("z"))) {
		position.z = pugi::cast<uint16_t>(attr.value());
	} else {
		std::cout << "[Error] Raid: z tag missing for singlespawn event." << std::endl;
		return false;
	}
	return true;
}

bool SingleSpawnEvent::executeEvent()
{
	Monster* monster = Monster::createMonster(monsterName, 0, 0); //pota
	if (!monster) {
		std::cout << "[Error] Raids: Cant create monster " << monsterName << std::endl;
		return false;
	}

	if (!g_game.placeCreature(monster, position, false, true)) {
		delete monster;
		std::cout << "[Error] Raids: Cant place monster " << monsterName << std::endl;
		return false;
	}
	return true;
}

bool AreaSpawnEvent::configureRaidEvent(const pugi::xml_node& eventNode)
{
	if (!RaidEvent::configureRaidEvent(eventNode)) {
		return false;
	}

	pugi::xml_attribute attr;
	if ((attr = eventNode.attribute("radius"))) {
		int32_t radius = pugi::cast<int32_t>(attr.value());
		Position centerPos;

		if ((attr = eventNode.attribute("centerx"))) {
			centerPos.x = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: centerx tag missing for areaspawn event." << std::endl;
			return false;
		}

		if ((attr = eventNode.attribute("centery"))) {
			centerPos.y = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: centery tag missing for areaspawn event." << std::endl;
			return false;
		}

		if ((attr = eventNode.attribute("centerz"))) {
			centerPos.z = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: centerz tag missing for areaspawn event." << std::endl;
			return false;
		}

		fromPos.x = std::max<int32_t>(0, centerPos.getX() - radius);
		fromPos.y = std::max<int32_t>(0, centerPos.getY() - radius);
		fromPos.z = centerPos.z;

		toPos.x = std::min<int32_t>(0xFFFF, centerPos.getX() + radius);
		toPos.y = std::min<int32_t>(0xFFFF, centerPos.getY() + radius);
		toPos.z = centerPos.z;
	} else {
		if ((attr = eventNode.attribute("fromx"))) {
			fromPos.x = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: fromx tag missing for areaspawn event." << std::endl;
			return false;
		}

		if ((attr = eventNode.attribute("fromy"))) {
			fromPos.y = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: fromy tag missing for areaspawn event." << std::endl;
			return false;
		}

		if ((attr = eventNode.attribute("fromz"))) {
			fromPos.z = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: fromz tag missing for areaspawn event." << std::endl;
			return false;
		}

		if ((attr = eventNode.attribute("tox"))) {
			toPos.x = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: tox tag missing for areaspawn event." << std::endl;
			return false;
		}

		if ((attr = eventNode.attribute("toy"))) {
			toPos.y = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: toy tag missing for areaspawn event." << std::endl;
			return false;
		}

		if ((attr = eventNode.attribute("toz"))) {
			toPos.z = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Error] Raid: toz tag missing for areaspawn event." << std::endl;
			return false;
		}
	}

	for (auto monsterNode : eventNode.children()) {
		const char* name;

		if ((attr = monsterNode.attribute("name"))) {
			name = attr.value();
		} else {
			std::cout << "[Error] Raid: name tag missing for monster node." << std::endl;
			return false;
		}

		uint32_t minAmount;
		if ((attr = monsterNode.attribute("minamount"))) {
			minAmount = pugi::cast<uint32_t>(attr.value());
		} else {
			minAmount = 0;
		}

		uint32_t maxAmount;
		if ((attr = monsterNode.attribute("maxamount"))) {
			maxAmount = pugi::cast<uint32_t>(attr.value());
		} else {
			maxAmount = 0;
		}

		if (maxAmount == 0 && minAmount == 0) {
			if ((attr = monsterNode.attribute("amount"))) {
				minAmount = pugi::cast<uint32_t>(attr.value());
				maxAmount = minAmount;
			} else {
				std::cout << "[Error] Raid: amount tag missing for monster node." << std::endl;
				return false;
			}
		}

		spawnList.emplace_back(name, minAmount, maxAmount);
	}
	return true;
}

bool AreaSpawnEvent::executeEvent()
{
	for (const MonsterSpawn& spawn : spawnList) {
		uint32_t amount = uniform_random(spawn.minAmount, spawn.maxAmount);
		for (uint32_t i = 0; i < amount; ++i) {
			Monster* monster = Monster::createMonster(spawn.name, 0, 0); //pota
			if (!monster) {
				std::cout << "[Error - AreaSpawnEvent::executeEvent] Can't create monster " << spawn.name << std::endl;
				return false;
			}

			bool success = false;
			for (int32_t tries = 0; tries < MAXIMUM_TRIES_PER_MONSTER; tries++) {
				Tile* tile = g_game.map.getTile(uniform_random(fromPos.x, toPos.x), uniform_random(fromPos.y, toPos.y), uniform_random(fromPos.z, toPos.z));
				if (tile && !tile->isMoveableBlocking() && !tile->hasFlag(TILESTATE_PROTECTIONZONE) && tile->getTopCreature() == nullptr && g_game.placeCreature(monster, tile->getPosition(), false, true)) {
					success = true;
					break;
				}
			}

			if (!success) {
				delete monster;
			}
		}
	}
	return true;
}

bool ScriptEvent::configureRaidEvent(const pugi::xml_node& eventNode)
{
	if (!RaidEvent::configureRaidEvent(eventNode)) {
		return false;
	}

	pugi::xml_attribute scriptAttribute = eventNode.attribute("script");
	if (!scriptAttribute) {
		std::cout << "Error: [ScriptEvent::configureRaidEvent] No script file found for raid" << std::endl;
		return false;
	}

	if (!loadScript("data/raids/scripts/" + std::string(scriptAttribute.as_string()))) {
		std::cout << "Error: [ScriptEvent::configureRaidEvent] Can not load raid script." << std::endl;
		return false;
	}
	return true;
}

std::string ScriptEvent::getScriptEventName() const
{
	return "onRaid";
}

bool ScriptEvent::executeEvent()
{
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - ScriptEvent::onRaid] Call stack overflow" << std::endl;
		return false;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(scriptId, scriptInterface);

	scriptInterface->pushFunction(scriptId);

	return scriptInterface->callFunction(0);
}
