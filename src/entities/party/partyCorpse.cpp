// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../party.hpp"
#include "../../game/game.hpp"
#include "../../config/configmanager.hpp"
#include "../../scripting/events/events.hpp"

extern Game g_game;
extern ConfigManager g_config;
extern Events* g_events;

bool Party::canOpenCorpse(uint32_t ownerId) const
{
	if (Player* player = g_game.getPlayerByID(ownerId)) {
		return leader->getID() == ownerId || player->getParty() == this;
	}
	return false;
}

