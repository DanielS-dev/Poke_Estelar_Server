// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_RAID_H_3583C7C054584881856D55765DEDAFA9
#define FS_RAID_H_3583C7C054584881856D55765DEDAFA9

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "raidEvent.hpp"

enum RaidState_t {
	RAIDSTATE_IDLE,
	RAIDSTATE_EXECUTING,
};

class Raid
{
	public:
		Raid(std::string name, uint32_t interval, uint32_t marginTime, bool repeat) :
			name(std::move(name)), interval(interval), margin(marginTime), repeat(repeat) {}
		~Raid();

		Raid(const Raid&) = delete;
		Raid& operator=(const Raid&) = delete;

		bool loadFromXml(const std::string& filename);

		void startRaid();

		void executeRaidEvent(RaidEvent* raidEvent);
		void resetRaid();

		RaidEvent* getNextRaidEvent();
		void setState(RaidState_t newState) {
			state = newState;
		}
		const std::string& getName() const {
			return name;
		}

		bool isLoaded() const {
			return loaded;
		}
		uint64_t getMargin() const {
			return margin;
		}
		uint32_t getInterval() const {
			return interval;
		}
		bool canBeRepeated() const {
			return repeat;
		}

		void stopEvents();

	private:
		std::vector<RaidEvent*> raidEvents;
		std::string name;
		uint32_t interval;
		uint32_t nextEvent = 0;
		uint64_t margin;
		RaidState_t state = RAIDSTATE_IDLE;
		uint32_t nextEventEvent = 0;
		bool loaded = false;
		bool repeat;
};

#endif
