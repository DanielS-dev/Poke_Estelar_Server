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

void Player::sendCancelMessage(ReturnValue message) const
{
	sendCancelMessage(getReturnMessage(message));
}


void Player::sendStats()
{
	if (client) {
		client->sendStats();
		lastStatsTrainingTime = getOfflineTrainingTime() / 60 / 1000;
	}
}


void Player::sendPing()
{
	int64_t timeNow = OTSYS_TIME();

	bool hasLostConnection = false;
	if ((timeNow - lastPing) >= 5000) {
		lastPing = timeNow;
		if (client) {
			client->sendPing();
		} else {
			hasLostConnection = true;
		}
	}

	int64_t noPongTime = timeNow - lastPong;
	if ((hasLostConnection || noPongTime >= 7000) && attackedCreature && attackedCreature->getPlayer()) {
		setAttackedCreature(nullptr);
	}

	if (noPongTime >= 60000 && canLogout()) {
		if (g_creatureEvents->playerLogout(this)) {
			if (client) {
				client->logout(true, true);
			} else {
				g_game.removeCreature(this, true);
			}
		}
	}
}


Item* Player::getWriteItem(uint32_t& windowTextId, uint16_t& maxWriteLen)
{
	windowTextId = this->windowTextId;
	maxWriteLen = this->maxWriteLen;
	return writeItem;
}


void Player::setWriteItem(Item* item, uint16_t maxWriteLen /*= 0*/)
{
	windowTextId++;

	if (writeItem) {
		writeItem->decrementReferenceCounter();
	}

	if (item) {
		writeItem = item;
		this->maxWriteLen = maxWriteLen;
		writeItem->incrementReferenceCounter();
	} else {
		writeItem = nullptr;
		this->maxWriteLen = 0;
	}
}


House* Player::getEditHouse(uint32_t& windowTextId, uint32_t& listId)
{
	windowTextId = this->windowTextId;
	listId = this->editListId;
	return editHouse;
}


void Player::setEditHouse(House* house, uint32_t listId /*= 0*/)
{
	windowTextId++;
	editHouse = house;
	editListId = listId;
}


void Player::sendHouseWindow(House* house, uint32_t listId) const
{
	if (!client) {
		return;
	}

	std::string text;
	if (house->getAccessList(listId, text)) {
		client->sendHouseWindow(windowTextId, text);
	}
}

//container

bool Player::hasModalWindowOpen(uint32_t modalWindowId) const
{
	return find(modalWindows.begin(), modalWindows.end(), modalWindowId) != modalWindows.end();
}


void Player::onModalWindowHandled(uint32_t modalWindowId)
{
	modalWindows.remove(modalWindowId);
}


void Player::sendModalWindow(const ModalWindow& modalWindow)
{
	if (!client) {
		return;
	}

	modalWindows.push_front(modalWindow.id);
	client->sendModalWindow(modalWindow);
}


void Player::clearModalWindows()
{
	modalWindows.clear();
}

uint16_t Player::getHelpers() const
{
	uint16_t helpers;

	if (guild && party) {
		std::unordered_set<Player*> helperSet;

		const auto& guildMembers = guild->getMembersOnline();
		helperSet.insert(guildMembers.begin(), guildMembers.end());

		const auto& partyMembers = party->getMembers();
		helperSet.insert(partyMembers.begin(), partyMembers.end());

		const auto& partyInvitees = party->getInvitees();
		helperSet.insert(partyInvitees.begin(), partyInvitees.end());

		helperSet.insert(party->getLeader());

		helpers = helperSet.size();
	} else if (guild) {
		helpers = guild->getMembersOnline().size();
	} else if (party) {
		helpers = party->getMemberCount() + party->getInvitationCount() + 1;
	} else {
		helpers = 0;
	}

	return helpers;
}


void Player::sendClosePrivate(uint16_t channelId)
{
	if (channelId == CHANNEL_GUILD || channelId == CHANNEL_PARTY) {
		g_chat->removeUserFromChannel(*this, channelId);
	}

	if (client) {
		client->sendClosePrivate(channelId);
	}
}

uint64_t Player::getMoney() const
{
	std::vector<const Container*> containers;
	uint64_t moneyCount = 0;

	for (int32_t i = CONST_SLOT_FIRST; i <= CONST_SLOT_LAST; ++i) {
		Item* item = inventory[i];
		if (!item) {
			continue;
		}

		const Container* container = item->getContainer();
		if (container) {
			containers.push_back(container);
		} else {
			moneyCount += item->getWorth();
		}
	}

	size_t i = 0;
	while (i < containers.size()) {
		const Container* container = containers[i++];
		for (const Item* item : container->getItemList()) {
			const Container* tmpContainer = item->getContainer();
			if (tmpContainer) {
				containers.push_back(tmpContainer);
			} else {
				moneyCount += item->getWorth();
			}
		}
	}
	return moneyCount;
}


std::forward_list<Condition*> Player::getMuteConditions() const
{
	std::forward_list<Condition*> muteConditions;
	for (Condition* condition : conditions) {
		if (condition->getTicks() <= 0) {
			continue;
		}

		ConditionType_t type = condition->getType();
		if (type != CONDITION_MUTED && type != CONDITION_CHANNELMUTEDTICKS && type != CONDITION_YELLTICKS) {
			continue;
		}

		muteConditions.push_front(condition);
	}
	return muteConditions;
}


