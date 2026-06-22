// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_WAITLIST_H_7E4299E552E44F10BC4F4E50BF3D7241
#define FS_WAITLIST_H_7E4299E552E44F10BC4F4E50BF3D7241

#include "../entities/player.hpp"

struct Wait {
	constexpr Wait(int64_t timeout, uint32_t playerGUID) :
		timeout(timeout), playerGUID(playerGUID) {}

	int64_t timeout;
	uint32_t playerGUID;
};

typedef std::list<Wait> WaitList;
typedef WaitList::iterator WaitListIterator;

class WaitingList
{
	public:
		static WaitingList* getInstance() {
			static WaitingList waitingList;
			return &waitingList;
		}

		bool clientLogin(const Player* player);
		uint32_t getClientSlot(const Player* player);
		static uint32_t getTime(uint32_t slot);

	protected:
		WaitList priorityWaitList;
		WaitList waitList;

		static uint32_t getTimeout(uint32_t slot);
		WaitListIterator findClient(const Player* player, uint32_t& slot);
		static void cleanupList(WaitList& list);
};

#endif
