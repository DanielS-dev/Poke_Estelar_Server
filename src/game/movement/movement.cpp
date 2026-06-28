// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <sstream>

#include "../game.hpp"

#include "../../core/logger.hpp"
#include "../../core/pugicast.hpp"

#include "movement.hpp"
#include "../../core/tools/stringsTools.hpp"

extern Game g_game;
extern Vocations g_vocations;

MoveEvents::MoveEvents() :
	scriptInterface("MoveEvents Interface")
{
	scriptInterface.initState();
}

MoveEvents::~MoveEvents()
{
	clear();
}

void MoveEvents::clearMap(MoveListMap& map)
{
	std::unordered_set<MoveEvent*> set;
	for (const auto& it : map) {
		const MoveEventList& moveEventList = it.second;
		for (const auto& i : moveEventList.moveEvent) {
			for (MoveEvent* moveEvent : i) {
				set.insert(moveEvent);
			}
		}
	}
	map.clear();

	for (MoveEvent* moveEvent : set) {
		delete moveEvent;
	}
}

void MoveEvents::clear()
{
	clearMap(itemIdMap);
	clearMap(actionIdMap);
	clearMap(uniqueIdMap);

	for (const auto& it : positionMap) {
		const MoveEventList& moveEventList = it.second;
		for (const auto& i : moveEventList.moveEvent) {
			for (MoveEvent* moveEvent : i) {
				delete moveEvent;
			}
		}
	}
	positionMap.clear();

	scriptInterface.reInitState();
}

LuaScriptInterface& MoveEvents::getScriptInterface()
{
	return scriptInterface;
}

std::string MoveEvents::getScriptBaseName() const
{
	return "movements";
}

Event* MoveEvents::getEvent(const std::string& nodeName)
{
	if (strcasecmp(nodeName.c_str(), "movevent") != 0) {
		return nullptr;
	}
	return new MoveEvent(&scriptInterface);
}

bool MoveEvents::registerEvent(Event* event, const pugi::xml_node& node)
{
	MoveEvent* moveEvent = static_cast<MoveEvent*>(event); //event is guaranteed to be a MoveEvent

	const MoveEvent_t eventType = moveEvent->getEventType();
	if (eventType == MOVE_EVENT_ADD_ITEM || eventType == MOVE_EVENT_REMOVE_ITEM) {
		pugi::xml_attribute tileItemAttribute = node.attribute("tileitem");
		if (tileItemAttribute && pugi::cast<uint16_t>(tileItemAttribute.value()) == 1) {
			switch (eventType) {
				case MOVE_EVENT_ADD_ITEM:
					moveEvent->setEventType(MOVE_EVENT_ADD_ITEM_ITEMTILE);
					break;
				case MOVE_EVENT_REMOVE_ITEM:
					moveEvent->setEventType(MOVE_EVENT_REMOVE_ITEM_ITEMTILE);
					break;
				default:
					break;
			}
		}
	}

	pugi::xml_attribute attr;
	if ((attr = node.attribute("itemid"))) {
		int32_t id = pugi::cast<int32_t>(attr.value());
		addEvent(moveEvent, id, itemIdMap);
		if (moveEvent->getEventType() == MOVE_EVENT_EQUIP) {
			ItemType& it = Item::items.getItemType(id);
			it.wieldInfo = moveEvent->getWieldInfo();
			it.minReqLevel = moveEvent->getReqLevel();
			it.minReqMagicLevel = moveEvent->getReqMagLv();
			it.vocationString = moveEvent->getVocationString();
		}
	} else if ((attr = node.attribute("fromid"))) {
		uint32_t id = pugi::cast<uint32_t>(attr.value());
		uint32_t endId = pugi::cast<uint32_t>(node.attribute("toid").value());

		addEvent(moveEvent, id, itemIdMap);

		if (moveEvent->getEventType() == MOVE_EVENT_EQUIP) {
			ItemType& it = Item::items.getItemType(id);
			it.wieldInfo = moveEvent->getWieldInfo();
			it.minReqLevel = moveEvent->getReqLevel();
			it.minReqMagicLevel = moveEvent->getReqMagLv();
			it.vocationString = moveEvent->getVocationString();

			while (++id <= endId) {
				addEvent(moveEvent, id, itemIdMap);

				ItemType& tit = Item::items.getItemType(id);
				tit.wieldInfo = moveEvent->getWieldInfo();
				tit.minReqLevel = moveEvent->getReqLevel();
				tit.minReqMagicLevel = moveEvent->getReqMagLv();
				tit.vocationString = moveEvent->getVocationString();
			}
		} else {
			while (++id <= endId) {
				addEvent(moveEvent, id, itemIdMap);
			}
		}
	} else if ((attr = node.attribute("uniqueid"))) {
		addEvent(moveEvent, pugi::cast<int32_t>(attr.value()), uniqueIdMap);
	} else if ((attr = node.attribute("fromuid"))) {
		uint32_t id = pugi::cast<uint32_t>(attr.value());
		uint32_t endId = pugi::cast<uint32_t>(node.attribute("touid").value());
		addEvent(moveEvent, id, uniqueIdMap);
		while (++id <= endId) {
			addEvent(moveEvent, id, uniqueIdMap);
		}
	} else if ((attr = node.attribute("actionid"))) {
		addEvent(moveEvent, pugi::cast<int32_t>(attr.value()), actionIdMap);
	} else if ((attr = node.attribute("fromaid"))) {
		uint32_t id = pugi::cast<uint32_t>(attr.value());
		uint32_t endId = pugi::cast<uint32_t>(node.attribute("toaid").value());
		addEvent(moveEvent, id, actionIdMap);
		while (++id <= endId) {
			addEvent(moveEvent, id, actionIdMap);
		}
	} else if ((attr = node.attribute("pos"))) {
		std::vector<int32_t> posList = vectorAtoi(explodeString(attr.as_string(), ";"));
		if (posList.size() < 3) {
			return false;
		}

		Position pos(posList[0], posList[1], posList[2]);
		addEvent(moveEvent, pos, positionMap);
	} else {
		return false;
	}
	return true;
}

