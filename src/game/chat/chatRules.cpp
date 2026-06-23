// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "chatRules.hpp"
#include "../../entities/player.hpp"

namespace ChatRules
{
	void normalizeSpeakType(const Player& player, uint16_t channelId, SpeakClasses& type)
	{
		if (channelId == CHANNEL_GUILD) {
			const GuildRank* rank = player.getGuildRank();
			if (rank && rank->level > 1) {
				type = TALKTYPE_CHANNEL_O;
			} else if (type != TALKTYPE_CHANNEL_Y) {
				type = TALKTYPE_CHANNEL_Y;
			}
		} else if (type != TALKTYPE_CHANNEL_Y && (channelId == CHANNEL_PRIVATE || channelId == CHANNEL_PARTY)) {
			type = TALKTYPE_CHANNEL_Y;
		}
	}
}
