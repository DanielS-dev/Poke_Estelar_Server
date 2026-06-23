// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_RAID_LOADER_H_3583C7C054584881856D55765DEDAFA9
#define FS_RAID_LOADER_H_3583C7C054584881856D55765DEDAFA9

class Raids;

class RaidLoader
{
	public:
		static bool loadFromXml(Raids& raids);
};

#endif
