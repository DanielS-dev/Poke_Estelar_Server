// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <fstream>

#include "command.hpp"
#include "commandRules.hpp"
#include "../entities/player.hpp"

namespace CommandRules
{
	bool canExecute(Player& player, const Command& command)
	{
		if (command.groupId > player.getGroup()->id || command.accountType > player.getAccountType()) {
			if (player.getGroup()->access) {
				player.sendTextMessage(MESSAGE_STATUS_SMALL, "You can not execute this command.");
			}

			return false;
		}
		return true;
	}

	void logCommand(Player& player, const std::string& commandText)
	{
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_RED, commandText);

		std::ostringstream logFile;
		logFile << "data/logs/" << player.getName() << " commands.log";
		std::ofstream out(logFile.str(), std::ios::app);
		if (out.is_open()) {
			time_t ticks = time(nullptr);
			const tm* now = localtime(&ticks);
			char buf[32];
			strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", now);

			out << '[' << buf << "] " << commandText << std::endl;
			out.close();
		}
	}
}
