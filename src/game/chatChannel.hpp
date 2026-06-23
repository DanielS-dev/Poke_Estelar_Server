// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_CHAT_CHANNEL_H_F1574642D0384ABFAB52B7ED906E5628
#define FS_CHAT_CHANNEL_H_F1574642D0384ABFAB52B7ED906E5628

#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <utility>

#include "../core/const.hpp"

class Chat;
class Player;

typedef std::map<uint32_t, Player*> UsersMap;
typedef std::map<uint32_t, const Player*> InvitedMap;

class ChatChannel
{
	public:
		ChatChannel() = default;
		ChatChannel(uint16_t channelId, std::string channelName):
			name(std::move(channelName)),
			id(channelId) {}

		virtual ~ChatChannel() = default;

		bool addUser(Player& player);
		bool removeUser(const Player& player);

		bool talk(const Player& fromPlayer, SpeakClasses type, const std::string& text);
		void sendToAll(const std::string& message, SpeakClasses type) const;

		const std::string& getName() const {
			return name;
		}
		uint16_t getId() const {
			return id;
		}
		const UsersMap& getUsers() const {
			return users;
		}
		virtual const InvitedMap* getInvitedUsers() const {
			return nullptr;
		}

		virtual uint32_t getOwner() const {
			return 0;
		}

		bool isPublicChannel() const { return publicChannel; }

		bool executeOnJoinEvent(const Player& player);
		bool executeCanJoinEvent(const Player& player);
		bool executeOnLeaveEvent(const Player& player);
		bool executeOnSpeakEvent(const Player& player, SpeakClasses& type, const std::string& message);

	protected:
		UsersMap users;

		std::string name;

		int32_t canJoinEvent = -1;
		int32_t onJoinEvent = -1;
		int32_t onLeaveEvent = -1;
		int32_t onSpeakEvent = -1;

		uint16_t id;
		bool publicChannel = false;

	friend class Chat;
	friend class ChatLoader;
};

class PrivateChatChannel final : public ChatChannel
{
	public:
		PrivateChatChannel(uint16_t channelId, std::string channelName) : ChatChannel(channelId, channelName) {}

		uint32_t getOwner() const final {
			return owner;
		}
		void setOwner(uint32_t owner) {
			this->owner = owner;
		}

		bool isInvited(uint32_t guid) const;

		void invitePlayer(const Player& player, Player& invitePlayer);
		void excludePlayer(const Player& player, Player& excludePlayer);

		bool removeInvite(uint32_t guid);

		void closeChannel() const;

		const InvitedMap* getInvitedUsers() const final {
			return &invites;
		}

	protected:
		InvitedMap invites;
		uint32_t owner = 0;
};

typedef std::list<ChatChannel*> ChannelList;

#endif