void MoveEvents::addEvent(MoveEvent* moveEvent, int32_t id, MoveListMap& map)
{
	auto it = map.find(id);
	if (it == map.end()) {
		MoveEventList moveEventList;
		moveEventList.moveEvent[moveEvent->getEventType()].push_back(moveEvent);
		map[id] = moveEventList;
	} else {
		std::list<MoveEvent*>& moveEventList = it->second.moveEvent[moveEvent->getEventType()];
		for (MoveEvent* existingMoveEvent : moveEventList) {
			if (existingMoveEvent->getSlot() == moveEvent->getSlot()) {
				LOG_WARN("Scripts", "Duplicate move event registration for id " + std::to_string(id));
			}
		}
		moveEventList.push_back(moveEvent);
	}
}

MoveEvent* MoveEvents::getEvent(Item* item, MoveEvent_t eventType, slots_t slot)
{
	uint32_t slotp;
	switch (slot) {
		case CONST_SLOT_HEAD: slotp = SLOTP_HEAD; break;
		case CONST_SLOT_NECKLACE: slotp = SLOTP_NECKLACE; break;
		case CONST_SLOT_BACKPACK: slotp = SLOTP_BACKPACK; break;
		case CONST_SLOT_ARMOR: slotp = SLOTP_ARMOR; break;
		case CONST_SLOT_RIGHT: slotp = SLOTP_RIGHT; break;
		case CONST_SLOT_LEFT: slotp = SLOTP_LEFT; break;
		case CONST_SLOT_LEGS: slotp = SLOTP_LEGS; break;
		case CONST_SLOT_FEET: slotp = SLOTP_FEET; break;
		case CONST_SLOT_AMMO: slotp = SLOTP_AMMO; break;
		case CONST_SLOT_RING: slotp = SLOTP_RING; break;
		case CONST_SLOT_ORDER: slotp = SLOTP_ORDER; break; //pota
		case CONST_SLOT_INFO: slotp = SLOTP_INFO; break; //pota
		default: slotp = 0; break;
	}

	auto it = itemIdMap.find(item->getID());
	if (it != itemIdMap.end()) {
		std::list<MoveEvent*>& moveEventList = it->second.moveEvent[eventType];
		for (MoveEvent* moveEvent : moveEventList) {
			if ((moveEvent->getSlot() & slotp) != 0) {
				return moveEvent;
			}
		}
	}
	return nullptr;
}

MoveEvent* MoveEvents::getEvent(Item* item, MoveEvent_t eventType)
{
	MoveListMap::iterator it;

	if (item->hasAttribute(ITEM_ATTRIBUTE_UNIQUEID)) {
		it = uniqueIdMap.find(item->getUniqueId());
		if (it != uniqueIdMap.end()) {
			std::list<MoveEvent*>& moveEventList = it->second.moveEvent[eventType];
			if (!moveEventList.empty()) {
				return *moveEventList.begin();
			}
		}
	}

	if (item->hasAttribute(ITEM_ATTRIBUTE_ACTIONID)) {
		it = actionIdMap.find(item->getActionId());
		if (it != actionIdMap.end()) {
			std::list<MoveEvent*>& moveEventList = it->second.moveEvent[eventType];
			if (!moveEventList.empty()) {
				return *moveEventList.begin();
			}
		}
	}

	it = itemIdMap.find(item->getID());
	if (it != itemIdMap.end()) {
		std::list<MoveEvent*>& moveEventList = it->second.moveEvent[eventType];
		if (!moveEventList.empty()) {
			return *moveEventList.begin();
		}
	}
	return nullptr;
}

