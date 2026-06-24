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

Spawn::~Spawn()
{
	for (const auto& it : spawnedMap) {
		Monster* monster = it.second;
		monster->setSpawn(nullptr);
		monster->decrementReferenceCounter();
	}
}

bool Spawn::isInSpawnZone(const Position& pos)
{
	return Spawns::isInZone(centerPos, radius, pos);
}

bool Spawn::addMonster(const std::string& name, const Position& pos, Direction dir, uint32_t interval)
{
	MonsterType* mType = g_monsters.getMonsterType(name);
	if (!mType) {
		std::cout << "[Spawn::addMonster] Can not find " << name << std::endl;
		return false;
	}

	this->interval = std::min(this->interval, interval);

	spawnBlock_t sb;
	sb.mType = mType;
	sb.pos = pos;
	sb.direction = dir;
	sb.interval = interval;
	sb.lastSpawn = 0;

	uint32_t spawnId = spawnMap.size() + 1;
	spawnMap[spawnId] = sb;
	return true;
}

void Spawn::removeMonster(Monster* monster)
{
	for (auto it = spawnedMap.begin(), end = spawnedMap.end(); it != end; ++it) {
		if (it->second == monster) {
			monster->decrementReferenceCounter();
			spawnedMap.erase(it);
			break;
		}
	}
}

