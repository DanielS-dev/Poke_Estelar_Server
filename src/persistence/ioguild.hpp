// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_IOGUILD_H_EF9ACEBA0B844C388B70FF52E69F1AFF
#define FS_IOGUILD_H_EF9ACEBA0B844C388B70FF52E69F1AFF

typedef std::vector<uint32_t> GuildWarList;

class IOGuild
{
	public:
		static uint32_t getGuildIdByName(const std::string& name);
		static void getWarList(uint32_t guildId, GuildWarList& guildWarList);
};

#endif
