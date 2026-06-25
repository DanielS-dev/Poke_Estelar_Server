// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"

void LuaScriptInterface::registerPlayerMonsterNpcBindings()
{
	// Player
	registerClass("Player", "Creature", LuaScriptInterface::luaPlayerCreate);
	registerMetaMethod("Player", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Player", "isPlayer", LuaScriptInterface::luaPlayerIsPlayer);

	registerMethod("Player", "getGuid", LuaScriptInterface::luaPlayerGetGuid);
	registerMethod("Player", "getIp", LuaScriptInterface::luaPlayerGetIp);
	registerMethod("Player", "getAccountId", LuaScriptInterface::luaPlayerGetAccountId);
	registerMethod("Player", "getLastLoginSaved", LuaScriptInterface::luaPlayerGetLastLoginSaved);
	registerMethod("Player", "getLastLogout", LuaScriptInterface::luaPlayerGetLastLogout);

	registerMethod("Player", "getAccountType", LuaScriptInterface::luaPlayerGetAccountType);
	registerMethod("Player", "setAccountType", LuaScriptInterface::luaPlayerSetAccountType);

	registerMethod("Player", "getCapacity", LuaScriptInterface::luaPlayerGetCapacity);
	registerMethod("Player", "setCapacity", LuaScriptInterface::luaPlayerSetCapacity);

	registerMethod("Player", "getFreeCapacity", LuaScriptInterface::luaPlayerGetFreeCapacity);

	registerMethod("Player", "getDepotChest", LuaScriptInterface::luaPlayerGetDepotChest);
	registerMethod("Player", "getInbox", LuaScriptInterface::luaPlayerGetInbox);

	registerMethod("Player", "getSkullTime", LuaScriptInterface::luaPlayerGetSkullTime);
	registerMethod("Player", "setSkullTime", LuaScriptInterface::luaPlayerSetSkullTime);
	registerMethod("Player", "getDeathPenalty", LuaScriptInterface::luaPlayerGetDeathPenalty);

	registerMethod("Player", "getExperience", LuaScriptInterface::luaPlayerGetExperience);
	registerMethod("Player", "addExperience", LuaScriptInterface::luaPlayerAddExperience);
	registerMethod("Player", "removeExperience", LuaScriptInterface::luaPlayerRemoveExperience);
	registerMethod("Player", "getLevel", LuaScriptInterface::luaPlayerGetLevel);

	registerMethod("Player", "getMagicLevel", LuaScriptInterface::luaPlayerGetMagicLevel);
	registerMethod("Player", "getBaseMagicLevel", LuaScriptInterface::luaPlayerGetBaseMagicLevel);
	registerMethod("Player", "setMaxMana", LuaScriptInterface::luaPlayerSetMaxMana);
	registerMethod("Player", "getManaSpent", LuaScriptInterface::luaPlayerGetManaSpent);
	registerMethod("Player", "addManaSpent", LuaScriptInterface::luaPlayerAddManaSpent);

	registerMethod("Player", "getBaseMaxHealth", LuaScriptInterface::luaPlayerGetBaseMaxHealth);
	registerMethod("Player", "getBaseMaxMana", LuaScriptInterface::luaPlayerGetBaseMaxMana);

	registerMethod("Player", "getSkillLevel", LuaScriptInterface::luaPlayerGetSkillLevel);
	registerMethod("Player", "getEffectiveSkillLevel", LuaScriptInterface::luaPlayerGetEffectiveSkillLevel);
	registerMethod("Player", "getSkillPercent", LuaScriptInterface::luaPlayerGetSkillPercent);
	registerMethod("Player", "getSkillTries", LuaScriptInterface::luaPlayerGetSkillTries);
	registerMethod("Player", "addSkillTries", LuaScriptInterface::luaPlayerAddSkillTries);

	registerMethod("Player", "addOfflineTrainingTime", LuaScriptInterface::luaPlayerAddOfflineTrainingTime);
	registerMethod("Player", "getOfflineTrainingTime", LuaScriptInterface::luaPlayerGetOfflineTrainingTime);
	registerMethod("Player", "removeOfflineTrainingTime", LuaScriptInterface::luaPlayerRemoveOfflineTrainingTime);

	registerMethod("Player", "addOfflineTrainingTries", LuaScriptInterface::luaPlayerAddOfflineTrainingTries);

	registerMethod("Player", "getOfflineTrainingSkill", LuaScriptInterface::luaPlayerGetOfflineTrainingSkill);
	registerMethod("Player", "setOfflineTrainingSkill", LuaScriptInterface::luaPlayerSetOfflineTrainingSkill);

	registerMethod("Player", "getItemCount", LuaScriptInterface::luaPlayerGetItemCount);
	registerMethod("Player", "getItemById", LuaScriptInterface::luaPlayerGetItemById);

	registerMethod("Player", "getVocation", LuaScriptInterface::luaPlayerGetVocation);
	registerMethod("Player", "setVocation", LuaScriptInterface::luaPlayerSetVocation);

	registerMethod("Player", "getSex", LuaScriptInterface::luaPlayerGetSex);
	registerMethod("Player", "setSex", LuaScriptInterface::luaPlayerSetSex);

	registerMethod("Player", "getTown", LuaScriptInterface::luaPlayerGetTown);
	registerMethod("Player", "setTown", LuaScriptInterface::luaPlayerSetTown);

	registerMethod("Player", "getGuild", LuaScriptInterface::luaPlayerGetGuild);
	registerMethod("Player", "setGuild", LuaScriptInterface::luaPlayerSetGuild);

	registerMethod("Player", "getGuildLevel", LuaScriptInterface::luaPlayerGetGuildLevel);
	registerMethod("Player", "setGuildLevel", LuaScriptInterface::luaPlayerSetGuildLevel);

	registerMethod("Player", "getGuildNick", LuaScriptInterface::luaPlayerGetGuildNick);
	registerMethod("Player", "setGuildNick", LuaScriptInterface::luaPlayerSetGuildNick);

	registerMethod("Player", "getGroup", LuaScriptInterface::luaPlayerGetGroup);
	registerMethod("Player", "setGroup", LuaScriptInterface::luaPlayerSetGroup);

	registerMethod("Player", "getStamina", LuaScriptInterface::luaPlayerGetStamina);
	registerMethod("Player", "setStamina", LuaScriptInterface::luaPlayerSetStamina);

	registerMethod("Player", "getSoul", LuaScriptInterface::luaPlayerGetSoul);
	registerMethod("Player", "addSoul", LuaScriptInterface::luaPlayerAddSoul);
	registerMethod("Player", "getMaxSoul", LuaScriptInterface::luaPlayerGetMaxSoul);

	registerMethod("Player", "getBankBalance", LuaScriptInterface::luaPlayerGetBankBalance);
	registerMethod("Player", "setBankBalance", LuaScriptInterface::luaPlayerSetBankBalance);

	registerMethod("Player", "getStorageValue", LuaScriptInterface::luaPlayerGetStorageValue);
	registerMethod("Player", "setStorageValue", LuaScriptInterface::luaPlayerSetStorageValue);

	registerMethod("Player", "addItem", LuaScriptInterface::luaPlayerAddItem);
	registerMethod("Player", "addItemEx", LuaScriptInterface::luaPlayerAddItemEx);
	registerMethod("Player", "removeItem", LuaScriptInterface::luaPlayerRemoveItem);

	registerMethod("Player", "getMoney", LuaScriptInterface::luaPlayerGetMoney);
	registerMethod("Player", "addMoney", LuaScriptInterface::luaPlayerAddMoney);
	registerMethod("Player", "removeMoney", LuaScriptInterface::luaPlayerRemoveMoney);

	registerMethod("Player", "showTextDialog", LuaScriptInterface::luaPlayerShowTextDialog);

	registerMethod("Player", "sendTextMessage", LuaScriptInterface::luaPlayerSendTextMessage);
	registerMethod("Player", "sendChannelMessage", LuaScriptInterface::luaPlayerSendChannelMessage);
	registerMethod("Player", "sendPrivateMessage", LuaScriptInterface::luaPlayerSendPrivateMessage);
	registerMethod("Player", "channelSay", LuaScriptInterface::luaPlayerChannelSay);
	registerMethod("Player", "openChannel", LuaScriptInterface::luaPlayerOpenChannel);

	registerMethod("Player", "getSlotItem", LuaScriptInterface::luaPlayerGetSlotItem);

	registerMethod("Player", "getParty", LuaScriptInterface::luaPlayerGetParty);

	registerMethod("Player", "addOutfit", LuaScriptInterface::luaPlayerAddOutfit);
	registerMethod("Player", "addOutfitAddon", LuaScriptInterface::luaPlayerAddOutfitAddon);
	registerMethod("Player", "removeOutfit", LuaScriptInterface::luaPlayerRemoveOutfit);
	registerMethod("Player", "removeOutfitAddon", LuaScriptInterface::luaPlayerRemoveOutfitAddon);
	registerMethod("Player", "hasOutfit", LuaScriptInterface::luaPlayerHasOutfit);
	registerMethod("Player", "sendOutfitWindow", LuaScriptInterface::luaPlayerSendOutfitWindow);

	registerMethod("Player", "addMount", LuaScriptInterface::luaPlayerAddMount);
	registerMethod("Player", "removeMount", LuaScriptInterface::luaPlayerRemoveMount);
	registerMethod("Player", "hasMount", LuaScriptInterface::luaPlayerHasMount);

	registerMethod("Player", "getPremiumDays", LuaScriptInterface::luaPlayerGetPremiumDays);
	registerMethod("Player", "addPremiumDays", LuaScriptInterface::luaPlayerAddPremiumDays);
	registerMethod("Player", "removePremiumDays", LuaScriptInterface::luaPlayerRemovePremiumDays);

	registerMethod("Player", "hasBlessing", LuaScriptInterface::luaPlayerHasBlessing);
	registerMethod("Player", "addBlessing", LuaScriptInterface::luaPlayerAddBlessing);
	registerMethod("Player", "removeBlessing", LuaScriptInterface::luaPlayerRemoveBlessing);

	registerMethod("Player", "canLearnSpell", LuaScriptInterface::luaPlayerCanLearnSpell);
	registerMethod("Player", "learnSpell", LuaScriptInterface::luaPlayerLearnSpell);
	registerMethod("Player", "forgetSpell", LuaScriptInterface::luaPlayerForgetSpell);
	registerMethod("Player", "hasLearnedSpell", LuaScriptInterface::luaPlayerHasLearnedSpell);

	registerMethod("Player", "sendTutorial", LuaScriptInterface::luaPlayerSendTutorial);
	registerMethod("Player", "addMapMark", LuaScriptInterface::luaPlayerAddMapMark);

	registerMethod("Player", "save", LuaScriptInterface::luaPlayerSave);
	registerMethod("Player", "popupFYI", LuaScriptInterface::luaPlayerPopupFYI);

	registerMethod("Player", "isPzLocked", LuaScriptInterface::luaPlayerIsPzLocked);

	registerMethod("Player", "getClient", LuaScriptInterface::luaPlayerGetClient);
	registerMethod("Player", "getHouse", LuaScriptInterface::luaPlayerGetHouse);

	registerMethod("Player", "setGhostMode", LuaScriptInterface::luaPlayerSetGhostMode);

	registerMethod("Player", "getContainerId", LuaScriptInterface::luaPlayerGetContainerId);
	registerMethod("Player", "getContainerById", LuaScriptInterface::luaPlayerGetContainerById);
	registerMethod("Player", "getContainerIndex", LuaScriptInterface::luaPlayerGetContainerIndex);

	// Monster
	registerClass("Monster", "Creature", LuaScriptInterface::luaMonsterCreate);
	registerMetaMethod("Monster", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Monster", "isMonster", LuaScriptInterface::luaMonsterIsMonster);

	registerMethod("Monster", "getType", LuaScriptInterface::luaMonsterGetType);

	registerMethod("Monster", "getSpawnPosition", LuaScriptInterface::luaMonsterGetSpawnPosition);
	registerMethod("Monster", "isInSpawnRange", LuaScriptInterface::luaMonsterIsInSpawnRange);

	registerMethod("Monster", "isIdle", LuaScriptInterface::luaMonsterIsIdle);
	registerMethod("Monster", "setIdle", LuaScriptInterface::luaMonsterSetIdle);

	registerMethod("Monster", "isTarget", LuaScriptInterface::luaMonsterIsTarget);
	registerMethod("Monster", "isOpponent", LuaScriptInterface::luaMonsterIsOpponent);
	registerMethod("Monster", "isFriend", LuaScriptInterface::luaMonsterIsFriend);

	registerMethod("Monster", "addFriend", LuaScriptInterface::luaMonsterAddFriend);
	registerMethod("Monster", "removeFriend", LuaScriptInterface::luaMonsterRemoveFriend);
	registerMethod("Monster", "getFriendList", LuaScriptInterface::luaMonsterGetFriendList);
	registerMethod("Monster", "getFriendCount", LuaScriptInterface::luaMonsterGetFriendCount);

	registerMethod("Monster", "addTarget", LuaScriptInterface::luaMonsterAddTarget);
	registerMethod("Monster", "removeTarget", LuaScriptInterface::luaMonsterRemoveTarget);
	registerMethod("Monster", "getTargetList", LuaScriptInterface::luaMonsterGetTargetList);
	registerMethod("Monster", "getTargetCount", LuaScriptInterface::luaMonsterGetTargetCount);

	registerMethod("Monster", "selectTarget", LuaScriptInterface::luaMonsterSelectTarget);
	registerMethod("Monster", "searchTarget", LuaScriptInterface::luaMonsterSearchTarget);

	//get exp from monsters
	registerMethod("Monster", "getExperience", LuaScriptInterface::luaMonsterGetExperience); //pota
	registerMethod("Monster", "setExperience", LuaScriptInterface::luaMonsterSetExperience); //pota
	registerMethod("Monster", "getLevel", LuaScriptInterface::luaMonsterGetLevel); //pota
	registerMethod("Monster", "getBoost", LuaScriptInterface::luaMonsterGetBoost); //pota

	// Npc
	registerClass("Npc", "Creature", LuaScriptInterface::luaNpcCreate);
	registerMetaMethod("Npc", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Npc", "isNpc", LuaScriptInterface::luaNpcIsNpc);

	registerMethod("Npc", "setMasterPos", LuaScriptInterface::luaNpcSetMasterPos);

	registerMethod("Npc", "getSpeechBubble", LuaScriptInterface::luaNpcGetSpeechBubble);
	registerMethod("Npc", "setSpeechBubble", LuaScriptInterface::luaNpcSetSpeechBubble);
}
