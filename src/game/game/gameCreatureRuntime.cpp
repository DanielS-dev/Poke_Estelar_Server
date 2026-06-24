// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../../core/pugicast.hpp"

#include "../../items/items.hpp"
#include "../commands/commands.hpp"
#include "../../entities/creature.hpp"
#include "../../entities/monster.hpp"
#include "../game.hpp"
#include "../../scripting/actions/actions.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../../persistence/market/iomarket.hpp"
#include "../../scripting/talkaction.hpp"
#include "../spells/spells.hpp"
#include "../../config/configmanager.hpp"
#include "../../app/services.hpp"
#include "../../scripting/globalevent.hpp"
#include "../../world/bed.hpp"
#include "../../core/scheduler.hpp"
#include "../../scripting/events/events.hpp"
#include "../../persistence/databasetasks.hpp"
#include "../../core/tools/auths.hpp"
#include "../../core/tools/dateTools.hpp"
#include "../../core/tools/fluidTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/xmlErro.hpp"

extern ConfigManager g_config;
extern Actions* g_actions;
extern Chat* g_chat;
extern TalkActions* g_talkActions;
extern Spells* g_spells;
extern Vocations g_vocations;
extern GlobalEvents* g_globalEvents;
extern Events* g_events;

bool Game::canThrowObjectTo(const Position& fromPos, const Position& toPos, bool checkLineOfSight /*= true*/,
                            int32_t rangex /*= Map::maxClientViewportX*/, int32_t rangey /*= Map::maxClientViewportY*/) const
{
	return map.canThrowObjectTo(fromPos, toPos, checkLineOfSight, rangex, rangey);
}


bool Game::isSightClear(const Position& fromPos, const Position& toPos, bool floorCheck) const
{
	return map.isSightClear(fromPos, toPos, floorCheck);
}


bool Game::internalCreatureTurn(Creature* creature, Direction dir)
{
	if (creature->getDirection() == dir) {
		return false;
	}

	creature->setDirection(dir);

	//send to client
	SpectatorVec list;
	map.getSpectators(list, creature->getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendCreatureTurn(creature);
	}
	return true;
}


bool Game::internalCreatureSay(Creature* creature, SpeakClasses type, const std::string& text,
                               bool ghostMode, SpectatorVec* listPtr/* = nullptr*/, const Position* pos/* = nullptr*/)
{
	if (text.empty()) {
		return false;
	}

	if (!pos) {
		pos = &creature->getPosition();
	}

	SpectatorVec list;

	if (!listPtr || listPtr->empty()) {
		// This somewhat complex construct ensures that the cached SpectatorVec
		// is used if available and if it can be used, else a local vector is
		// used (hopefully the compiler will optimize away the construction of
		// the temporary when it's not used).
		if (type != TALKTYPE_YELL && type != TALKTYPE_MONSTER_YELL) {
			map.getSpectators(list, *pos, false, false,
			              Map::maxClientViewportX, Map::maxClientViewportX,
			              Map::maxClientViewportY, Map::maxClientViewportY);
		} else {
			map.getSpectators(list, *pos, true, false, 18, 18, 14, 14);
		}
	} else {
		list = (*listPtr);
	}

	//send to client
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			if (!ghostMode || tmpPlayer->canSeeCreature(creature)) {
				tmpPlayer->sendCreatureSay(creature, type, text, pos);
			}
		}
	}

	//event method
	for (Creature* spectator : list) {
		spectator->onCreatureSay(creature, type, text);
	}
	return true;
}


void Game::checkCreatureWalk(uint32_t creatureId)
{
	Creature* creature = getCreatureByID(creatureId);
	if (creature && creature->getHealth() > 0) {
		creature->onWalk();
		cleanup();
	}
}


void Game::updateCreatureWalk(uint32_t creatureId)
{
	Creature* creature = getCreatureByID(creatureId);
	if (creature && creature->getHealth() > 0) {
		creature->goToFollowCreature();
	}
}


void Game::checkCreatureAttack(uint32_t creatureId)
{
	Creature* creature = getCreatureByID(creatureId);
	if (creature && creature->getHealth() > 0) {
		creature->onAttacking(0);
	}
}


void Game::addCreatureCheck(Creature* creature)
{
	creature->creatureCheck = true;

	if (creature->inCheckCreaturesVector) {
		// already in a vector
		return;
	}

	creature->inCheckCreaturesVector = true;
	checkCreatureLists[uniform_random(0, EVENT_CREATURECOUNT - 1)].push_back(creature);
	creature->incrementReferenceCounter();
}


void Game::removeCreatureCheck(Creature* creature)
{
	if (creature->inCheckCreaturesVector) {
		creature->creatureCheck = false;
	}
}


void Game::checkCreatures(size_t index)
{
	g_scheduler.addEvent(createSchedulerTask(EVENT_CHECK_CREATURE_INTERVAL, std::bind(&Game::checkCreatures, this, (index + 1) % EVENT_CREATURECOUNT)));

	auto& checkCreatureList = checkCreatureLists[index];
	auto it = checkCreatureList.begin(), end = checkCreatureList.end();
	while (it != end) {
		Creature* creature = *it;
		if (creature->creatureCheck) {
			if (creature->getHealth() > 0) {
				creature->onThink(EVENT_CREATURE_THINK_INTERVAL);
				creature->onAttacking(EVENT_CREATURE_THINK_INTERVAL);
				creature->executeConditions(EVENT_CREATURE_THINK_INTERVAL);
			} else {
				creature->onDeath();
			}
			++it;
		} else {
			creature->inCheckCreaturesVector = false;
			it = checkCreatureList.erase(it);
			ReleaseCreature(creature);
		}
	}

	cleanup();
}


void Game::changeSpeed(Creature* creature, int32_t varSpeedDelta)
{
	int32_t varSpeed = creature->getSpeed() - creature->getBaseSpeed();
	varSpeed += varSpeedDelta;

	creature->setSpeed(varSpeed);

	//send to clients
	SpectatorVec list;
	map.getSpectators(list, creature->getPosition(), false, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendChangeSpeed(creature, creature->getStepSpeed());
	}
}


void Game::internalCreatureChangeOutfit(Creature* creature, const Outfit_t& outfit)
{
	if (!g_events->eventCreatureOnChangeOutfit(creature, outfit)) {
		return;
	}

	creature->setCurrentOutfit(outfit);

	if (creature->isInvisible()) {
		return;
	}

	//send to clients
	SpectatorVec list;
	map.getSpectators(list, creature->getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendCreatureChangeOutfit(creature, outfit);
	}
}


void Game::internalCreatureChangeVisible(Creature* creature, bool visible)
{
	//send to clients
	SpectatorVec list;
	map.getSpectators(list, creature->getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendCreatureChangeVisible(creature, visible);
	}
}


void Game::changeLight(const Creature* creature)
{
	//send to clients
	SpectatorVec list;
	map.getSpectators(list, creature->getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendCreatureLight(creature);
	}
}


