// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

// Included inside LuaScriptInterface class declaration by ../luascript.hpp.

		explicit LuaScriptInterface(std::string interfaceName);
		virtual ~LuaScriptInterface();

		// non-copyable
		LuaScriptInterface(const LuaScriptInterface&) = delete;
		LuaScriptInterface& operator=(const LuaScriptInterface&) = delete;

		virtual bool initState();
		bool reInitState();

		int32_t loadFile(const std::string& file, Npc* npc = nullptr);

		const std::string& getFileById(int32_t scriptId);
		int32_t getEvent(const std::string& eventName);
		int32_t getMetaEvent(const std::string& globalName, const std::string& eventName);

		static ScriptEnvironment* getScriptEnv() {
			assert(scriptEnvIndex >= 0 && scriptEnvIndex < 16);
			return scriptEnv + scriptEnvIndex;
		}

		static bool reserveScriptEnv() {
			return ++scriptEnvIndex < 16;
		}

		static void resetScriptEnv() {
			assert(scriptEnvIndex >= 0);
			scriptEnv[scriptEnvIndex--].resetEnv();
		}

		static void reportError(const char* function, const std::string& error_desc, bool stack_trace = false);

		const std::string& getInterfaceName() const {
			return interfaceName;
		}
		const std::string& getLastLuaError() const {
			return lastLuaError;
		}

		lua_State* getLuaState() const {
			return luaState;
		}

		bool pushFunction(int32_t functionId);

		static int luaErrorHandler(lua_State* L);
		bool callFunction(int params);
		void callVoidFunction(int params);

		//push/pop common structures
		static void pushThing(lua_State* L, Thing* thing);
		static void pushVariant(lua_State* L, const LuaVariant& var);
		static void pushString(lua_State* L, const std::string& value);
		static void pushCallback(lua_State* L, int32_t callback);
		static void pushCylinder(lua_State* L, Cylinder* cylinder);

		static std::string popString(lua_State* L);
		static int32_t popCallback(lua_State* L);

		// Userdata
		template<class T>
		static void pushUserdata(lua_State* L, T* value)
		{
			T** userdata = static_cast<T**>(lua_newuserdata(L, sizeof(T*)));
			*userdata = value;
		}

		// Metatables
		static void setMetatable(lua_State* L, int32_t index, const std::string& name);
		static void setWeakMetatable(lua_State* L, int32_t index, const std::string& name);

		static void setItemMetatable(lua_State* L, int32_t index, const Item* item);
		static void setCreatureMetatable(lua_State* L, int32_t index, const Creature* creature);

		// Get
		template<typename T>
		inline static typename std::enable_if<std::is_enum<T>::value, T>::type
			getNumber(lua_State* L, int32_t arg)
		{
			return static_cast<T>(static_cast<int64_t>(lua_tonumber(L, arg)));
		}
		template<typename T>
		inline static typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
			getNumber(lua_State* L, int32_t arg)
		{
			return static_cast<T>(lua_tonumber(L, arg));
		}
		template<typename T>
		static T getNumber(lua_State *L, int32_t arg, T defaultValue)
		{
			const auto parameters = lua_gettop(L);
			if (parameters == 0 || arg > parameters) {
				return defaultValue;
			}
			return getNumber<T>(L, arg);
		}
		template<class T>
		static T* getUserdata(lua_State* L, int32_t arg)
		{
			T** userdata = getRawUserdata<T>(L, arg);
			if (!userdata) {
				return nullptr;
			}
			return *userdata;
		}
		template<class T>
		inline static T** getRawUserdata(lua_State* L, int32_t arg)
		{
			return static_cast<T**>(lua_touserdata(L, arg));
		}

		inline static bool getBoolean(lua_State* L, int32_t arg)
		{
			return lua_toboolean(L, arg) != 0;
		}
		inline static bool getBoolean(lua_State* L, int32_t arg, bool defaultValue)
		{
			const auto parameters = lua_gettop(L);
			if (parameters == 0 || arg > parameters) {
				return defaultValue;
			}
			return lua_toboolean(L, arg) != 0;
		}

		static std::string getString(lua_State* L, int32_t arg);
		static Position getPosition(lua_State* L, int32_t arg, int32_t& stackpos);
		static Position getPosition(lua_State* L, int32_t arg);
		static Outfit_t getOutfit(lua_State* L, int32_t arg);
		static LuaVariant getVariant(lua_State* L, int32_t arg);

		static Thing* getThing(lua_State* L, int32_t arg);
		static Creature* getCreature(lua_State* L, int32_t arg);
		static Player* getPlayer(lua_State* L, int32_t arg);

		template<typename T>
		static T getField(lua_State* L, int32_t arg, const std::string& key)
		{
			lua_getfield(L, arg, key.c_str());
			return getNumber<T>(L, -1);
		}

		static std::string getFieldString(lua_State* L, int32_t arg, const std::string& key);

		static LuaDataType getUserdataType(lua_State* L, int32_t arg);

		// Is
		inline static bool isNumber(lua_State* L, int32_t arg)
		{
			return lua_type(L, arg) == LUA_TNUMBER;
		}
		inline static bool isString(lua_State* L, int32_t arg)
		{
			return lua_isstring(L, arg) != 0;
		}
		inline static bool isBoolean(lua_State* L, int32_t arg)
		{
			return lua_isboolean(L, arg);
		}
		inline static bool isTable(lua_State* L, int32_t arg)
		{
			return lua_istable(L, arg);
		}
		inline static bool isFunction(lua_State* L, int32_t arg)
		{
			return lua_isfunction(L, arg);
		}
		inline static bool isUserdata(lua_State* L, int32_t arg)
		{
			return lua_isuserdata(L, arg) != 0;
		}

		// Push
		static void pushBoolean(lua_State* L, bool value);
		static void pushPosition(lua_State* L, const Position& position, int32_t stackpos = 0);
		static void pushOutfit(lua_State* L, const Outfit_t& outfit);

		//
		inline static void setField(lua_State* L, const char* index, lua_Number value)
		{
			lua_pushnumber(L, value);
			lua_setfield(L, -2, index);
		}

		inline static void setField(lua_State* L, const char* index, const std::string& value)
		{
			pushString(L, value);
			lua_setfield(L, -2, index);
		}

		static std::string escapeString(const std::string& string);

#ifndef LUAJIT_VERSION
		static const luaL_Reg luaBitReg[7];
#endif
		static const luaL_Reg luaConfigManagerTable[4];
		static const luaL_Reg luaDatabaseTable[9];
		static const luaL_Reg luaResultTable[6];

		static int protectedCall(lua_State* L, int nargs, int nresults);
