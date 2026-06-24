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

bool Party::removeInvite(Player& player, bool removeFromPlayer/* = true*/)
{
	auto it = std::find(inviteList.begin(), inviteList.end(), &player);
	if (it == inviteList.end()) {
		return false;
	}

	inviteList.erase(it);

	leader->sendCreatureShield(&player);
	player.sendCreatureShield(leader);

	if (removeFromPlayer) {
		player.removePartyInvitation(this);
	}

	if (empty()) {
		disband();
	} else {
		for (Player* member : memberList) {
			g_game.updatePlayerHelpers(*member);
		}

		g_game.updatePlayerHelpers(*leader);
	}

	return true;
}


void Party::revokeInvitation(Player& player)
{
	std::ostringstream ss;
	ss << leader->getName() << " has revoked " << (leader->getSex() == PLAYERSEX_FEMALE ? "her" : "his") << " invitation.";
	player.sendTextMessage(MESSAGE_INFO_DESCR, ss.str());

	ss.str(std::string());
	ss << "Invitation for " << player.getName() << " has been revoked.";
	leader->sendTextMessage(MESSAGE_INFO_DESCR, ss.str());

	removeInvite(player);
}


bool Party::invitePlayer(Player& player)
{
	if (isPlayerInvited(&player)) {
		return false;
	}

	std::ostringstream ss;
	ss << player.getName() << " has been invited.";

	if (memberList.empty() && inviteList.empty()) {
		ss << " Open the party channel to communicate with your members.";
		g_game.updatePlayerShield(leader);
		leader->sendCreatureSkull(leader);
	}

	leader->sendTextMessage(MESSAGE_INFO_DESCR, ss.str());

	inviteList.push_back(&player);

	for (Player* member : memberList) {
		g_game.updatePlayerHelpers(*member);
	}
	g_game.updatePlayerHelpers(*leader);

	leader->sendCreatureShield(&player);
	player.sendCreatureShield(leader);

	player.addPartyInvitation(this);

	ss.str(std::string());
	ss << leader->getName() << " has invited you to " << (leader->getSex() == PLAYERSEX_FEMALE ? "her" : "his") << " party.";
	player.sendTextMessage(MESSAGE_INFO_DESCR, ss.str());
	return true;
}


bool Party::isPlayerInvited(const Player* player) const
{
	return std::find(inviteList.begin(), inviteList.end(), player) != inviteList.end();
}


