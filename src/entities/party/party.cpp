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

Party::Party(Player* leader) : leader(leader)
{
	leader->setParty(this);
}


void Party::disband()
{
	if (!g_events->eventPartyOnDisband(this)) {
		return;
	}

	Player* currentLeader = leader;
	leader = nullptr;

	currentLeader->setParty(nullptr);
	currentLeader->sendClosePrivate(CHANNEL_PARTY);
	g_game.updatePlayerShield(currentLeader);
	g_game.updatePlayerHelpers(*currentLeader);
	currentLeader->sendCreatureSkull(currentLeader);
	currentLeader->sendTextMessage(MESSAGE_INFO_DESCR, "Your party has been disbanded.");

	for (Player* invitee : inviteList) {
		invitee->removePartyInvitation(this);
		currentLeader->sendCreatureShield(invitee);
	}
	inviteList.clear();

	for (Player* member : memberList) {
		member->setParty(nullptr);
		member->sendClosePrivate(CHANNEL_PARTY);
		member->sendTextMessage(MESSAGE_INFO_DESCR, "Your party has been disbanded.");
	}

	for (Player* member : memberList) {
		g_game.updatePlayerShield(member);

		for (Player* otherMember : memberList) {
			otherMember->sendCreatureSkull(member);
		}

		member->sendCreatureSkull(currentLeader);
		currentLeader->sendCreatureSkull(member);
		g_game.updatePlayerHelpers(*member);
	}
	memberList.clear();
	delete this;
}


bool Party::leaveParty(Player* player)
{
	if (!player) {
		return false;
	}

	if (player->getParty() != this && leader != player) {
		return false;
	}

	if (!g_events->eventPartyOnLeave(this, player)) {
		return false;
	}

	bool missingLeader = false;
	if (leader == player) {
		if (!memberList.empty()) {
			if (memberList.size() == 1 && inviteList.empty()) {
				missingLeader = true;
			} else {
				passPartyLeadership(memberList.front());
			}
		} else {
			missingLeader = true;
		}
	}

	//since we already passed the leadership, we remove the player from the list
	auto it = std::find(memberList.begin(), memberList.end(), player);
	if (it != memberList.end()) {
		memberList.erase(it);
	}

	player->setParty(nullptr);
	player->sendClosePrivate(CHANNEL_PARTY);
	g_game.updatePlayerShield(player);
	g_game.updatePlayerHelpers(*player);

	for (Player* member : memberList) {
		member->sendCreatureSkull(player);
		player->sendPlayerPartyIcons(member);
		g_game.updatePlayerHelpers(*member);
	}

	leader->sendCreatureSkull(player);
	player->sendCreatureSkull(player);
	player->sendPlayerPartyIcons(leader);

	player->sendTextMessage(MESSAGE_INFO_DESCR, "You have left the party.");

	updateSharedExperience();
	updateVocationsList();

	clearPlayerPoints(player);

	std::ostringstream ss;
	ss << player->getName() << " has left the party.";
	broadcastPartyMessage(MESSAGE_INFO_DESCR, ss.str());

	if (missingLeader || empty()) {
		disband();
	}

	return true;
}


