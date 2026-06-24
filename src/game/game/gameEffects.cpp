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

void Game::addCreatureHealth(const Creature* target)
{
	SpectatorVec list;
	map.getSpectators(list, target->getPosition(), true, true);
	addCreatureHealth(list, target);
}


void Game::addCreatureHealth(const SpectatorVec& list, const Creature* target)
{
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendCreatureHealth(target);
		}
	}
}


void Game::addMagicEffect(const Position& pos, uint16_t effect)
{
	SpectatorVec list;
	map.getSpectators(list, pos, true, true);
	addMagicEffect(list, pos, effect);
}


void Game::addMagicEffect(const SpectatorVec& list, const Position& pos, uint16_t effect)
{
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendMagicEffect(pos, effect);
		}
	}
}


void Game::addDistanceEffect(const Position& fromPos, const Position& toPos, uint8_t effect)
{
	SpectatorVec list;
	map.getSpectators(list, fromPos, false, true);
	map.getSpectators(list, toPos, false, true);
	addDistanceEffect(list, fromPos, toPos, effect);
}


void Game::addDistanceEffect(const SpectatorVec& list, const Position& fromPos, const Position& toPos, uint8_t effect)
{
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendDistanceShoot(fromPos, toPos, effect);
		}
	}
}


