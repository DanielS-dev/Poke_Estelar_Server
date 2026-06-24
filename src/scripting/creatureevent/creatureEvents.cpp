// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "creatureevent.hpp"
#include "../../core/tools/systemTools.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/player.hpp"

CreatureEvents::CreatureEvents() :
	scriptInterface("CreatureScript Interface")
{
	scriptInterface.initState();
}

CreatureEvents::~CreatureEvents()
{
	for (const auto& it : creatureEvents) {
		delete it.second;
	}
}

void CreatureEvents::clear()
{
	//clear creature events
	for (const auto& it : creatureEvents) {
		it.second->clearEvent();
	}

	//clear lua state
	scriptInterface.reInitState();
}

LuaScriptInterface& CreatureEvents::getScriptInterface()
{
	return scriptInterface;
}

std::string CreatureEvents::getScriptBaseName() const
{
	return "creaturescripts";
}

Event* CreatureEvents::getEvent(const std::string& nodeName)
{
	if (strcasecmp(nodeName.c_str(), "event") != 0) {
		return nullptr;
	}
	return new CreatureEvent(&scriptInterface);
}

bool CreatureEvents::registerEvent(Event* event, const pugi::xml_node&)
{
	CreatureEvent* creatureEvent = static_cast<CreatureEvent*>(event); //event is guaranteed to be a CreatureEvent
	if (creatureEvent->getEventType() == CREATURE_EVENT_NONE) {
		std::cout << "Error: [CreatureEvents::registerEvent] Trying to register event without type!" << std::endl;
		return false;
	}

	CreatureEvent* oldEvent = getEventByName(creatureEvent->getName(), false);
	if (oldEvent) {
		//if there was an event with the same that is not loaded
		//(happens when realoading), it is reused
		if (!oldEvent->isLoaded() && oldEvent->getEventType() == creatureEvent->getEventType()) {
			oldEvent->copyEvent(creatureEvent);
		}

		return false;
	} else {
		//if not, register it normally
		creatureEvents[creatureEvent->getName()] = creatureEvent;
		return true;
	}
}

CreatureEvent* CreatureEvents::getEventByName(const std::string& name, bool forceLoaded /*= true*/)
{
	auto it = creatureEvents.find(name);
	if (it != creatureEvents.end()) {
		if (!forceLoaded || it->second->isLoaded()) {
			return it->second;
		}
	}
	return nullptr;
}

bool CreatureEvents::playerLogin(Player* player) const
{
	//fire global event if is registered
	for (const auto& it : creatureEvents) {
		if (it.second->getEventType() == CREATURE_EVENT_LOGIN) {
			if (!it.second->executeOnLogin(player)) {
				return false;
			}
		}
	}
	return true;
}

bool CreatureEvents::playerLogout(Player* player) const
{
	//fire global event if is registered
	for (const auto& it : creatureEvents) {
		if (it.second->getEventType() == CREATURE_EVENT_LOGOUT) {
			if (!it.second->executeOnLogout(player)) {
				return false;
			}
		}
	}
	return true;
}

bool CreatureEvents::playerAdvance(Player* player, skills_t skill, uint32_t oldLevel,
                                       uint32_t newLevel)
{
	for (const auto& it : creatureEvents) {
		if (it.second->getEventType() == CREATURE_EVENT_ADVANCE) {
			if (!it.second->executeAdvance(player, skill, oldLevel, newLevel)) {
				return false;
			}
		}
	}
	return true;
}

/////////////////////////////////////

CreatureEvent::CreatureEvent(LuaScriptInterface* interface) :
	Event(interface), type(CREATURE_EVENT_NONE), loaded(false) {}
