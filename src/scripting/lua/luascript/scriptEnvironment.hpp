// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_SCRIPT_ENVIRONMENT_HPP
#define FS_SCRIPT_ENVIRONMENT_HPP

class ScriptEnvironment
{
	public:
		ScriptEnvironment();
		~ScriptEnvironment();

		// non-copyable
		ScriptEnvironment(const ScriptEnvironment&) = delete;
		ScriptEnvironment& operator=(const ScriptEnvironment&) = delete;

		void resetEnv();

		void setScriptId(int32_t scriptId, LuaScriptInterface* scriptInterface) {
			this->scriptId = scriptId;
			interface = scriptInterface;
		}
		bool setCallbackId(int32_t callbackId, LuaScriptInterface* scriptInterface);

		int32_t getScriptId() const {
			return scriptId;
		}
		LuaScriptInterface* getScriptInterface() {
			return interface;
		}

		void setTimerEvent() {
			timerEvent = true;
		}

		void getEventInfo(int32_t& scriptId, LuaScriptInterface*& scriptInterface, int32_t& callbackId, bool& timerEvent) const;

		void addTempItem(Item* item);
		static void removeTempItem(Item* item);
		uint32_t addThing(Thing* thing);
		void insertItem(uint32_t uid, Item* item);

		static DBResult_ptr getResultByID(uint32_t id);
		static uint32_t addResult(DBResult_ptr res);
		static bool removeResult(uint32_t id);

		void setNpc(Npc* npc) {
			curNpc = npc;
		}
		Npc* getNpc() const {
			return curNpc;
		}

		Thing* getThingByUID(uint32_t uid);
		Item* getItemByUID(uint32_t uid);
		Container* getContainerByUID(uint32_t uid);
		void removeItemByUID(uint32_t uid);

	private:
		typedef std::vector<const LuaVariant*> VariantVector;
		typedef std::map<uint32_t, int32_t> StorageMap;
		typedef std::map<uint32_t, DBResult_ptr> DBResultMap;

		LuaScriptInterface* interface;

		//for npc scripts
		Npc* curNpc = nullptr;

		//temporary item list
		static std::multimap<ScriptEnvironment*, Item*> tempItems;

		//local item map
		std::unordered_map<uint32_t, Item*> localMap;
		uint32_t lastUID = std::numeric_limits<uint16_t>::max();

		//script file id
		int32_t scriptId;
		int32_t callbackId;
		bool timerEvent;

		//result map
		static uint32_t lastResultId;
		static DBResultMap tempResults;
};

#endif
