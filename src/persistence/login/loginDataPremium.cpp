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

void IOLoginData::addPremiumDays(uint32_t accountId, int32_t addDays)
{
	std::ostringstream query;
	query << "UPDATE `accounts` SET `premdays` = `premdays` + " << addDays << " WHERE `id` = " << accountId;
	Database::getInstance()->executeQuery(query.str());
}

void IOLoginData::removePremiumDays(uint32_t accountId, int32_t removeDays)
{
	std::ostringstream query;
	query << "UPDATE `accounts` SET `premdays` = `premdays` - " << removeDays << " WHERE `id` = " << accountId;
	Database::getInstance()->executeQuery(query.str());
}

