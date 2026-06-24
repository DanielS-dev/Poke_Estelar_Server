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

Account IOLoginData::loadAccount(uint32_t accno)
{
	Account account;

	std::ostringstream query;
	query << "SELECT `id`, `name`, `password`, `type`, `premdays`, `lastday` FROM `accounts` WHERE `id` = " << accno;
	DBResult_ptr result = Database::getInstance()->storeQuery(query.str());
	if (!result) {
		return account;
	}

	account.id = result->getNumber<uint32_t>("id");
	account.name = result->getString("name");
	account.accountType = static_cast<AccountType_t>(result->getNumber<int32_t>("type"));
	account.premiumDays = result->getNumber<uint16_t>("premdays");
	account.lastDay = result->getNumber<time_t>("lastday");
	return account;
}

bool IOLoginData::saveAccount(const Account& acc)
{
	std::ostringstream query;
	query << "UPDATE `accounts` SET `premdays` = " << acc.premiumDays << ", `lastday` = " << acc.lastDay << " WHERE `id` = " << acc.id;
	return Database::getInstance()->executeQuery(query.str());
}

AccountType_t IOLoginData::getAccountType(uint32_t accountId)
{
	std::ostringstream query;
	query << "SELECT `type` FROM `accounts` WHERE `id` = " << accountId;
	DBResult_ptr result = Database::getInstance()->storeQuery(query.str());
	if (!result) {
		return ACCOUNT_TYPE_NORMAL;
	}
	return static_cast<AccountType_t>(result->getNumber<uint16_t>("type"));
}

void IOLoginData::setAccountType(uint32_t accountId, AccountType_t accountType)
{
	std::ostringstream query;
	query << "UPDATE `accounts` SET `type` = " << static_cast<uint16_t>(accountType) << " WHERE `id` = " << accountId;
	Database::getInstance()->executeQuery(query.str());
}

