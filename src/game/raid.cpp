// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <algorithm>
#include <functional>

#include "raid.hpp"

#include "../core/pugicast.hpp"
#include "../core/scheduler.hpp"
#include "../core/tools/systemTools.hpp"
#include "../core/tools/xmlErro.hpp"
#include "game.hpp"

extern Game g_game;

Raid::~Raid()
{
	for (RaidEvent* raidEvent : raidEvents) {
		delete raidEvent;
	}
}

bool Raid::loadFromXml(const std::string& filename)
{
	if (isLoaded()) {
		return true;
	}

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.c_str());
	if (!result) {
		printXMLError("Error - Raid::loadFromXml", filename, result);
		return false;
	}

	for (auto eventNode : doc.child("raid").children()) {
		RaidEvent* event;
		if (strcasecmp(eventNode.name(), "announce") == 0) {
			event = new AnnounceEvent();
		} else if (strcasecmp(eventNode.name(), "singlespawn") == 0) {
			event = new SingleSpawnEvent();
		} else if (strcasecmp(eventNode.name(), "areaspawn") == 0) {
			event = new AreaSpawnEvent();
		} else if (strcasecmp(eventNode.name(), "script") == 0) {
			event = new ScriptEvent(&g_game.raids.getScriptInterface());
		} else {
			continue;
		}

		if (event->configureRaidEvent(eventNode)) {
			raidEvents.push_back(event);
		} else {
			std::cout << "[Error - Raid::loadFromXml] In file (" << filename << "), eventNode: " << eventNode.name() << std::endl;
			delete event;
		}
	}

	std::sort(raidEvents.begin(), raidEvents.end(), RaidEvent::compareEvents);

	loaded = true;
	return true;
}

void Raid::startRaid()
{
	RaidEvent* raidEvent = getNextRaidEvent();
	if (raidEvent) {
		state = RAIDSTATE_EXECUTING;
		nextEventEvent = g_scheduler.addEvent(createSchedulerTask(raidEvent->getDelay(), std::bind(&Raid::executeRaidEvent, this, raidEvent)));
	}
}

void Raid::executeRaidEvent(RaidEvent* raidEvent)
{
	if (raidEvent->executeEvent()) {
		nextEvent++;
		RaidEvent* newRaidEvent = getNextRaidEvent();

		if (newRaidEvent) {
			uint32_t ticks = static_cast<uint32_t>(std::max<int32_t>(RAID_MINTICKS, newRaidEvent->getDelay() - raidEvent->getDelay()));
			nextEventEvent = g_scheduler.addEvent(createSchedulerTask(ticks, std::bind(&Raid::executeRaidEvent, this, newRaidEvent)));
		} else {
			resetRaid();
		}
	} else {
		resetRaid();
	}
}

void Raid::resetRaid()
{
	nextEvent = 0;
	state = RAIDSTATE_IDLE;
	g_game.raids.setRunning(nullptr);
	g_game.raids.setLastRaidEnd(OTSYS_TIME());
}

void Raid::stopEvents()
{
	if (nextEventEvent != 0) {
		g_scheduler.stopEvent(nextEventEvent);
		nextEventEvent = 0;
	}
}

RaidEvent* Raid::getNextRaidEvent()
{
	if (nextEvent < raidEvents.size()) {
		return raidEvents[nextEvent];
	}
	return nullptr;
}
