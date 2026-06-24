// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../../core/pugicast.hpp"

#include "../house.hpp"
#include "../bed.hpp"
#include "../../config/configmanager.hpp"
#include "../../game/game.hpp"
#include "../../persistence/ioguild.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/xmlErro.hpp"

extern ConfigManager g_config;
extern Game g_game;

void House::setAccessList(uint32_t listId, const std::string& textlist)
{
	if (listId == GUEST_LIST) {
		guestList.parseList(textlist);
	} else if (listId == SUBOWNER_LIST) {
		subOwnerList.parseList(textlist);
	} else {
		Door* door = getDoorByNumber(listId);
		if (door) {
			door->setAccessList(textlist);
		}

		// We dont have kick anyone
		return;
	}

	//kick uninvited players
	for (HouseTile* tile : houseTiles) {
		if (CreatureVector* creatures = tile->getCreatures()) {
			for (int32_t i = creatures->size(); --i >= 0;) {
				Player* player = (*creatures)[i]->getPlayer();
				if (player && !isInvited(player)) {
					kickPlayer(nullptr, player);
				}
			}
		}
	}
}

bool House::getAccessList(uint32_t listId, std::string& list) const
{
	if (listId == GUEST_LIST) {
		guestList.getList(list);
		return true;
	} else if (listId == SUBOWNER_LIST) {
		subOwnerList.getList(list);
		return true;
	}

	Door* door = getDoorByNumber(listId);
	if (!door) {
		return false;
	}

	return door->getAccessList(list);
}

bool House::isInvited(const Player* player)
{
	return getHouseAccessLevel(player) != HOUSE_NOT_INVITED;
}

void AccessList::parseList(const std::string& list)
{
	playerList.clear();
	guildList.clear();
	expressionList.clear();
	regExList.clear();
	this->list = list;
	if (list.empty()) {
		return;
	}

	std::istringstream listStream(list);
	std::string line;

	while (getline(listStream, line)) {
		trimString(line);
		trim_left(line, '\t');
		trim_right(line, '\t');
		trimString(line);

		if (line.empty() || line.front() == '#' || line.length() > 100) {
			continue;
		}

		toLowerCaseString(line);

		std::string::size_type at_pos = line.find("@");
		if (at_pos != std::string::npos) {
			addGuild(line.substr(at_pos + 1));
		} else if (line.find("!") != std::string::npos || line.find("*") != std::string::npos || line.find("?") != std::string::npos) {
			addExpression(line);
		} else {
			addPlayer(line);
		}
	}
}

void AccessList::addPlayer(const std::string& name)
{
	Player* player = g_game.getPlayerByName(name);
	if (player) {
		playerList.insert(player->getGUID());
	} else {
		uint32_t guid = IOLoginData::getGuidByName(name);
		if (guid != 0) {
			playerList.insert(guid);
		}
	}
}

void AccessList::addGuild(const std::string& name)
{
	uint32_t guildId = IOGuild::getGuildIdByName(name);
	if (guildId != 0) {
		guildList.insert(guildId);
	}
}

void AccessList::addExpression(const std::string& expression)
{
	if (std::find(expressionList.begin(), expressionList.end(), expression) != expressionList.end()) {
		return;
	}

	std::string outExp;
	outExp.reserve(expression.length());

	std::string metachars = ".[{}()\\+|^$";
	for (const char c : expression) {
		if (metachars.find(c) != std::string::npos) {
			outExp.push_back('\\');
		}
		outExp.push_back(c);
	}

	replaceString(outExp, "*", ".*");
	replaceString(outExp, "?", ".?");

	try {
		if (!outExp.empty()) {
			expressionList.push_back(outExp);

			if (outExp.front() == '!') {
				if (outExp.length() > 1) {
					regExList.emplace_front(std::regex(outExp.substr(1)), false);
				}
			} else {
				regExList.emplace_back(std::regex(outExp), true);
			}
		}
	} catch (...) {}
}

bool AccessList::isInList(const Player* player)
{
	std::string name = asLowerCaseString(player->getName());
	std::cmatch what;

	for (const auto& it : regExList) {
		if (std::regex_match(name.c_str(), what, it.first)) {
			return it.second;
		}
	}

	auto playerIt = playerList.find(player->getGUID());
	if (playerIt != playerList.end()) {
		return true;
	}

	const Guild* guild = player->getGuild();
	return guild && guildList.find(guild->getId()) != guildList.end();
}

void AccessList::getList(std::string& list) const
{
	list = this->list;
}

