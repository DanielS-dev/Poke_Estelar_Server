// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_COMMAND_H_C95A575CCADF434699D26CD042690970
#define FS_COMMAND_H_C95A575CCADF434699D26CD042690970

#include <cstdint>
#include <string>

#include "../../core/enums.hpp"

class Commands;
class Player;

typedef void (Commands::*CommandFunc)(Player&, const std::string&);

struct Command {
	Command(CommandFunc f, uint32_t groupId, AccountType_t accountType, bool log);

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