void MoveEvents::addEvent(MoveEvent* moveEvent, const Position& pos, MovePosListMap& map)
{
	auto it = map.find(pos);
	if (it == map.end()) {
		MoveEventList moveEventList;
		moveEventList.moveEvent[moveEvent->getEventType()].push_back(moveEvent);
		map[pos] = moveEventList;
	} else {
		std::list<MoveEvent*>& moveEventList = it->second.moveEvent[moveEvent->getEventType()];
		if (!moveEventList.empty()) {
			std::ostringstream message;
			message << "Duplicate move event registration for position " << pos;
			LOG_WARN("Scripts", message.str());
		}

		moveEventList.push_back(moveEvent);
	}
}

MoveEvent* MoveEvents::getEvent(const Tile* tile, MoveEvent_t eventType)
{
	auto it = positionMap.find(tile->getPosition());
	if (it != positionMap.end()) {
		std::list<MoveEvent*>& moveEventList = it->second.moveEvent[eventType];
		if (!moveEventList.empty()) {
			return *moveEventList.begin();
		}
	}
	return nullptr;
}

uint32_t MoveEvents::onCreatureMove(Creature* creature, const Tile* tile, MoveEvent_t eventType)
{
	const Position& pos = tile->getPosition();

	uint32_t ret = 1;

	MoveEvent* moveEvent = getEvent(tile, eventType);
	if (moveEvent) {
		ret &= moveEvent->fireStepEvent(creature, nullptr, pos);
	}

	for (size_t i = tile->getFirstIndex(), j = tile->getLastIndex(); i < j; ++i) {
		Thing* thing = tile->getThing(i);
		if (!thing) {
			continue;
		}

		Item* tileItem = thing->getItem();
		if (!tileItem) {
			continue;
		}

		moveEvent = getEvent(tileItem, eventType);
		if (moveEvent) {
			ret &= moveEvent->fireStepEvent(creature, tileItem, pos);
		}
	}
	return ret;
}

uint32_t MoveEvents::onPlayerEquip(Player* player, Item* item, slots_t slot, bool isCheck)
{
	MoveEvent* moveEvent = getEvent(item, MOVE_EVENT_EQUIP, slot);
	if (!moveEvent) {
		return 1;
	}
	return moveEvent->fireEquip(player, item, slot, isCheck);
}

uint32_t MoveEvents::onPlayerDeEquip(Player* player, Item* item, slots_t slot)
{
	MoveEvent* moveEvent = getEvent(item, MOVE_EVENT_DEEQUIP, slot);
	if (!moveEvent) {
		return 1;
	}
	return moveEvent->fireEquip(player, item, slot, true);
}

uint32_t MoveEvents::onItemMove(Item* item, Tile* tile, bool isAdd)
{
	MoveEvent_t eventType1, eventType2;
	if (isAdd) {
		eventType1 = MOVE_EVENT_ADD_ITEM;
		eventType2 = MOVE_EVENT_ADD_ITEM_ITEMTILE;
	} else {
		eventType1 = MOVE_EVENT_REMOVE_ITEM;
		eventType2 = MOVE_EVENT_REMOVE_ITEM_ITEMTILE;
	}

	uint32_t ret = 1;
	MoveEvent* moveEvent = getEvent(tile, eventType1);
	if (moveEvent) {
		ret &= moveEvent->fireAddRemItem(item, nullptr, tile->getPosition());
	}

	moveEvent = getEvent(item, eventType1);
	if (moveEvent) {
		ret &= moveEvent->fireAddRemItem(item, nullptr, tile->getPosition());
	}

	for (size_t i = tile->getFirstIndex(), j = tile->getLastIndex(); i < j; ++i) {
		Thing* thing = tile->getThing(i);
		if (!thing) {
			continue;
		}

		Item* tileItem = thing->getItem();
		if (!tileItem || tileItem == item) {
			continue;
		}

		moveEvent = getEvent(tileItem, eventType2);
		if (moveEvent) {
			ret &= moveEvent->fireAddRemItem(item, tileItem, tile->getPosition());
		}
	}
	return ret;
}
