// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_MOVEMENT_H_5E0D2626D4634ACA83AC6509518E5F49
#define FS_MOVEMENT_H_5E0D2626D4634ACA83AC6509518E5F49

#include <list>
#include <map>

#include "movementEvent.hpp"

struct MoveEventList {
	std::list<MoveEvent*> moveEvent[MOVE_EVENT_LAST];
};

class MoveEvents final : public BaseEvents
{
	public:
		MoveEvents();
		~MoveEvents();

		// non-copyable
		MoveEvents(const MoveEvents&) = delete;
		MoveEvents& operator=(const MoveEvents&) = delete;

		uint32_t onCreatureMove(Creature* creature, const Tile* tile, MoveEvent_t eventType);
		uint32_t onPlayerEquip(Player* player, Item* item, slots_t slot, bool isCheck);
		uint32_t onPlayerDeEquip(Player* player, Item* item, slots_t slot);
		uint32_t onItemMove(Item* item, Tile* tile, bool isAdd);

		MoveEvent* getEvent(Item* item, MoveEvent_t eventType);

	protected:
		typedef std::map<int32_t, MoveEventList> MoveListMap;
		void clearMap(MoveListMap& map);

		typedef std::map<Position, MoveEventList> MovePosListMap;
		void clear() final;
		LuaScriptInterface& getScriptInterface() final;
		std::string getScriptBaseName() const final;
		Event* getEvent(const std::string& nodeName) final;
		bool registerEvent(Event* event, const pugi::xml_node& node) final;

		void addEvent(MoveEvent* moveEvent, int32_t id, MoveListMap& map);

		void addEvent(MoveEvent* moveEvent, const Position& pos, MovePosListMap& map);
		MoveEvent* getEvent(const Tile* tile, MoveEvent_t eventType);

		MoveEvent* getEvent(Item* item, MoveEvent_t eventType, slots_t slot);

		MoveListMap uniqueIdMap;
		MoveListMap actionIdMap;
		MoveListMap itemIdMap;
		MovePosListMap positionMap;

		LuaScriptInterface scriptInterface;
};

#endif
