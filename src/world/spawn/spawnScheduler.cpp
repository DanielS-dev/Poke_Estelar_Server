// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../spawn.hpp"

#include "../../config/configmanager.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/scheduler.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../entities/monster.hpp"
#include "../../game/game.hpp"
#include "../../scripting/events/events.hpp"

extern ConfigManager g_config;
extern Monsters g_monsters;
extern Game g_game;
extern Events* g_events;

void Spawn::startSpawnCheck()
{
	if (checkSpawnEvent == 0) {
		checkSpawnEvent = g_scheduler.addEvent(createSchedulerTask(getInterval(), std::bind(&Spawn::checkSpawn, this)));
	}
}

void Spawn::startup()
{
	for (const auto& it : spawnMap) {
		uint32_t spawnId = it.first;
		const spawnBlock_t& sb = it.second;
		spawnMonster(spawnId, sb.mType, sb.pos, sb.direction, true);
	}
}

void Spawn::checkSpawn()
{
	checkSpawnEvent = 0;

	cleanup();

	uint32_t spawnCount = 0;

	for (auto& it : spawnMap) {
		uint32_t spawnId = it.first;
		if (spawnedMap.find(spawnId) != spawnedMap.end()) {
			continue;
		}

		spawnBlock_t& sb = it.second;
		if (OTSYS_TIME() >= sb.lastSpawn + sb.interval) {
			// if (findPlayer(sb.pos)) {
				// sb.lastSpawn = OTSYS_TIME();
				// continue;
			// }

			spawnMonster(spawnId, sb.mType, sb.pos, sb.direction);
			if (++spawnCount >= static_cast<uint32_t>(g_config.getNumber(ConfigManager::RATE_SPAWN))) {
				break;
			}
		}
	}

	if (spawnedMap.size() < spawnMap.size()) {
		checkSpawnEvent = g_scheduler.addEvent(createSchedulerTask(getInterval(), std::bind(&Spawn::checkSpawn, this)));
	}
}

void Spawn::cleanup()
{
	auto it = spawnedMap.begin();
	while (it != spawnedMap.end()) {
		uint32_t spawnId = it->first;
		Monster* monster = it->second;
		if (monster->isRemoved()) {
			if (spawnId != 0) {
				spawnMap[spawnId].lastSpawn = OTSYS_TIME();
			}

			monster->decrementReferenceCounter();
			it = spawnedMap.erase(it);
		} else if (!isInSpawnZone(monster->getPosition()) && spawnId != 0) {
			spawnedMap.insert(spawned_pair(0, monster));
			it = spawnedMap.erase(it);
		} else {
			++it;
		}
	}
}

void Spawn::stopEvent()
{
	if (checkSpawnEvent != 0) {
		g_scheduler.stopEvent(checkSpawnEvent);
		checkSpawnEvent = 0;
	}
}
