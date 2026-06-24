// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "iologindata.hpp"
#include "../../config/configmanager.hpp"
#include "../../core/tools/auths.hpp"
#include "../../game/game.hpp"
#include "../ioguild.hpp"

extern ConfigManager g_config;
extern Game g_game;

std::string decodeSecret(const std::string& secret)
{
	// simple base32 decoding
	std::string key;
	key.reserve(10);

	uint32_t buffer = 0, left = 0;
	for (const auto& ch : secret) {
		buffer <<= 5;
		if (ch >= 'A' && ch <= 'Z') {
			buffer |= (ch & 0x1F) - 1;
		} else if (ch >= '2' && ch <= '7') {
			buffer |= ch - 24;
		} else {
			// if a key is broken, return empty and the comparison
			// will always be false since the token must not be empty
			return {};
		}

		left += 5;
		if (left >= 8) {
			left -= 8;
			key.push_back(static_cast<char>(buffer >> left));
		}
	}

	return key;
}

bool IOLoginData::loginserverAuthentication(const std::string& name, const std::string& password, Account& account)
{
	Database* db = Database::getInstance();

	std::ostringstream query;
	query << "SELECT `id`, `name`, `password`, `secret`, `type`, `premdays`, `lastday` FROM `accounts` WHERE `name` = " << db->escapeString(name);
	DBResult_ptr result = db->storeQuery(query.str());
	if (!result) {
		return false;
	}

	if (transformToSHA1(password) != result->getString("password")) {
		return false;
	}

	account.id = result->getNumber<uint32_t>("id");
	account.name = result->getString("name");
	account.key = decodeSecret(result->getString("secret"));
	account.accountType = static_cast<AccountType_t>(result->getNumber<int32_t>("type"));
	account.premiumDays = result->getNumber<uint16_t>("premdays");
	account.lastDay = result->getNumber<time_t>("lastday");

	query.str(std::string());
	query << "SELECT `name`, `deletion` FROM `players` WHERE `account_id` = " << account.id;
	result = db->storeQuery(query.str());
	if (result) {
		do {
			if (result->getNumber<uint64_t>("deletion") == 0) {
				account.characters.push_back(result->getString("name"));
			}
		} while (result->next());
		std::sort(account.characters.begin(), account.characters.end());
	}
	return true;
}

uint32_t IOLoginData::gameworldAuthentication(const std::string& accountName, const std::string& password, std::string& characterName)
{
	Database* db = Database::getInstance();

	std::ostringstream query;
	query << "SELECT `id`, `password` FROM `accounts` WHERE `name` = " << db->escapeString(accountName);
	DBResult_ptr result = db->storeQuery(query.str());
	if (!result) {
		return 0;
	}

	if (transformToSHA1(password) != result->getString("password")) {
		return 0;
	}

	uint32_t accountId = result->getNumber<uint32_t>("id");

	query.str(std::string());
	query << "SELECT `account_id`, `name`, `deletion` FROM `players` WHERE `name` = " << db->escapeString(characterName);
	result = db->storeQuery(query.str());
	if (!result) {
		return 0;
	}

	if (result->getNumber<uint32_t>("account_id") != accountId || result->getNumber<uint64_t>("deletion") != 0) {
		return 0;
	}
	characterName = result->getString("name");
	return accountId;
}

