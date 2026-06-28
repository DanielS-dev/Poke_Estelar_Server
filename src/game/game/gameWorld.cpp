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
#include "../../core/logger.hpp"

extern ConfigManager g_config;
extern Actions* g_actions;
extern Chat* g_chat;
extern TalkActions* g_talkActions;
extern Spells* g_spells;
extern Vocations g_vocations;
extern GlobalEvents* g_globalEvents;
extern Events* g_events;

void Game::addCommandTag(char tag)
{
	for (char commandTag : commandTags) {
		if (commandTag == tag) {
			return;
		}
	}
	commandTags.push_back(tag);
}


void Game::resetCommandTag()
{
	commandTags.clear();
}


void Game::shutdown()
{
	LOG_INFO("Server", "Shutting down game server.");

	g_scheduler.shutdown();
	g_databaseTasks.shutdown();
	g_dispatcher.shutdown();
	map.spawns.clear();
	raids.clear();

	cleanup();

	if (serviceManager) {
		serviceManager->stop();
	}

	ConnectionManager::getInstance().closeAll();

	LOG_INFO("Server", "Game server shutdown complete.");
}


void Game::cleanup()
{
	//free memory
	for (auto creature : ToReleaseCreatures) {
		creature->decrementReferenceCounter();
	}
	ToReleaseCreatures.clear();

	for (auto item : ToReleaseItems) {
		item->decrementReferenceCounter();
	}
	ToReleaseItems.clear();

	for (Item* item : toDecayItems) {
		const uint32_t dur = item->getDuration();
		if (dur >= EVENT_DECAYINTERVAL * EVENT_DECAY_BUCKETS) {
			decayItems[lastBucket].push_back(item);
		} else {
			decayItems[(lastBucket + 1 + dur / 1000) % EVENT_DECAY_BUCKETS].push_back(item);
		}
	}
	toDecayItems.clear();
}


void Game::ReleaseCreature(Creature* creature)
{
	ToReleaseCreatures.push_back(creature);
}


void Game::ReleaseItem(Item* item)
{
	ToReleaseItems.push_back(item);
}


void Game::broadcastMessage(const std::string& text, MessageClasses type) const
{
	LOG_INFO("Game", "Broadcasted message: \"" + text + "\".");
	for (const auto& it : players) {
		it.second->sendTextMessage(type, text);
	}
}


void Game::updateCreatureWalkthrough(const Creature* creature)
{
	//send to clients
	SpectatorVec list;
	map.getSpectators(list, creature->getPosition(), true, true);
	for (Creature* spectator : list) {
		Player* tmpPlayer = spectator->getPlayer();
		tmpPlayer->sendCreatureWalkthrough(creature, tmpPlayer->canWalkthroughEx(creature));
	}
}


void Game::updateCreatureSkull(const Creature* creature)
{
	SpectatorVec list;
	map.getSpectators(list, creature->getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendCreatureSkull(creature);
	}
}


void Game::updatePlayerShield(Player* player)
{
	SpectatorVec list;
	map.getSpectators(list, player->getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendCreatureShield(player);
	}
}


void Game::updatePlayerHelpers(const Player& player)
{
	uint32_t creatureId = player.getID();
	uint16_t helpers = player.getHelpers();

	SpectatorVec list;
	map.getSpectators(list, player.getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendCreatureHelpers(creatureId, helpers);
	}
}


void Game::updateCreatureType(Creature* creature)
{
	const Player* masterPlayer = nullptr;

	uint32_t creatureId = creature->getID();
	CreatureType_t creatureType = creature->getType();
	if (creatureType == CREATURETYPE_MONSTER) {
		const Creature* master = creature->getMaster();
		if (master) {
			masterPlayer = master->getPlayer();
			if (masterPlayer) {
				creatureType = CREATURETYPE_SUMMON_OTHERS;
			}
		}
	}

	//send to clients
	SpectatorVec list;
	map.getSpectators(list, creature->getPosition(), true, true);

	if (creatureType == CREATURETYPE_SUMMON_OTHERS) {
		for (Creature* spectator : list) {
			Player* player = spectator->getPlayer();
			if (masterPlayer == player) {
				player->sendCreatureType(creatureId, CREATURETYPE_SUMMON_OWN);
			} else {
				player->sendCreatureType(creatureId, creatureType);
			}
		}
	} else {
		for (Creature* spectator : list) {
			spectator->getPlayer()->sendCreatureType(creatureId, creatureType);
		}
	}
}


