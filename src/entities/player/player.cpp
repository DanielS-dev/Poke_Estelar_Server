// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <bitset>

#include "../player.hpp"
#include "../../world/bed.hpp"
#include "../../game/chat/chat.hpp"
#include "../../game/combat/combat.hpp"
#include "../../config/configmanager.hpp"
#include "../../scripting/creatureevent/creatureevent.hpp"
#include "../../scripting/events/events.hpp"
#include "../../game/game.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../monster.hpp"
#include "../../game/movement/movement.hpp"
#include "../../core/scheduler.hpp"
#include "../../game/weapons/weapons.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/returnMessageTools.hpp"
#include "../../core/tools/stringsTools.hpp"

extern ConfigManager g_config;
extern Game g_game;
extern Chat* g_chat;
extern Vocations g_vocations;
extern MoveEvents* g_moveEvents;
extern Weapons* g_weapons;
extern CreatureEvents* g_creatureEvents;
extern Events* g_events;

MuteCountMap Player::muteCountMap;

uint32_t Player::playerAutoID = 0x10000000;

Player::Player(ProtocolGame_ptr p) :
	Creature(), lastPing(OTSYS_TIME()), lastPong(lastPing), inbox(new Inbox(ITEM_INBOX)), client(std::move(p))
{
	inbox->incrementReferenceCounter();
}


Player::~Player()
{
	for (Item* item : inventory) {
		if (item) {
			item->setParent(nullptr);
			item->decrementReferenceCounter();
		}
	}

	for (const auto& it : depotLockerMap) {
		it.second->removeInbox(inbox);
		it.second->decrementReferenceCounter();
	}

	inbox->decrementReferenceCounter();

	setWriteItem(nullptr);
	setEditHouse(nullptr);
}


bool Player::setVocation(uint16_t vocId)
{
	Vocation* voc = g_vocations.getVocation(vocId);
	if (!voc) {
		return false;
	}
	vocation = voc;

	Condition* condition = getCondition(CONDITION_REGENERATION, CONDITIONID_DEFAULT);
	if (condition) {
		condition->setParam(CONDITION_PARAM_HEALTHGAIN, vocation->getHealthGainAmount());
		condition->setParam(CONDITION_PARAM_HEALTHTICKS, vocation->getHealthGainTicks() * 1000);
		condition->setParam(CONDITION_PARAM_MANAGAIN, vocation->getManaGainAmount());
		condition->setParam(CONDITION_PARAM_MANATICKS, vocation->getManaGainTicks() * 1000);
	}
	return true;
}


bool Player::isPushable() const
{
	if (hasFlag(PlayerFlag_CannotBePushed)) {
		return false;
	}
	return Creature::isPushable();
}


std::string Player::getDescription(int32_t lookDistance) const
{
	std::ostringstream s;

	if (lookDistance == -1) {
		s << "yourself.";

		if (group->access) {
			s << " You are " << group->name << '.';
		} else if (vocation->getId() != VOCATION_NONE) {
			s << " You are " << vocation->getVocDescription() << '.';
		} else {
			s << " You have no vocation.";
		}
	} else {
		s << name;
		if (!group->access) {
			s << " (Level " << level << ')';
		}
		s << '.';

		if (sex == PLAYERSEX_FEMALE) {
			s << " She";
		} else {
			s << " He";
		}

		if (group->access) {
			s << " is " << group->name << '.';
		} else if (vocation->getId() != VOCATION_NONE) {
			s << " is " << vocation->getVocDescription() << '.';
		} else {
			s << " has no vocation.";
		}
	}

	if (party) {
		if (lookDistance == -1) {
			s << " Your party has ";
		} else if (sex == PLAYERSEX_FEMALE) {
			s << " She is in a party with ";
		} else {
			s << " He is in a party with ";
		}

		size_t memberCount = party->getMemberCount() + 1;
		if (memberCount == 1) {
			s << "1 member and ";
		} else {
			s << memberCount << " members and ";
		}

		size_t invitationCount = party->getInvitationCount();
		if (invitationCount == 1) {
			s << "1 pending invitation.";
		} else {
			s << invitationCount << " pending invitations.";
		}
	}

	if (guild && guildRank) {
		if (lookDistance == -1) {
			s << " You are ";
		} else if (sex == PLAYERSEX_FEMALE) {
			s << " She is ";
		} else {
			s << " He is ";
		}

		s << guildRank->name << " of the " << guild->getName();
		if (!guildNick.empty()) {
			s << " (" << guildNick << ')';
		}

		size_t memberCount = guild->getMemberCount();
		if (memberCount == 1) {
			s << ", which has 1 member, " << guild->getMembersOnline().size() << " of them online.";
		} else {
			s << ", which has " << memberCount << " members, " << guild->getMembersOnline().size() << " of them online.";
		}
	}
	return s.str();
}


