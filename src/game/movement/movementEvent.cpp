// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "movementEvent.hpp"

MoveEvent::MoveEvent(LuaScriptInterface* interface) : Event(interface) {}

MoveEvent::MoveEvent(const MoveEvent* copy) :
	Event(copy),
	eventType(copy->eventType),
	stepFunction(copy->stepFunction),
	moveFunction(copy->moveFunction),
	equipFunction(copy->equipFunction),
	slot(copy->slot),
	reqLevel(copy->reqLevel),
	reqMagLevel(copy->reqMagLevel),
	premium(copy->premium),
	vocationString(copy->vocationString),
	wieldInfo(copy->wieldInfo),
	vocEquipMap(copy->vocEquipMap) {}

MoveEvent_t MoveEvent::getEventType() const
{
	return eventType;
}

void MoveEvent::setEventType(MoveEvent_t type)
{
	eventType = type;
}

uint32_t MoveEvent::getSlot() const
{
	return slot;
}

uint32_t MoveEvent::getReqLevel() const
{
	return reqLevel;
}

uint32_t MoveEvent::getReqMagLv() const
{
	return reqMagLevel;
}

bool MoveEvent::isPremium() const
{
	return premium;
}

const std::string& MoveEvent::getVocationString() const
{
	return vocationString;
}

uint32_t MoveEvent::getWieldInfo() const
{
	return wieldInfo;
}

const VocEquipMap& MoveEvent::getVocEquipMap() const
{
	return vocEquipMap;
}
