// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../party.hpp"
#include "../../game/game.hpp"
#include "../../config/configmanager.hpp"
#include "../../scripting/events/events.hpp"

extern Game g_game;
extern ConfigManager g_config;
extern Events* g_events;

void Party::updateSharedExperience()
{
	if (sharedExpActive) {
		bool result = canEnableSharedExperience();
		if (result != sharedExpEnabled) {
			sharedExpEnabled = result;
			updateAllPartyIcons();
		}
	}
}


void Party::updateVocationsList()
{
	std::set<uint32_t> vocationIds;

	uint32_t vocationId = leader->getVocation()->getFromVocation();
	if (vocationId != VOCATION_NONE) {
		vocationIds.insert(vocationId);
	}

	for (const Player* member : memberList) {
		vocationId = member->getVocation()->getFromVocation();
		if (vocationId != VOCATION_NONE) {
			vocationIds.insert(vocationId);
		}
	}

	size_t size = vocationIds.size();
	if (size > 1) {
		extraExpRate = static_cast<float>(size * (10 + (size - 1) * 5)) / 100.f;
	} else {
		extraExpRate = 0.20f;
	}
}


bool Party::setSharedExperience(Player* player, bool sharedExpActive)
{
	if (!player || leader != player) {
		return false;
	}

	if (this->sharedExpActive == sharedExpActive) {
		return true;
	}

	this->sharedExpActive = sharedExpActive;

	if (sharedExpActive) {
		this->sharedExpEnabled = canEnableSharedExperience();

		if (this->sharedExpEnabled) {
			leader->sendTextMessage(MESSAGE_INFO_DESCR, "Shared Experience is now active.");
		} else {
			leader->sendTextMessage(MESSAGE_INFO_DESCR, "Shared Experience has been activated, but some members of your party are inactive.");
		}
	} else {
		leader->sendTextMessage(MESSAGE_INFO_DESCR, "Shared Experience has been deactivated.");
	}

	updateAllPartyIcons();
	return true;
}


void Party::shareExperience(uint64_t experience, Creature* source/* = nullptr*/)
{
	uint32_t shareExperience = static_cast<uint64_t>(std::ceil(((static_cast<double>(experience) / (memberList.size() + 1)) + (static_cast<double>(experience) * extraExpRate))));
	for (Player* member : memberList) {
		member->onGainSharedExperience(shareExperience, source);
	}
	leader->onGainSharedExperience(shareExperience, source);
}


bool Party::canUseSharedExperience(const Player* player) const
{
	if (memberList.empty()) {
		return false;
	}

	uint32_t highestLevel = leader->getLevel();
	for (Player* member : memberList) {
		if (member->getLevel() > highestLevel) {
			highestLevel = member->getLevel();
		}
	}

	uint32_t minLevel = static_cast<int32_t>(std::ceil((static_cast<float>(highestLevel) * 2) / 3));
	if (player->getLevel() < minLevel) {
		return false;
	}

	if (!Position::areInRange<30, 30, 1>(leader->getPosition(), player->getPosition())) {
		return false;
	}

	//if (!player->hasFlag(PlayerFlag_NotGainInFight)) {
		//check if the player has healed/attacked anything recently
	//	auto it = ticksMap.find(player->getID());
	//	if (it == ticksMap.end()) {
	//		return false;
	//	}

	//	uint64_t timeDiff = OTSYS_TIME() - it->second;
	//	if (timeDiff > static_cast<uint64_t>(g_config.getNumber(ConfigManager::PZ_LOCKED))) {
	//		return false;
	//	}
	//}
	return true;
}


bool Party::canEnableSharedExperience()
{
	if (!canUseSharedExperience(leader)) {
		return false;
	}

	for (Player* member : memberList) {
		if (!canUseSharedExperience(member)) {
			return false;
		}
	}
	return true;
}


void Party::updatePlayerTicks(Player* player, uint32_t points)
{
	if (points != 0 && !player->hasFlag(PlayerFlag_NotGainInFight)) {
		ticksMap[player->getID()] = OTSYS_TIME();
		updateSharedExperience();
	}
}


void Party::clearPlayerPoints(Player* player)
{
	auto it = ticksMap.find(player->getID());
	if (it != ticksMap.end()) {
		ticksMap.erase(it);
		updateSharedExperience();
	}
}


