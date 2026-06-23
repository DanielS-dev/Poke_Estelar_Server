// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_COMMAND_RULES_H_C95A575CCADF434699D26CD042690970
#define FS_COMMAND_RULES_H_C95A575CCADF434699D26CD042690970

#include <string>

struct Command;
class Player;

namespace CommandRules
{
	bool canExecute(Player& player, const Command& command);
	void logCommand(Player& player, const std::string& commandText);
}

#endif
