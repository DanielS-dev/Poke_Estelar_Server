// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_QUESTS_H_16E44051F23547BE8097F8EA9FCAACA0
#define FS_QUESTS_H_16E44051F23547BE8097F8EA9FCAACA0

#include "quest.hpp"

class Player;
class QuestLoader;

class Quests
{
	public:
		const QuestsList& getQuests() const {
			return quests;
		}

		bool loadFromXml();
		Quest* getQuestByID(uint16_t id);
		bool isQuestStorage(const uint32_t key, const int32_t value, const int32_t oldValue) const;
		uint16_t getQuestsCount(Player* player) const;
		bool reload();

	private:
		QuestsList quests;

	friend class QuestLoader;
};

#endif
