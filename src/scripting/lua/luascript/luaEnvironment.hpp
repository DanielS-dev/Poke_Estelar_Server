// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_LUA_ENVIRONMENT_HPP
#define FS_LUA_ENVIRONMENT_HPP

class LuaEnvironment : public LuaScriptInterface
{
public:
	LuaEnvironment();
		~LuaEnvironment();

		// non-copyable
		LuaEnvironment(const LuaEnvironment&) = delete;
		LuaEnvironment& operator=(const LuaEnvironment&) = delete;

		bool initState();
		bool reInitState();
		bool closeState();

		LuaScriptInterface* getTestInterface();

		Combat* getCombatObject(uint32_t id) const;
		Combat* createCombatObject(LuaScriptInterface* interface);
		void clearCombatObjects(LuaScriptInterface* interface);

		AreaCombat* getAreaObject(uint32_t id) const;
		uint32_t createAreaObject(LuaScriptInterface* interface);
		void clearAreaObjects(LuaScriptInterface* interface);

	private:
		void executeTimerEvent(uint32_t eventIndex);

		std::unordered_map<uint32_t, LuaTimerEventDesc> timerEvents;
		std::unordered_map<uint32_t, Combat*> combatMap;
		std::unordered_map<uint32_t, AreaCombat*> areaMap;

		std::unordered_map<LuaScriptInterface*, std::vector<uint32_t>> combatIdMap;
		std::unordered_map<LuaScriptInterface*, std::vector<uint32_t>> areaIdMap;

		LuaScriptInterface* testInterface = nullptr;

		uint32_t lastEventTimerId = 1;
		uint32_t lastCombatId = 0;
		uint32_t lastAreaId = 0;

	friend class LuaScriptInterface;
	friend class CombatSpell;
};


#endif
