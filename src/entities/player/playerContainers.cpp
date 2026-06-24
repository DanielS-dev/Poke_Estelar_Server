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

void Player::addContainer(uint8_t cid, Container* container)
{
	if (cid > 0xF) {
		return;
	}

	if (container->getID() == ITEM_BROWSEFIELD) {
		container->incrementReferenceCounter();
	}

	auto it = openContainers.find(cid);
	if (it != openContainers.end()) {
		OpenContainer& openContainer = it->second;
		Container* oldContainer = openContainer.container;
		if (oldContainer->getID() == ITEM_BROWSEFIELD) {
			oldContainer->decrementReferenceCounter();
		}

		openContainer.container = container;
		openContainer.index = 0;
	} else {
		OpenContainer openContainer;
		openContainer.container = container;
		openContainer.index = 0;
		openContainers[cid] = openContainer;
	}
}


void Player::closeContainer(uint8_t cid)
{
	auto it = openContainers.find(cid);
	if (it == openContainers.end()) {
		return;
	}

	OpenContainer openContainer = it->second;
	Container* container = openContainer.container;
	openContainers.erase(it);

	if (container && container->getID() == ITEM_BROWSEFIELD) {
		container->decrementReferenceCounter();
	}
}


void Player::setContainerIndex(uint8_t cid, uint16_t index)
{
	auto it = openContainers.find(cid);
	if (it == openContainers.end()) {
		return;
	}
	it->second.index = index;
}


Container* Player::getContainerByID(uint8_t cid)
{
	auto it = openContainers.find(cid);
	if (it == openContainers.end()) {
		return nullptr;
	}
	return it->second.container;
}

int8_t Player::getContainerID(const Container* container) const
{
	for (const auto& it : openContainers) {
		if (it.second.container == container) {
			return it.first;
		}
	}
	return -1;
}

uint16_t Player::getContainerIndex(uint8_t cid) const
{
	auto it = openContainers.find(cid);
	if (it == openContainers.end()) {
		return 0;
	}
	return it->second.index;
}


bool Player::canOpenCorpse(uint32_t ownerId) const
{
	return getID() == ownerId || (party && party->canOpenCorpse(ownerId));
}

uint16_t Player::getLookCorpse() const
{
	if (sex == PLAYERSEX_FEMALE) {
		return ITEM_FEMALE_CORPSE;
	} else {
		return ITEM_MALE_CORPSE;
	}
}


void Player::sendAddContainerItem(const Container* container, const Item* item)
{
	if (!client) {
		return;
	}

	for (const auto& it : openContainers) {
		const OpenContainer& openContainer = it.second;
		if (openContainer.container != container) {
			continue;
		}

		uint16_t slot = openContainer.index;
		if (container->getID() == ITEM_BROWSEFIELD) {
			uint16_t containerSize = container->size() - 1;
			uint16_t pageEnd = openContainer.index + container->capacity() - 1;
			if (containerSize > pageEnd) {
				slot = pageEnd;
				item = container->getItemByIndex(pageEnd);
			} else {
				slot = containerSize;
			}
		} else if (openContainer.index >= container->capacity()) {
			item = container->getItemByIndex(openContainer.index - 1);
		}
		client->sendAddContainerItem(it.first, slot, item);
	}
}


void Player::sendUpdateContainerItem(const Container* container, uint16_t slot, const Item* newItem)
{
	if (!client) {
		return;
	}

	for (const auto& it : openContainers) {
		const OpenContainer& openContainer = it.second;
		if (openContainer.container != container) {
			continue;
		}

		if (slot < openContainer.index) {
			continue;
		}

		uint16_t pageEnd = openContainer.index + container->capacity();
		if (slot >= pageEnd) {
			continue;
		}

		client->sendUpdateContainerItem(it.first, slot, newItem);
	}
}


void Player::sendRemoveContainerItem(const Container* container, uint16_t slot)
{
	if (!client) {
		return;
	}

	for (auto& it : openContainers) {
		OpenContainer& openContainer = it.second;
		if (openContainer.container != container) {
			continue;
		}

		uint16_t& firstIndex = openContainer.index;
		if (firstIndex > 0 && firstIndex >= container->size() - 1) {
			firstIndex -= container->capacity();
			sendContainer(it.first, container, false, firstIndex);
		}

		client->sendRemoveContainerItem(it.first, std::max<uint16_t>(slot, firstIndex), container->getItemByIndex(container->capacity() + firstIndex));
	}
}


void Player::onAddContainerItem(const Item* item)
{
	checkTradeState(item);
}


void Player::onUpdateContainerItem(const Container* container, const Item* oldItem, const Item* newItem)
{
	if (oldItem != newItem) {
		onRemoveContainerItem(container, oldItem);
	}

	if (tradeState != TRADE_TRANSFER) {
		checkTradeState(oldItem);
	}
}


void Player::onRemoveContainerItem(const Container* container, const Item* item)
{
	if (tradeState != TRADE_TRANSFER) {
		checkTradeState(item);

		if (tradeItem) {
			if (tradeItem->getParent() != container && container->isHoldingItem(tradeItem)) {
				g_game.internalCloseTrade(this);
			}
		}
	}
}


void Player::onCloseContainer(const Container* container)
{
	if (!client) {
		return;
	}

	for (const auto& it : openContainers) {
		if (it.second.container == container) {
			client->sendCloseContainer(it.first);
		}
	}
}


void Player::onSendContainer(const Container* container)
{
	if (!client) {
		return;
	}

	bool hasParent = container->hasParent();
	for (const auto& it : openContainers) {
		const OpenContainer& openContainer = it.second;
		if (openContainer.container == container) {
			client->sendContainer(it.first, container, hasParent, openContainer.index);
		}
	}
}

//inventory

void Player::onUpdateInventoryItem(Item* oldItem, Item* newItem)
{
	if (oldItem != newItem) {
		onRemoveInventoryItem(oldItem);
	}

	if (tradeState != TRADE_TRANSFER) {
		checkTradeState(oldItem);
	}
}


void Player::onRemoveInventoryItem(Item* item)
{
	if (tradeState != TRADE_TRANSFER) {
		checkTradeState(item);

		if (tradeItem) {
			const Container* container = item->getContainer();
			if (container && container->isHoldingItem(tradeItem)) {
				g_game.internalCloseTrade(this);
			}
		}
	}
}


void Player::autoCloseContainers(const Container* container)
{
	std::vector<uint32_t> closeList;
	for (const auto& it : openContainers) {
		Container* tmpContainer = it.second.container;
		while (tmpContainer) {
			if (tmpContainer->isRemoved() || tmpContainer == container) {
				closeList.push_back(it.first);
				break;
			}

			tmpContainer = dynamic_cast<Container*>(tmpContainer->getParent());
		}
	}

	for (uint32_t containerId : closeList) {
		closeContainer(containerId);
		if (client) {
			client->sendCloseContainer(containerId);
		}
	}
}


