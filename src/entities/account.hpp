// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_ACCOUNT_H_34817537BA2B4CB7B71AA562AFBB118F
#define FS_ACCOUNT_H_34817537BA2B4CB7B71AA562AFBB118F

#include "../core/enums.hpp"

struct Account {
	std::vector<std::string> characters;
	std::string name;
	std::string key;
	time_t lastDay = 0;
	uint32_t id = 0;
	uint16_t premiumDays = 0;
	AccountType_t accountType = ACCOUNT_TYPE_NORMAL;

	Account() = default;
};

#endif
