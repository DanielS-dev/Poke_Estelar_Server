// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.h"

#include "guild.h"

#include "../game/game.h"

extern Game g_game;

void Guild::addMember(Player* player)
{
	membersOnline.push_back(player);
	for (Player* member : membersOnline) {
		g_game.updatePlayerHelpers(*member);
	}
}

void Guild::removeMember(Player* player)
{
	membersOnline.remove(player);
	for (Player* member : membersOnline) {
		g_game.updatePlayerHelpers(*member);
	}
	g_game.updatePlayerHelpers(*player);

	if (membersOnline.empty()) {
		g_game.removeGuild(id);
		delete this;
	}
}

GuildRank* Guild::getRankById(uint32_t rankId)
{
	for (auto& rank : ranks) {
		if (rank.id == rankId) {
			return &rank;
		}
	}
	return nullptr;
}

const GuildRank* Guild::getRankByLevel(uint8_t level) const
{
	for (const auto& rank : ranks) {
		if (rank.level == level) {
			return &rank;
		}
	}
	return nullptr;
}

void Guild::addRank(uint32_t rankId, const std::string& rankName, uint8_t level)
{
	ranks.emplace_back(rankId, rankName, level);
}
