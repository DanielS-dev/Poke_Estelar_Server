// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "ioguild.hpp"
#include "database.hpp"

uint32_t IOGuild::getGuildIdByName(const std::string& name)
{
	Database* db = Database::getInstance();

	std::ostringstream query;
	query << "SELECT `id` FROM `guilds` WHERE `name` = " << db->escapeString(name);

	DBResult_ptr result = db->storeQuery(query.str());
	if (!result) {
		return 0;
	}
	return result->getNumber<uint32_t>("id");
}

void IOGuild::getWarList(uint32_t guildId, GuildWarList& guildWarList)
{
	std::ostringstream query;
	query << "SELECT `guild1`, `guild2` FROM `guild_wars` WHERE (`guild1` = " << guildId << " OR `guild2` = " << guildId << ") AND `ended` = 0 AND `status` = 1";

	DBResult_ptr result = Database::getInstance()->storeQuery(query.str());
	if (!result) {
		return;
	}

	do {
		uint32_t guild1 = result->getNumber<uint32_t>("guild1");
		if (guildId != guild1) {
			guildWarList.push_back(guild1);
		} else {
			guildWarList.push_back(result->getNumber<uint32_t>("guild2"));
		}
	} while (result->next());
}
