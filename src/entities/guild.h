// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_GUILD_H_C00F0A1D732E4BA88FF62ACBE74D76BC
#define FS_GUILD_H_C00F0A1D732E4BA88FF62ACBE74D76BC

class Player;

struct GuildRank {
	uint32_t id;
	std::string name;
	uint8_t level;

	GuildRank(uint32_t id, std::string name, uint8_t level) :
		id(id), name(std::move(name)), level(level) {}
};

class Guild
{
	public:
		Guild(uint32_t id, std::string name) : name(std::move(name)), id(id) {}

		void addMember(Player* player);
		void removeMember(Player* player);

		uint32_t getId() const {
			return id;
		}
		const std::string& getName() const {
			return name;
		}
		const std::list<Player*>& getMembersOnline() const {
			return membersOnline;
		}
		uint32_t getMemberCount() const {
			return memberCount;
		}
		void setMemberCount(uint32_t count) {
			memberCount = count;
		}

		GuildRank* getRankById(uint32_t id);
		const GuildRank* getRankByLevel(uint8_t level) const;
		void addRank(uint32_t id, const std::string& name, uint8_t level);

		const std::string& getMotd() const {
			return motd;
		}
		void setMotd(const std::string& motd) {
			this->motd = motd;
		}

	private:
		std::list<Player*> membersOnline;
		std::vector<GuildRank> ranks;
		std::string name;
		std::string motd;
		uint32_t id;
		uint32_t memberCount = 0;
};

#endif
