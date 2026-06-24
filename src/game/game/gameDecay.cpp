// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../../core/pugicast.hpp"

#include "../../items/items.hpp"
#include "../commands/commands.hpp"
#include "../../entities/creature.hpp"
#include "../../entities/monster.hpp"
#include "../game.hpp"
#include "../../scripting/actions/actions.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../../persistence/market/iomarket.hpp"
#include "../../scripting/talkaction.hpp"
#include "../spells/spells.hpp"
#include "../../config/configmanager.hpp"
#include "../../app/services.hpp"
#include "../../scripting/globalevent.hpp"
#include "../../world/bed.hpp"
#include "../../core/scheduler.hpp"
#include "../../scripting/events/events.hpp"
#include "../../persistence/databasetasks.hpp"
#include "../../core/tools/auths.hpp"
#include "../../core/tools/dateTools.hpp"
#include "../../core/tools/fluidTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/xmlErro.hpp"

extern ConfigManager g_config;
extern Actions* g_actions;
extern Chat* g_chat;
extern TalkActions* g_talkActions;
extern Spells* g_spells;
extern Vocations g_vocations;
extern GlobalEvents* g_globalEvents;
extern Events* g_events;

void Game::startDecay(Item* item)
{
	if (!item || !item->canDecay()) {
		return;
	}

	ItemDecayState_t decayState = item->getDecaying();
	if (decayState == DECAYING_TRUE) {
		return;
	}

	if (item->getDuration() > 0) {
		item->incrementReferenceCounter();
		item->setDecaying(DECAYING_TRUE);
		toDecayItems.push_front(item);
	} else {
		internalDecayItem(item);
	}
}


void Game::internalDecayItem(Item* item)
{
	const ItemType& it = Item::items[item->getID()];
	if (it.decayTo != 0) {
		Item* newItem = transformItem(item, it.decayTo);
		startDecay(newItem);
	} else {
		ReturnValue ret = internalRemoveItem(item);
		if (ret != RETURNVALUE_NOERROR) {
			std::cout << "[Debug - Game::internalDecayItem] internalDecayItem failed, error code: " << static_cast<uint32_t>(ret) << ", item id: " << item->getID() << std::endl;
		}
	}
}


void Game::checkDecay()
{
	g_scheduler.addEvent(createSchedulerTask(EVENT_DECAYINTERVAL, std::bind(&Game::checkDecay, this)));

	size_t bucket = (lastBucket + 1) % EVENT_DECAY_BUCKETS;

	auto it = decayItems[bucket].begin(), end = decayItems[bucket].end();
	while (it != end) {
		Item* item = *it;
		if (!item->canDecay()) {
			item->setDecaying(DECAYING_FALSE);
			ReleaseItem(item);
			it = decayItems[bucket].erase(it);
			continue;
		}

		int32_t duration = item->getDuration();
		int32_t decreaseTime = std::min<int32_t>(EVENT_DECAYINTERVAL * EVENT_DECAY_BUCKETS, duration);

		duration -= decreaseTime;
		item->decreaseDuration(decreaseTime);

		if (duration <= 0) {
			it = decayItems[bucket].erase(it);
			internalDecayItem(item);
			ReleaseItem(item);
		} else if (duration < EVENT_DECAYINTERVAL * EVENT_DECAY_BUCKETS) {
			it = decayItems[bucket].erase(it);
			size_t newBucket = (bucket + ((duration + EVENT_DECAYINTERVAL / 2) / 1000)) % EVENT_DECAY_BUCKETS;
			if (newBucket == bucket) {
				internalDecayItem(item);
				ReleaseItem(item);
			} else {
				decayItems[newBucket].push_back(item);
			}
		} else {
			++it;
		}
	}

	lastBucket = bucket;
	cleanup();
}


