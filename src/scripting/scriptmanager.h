// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_SCRIPTMANAGER_H_F9428B7803A44FB88EB1A915CFD37F8B
#define FS_SCRIPTMANAGER_H_F9428B7803A44FB88EB1A915CFD37F8B

class ScriptingManager
{
	public:
		ScriptingManager() = default;
		~ScriptingManager();

		// non-copyable
		ScriptingManager(const ScriptingManager&) = delete;
		ScriptingManager& operator=(const ScriptingManager&) = delete;

		static ScriptingManager* getInstance() {
			static ScriptingManager instance;
			return &instance;
		}

		bool loadScriptSystems();
};

#endif
