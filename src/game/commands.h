// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_COMMANDS_H_C95A575CCADF434699D26CD042690970
#define FS_COMMANDS_H_C95A575CCADF434699D26CD042690970

#include "../core/enums.h"

class Player;

struct Command;
struct s_defcommands;

class Commands
{
	public:
		Commands();
		~Commands();

		// non-copyable
		Commands(const Commands&) = delete;
		Commands& operator=(const Commands&) = delete;

		bool loadFromXml();
		bool reload();

		bool exeCommand(Player& player, const std::string& cmd);

	protected:
		//commands
		void reloadInfo(Player& player, const std::string& param);
		void sellHouse(Player& player, const std::string& param);
		void forceRaid(Player& player, const std::string& param);

		//table of commands
		static s_defcommands defined_commands[];

		std::map<std::string, Command*> commandMap;
};

typedef void (Commands::*CommandFunc)(Player&, const std::string&);

struct Command {
	Command(CommandFunc f, uint32_t groupId, AccountType_t accountType, bool log)
		: f(f), groupId(groupId), accountType(accountType), log(log) {}

	CommandFunc f;
	uint32_t groupId;
	AccountType_t accountType;
	bool log;
};

struct s_defcommands {
	const char* name;
	CommandFunc f;
};

#endif
