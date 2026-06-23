// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <functional>
#include <iostream>

#include "raids.hpp"

#include "../core/scheduler.hpp"
#include "../core/tools/random.hpp"
#include "../core/tools/stringsTools.hpp"
#include "../core/tools/systemTools.hpp"
#include "raidLoader.hpp"

extern Scheduler g_scheduler;

static constexpr int32_t MAX_RAND_RANGE = 10000000;

Raids::Raids()
{
	scriptInterface.initState();
}

Raids::~Raids()
{
	for (Raid* raid : raidList) {
		delete raid;
	}
}

bool Raids::loadFromXml()
{
	return RaidLoader::loadFromXml(*this);
}

bool Raids::startup()
{
	if (!isLoaded() || isStarted()) {
		return false;
	}

	setLastRaidEnd(OTSYS_TIME());

	checkRaidsEvent = g_scheduler.addEvent(createSchedulerTask(CHECK_RAIDS_INTERVAL * 1000, std::bind(&Raids::checkRaids, this)));

	started = true;
	return started;
}

void Raids::checkRaids()
{
	if (!getRunning()) {
		uint64_t now = OTSYS_TIME();

		for (auto it = raidList.begin(), end = raidList.end(); it != end; ++it) {
			Raid* raid = *it;
			if (now >= (getLastRaidEnd() + raid->getMargin())) {
				if (((MAX_RAND_RANGE * CHECK_RAIDS_INTERVAL) / raid->getInterval()) >= static_cast<uint32_t>(uniform_random(0, MAX_RAND_RANGE))) {
					setRunning(raid);
					raid->startRaid();

					if (!raid->canBeRepeated()) {
						raidList.erase(it);
					}
					break;
				}
			}
		}
	}

	checkRaidsEvent = g_scheduler.addEvent(createSchedulerTask(CHECK_RAIDS_INTERVAL * 1000, std::bind(&Raids::checkRaids, this)));
}

void Raids::clear()
{
	g_scheduler.stopEvent(checkRaidsEvent);
	checkRaidsEvent = 0;

	for (Raid* raid : raidList) {
		raid->stopEvents();
		delete raid;
	}
	raidList.clear();

	loaded = false;
	started = false;
	running = nullptr;
	lastRaidEnd = 0;

	scriptInterface.reInitState();
}

bool Raids::reload()
{
	clear();
	return loadFromXml();
}

Raid* Raids::getRaidByName(const std::string& name)
{
	for (Raid* raid : raidList) {
		if (strcasecmp(raid->getName().c_str(), name.c_str()) == 0) {
			return raid;
		}
	}
	return nullptr;
}
