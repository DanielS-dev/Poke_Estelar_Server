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

void Player::addStorageValue(const uint32_t key, const int32_t value, const bool isLogin/* = false*/)
{
	if (IS_IN_KEYRANGE(key, RESERVED_RANGE)) {
		if (IS_IN_KEYRANGE(key, OUTFITS_RANGE)) {
			outfits.emplace_back(
				value >> 16,
				value & 0xFF
			);
			return;
		} else if (IS_IN_KEYRANGE(key, MOUNTS_RANGE)) {
			// do nothing
		} else {
			std::cout << "Warning: unknown reserved key: " << key << " player: " << getName() << std::endl;
			return;
		}
	}

	if (value != -1) {
		int32_t oldValue;
		getStorageValue(key, oldValue);

		storageMap[key] = value;

		if (!isLogin) {
			auto currentFrameTime = g_dispatcher.getDispatcherCycle();
			if (lastQuestlogUpdate != currentFrameTime && g_game.quests.isQuestStorage(key, value, oldValue)) {
				lastQuestlogUpdate = currentFrameTime;
				sendTextMessage(MESSAGE_EVENT_ADVANCE, "Your questlog has been updated.");
			}
		}
	} else {
		storageMap.erase(key);
	}
}


bool Player::getStorageValue(const uint32_t key, int32_t& value) const
{
	auto it = storageMap.find(key);
	if (it == storageMap.end()) {
		value = -1;
		return false;
	}

	value = it->second;
	return true;
}


void Player::onReceiveMail() const
{
	if (isNearDepotBox()) {
		sendTextMessage(MESSAGE_EVENT_ADVANCE, "New mail has arrived.");
	}
}


bool Player::isNearDepotBox() const
{
	const Position& pos = getPosition();
	for (int32_t cx = -1; cx <= 1; ++cx) {
		for (int32_t cy = -1; cy <= 1; ++cy) {
			Tile* tile = g_game.map.getTile(pos.x + cx, pos.y + cy, pos.z);
			if (!tile) {
				continue;
			}

			if (tile->hasFlag(TILESTATE_DEPOT)) {
				return true;
			}
		}
	}
	return false;
}


DepotChest* Player::getDepotChest(uint32_t depotId, bool autoCreate)
{
	auto it = depotChests.find(depotId);
	if (it != depotChests.end()) {
		return it->second;
	}

	if (!autoCreate) {
		return nullptr;
	}

	DepotChest* depotChest = new DepotChest(ITEM_DEPOT);
	depotChest->incrementReferenceCounter();
	depotChest->setMaxDepotItems(getMaxDepotItems());
	depotChests[depotId] = depotChest;
	return depotChest;
}


DepotLocker* Player::getDepotLocker(uint32_t depotId)
{
	auto it = depotLockerMap.find(depotId);
	if (it != depotLockerMap.end()) {
		inbox->setParent(it->second);
		return it->second;
	}

	DepotLocker* depotLocker = new DepotLocker(ITEM_LOCKER1);
	depotLocker->setDepotId(depotId);
	depotLocker->internalAddThing(Item::CreateItem(ITEM_MARKET));
	depotLocker->internalAddThing(inbox);
	depotLocker->internalAddThing(getDepotChest(depotId, true));
	depotLockerMap[depotId] = depotLocker;
	return depotLocker;
}


