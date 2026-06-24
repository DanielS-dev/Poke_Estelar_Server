// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <boost/range/adaptor/reversed.hpp>

#include "../luascript.hpp"
#include "../../events/events.hpp"
#include "../../../game/chat/chat.hpp"
#include "../../../entities/player.hpp"
#include "../../../game/game.hpp"
#include "../../../network/protocolstatus.hpp"
#include "../../../game/spells/spells.hpp"
#include "../../../persistence/login/iologindata.hpp"
#include "../../../config/configmanager.hpp"
#include "../../../world/teleport.hpp"
#include "../../../persistence/databasemanager.hpp"
#include "../../../world/bed.hpp"
#include "../../../entities/monster.hpp"
#include "../../../core/scheduler.hpp"
#include "../../../persistence/databasetasks.hpp"
#include "../../../core/tools/random.hpp"
#include "../../../core/tools/gameEnumTools.hpp"
#include "../../../core/tools/returnMessageTools.hpp"
#include "../../../core/tools/stringsTools.hpp"

extern Chat* g_chat;
extern Game g_game;
extern Monsters g_monsters;
extern ConfigManager g_config;
extern Vocations g_vocations;
extern Spells* g_spells;
extern Events* g_events;

int LuaScriptInterface::luaPlayerGetCapacity(lua_State* L)
{
	// player:getCapacity()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getCapacity());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetCapacity(lua_State* L)
{
	// player:setCapacity(capacity)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->capacity = getNumber<uint32_t>(L, 2);
		player->sendStats();
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetFreeCapacity(lua_State* L)
{
	// player:getFreeCapacity()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getFreeCapacity());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetDepotChest(lua_State* L)
{
	// player:getDepotChest(depotId[, autoCreate = false])
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	uint32_t depotId = getNumber<uint32_t>(L, 2);
	bool autoCreate = getBoolean(L, 3, false);
	DepotChest* depotChest = player->getDepotChest(depotId, autoCreate);
	if (depotChest) {
		player->setLastDepotId(depotId); // FIXME: workaround for #2251
		pushUserdata<Item>(L, depotChest);
		setItemMetatable(L, -1, depotChest);
	} else {
		pushBoolean(L, false);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetInbox(lua_State* L)
{
	// player:getInbox()
	Player* player = getUserdata<Player>(L, 1);
	if (!player) {
		lua_pushnil(L);
		return 1;
	}

	Inbox* inbox = player->getInbox();
	if (inbox) {
		pushUserdata<Item>(L, inbox);
		setItemMetatable(L, -1, inbox);
	} else {
		pushBoolean(L, false);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetSkullTime(lua_State* L)
{
	// player:getSkullTime()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getSkullTicks());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetSkullTime(lua_State* L)
{
	// player:setSkullTime(skullTime)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->setSkullTicks(getNumber<int64_t>(L, 2));
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetDeathPenalty(lua_State* L)
{
	// player:getDeathPenalty()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, static_cast<uint32_t>(player->getLostPercent() * 100));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetExperience(lua_State* L)
{
	// player:getExperience()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getExperience());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddExperience(lua_State* L)
{
	// player:addExperience(experience[, sendText = false])
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		int64_t experience = getNumber<int64_t>(L, 2);
		bool sendText = getBoolean(L, 3, false);
		player->addExperience(nullptr, experience, sendText);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerRemoveExperience(lua_State* L)
{
	// player:removeExperience(experience[, sendText = false])
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		int64_t experience = getNumber<int64_t>(L, 2);
		bool sendText = getBoolean(L, 3, false);
		player->removeExperience(experience, sendText);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetLevel(lua_State* L)
{
	// player:getLevel()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getLevel());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetMagicLevel(lua_State* L)
{
	// player:getMagicLevel()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getMagicLevel());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetBaseMagicLevel(lua_State* L)
{
	// player:getBaseMagicLevel()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getBaseMagicLevel());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetMaxMana(lua_State* L)
{
	// player:setMaxMana(maxMana)
	Player* player = getPlayer(L, 1);
	if (player) {
		player->manaMax = getNumber<int32_t>(L, 2);
		player->mana = std::min<int32_t>(player->mana, player->manaMax);
		player->sendStats();
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetManaSpent(lua_State* L)
{
	// player:getManaSpent()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getSpentMana());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddManaSpent(lua_State* L)
{
	// player:addManaSpent(amount)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->addManaSpent(getNumber<uint64_t>(L, 2));
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetBaseMaxHealth(lua_State* L)
{
	// player:getBaseMaxHealth()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->healthMax);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetBaseMaxMana(lua_State* L)
{
	// player:getBaseMaxMana()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->manaMax);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetSkillLevel(lua_State* L)
{
	// player:getSkillLevel(skillType)
	skills_t skillType = getNumber<skills_t>(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player && skillType <= SKILL_LAST) {
		lua_pushnumber(L, player->skills[skillType].level);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetEffectiveSkillLevel(lua_State* L)
{
	// player:getEffectiveSkillLevel(skillType)
	skills_t skillType = getNumber<skills_t>(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player && skillType <= SKILL_LAST) {
		lua_pushnumber(L, player->getSkillLevel(skillType));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetSkillPercent(lua_State* L)
{
	// player:getSkillPercent(skillType)
	skills_t skillType = getNumber<skills_t>(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player && skillType <= SKILL_LAST) {
		lua_pushnumber(L, player->skills[skillType].percent);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetSkillTries(lua_State* L)
{
	// player:getSkillTries(skillType)
	skills_t skillType = getNumber<skills_t>(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player && skillType <= SKILL_LAST) {
		lua_pushnumber(L, player->skills[skillType].tries);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddSkillTries(lua_State* L)
{
	// player:addSkillTries(skillType, tries)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		skills_t skillType = getNumber<skills_t>(L, 2);
		uint64_t tries = getNumber<uint64_t>(L, 3);
		player->addSkillAdvance(skillType, tries);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddOfflineTrainingTime(lua_State* L)
{
	// player:addOfflineTrainingTime(time)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		int32_t time = getNumber<int32_t>(L, 2);
		player->addOfflineTrainingTime(time);
		player->sendStats();
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetOfflineTrainingTime(lua_State* L)
{
	// player:getOfflineTrainingTime()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getOfflineTrainingTime());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerRemoveOfflineTrainingTime(lua_State* L)
{
	// player:removeOfflineTrainingTime(time)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		int32_t time = getNumber<int32_t>(L, 2);
		player->removeOfflineTrainingTime(time);
		player->sendStats();
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddOfflineTrainingTries(lua_State* L)
{
	// player:addOfflineTrainingTries(skillType, tries)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		skills_t skillType = getNumber<skills_t>(L, 2);
		uint64_t tries = getNumber<uint64_t>(L, 3);
		pushBoolean(L, player->addOfflineTrainingTries(skillType, tries));
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetOfflineTrainingSkill(lua_State* L)
{
	// player:getOfflineTrainingSkill()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getOfflineTrainingSkill());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetOfflineTrainingSkill(lua_State* L)
{
	// player:setOfflineTrainingSkill(skillId)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		uint32_t skillId = getNumber<uint32_t>(L, 2);
		player->setOfflineTrainingSkill(skillId);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetStamina(lua_State* L)
{
	// player:getStamina()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getStaminaMinutes());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetStamina(lua_State* L)
{
	// player:setStamina(stamina)
	uint16_t stamina = getNumber<uint16_t>(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->staminaMinutes = std::min<uint16_t>(2520, stamina);
		player->sendStats();
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetSoul(lua_State* L)
{
	// player:getSoul()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getSoul());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerAddSoul(lua_State* L)
{
	// player:addSoul(soulChange)
	int32_t soulChange = getNumber<int32_t>(L, 2);
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->changeSoul(soulChange);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetMaxSoul(lua_State* L)
{
	// player:getMaxSoul()
	Player* player = getUserdata<Player>(L, 1);
	if (player && player->vocation) {
		lua_pushnumber(L, player->vocation->getSoulMax());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerGetBankBalance(lua_State* L)
{
	// player:getBankBalance()
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		lua_pushnumber(L, player->getBankBalance());
	} else {
		lua_pushnil(L);
	}
	return 1;
}


int LuaScriptInterface::luaPlayerSetBankBalance(lua_State* L)
{
	// player:setBankBalance(bankBalance)
	Player* player = getUserdata<Player>(L, 1);
	if (player) {
		player->setBankBalance(getNumber<uint64_t>(L, 2));
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}


