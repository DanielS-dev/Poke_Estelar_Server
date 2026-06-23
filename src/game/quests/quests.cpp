// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "quests.hpp"

#include "questLoader.hpp"

bool Quests::reload()
{
	quests.clear();
	return loadFromXml();
}

bool Quests::loadFromXml()
{
	return QuestLoader::loadFromXml(*this);
}

Quest* Quests::getQuestByID(uint16_t id)
{
	for (Quest& quest : quests) {
		if (quest.id == id) {
			return &quest;
		}
	}
	return nullptr;
}

uint16_t Quests::getQuestsCount(Player* player) const
{
	uint16_t count = 0;
	for (const Quest& quest : quests) {
		if (quest.isStarted(player)) {
			count++;
		}
	}
	return count;
}

bool Quests::isQuestStorage(const uint32_t key, const int32_t value, const int32_t oldValue) const
{
	for (const Quest& quest : quests) {
		if (quest.getStartStorageId() == key && quest.getStartStorageValue() == value) {
			return true;
		}

		for (const Mission& mission : quest.getMissions()) {
			if (mission.getStorageId() == key && value >= mission.getStartStorageValue() && value <= mission.getEndStorageValue()) {
				return mission.mainDescription.empty() || oldValue < mission.getStartStorageValue() || oldValue > mission.getEndStorageValue();
			}
		}
	}
	return false;
}
