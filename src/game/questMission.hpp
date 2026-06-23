// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_QUEST_MISSION_H_16E44051F23547BE8097F8EA9FCAACA0
#define FS_QUEST_MISSION_H_16E44051F23547BE8097F8EA9FCAACA0

#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <utility>

class Player;

class Mission
{
	public:
		Mission(std::string name, int32_t storageID, int32_t startValue, int32_t endValue, bool ignoreEndValue) :
			name(std::move(name)), storageID(storageID), startValue(startValue), endValue(endValue), ignoreEndValue(ignoreEndValue) {}

		bool isCompleted(Player* player) const;
		bool isStarted(Player* player) const;
		std::string getName(Player* player) const;
		std::string getDescription(Player* player) const;

		uint32_t getStorageId() const {
			return storageID;
		}
		int32_t getStartStorageValue() const {
			return startValue;
		}
		int32_t getEndStorageValue() const {
			return endValue;
		}

		std::map<int32_t, std::string> descriptions;
		std::string mainDescription;

	private:
		std::string name;
		uint32_t storageID;
		int32_t startValue, endValue;
		bool ignoreEndValue;
};

typedef std::list<Mission> MissionsList;

#endif
