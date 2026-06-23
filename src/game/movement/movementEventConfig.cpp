// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../../core/pugicast.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/vocation.hpp"

#include "movementEvent.hpp"

extern Vocations g_vocations;

std::string MoveEvent::getScriptEventName() const
{
	switch (eventType) {
		case MOVE_EVENT_STEP_IN: return "onStepIn";
		case MOVE_EVENT_STEP_OUT: return "onStepOut";
		case MOVE_EVENT_EQUIP: return "onEquip";
		case MOVE_EVENT_DEEQUIP: return "onDeEquip";
		case MOVE_EVENT_ADD_ITEM: return "onAddItem";
		case MOVE_EVENT_REMOVE_ITEM: return "onRemoveItem";
		default:
			std::cout << "[Error - MoveEvent::getScriptEventName] Invalid event type" << std::endl;
			return std::string();
	}
}

bool MoveEvent::configureEvent(const pugi::xml_node& node)
{
	pugi::xml_attribute eventAttr = node.attribute("event");
	if (!eventAttr) {
		std::cout << "[Error - MoveEvent::configureMoveEvent] Missing event" << std::endl;
		return false;
	}

	std::string tmpStr = asLowerCaseString(eventAttr.as_string());
	if (tmpStr == "stepin") {
		eventType = MOVE_EVENT_STEP_IN;
	} else if (tmpStr == "stepout") {
		eventType = MOVE_EVENT_STEP_OUT;
	} else if (tmpStr == "equip") {
		eventType = MOVE_EVENT_EQUIP;
	} else if (tmpStr == "deequip") {
		eventType = MOVE_EVENT_DEEQUIP;
	} else if (tmpStr == "additem") {
		eventType = MOVE_EVENT_ADD_ITEM;
	} else if (tmpStr == "removeitem") {
		eventType = MOVE_EVENT_REMOVE_ITEM;
	} else {
		std::cout << "Error: [MoveEvent::configureMoveEvent] No valid event name " << eventAttr.as_string() << std::endl;
		return false;
	}

	if (eventType == MOVE_EVENT_EQUIP || eventType == MOVE_EVENT_DEEQUIP) {
		pugi::xml_attribute slotAttribute = node.attribute("slot");
		if (slotAttribute) {
			tmpStr = asLowerCaseString(slotAttribute.as_string());
			if (tmpStr == "head") {
				slot = SLOTP_HEAD;
			} else if (tmpStr == "necklace") {
				slot = SLOTP_NECKLACE;
			} else if (tmpStr == "backpack") {
				slot = SLOTP_BACKPACK;
			} else if (tmpStr == "armor") {
				slot = SLOTP_ARMOR;
			} else if (tmpStr == "right-hand") {
				slot = SLOTP_RIGHT;
			} else if (tmpStr == "left-hand") {
				slot = SLOTP_LEFT;
			} else if (tmpStr == "hand" || tmpStr == "shield") {
				slot = SLOTP_RIGHT | SLOTP_LEFT;
			} else if (tmpStr == "legs") {
				slot = SLOTP_LEGS;
			} else if (tmpStr == "feet") {
				slot = SLOTP_FEET;
			} else if (tmpStr == "ring") {
				slot = SLOTP_RING;
			} else if (tmpStr == "ammo") {
				slot = SLOTP_AMMO;
			} else if (tmpStr == "order") { //pota
				slot = SLOTP_ORDER;
			} else if (tmpStr == "info") { //pota
				slot = SLOTP_INFO;
			} else {
				std::cout << "[Warning - MoveEvent::configureMoveEvent] Unknown slot type: " << slotAttribute.as_string() << std::endl;
			}
		}

		wieldInfo = 0;

		pugi::xml_attribute levelAttribute = node.attribute("level");
		if (levelAttribute) {
			reqLevel = pugi::cast<uint32_t>(levelAttribute.value());
			if (reqLevel > 0) {
				wieldInfo |= WIELDINFO_LEVEL;
			}
		}

		pugi::xml_attribute magLevelAttribute = node.attribute("maglevel");
		if (magLevelAttribute) {
			reqMagLevel = pugi::cast<uint32_t>(magLevelAttribute.value());
			if (reqMagLevel > 0) {
				wieldInfo |= WIELDINFO_MAGLV;
			}
		}

		pugi::xml_attribute premiumAttribute = node.attribute("premium");
		if (premiumAttribute) {
			premium = premiumAttribute.as_bool();
			if (premium) {
				wieldInfo |= WIELDINFO_PREMIUM;
			}
		}

		//Gather vocation information
		std::list<std::string> vocStringList;
		for (auto vocationNode : node.children()) {
			pugi::xml_attribute vocationNameAttribute = vocationNode.attribute("name");
			if (!vocationNameAttribute) {
				continue;
			}

			int32_t vocationId = g_vocations.getVocationId(vocationNameAttribute.as_string());
			if (vocationId != -1) {
				vocEquipMap[vocationId] = true;
				if (vocationNode.attribute("showInDescription").as_bool(true)) {
					vocStringList.push_back(asLowerCaseString(vocationNameAttribute.as_string()));
				}
			}
		}

		if (!vocEquipMap.empty()) {
			wieldInfo |= WIELDINFO_VOCREQ;
		}

		for (const std::string& str : vocStringList) {
			if (!vocationString.empty()) {
				if (str != vocStringList.back()) {
					vocationString.push_back(',');
					vocationString.push_back(' ');
				} else {
					vocationString += " and ";
				}
			}

			vocationString += str;
			vocationString.push_back('s');
		}
	}
	return true;
}

bool MoveEvent::loadFunction(const pugi::xml_attribute& attr)
{
	const char* functionName = attr.as_string();
	if (strcasecmp(functionName, "onstepinfield") == 0) {
		stepFunction = StepInField;
	} else if (strcasecmp(functionName, "onstepoutfield") == 0) {
		stepFunction = StepOutField;
	} else if (strcasecmp(functionName, "onaddfield") == 0) {
		moveFunction = AddItemField;
	} else if (strcasecmp(functionName, "onremovefield") == 0) {
		moveFunction = RemoveItemField;
	} else if (strcasecmp(functionName, "onequipitem") == 0) {
		equipFunction = EquipItem;
	} else if (strcasecmp(functionName, "ondeequipitem") == 0) {
		equipFunction = DeEquipItem;
	} else {
		std::cout << "[Warning - MoveEvent::loadFunction] Function \"" << functionName << "\" does not exist." << std::endl;
		return false;
	}

	scripted = false;
	return true;
}
