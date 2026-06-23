// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "chat.hpp"
#include "chatLoader.hpp"
#include "chatRules.hpp"
#include "../../entities/player.hpp"

Chat::Chat():
	scriptInterface("Chat Interface"),
	dummyPrivate(CHANNEL_PRIVATE, "Private Chat Channel")
{
	scriptInterface.initState();
}

bool Chat::load()
{
	return ChatLoader::load(*this);
}

ChatChannel* Chat::createChannel(const Player& player, uint16_t channelId)
{
	if (getChannel(player, channelId)) {
		return nullptr;
	}

	switch (channelId) {
		case CHANNEL_GUILD: {
			Guild* guild = player.getGuild();
			if (guild) {
				auto ret = guildChannels.emplace(std::make_pair(guild->getId(), ChatChannel(channelId, guild->getName())));
				return &ret.first->second;
			}
			break;
		}

		case CHANNEL_PARTY: {
			Party* party = player.getParty();
			if (party) {
				auto ret = partyChannels.emplace(std::make_pair(party, ChatChannel(channelId, "Party")));
				return &ret.first->second;
			}
			break;
		}

		case CHANNEL_PRIVATE: {
			//only 1 private channel for each premium player
			if (!player.isPremium() || getPrivateChannel(player)) {
				return nullptr;
			}

			//find a free private channel slot
			for (uint16_t i = 100; i < 10000; ++i) {
				auto ret = privateChannels.emplace(std::make_pair(i, PrivateChatChannel(i, player.getName() + "'s Channel")));
				if (ret.second) { //second is a bool that indicates that a new channel has been placed in the map
					auto& newChannel = (*ret.first).second;
					newChannel.setOwner(player.getGUID());
					return &newChannel;
				}
			}
			break;
		}

		default:
			break;
	}
	return nullptr;
}

bool Chat::deleteChannel(const Player& player, uint16_t channelId)
{
	switch (channelId) {
		case CHANNEL_GUILD: {
			Guild* guild = player.getGuild();
			if (!guild) {
				return false;
			}

			auto it = guildChannels.find(guild->getId());
			if (it == guildChannels.end()) {
				return false;
			}

			guildChannels.erase(it);
			break;
		}

		case CHANNEL_PARTY: {
			Party* party = player.getParty();
			if (!party) {
				return false;
			}

			auto it = partyChannels.find(party);
			if (it == partyChannels.end()) {
				return false;
			}

			partyChannels.erase(it);
			break;
		}

		default: {
			auto it = privateChannels.find(channelId);
			if (it == privateChannels.end()) {
				return false;
			}

			it->second.closeChannel();

			privateChannels.erase(it);
			break;
		}
	}
	return true;
}

ChatChannel* Chat::addUserToChannel(Player& player, uint16_t channelId)
{
	ChatChannel* channel = getChannel(player, channelId);
	if (channel && channel->addUser(player)) {
		return channel;
	}
	return nullptr;
}

bool Chat::removeUserFromChannel(const Player& player, uint16_t channelId)
{
	ChatChannel* channel = getChannel(player, channelId);
	if (!channel || !channel->removeUser(player)) {
		return false;
	}

	if (channel->getOwner() == player.getGUID()) {
		deleteChannel(player, channelId);
	}
	return true;
}

void Chat::removeUserFromAllChannels(const Player& player)
{
	for (auto& it : normalChannels) {
		it.second.removeUser(player);
	}

	for (auto& it : partyChannels) {
		it.second.removeUser(player);
	}

	for (auto& it : guildChannels) {
		it.second.removeUser(player);
	}

	auto it = privateChannels.begin();
	while (it != privateChannels.end()) {
		PrivateChatChannel* channel = &it->second;
		channel->removeInvite(player.getGUID());
		channel->removeUser(player);
		if (channel->getOwner() == player.getGUID()) {
			channel->closeChannel();
			it = privateChannels.erase(it);
		} else {
			++it;
		}
	}
}

bool Chat::talkToChannel(const Player& player, SpeakClasses type, const std::string& text, uint16_t channelId)
{
	ChatChannel* channel = getChannel(player, channelId);
	if (!channel) {
		return false;
	}

	ChatRules::normalizeSpeakType(player, channelId, type);

	if (!channel->executeOnSpeakEvent(player, type, text)) {
		return false;
	}

	return channel->talk(player, type, text);
}

ChannelList Chat::getChannelList(const Player& player)
{
	ChannelList list;
	if (player.getGuild()) {
		ChatChannel* channel = getChannel(player, CHANNEL_GUILD);
		if (channel) {
			list.push_back(channel);
		} else {
			channel = createChannel(player, CHANNEL_GUILD);
			if (channel) {
				list.push_back(channel);
			}
		}
	}

	if (player.getParty()) {
		ChatChannel* channel = getChannel(player, CHANNEL_PARTY);
		if (channel) {
			list.push_back(channel);
		} else {
			channel = createChannel(player, CHANNEL_PARTY);
			if (channel) {
				list.push_back(channel);
			}
		}
	}

	for (const auto& it : normalChannels) {
		ChatChannel* channel = getChannel(player, it.first);
		if (channel) {
			list.push_back(channel);
		}
	}

	bool hasPrivate = false;
	for (auto& it : privateChannels) {
		if (PrivateChatChannel* channel = &it.second) {
			uint32_t guid = player.getGUID();
			if (channel->isInvited(guid)) {
				list.push_back(channel);
			}

			if (channel->getOwner() == guid) {
				hasPrivate = true;
			}
		}
	}

	if (!hasPrivate && player.isPremium()) {
		list.push_front(&dummyPrivate);
	}
	return list;
}

ChatChannel* Chat::getChannel(const Player& player, uint16_t channelId)
{
	switch (channelId) {
		case CHANNEL_GUILD: {
			Guild* guild = player.getGuild();
			if (guild) {
				auto it = guildChannels.find(guild->getId());
				if (it != guildChannels.end()) {
					return &it->second;
				}
			}
			break;
		}

		case CHANNEL_PARTY: {
			Party* party = player.getParty();
			if (party) {
				auto it = partyChannels.find(party);
				if (it != partyChannels.end()) {
					return &it->second;
				}
			}
			break;
		}

		default: {
			auto it = normalChannels.find(channelId);
			if (it != normalChannels.end()) {
				ChatChannel& channel = it->second;
				if (!channel.executeCanJoinEvent(player)) {
					return nullptr;
				}
				return &channel;
			} else {
				auto it2 = privateChannels.find(channelId);
				if (it2 != privateChannels.end() && it2->second.isInvited(player.getGUID())) {
					return &it2->second;
				}
			}
			break;
		}
	}
	return nullptr;
}

ChatChannel* Chat::getGuildChannelById(uint32_t guildId)
{
	auto it = guildChannels.find(guildId);
	if (it == guildChannels.end()) {
		return nullptr;
	}
	return &it->second;
}

ChatChannel* Chat::getChannelById(uint16_t channelId)
{
	auto it = normalChannels.find(channelId);
	if (it == normalChannels.end()) {
		return nullptr;
	}
	return &it->second;
}

PrivateChatChannel* Chat::getPrivateChannel(const Player& player)
{
	for (auto& it : privateChannels) {
		if (it.second.getOwner() == player.getGUID()) {
			return &it.second;
		}
	}
	return nullptr;
}
