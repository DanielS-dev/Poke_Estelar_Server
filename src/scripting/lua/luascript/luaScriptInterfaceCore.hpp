// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

// Included inside LuaScriptInterface class declaration by ../luascript.hpp.

		virtual bool closeState();

		void registerFunctions();

		void registerClass(const std::string& className, const std::string& baseClass, lua_CFunction newFunction = nullptr);
		void registerTable(const std::string& tableName);
		void registerMethod(const std::string& className, const std::string& methodName, lua_CFunction func);
		void registerMetaMethod(const std::string& className, const std::string& methodName, lua_CFunction func);
		void registerGlobalMethod(const std::string& functionName, lua_CFunction func);
		void registerVariable(const std::string& tableName, const std::string& name, lua_Number value);
		void registerGlobalVariable(const std::string& name, lua_Number value);
		void registerGlobalBoolean(const std::string& name, bool value);

		std::string getStackTrace(const std::string& error_desc);

		static std::string getErrorDesc(ErrorCode_t code);
		static bool getArea(lua_State* L, std::list<uint32_t>& list, uint32_t& rows);

