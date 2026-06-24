// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../creature.hpp"

#include "../monster.hpp"
#include "../../config/configmanager.hpp"
#include "../../core/scheduler.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern ConfigManager g_config;
extern CreatureEvents* g_creatureEvents;

void Creature::onThink(uint32_t interval)
{
	if (!isMapLoaded && useCacheMap()) {
		isMapLoaded = true;
		updateMapCache();
	}

	if (followCreature && master != followCreature && !canSeeCreature(followCreature)) {
		onCreatureDisappear(followCreature, false);
	}

	if (attackedCreature && master != attackedCreature && !canSeeCreature(attackedCreature)) {
		onCreatureDisappear(attackedCreature, false);
	}

	blockTicks += interval;
	if (blockTicks >= 1000) {
		blockCount = std::min<uint32_t>(blockCount + 1, 2);
		blockTicks = 0;
	}

	if (followCreature) {
		walkUpdateTicks += interval;
		if (forceUpdateFollowPath || walkUpdateTicks >= 2000) {
			walkUpdateTicks = 0;
			forceUpdateFollowPath = false;
			isUpdatingPath = true;
		}
	}

	if (isUpdatingPath) {
		isUpdatingPath = false;
		goToFollowCreature();
	}

	//scripting event - onThink
	const CreatureEventList& thinkEvents = getCreatureEvents(CREATURE_EVENT_THINK);
	for (CreatureEvent* thinkEvent : thinkEvents) {
		thinkEvent->executeOnThink(this, interval);
	}
}

void Creature::onAttacking(uint32_t interval)
{
	if (!attackedCreature) {
		return;
	}

	onAttacked();
	attackedCreature->onAttacked();

	if (g_game.isSightClear(getPosition(), attackedCreature->getPosition(), true)) {
		doAttacking(interval);
	}
}

void Creature::onIdleStatus()
{
	if (getHealth() > 0) {
		damageMap.clear();
		lastHitCreatureId = 0;
	}
}

