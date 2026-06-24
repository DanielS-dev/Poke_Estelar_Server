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

void Party::updateAllPartyIcons()
{
	for (Player* member : memberList) {
		for (Player* otherMember : memberList) {
			member->sendCreatureShield(otherMember);
		}

		member->sendCreatureShield(leader);
		leader->sendCreatureShield(member);
	}
	leader->sendCreatureShield(leader);
}


void Party::broadcastPartyMessage(MessageClasses msgClass, const std::string& msg, bool sendToInvitations /*= false*/)
{
	for (Player* member : memberList) {
		member->sendTextMessage(msgClass, msg);
	}

	leader->sendTextMessage(msgClass, msg);

	if (sendToInvitations) {
		for (Player* invitee : inviteList) {
			invitee->sendTextMessage(msgClass, msg);
		}
	}
}


void Party::broadcastPartyLoot(const std::string& loot)
{
	leader->sendTextMessage(MESSAGE_INFO_DESCR, loot);

	for (Player* member : memberList) {
		member->sendTextMessage(MESSAGE_INFO_DESCR, loot);
	}
}


