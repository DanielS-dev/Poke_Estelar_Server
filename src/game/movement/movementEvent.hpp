// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_MOVEMENTEVENT_H_292779101153421D9CC712B2DC64A80C
#define FS_MOVEMENTEVENT_H_292779101153421D9CC712B2DC64A80C

#include <string>

#include "movementTypes.hpp"
#include "../../scripting/baseevents.hpp"
#include "../../items/item.hpp"
#include "../../scripting/lua/luascript.hpp"

class MoveEvent final : public Event
{
	public:
		explicit MoveEvent(LuaScriptInterface* interface);
		explicit MoveEvent(const MoveEvent* copy);

		MoveEvent_t getEventType() const;
		void setEventType(MoveEvent_t type);

		bool configureEvent(const pugi::xml_node& node) final;
		bool loadFunction(const pugi::xml_attribute& attr) final;

		uint32_t fireStepEvent(Creature* creature, Item* item, const Position& pos);
		uint32_t fireAddRemItem(Item* item, Item* tileItem, const Position& pos);
		uint32_t fireEquip(Player* player, Item* item, slots_t slot, bool boolean);

		uint32_t getSlot() const;

		//scripting
		bool executeStep(Creature* creature, Item* item, const Position& pos);
		bool executeEquip(Player* player, Item* item, slots_t slot);
		bool executeAddRemItem(Item* item, Item* tileItem, const Position& pos);
		//

		//onEquip information
		uint32_t getReqLevel() const;
		uint32_t getReqMagLv() const;
		bool isPremium() const;
		const std::string& getVocationString() const;
		uint32_t getWieldInfo() const;
		const VocEquipMap& getVocEquipMap() const;

	protected:
		std::string getScriptEventName() const final;

		static StepFunction StepInField;
		static StepFunction StepOutField;

		static MoveFunction AddItemField;
		static MoveFunction RemoveItemField;
		static EquipFunction EquipItem;
		static EquipFunction DeEquipItem;

		MoveEvent_t eventType = MOVE_EVENT_NONE;
		StepFunction* stepFunction = nullptr;
		MoveFunction* moveFunction = nullptr;
		EquipFunction* equipFunction = nullptr;
		uint32_t slot = SLOTP_WHEREEVER;

		//onEquip information
		uint32_t reqLevel = 0;
		uint32_t reqMagLevel = 0;
		bool premium = false;
		std::string vocationString;
		uint32_t wieldInfo = 0;
		VocEquipMap vocEquipMap;
};

#endif
