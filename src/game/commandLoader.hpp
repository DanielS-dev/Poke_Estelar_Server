// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_COMMAND_LOADER_H_C95A575CCADF434699D26CD042690970
#define FS_COMMAND_LOADER_H_C95A575CCADF434699D26CD042690970

class Commands;

class CommandLoader
{
	public:
		static bool loadFromXml(Commands& commands);
};

#endif