void Game::updatePremium(Account& account)
{
	bool save = false;
	time_t timeNow = time(nullptr);

	if (account.premiumDays != 0 && account.premiumDays != std::numeric_limits<uint16_t>::max()) {
		if (account.lastDay == 0) {
			account.lastDay = timeNow;
			save = true;
		} else {
			uint32_t days = (timeNow - account.lastDay) / 86400;
			if (days > 0) {
				if (days >= account.premiumDays) {
					account.premiumDays = 0;
					account.lastDay = 0;
				} else {
					account.premiumDays -= days;
					time_t remainder = (timeNow - account.lastDay) % 86400;
					account.lastDay = timeNow - remainder;
				}

				save = true;
			}
		}
	} else if (account.lastDay != 0) {
		account.lastDay = 0;
		save = true;
	}

	if (save && !IOLoginData::saveAccount(account)) {
		std::cout << "> ERROR: Failed to save account: " << account.name << "!" << std::endl;
	}
}


void Game::loadMotdNum()
{
	Database* db = Database::getInstance();

	DBResult_ptr result = db->storeQuery("SELECT `value` FROM `server_config` WHERE `config` = 'motd_num'");
	if (result) {
		motdNum = result->getNumber<uint32_t>("value");
	} else {
		db->executeQuery("INSERT INTO `server_config` (`config`, `value`) VALUES ('motd_num', '0')");
	}

	result = db->storeQuery("SELECT `value` FROM `server_config` WHERE `config` = 'motd_hash'");
	if (result) {
		motdHash = result->getString("value");
		if (motdHash != transformToSHA1(g_config.getString(ConfigManager::MOTD))) {
			++motdNum;
		}
	} else {
		db->executeQuery("INSERT INTO `server_config` (`config`, `value`) VALUES ('motd_hash', '')");
	}
}


void Game::saveMotdNum() const
{
	Database* db = Database::getInstance();

	std::ostringstream query;
	query << "UPDATE `server_config` SET `value` = '" << motdNum << "' WHERE `config` = 'motd_num'";
	db->executeQuery(query.str());

	query.str(std::string());
	query << "UPDATE `server_config` SET `value` = '" << transformToSHA1(g_config.getString(ConfigManager::MOTD)) << "' WHERE `config` = 'motd_hash'";
	db->executeQuery(query.str());
}


void Game::checkPlayersRecord()
{
	const size_t playersOnline = getPlayersOnline();
	if (playersOnline > playersRecord) {
		uint32_t previousRecord = playersRecord;
		playersRecord = playersOnline;

		for (const auto& it : g_globalEvents->getEventMap(GLOBALEVENT_RECORD)) {
			it.second->executeRecord(playersRecord, previousRecord);
		}
		updatePlayersRecord();
	}
}


void Game::updatePlayersRecord() const
{
	Database* db = Database::getInstance();

	std::ostringstream query;
	query << "UPDATE `server_config` SET `value` = '" << playersRecord << "' WHERE `config` = 'players_record'";
	db->executeQuery(query.str());
}


void Game::loadPlayersRecord()
{
	Database* db = Database::getInstance();

	DBResult_ptr result = db->storeQuery("SELECT `value` FROM `server_config` WHERE `config` = 'players_record'");
	if (result) {
		playersRecord = result->getNumber<uint32_t>("value");
	} else {
		db->executeQuery("INSERT INTO `server_config` (`config`, `value`) VALUES ('players_record', '0')");
	}
}

uint64_t Game::getExperienceStage(uint32_t level)
{
	if (!stagesEnabled) {
		return g_config.getNumber(ConfigManager::RATE_EXPERIENCE);
	}

	if (useLastStageLevel && level >= lastStageLevel) {
		return stages[lastStageLevel];
	}

	return stages[level];
}


bool Game::loadExperienceStages()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/stages.xml");
	if (!result) {
		printXMLError("Error - Game::loadExperienceStages", "data/XML/stages.xml", result);
		return false;
	}

	for (auto stageNode : doc.child("stages").children()) {
		if (strcasecmp(stageNode.name(), "config") == 0) {
			stagesEnabled = stageNode.attribute("enabled").as_bool();
		} else {
			uint32_t minLevel, maxLevel, multiplier;

			pugi::xml_attribute minLevelAttribute = stageNode.attribute("minlevel");
			if (minLevelAttribute) {
				minLevel = pugi::cast<uint32_t>(minLevelAttribute.value());
			} else {
				minLevel = 1;
			}

			pugi::xml_attribute maxLevelAttribute = stageNode.attribute("maxlevel");
			if (maxLevelAttribute) {
				maxLevel = pugi::cast<uint32_t>(maxLevelAttribute.value());
			} else {
				maxLevel = 0;
				lastStageLevel = minLevel;
				useLastStageLevel = true;
			}

			pugi::xml_attribute multiplierAttribute = stageNode.attribute("multiplier");
			if (multiplierAttribute) {
				multiplier = pugi::cast<uint32_t>(multiplierAttribute.value());
			} else {
				multiplier = 1;
			}

			if (useLastStageLevel) {
				stages[lastStageLevel] = multiplier;
			} else {
				for (uint32_t i = minLevel; i <= maxLevel; ++i) {
					stages[i] = multiplier;
				}
			}
		}
	}
	return true;
}


