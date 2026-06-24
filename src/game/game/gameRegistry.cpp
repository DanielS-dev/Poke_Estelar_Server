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

void Game::addPlayer(Player* player)
{
	const std::string& lowercase_name = asLowerCaseString(player->getName());
	mappedPlayerNames[lowercase_name] = player;
	wildcardTree.insert(lowercase_name);
	players[player->getID()] = player;
}


void Game::removePlayer(Player* player)
{
	const std::string& lowercase_name = asLowerCaseString(player->getName());
	mappedPlayerNames.erase(lowercase_name);
	wildcardTree.remove(lowercase_name);
	players.erase(player->getID());
}


void Game::addNpc(Npc* npc)
{
	npcs[npc->getID()] = npc;
}


void Game::removeNpc(Npc* npc)
{
	npcs.erase(npc->getID());
}


void Game::addMonster(Monster* monster)
{
	monsters[monster->getID()] = monster;
}


void Game::removeMonster(Monster* monster)
{
	monsters.erase(monster->getID());
}


Guild* Game::getGuild(uint32_t id) const
{
	auto it = guilds.find(id);
	if (it == guilds.end()) {
		return nullptr;
	}
	return it->second;
}


void Game::addGuild(Guild* guild)
{
	guilds[guild->getId()] = guild;
}


void Game::removeGuild(uint32_t guildId)
{
	guilds.erase(guildId);
}


void Game::decreaseBrowseFieldRef(const Position& pos)
{
	Tile* tile = map.getTile(pos.x, pos.y, pos.z);
	if (!tile) {
		return;
	}

	auto it = browseFields.find(tile);
	if (it != browseFields.end()) {
		it->second->decrementReferenceCounter();
	}
}


void Game::internalRemoveItems(std::vector<Item*> itemList, uint32_t amount, bool stackable)
{
	if (stackable) {
		for (Item* item : itemList) {
			if (item->getItemCount() > amount) {
				internalRemoveItem(item, amount);
				break;
			} else {
				amount -= item->getItemCount();
				internalRemoveItem(item);
			}
		}
	} else {
		for (Item* item : itemList) {
			internalRemoveItem(item);
		}
	}
}


BedItem* Game::getBedBySleeper(uint32_t guid) const
{
	auto it = bedSleepersMap.find(guid);
	if (it == bedSleepersMap.end()) {
		return nullptr;
	}
	return it->second;
}


void Game::setBedSleeper(BedItem* bed, uint32_t guid)
{
	bedSleepersMap[guid] = bed;
}


void Game::removeBedSleeper(uint32_t guid)
{
	auto it = bedSleepersMap.find(guid);
	if (it != bedSleepersMap.end()) {
		bedSleepersMap.erase(it);
	}
}


Item* Game::getUniqueItem(uint16_t uniqueId)
{
	auto it = uniqueItems.find(uniqueId);
	if (it == uniqueItems.end()) {
		return nullptr;
	}
	return it->second;
}


bool Game::addUniqueItem(uint16_t uniqueId, Item* item)
{
	auto result = uniqueItems.emplace(uniqueId, item);
	if (!result.second) {
		std::cout << "Duplicate unique id: " << uniqueId << std::endl;
	}
	return result.second;
}


void Game::removeUniqueItem(uint16_t uniqueId)
{
	auto it = uniqueItems.find(uniqueId);
	if (it != uniqueItems.end()) {
		uniqueItems.erase(it);
	}
}

