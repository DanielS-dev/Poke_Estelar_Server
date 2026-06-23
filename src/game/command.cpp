// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "command.hpp"

Command::Command(CommandFunc f, uint32_t groupId, AccountType_t accountType, bool log)
	: f(f), groupId(groupId), accountType(accountType), log(log) {}
