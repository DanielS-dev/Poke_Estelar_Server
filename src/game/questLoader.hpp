// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_QUEST_LOADER_H_16E44051F23547BE8097F8EA9FCAACA0
#define FS_QUEST_LOADER_H_16E44051F23547BE8097F8EA9FCAACA0

class Quests;

class QuestLoader
{
	public:
		static bool loadFromXml(Quests& quests);
};

#endif
