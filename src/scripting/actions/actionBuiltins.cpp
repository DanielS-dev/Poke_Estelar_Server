// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "actions.hpp"
#include "../../world/bed.hpp"
#include "../../config/configmanager.hpp"
#include "../../items/container.hpp"
#include "../../game/game.hpp"
#include "../../core/pugicast.hpp"
#include "../../game/spells/spells.hpp"

extern Game g_game;
extern Spells* g_spells;
extern Actions* g_actions;
extern ConfigManager g_config;

bool Action::increaseItemId(Player*, Item* item, const Position&, Thing*, const Position&, bool)
{
	g_game.startDecay(g_game.transformItem(item, item->getID() + 1));
	return true;
}

bool Action::decreaseItemId(Player*, Item* item, const Position&, Thing*, const Position&, bool)
{
	g_game.startDecay(g_game.transformItem(item, item->getID() - 1));
	return true;
}

bool Action::enterMarket(Player* player, Item*, const Position&, Thing*, const Position&, bool)
{
	if (player->getLastDepotId() == -1) {
		return false;
	}

	player->sendMarketEnter(player->getLastDepotId());
	return true;
}

