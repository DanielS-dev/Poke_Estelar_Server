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

bool Spawn::findPlayer(const Position& pos)
{
	SpectatorVec list;
	g_game.map.getSpectators(list, pos, false, true);
	for (Creature* spectator : list) {
		if (!spectator->getPlayer()->hasFlag(PlayerFlag_IgnoredByMonsters)) {
			return true;
		}
	}
	return false;
}

bool Spawn::spawnMonster(uint32_t spawnId, MonsterType* mType, const Position& pos, Direction dir, bool startup /*= false*/) //pota
{
	std::unique_ptr<Monster> monster_ptr(new Monster(mType, 0, 0)); //pota
	bool result = g_events->eventMonsterOnSpawn(monster_ptr.get(), pos, startup, false);
	if (result) {
		if (startup) {
			//No need to send out events to the surrounding since there is no one out there to listen!
			if (!g_game.internalPlaceCreature(monster_ptr.get(), pos, true)) {
				return false;
			}
		} else {
			if (!g_game.placeCreature(monster_ptr.get(), pos, false, true)) {
				return false;
			}
		}
	}
 
	Monster* monster = monster_ptr.release();
	monster->setDirection(dir);
	monster->setSpawn(this);
	monster->setMasterPos(pos);
	monster->incrementReferenceCounter();
 
	if (result) {
		spawnedMap.insert(spawned_pair(spawnId, monster));
	}
	spawnMap[spawnId].lastSpawn = OTSYS_TIME();
	return result;
}

