// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

// Included inside LuaScriptInterface protected section by ../luascript.hpp.

		//
		lua_State* luaState = nullptr;
		std::string lastLuaError;

		std::string interfaceName;
		int32_t eventTableRef = -1;

		static ScriptEnvironment scriptEnv[16];
		static int32_t scriptEnvIndex;

		int32_t runningEventId = EVENT_ID_USER;
		std::string loadingFile;

		//script file cache
		std::map<int32_t, std::string> cacheFiles;
