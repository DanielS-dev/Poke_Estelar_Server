// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "actions.hpp"
#include "../../world/bed.hpp"
#include "../../config/configmanager.hpp"
#include "../../items/container.hpp"
#include "../../game/game.hpp"
#include "../../core/logger.hpp"
#include "../../core/pugicast.hpp"
#include "../../game/spells/spells.hpp"

extern Game g_game;
extern Spells* g_spells;
extern Actions* g_actions;
extern ConfigManager g_config;

Actions::Actions() :
	scriptInterface("Action Interface")
{
	scriptInterface.initState();
}

Actions::~Actions()
{
	clear();
}

inline void Actions::clearMap(ActionUseMap& map)
{
	// Filter out duplicates to avoid double-free
	std::unordered_set<Action*> set;
	for (const auto& it : map) {
		set.insert(it.second);
	}
	map.clear();

	for (Action* action : set) {
		delete action;
	}
}

void Actions::clear()
{
	clearMap(useItemMap);
	clearMap(uniqueItemMap);
	clearMap(actionItemMap);

	scriptInterface.reInitState();
}

LuaScriptInterface& Actions::getScriptInterface()
{
	return scriptInterface;
}

std::string Actions::getScriptBaseName() const
{
	return "actions";
}

Event* Actions::getEvent(const std::string& nodeName)
{
	if (strcasecmp(nodeName.c_str(), "action") != 0) {
		return nullptr;
	}
	return new Action(&scriptInterface);
}

bool Actions::registerEvent(Event* event, const pugi::xml_node& node)
{
	Action* action = static_cast<Action*>(event); //event is guaranteed to be an Action

	pugi::xml_attribute attr;
	if ((attr = node.attribute("itemid"))) {
		uint16_t id = pugi::cast<uint16_t>(attr.value());

		auto result = useItemMap.emplace(id, action);
		if (!result.second) {
			LOG_WARN("Scripts", "Duplicate action registration for itemid " + std::to_string(id));
		}
		return result.second;
	} else if ((attr = node.attribute("fromid"))) {
		pugi::xml_attribute toIdAttribute = node.attribute("toid");
		if (!toIdAttribute) {
			LOG_WARN("Scripts", "Action range is missing toid for fromid " + std::string(attr.as_string()));
			return false;
		}

		uint16_t fromId = pugi::cast<uint16_t>(attr.value());
		uint16_t iterId = fromId;
		uint16_t toId = pugi::cast<uint16_t>(toIdAttribute.value());

		auto result = useItemMap.emplace(iterId, action);
		if (!result.second) {
			LOG_WARN("Scripts", "Duplicate action registration for itemid " + std::to_string(iterId) +
				" in range " + std::to_string(fromId) + "-" + std::to_string(toId));
		}

		bool success = result.second;
		while (++iterId <= toId) {
			result = useItemMap.emplace(iterId, action);
			if (!result.second) {
				LOG_WARN("Scripts", "Duplicate action registration for itemid " + std::to_string(iterId) +
					" in range " + std::to_string(fromId) + "-" + std::to_string(toId));
				continue;
			}
			success = true;
		}
		return success;
	} else if ((attr = node.attribute("uniqueid"))) {
		uint16_t uid = pugi::cast<uint16_t>(attr.value());

		auto result = uniqueItemMap.emplace(uid, action);
		if (!result.second) {
			LOG_WARN("Scripts", "Duplicate action registration for uniqueid " + std::to_string(uid));
		}
		return result.second;
	} else if ((attr = node.attribute("fromuid"))) {
		pugi::xml_attribute toUidAttribute = node.attribute("touid");
		if (!toUidAttribute) {
			LOG_WARN("Scripts", "Action range is missing touid for fromuid " + std::string(attr.as_string()));
			return false;
		}

		uint16_t fromUid = pugi::cast<uint16_t>(attr.value());
		uint16_t iterUid = fromUid;
		uint16_t toUid = pugi::cast<uint16_t>(toUidAttribute.value());

		auto result = uniqueItemMap.emplace(iterUid, action);
		if (!result.second) {
			LOG_WARN("Scripts", "Duplicate action registration for uniqueid " + std::to_string(iterUid) +
				" in range " + std::to_string(fromUid) + "-" + std::to_string(toUid));
		}

		bool success = result.second;
		while (++iterUid <= toUid) {
			result = uniqueItemMap.emplace(iterUid, action);
			if (!result.second) {
				LOG_WARN("Scripts", "Duplicate action registration for uniqueid " + std::to_string(iterUid) +
					" in range " + std::to_string(fromUid) + "-" + std::to_string(toUid));
				continue;
			}
			success = true;
		}
		return success;
	} else if ((attr = node.attribute("actionid"))) {
		uint16_t aid = pugi::cast<uint16_t>(attr.value());

		auto result = actionItemMap.emplace(aid, action);
		if (!result.second) {
			LOG_WARN("Scripts", "Duplicate action registration for actionid " + std::to_string(aid));
		}
		return result.second;
	} else if ((attr = node.attribute("fromaid"))) {
		pugi::xml_attribute toAidAttribute = node.attribute("toaid");
		if (!toAidAttribute) {
			LOG_WARN("Scripts", "Action range is missing toaid for fromaid " + std::string(attr.as_string()));
			return false;
		}

		uint16_t fromAid = pugi::cast<uint16_t>(attr.value());
		uint16_t iterAid = fromAid;
		uint16_t toAid = pugi::cast<uint16_t>(toAidAttribute.value());

		auto result = actionItemMap.emplace(iterAid, action);
		if (!result.second) {
			LOG_WARN("Scripts", "Duplicate action registration for actionid " + std::to_string(iterAid) +
				" in range " + std::to_string(fromAid) + "-" + std::to_string(toAid));
		}

		bool success = result.second;
		while (++iterAid <= toAid) {
			result = actionItemMap.emplace(iterAid, action);
			if (!result.second) {
				LOG_WARN("Scripts", "Duplicate action registration for actionid " + std::to_string(iterAid) +
					" in range " + std::to_string(fromAid) + "-" + std::to_string(toAid));
				continue;
			}
			success = true;
		}
		return success;
	}
	return false;
}

Action* Actions::getAction(const Item* item)
{
	if (item->hasAttribute(ITEM_ATTRIBUTE_UNIQUEID)) {
		auto it = uniqueItemMap.find(item->getUniqueId());
		if (it != uniqueItemMap.end()) {
			return it->second;
		}
	}

	if (item->hasAttribute(ITEM_ATTRIBUTE_ACTIONID)) {
		auto it = actionItemMap.find(item->getActionId());
		if (it != actionItemMap.end()) {
			return it->second;
		}
	}

	auto it = useItemMap.find(item->getID());
	if (it != useItemMap.end()) {
		return it->second;
	}

	//rune items
	return g_spells->getRuneSpell(item->getID());
}
