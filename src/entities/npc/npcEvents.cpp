// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../npc.hpp"

#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern LuaEnvironment g_luaEnvironment;

void Npc::onCreatureAppear(Creature* creature, bool isLogin)
{
	Creature::onCreatureAppear(creature, isLogin);

	if (creature == this) {
		if (walkTicks > 0) {
			addEventWalk();
		}

		if (npcEventHandler) {
			npcEventHandler->onCreatureAppear(creature);
		}
	} else if (creature->getPlayer()) {
		if (npcEventHandler) {
			npcEventHandler->onCreatureAppear(creature);
		}
	}
}

void Npc::onRemoveCreature(Creature* creature, bool isLogout)
{
	Creature::onRemoveCreature(creature, isLogout);

	if (creature == this) {
		closeAllShopWindows();
		if (npcEventHandler) {
			npcEventHandler->onCreatureDisappear(creature);
		}
	} else if (creature->getPlayer()) {
		if (npcEventHandler) {
			npcEventHandler->onCreatureDisappear(creature);
		}
	}
}

void Npc::onCreatureMove(Creature* creature, const Tile* newTile, const Position& newPos,
                         const Tile* oldTile, const Position& oldPos, bool teleport)
{
	Creature::onCreatureMove(creature, newTile, newPos, oldTile, oldPos, teleport);

	if (creature == this || creature->getPlayer()) {
		if (npcEventHandler) {
			npcEventHandler->onCreatureMove(creature, oldPos, newPos);
		}
	}
}

void Npc::onCreatureSay(Creature* creature, SpeakClasses type, const std::string& text)
{
	if (creature->getID() == id) {
		return;
	}

	//only players for script events
	Player* player = creature->getPlayer();
	if (player) {
		if (npcEventHandler) {
			npcEventHandler->onCreatureSay(player, type, text);
		}
	}
}

void Npc::onPlayerCloseChannel(Player* player)
{
	if (npcEventHandler) {
		npcEventHandler->onPlayerCloseChannel(player);
	}
}

void Npc::onThink(uint32_t interval)
{
	Creature::onThink(interval);

	if (npcEventHandler) {
		npcEventHandler->onThink();
	}

	if (getTimeSinceLastMove() >= walkTicks) {
		addEventWalk();
	}
}

