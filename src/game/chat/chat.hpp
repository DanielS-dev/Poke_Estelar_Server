// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_CHAT_H_F1574642D0384ABFAB52B7ED906E5628
#define FS_CHAT_H_F1574642D0384ABFAB52B7ED906E5628

#include "chatChannel.hpp"
#include "../../scripting/luascript.hpp"

class ChatLoader;
class Party;
class Player;

class Chat
{
	public:
		Chat();

		// non-copyable
		Chat(const Chat&) = delete;
		Chat& operator=(const Chat&) = delete;

		bool load();

		ChatChannel* createChannel(const Player& player, uint16_t channelId);
		bool deleteChannel(const Player& player, uint16_t channelId);

		ChatChannel* addUserToChannel(Player& player, uint16_t channelId);
		bool removeUserFromChannel(const Player& player, uint16_t channelId);
		void removeUserFromAllChannels(const Player& player);

		bool talkToChannel(const Player& player, SpeakClasses type, const std::string& text, uint16_t channelId);

		ChannelList getChannelList(const Player& player);

		ChatChannel* getChannel(const Player& player, uint16_t channelId);
		ChatChannel* getChannelById(uint16_t channelId);
		ChatChannel* getGuildChannelById(uint32_t guildId);
		PrivateChatChannel* getPrivateChannel(const Player& player);

		LuaScriptInterface* getScriptInterface() {
			return &scriptInterface;
		}

	private:
		std::map<uint16_t, ChatChannel> normalChannels;
		std::map<uint16_t, PrivateChatChannel> privateChannels;
		std::map<Party*, ChatChannel> partyChannels;
		std::map<uint32_t, ChatChannel> guildChannels;

		LuaScriptInterface scriptInterface;

		PrivateChatChannel dummyPrivate;

	friend class ChatLoader;
};

#endif
