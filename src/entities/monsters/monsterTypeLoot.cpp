// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../monsters.hpp"
#include "../monster.hpp"
#include "../player.hpp"
#include "../../config/configmanager.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/combat/combat.hpp"
#include "../../game/game.hpp"
#include "../../game/spells/spells.hpp"
#include "../../game/weapons/weapons.hpp"

extern Game g_game;
extern Spells* g_spells;
extern Monsters g_monsters;
extern ConfigManager g_config;

uint32_t Monsters::getLootRandom()
{
	return uniform_random(0, MAX_LOOTCHANCE) / g_config.getNumber(ConfigManager::RATE_LOOT);
}

//void MonsterType::createLoot(Container* corpse)
void MonsterType::createLoot(Container* corpse, double bonus) //pota
{
	if (g_config.getNumber(ConfigManager::RATE_LOOT) == 0) {
		corpse->startDecaying();
		return;
	}

	Player* owner = g_game.getPlayerByID(corpse->getCorpseOwner());
	if (!owner || owner->getStaminaMinutes() > 840) {
		for (auto it = info.lootItems.rbegin(), end = info.lootItems.rend(); it != end; ++it) {
//			auto itemList = createLootItem(*it);

			auto itemList = createLootItem(*it, bonus); //pota
			if (itemList.empty()) {
				continue;
			}

			for (Item* item : itemList) {
				//check containers
				if (Container* container = item->getContainer()) {
//					if (!createLootContainer(container, *it)) {
					if (!createLootContainer(container, *it, bonus)) { //pota
						delete container;
						continue;
					}
				}

				if (g_game.internalAddItem(corpse, item) != RETURNVALUE_NOERROR) {
					corpse->internalAddThing(item);
				}
			}
		}

		if (owner) {
			std::ostringstream ss;
			ss << "Loot of " << nameDescription << ": " << corpse->getContentDescription();

			if (owner->getParty()) {
				owner->getParty()->broadcastPartyLoot(ss.str());
			} else {
				owner->sendTextMessage(MESSAGE_LOOT, ss.str());
			}
		}
	} else {
		std::ostringstream ss;
		ss << "Loot of " << nameDescription << ": nothing (due to low stamina)";

		if (owner->getParty()) {
			owner->getParty()->broadcastPartyLoot(ss.str());
		} else {
			owner->sendTextMessage(MESSAGE_LOOT, ss.str());
		}
	}

	corpse->startDecaying();
}

//std::vector<Item*> MonsterType::createLootItem(const LootBlock& lootBlock)
std::vector<Item*> MonsterType::createLootItem(const LootBlock& lootBlock, double bonus) //pota
{
	int32_t itemCount = 0;

	uint32_t randvalue = Monsters::getLootRandom();
	double modifier = randvalue * bonus; //pota
	// make sure no underflow happens
	if (static_cast<int64_t>(randvalue) - modifier < 0) { //pota
		randvalue = 0;
	} else {
		randvalue = randvalue - modifier;
	}
	if (randvalue < lootBlock.chance) {
		if (Item::items[lootBlock.id].stackable) {
			itemCount = randvalue % lootBlock.countmax + 1;
		} else {
			itemCount = 1;
		}
	}

	std::vector<Item*> itemList;
	while (itemCount > 0) {
		uint16_t n = static_cast<uint16_t>(std::min<int32_t>(itemCount, 100));
		Item* tmpItem = Item::CreateItem(lootBlock.id, n);
		if (!tmpItem) {
			break;
		}

		itemCount -= n;

		if (lootBlock.subType != -1) {
			tmpItem->setSubType(lootBlock.subType);
		}

		if (lootBlock.actionId != -1) {
			tmpItem->setActionId(lootBlock.actionId);
		}

		if (!lootBlock.text.empty()) {
			tmpItem->setText(lootBlock.text);
		}

		itemList.push_back(tmpItem);
	}
	return itemList;
}

//bool MonsterType::createLootContainer(Container* parent, const LootBlock& lootblock)
bool MonsterType::createLootContainer(Container* parent, const LootBlock& lootblock, double bonus) //pota
{
	auto it = lootblock.childLoot.begin(), end = lootblock.childLoot.end();
	if (it == end) {
		return true;
	}

	for (; it != end && parent->size() < parent->capacity(); ++it) {
//		auto itemList = createLootItem(*it);
		auto itemList = createLootItem(*it, bonus); //pota
		for (Item* tmpItem : itemList) {
			if (Container* container = tmpItem->getContainer()) {
				if (!createLootContainer(container, *it)) {
					delete container;
				} else {
					parent->internalAddThing(container);
				}
			} else {
				parent->internalAddThing(tmpItem);
			}
		}
	}
	return !parent->empty();
}

