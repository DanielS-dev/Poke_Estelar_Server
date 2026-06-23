// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_CHAT_RULES_H_F1574642D0384ABFAB52B7ED906E5628
#define FS_CHAT_RULES_H_F1574642D0384ABFAB52B7ED906E5628

#include "../core/const.hpp"

class Player;

namespace ChatRules
{
	void normalizeSpeakType(const Player& player, uint16_t channelId, SpeakClasses& type);
}

#endif
