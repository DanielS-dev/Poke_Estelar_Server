// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"

void LuaScriptInterface::registerSocialCombatBindings()
{
	// Guild
	registerClass("Guild", "", LuaScriptInterface::luaGuildCreate);
	registerMetaMethod("Guild", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Guild", "getId", LuaScriptInterface::luaGuildGetId);
	registerMethod("Guild", "getName", LuaScriptInterface::luaGuildGetName);
	registerMethod("Guild", "getMembersOnline", LuaScriptInterface::luaGuildGetMembersOnline);

	registerMethod("Guild", "addRank", LuaScriptInterface::luaGuildAddRank);
	registerMethod("Guild", "getRankById", LuaScriptInterface::luaGuildGetRankById);
	registerMethod("Guild", "getRankByLevel", LuaScriptInterface::luaGuildGetRankByLevel);

	registerMethod("Guild", "getMotd", LuaScriptInterface::luaGuildGetMotd);
	registerMethod("Guild", "setMotd", LuaScriptInterface::luaGuildSetMotd);

	// Group
	registerClass("Group", "", LuaScriptInterface::luaGroupCreate);
	registerMetaMethod("Group", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Group", "getId", LuaScriptInterface::luaGroupGetId);
	registerMethod("Group", "getName", LuaScriptInterface::luaGroupGetName);
	registerMethod("Group", "getFlags", LuaScriptInterface::luaGroupGetFlags);
	registerMethod("Group", "getAccess", LuaScriptInterface::luaGroupGetAccess);
	registerMethod("Group", "getMaxDepotItems", LuaScriptInterface::luaGroupGetMaxDepotItems);
	registerMethod("Group", "getMaxVipEntries", LuaScriptInterface::luaGroupGetMaxVipEntries);

	// Vocation
	registerClass("Vocation", "", LuaScriptInterface::luaVocationCreate);
	registerMetaMethod("Vocation", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Vocation", "getId", LuaScriptInterface::luaVocationGetId);
	registerMethod("Vocation", "getClientId", LuaScriptInterface::luaVocationGetClientId);
	registerMethod("Vocation", "getName", LuaScriptInterface::luaVocationGetName);
	registerMethod("Vocation", "getDescription", LuaScriptInterface::luaVocationGetDescription);

	registerMethod("Vocation", "getRequiredSkillTries", LuaScriptInterface::luaVocationGetRequiredSkillTries);
	registerMethod("Vocation", "getRequiredManaSpent", LuaScriptInterface::luaVocationGetRequiredManaSpent);

	registerMethod("Vocation", "getCapacityGain", LuaScriptInterface::luaVocationGetCapacityGain);

	registerMethod("Vocation", "getHealthGain", LuaScriptInterface::luaVocationGetHealthGain);
	registerMethod("Vocation", "getHealthGainTicks", LuaScriptInterface::luaVocationGetHealthGainTicks);
	registerMethod("Vocation", "getHealthGainAmount", LuaScriptInterface::luaVocationGetHealthGainAmount);

	registerMethod("Vocation", "getManaGain", LuaScriptInterface::luaVocationGetManaGain);
	registerMethod("Vocation", "getManaGainTicks", LuaScriptInterface::luaVocationGetManaGainTicks);
	registerMethod("Vocation", "getManaGainAmount", LuaScriptInterface::luaVocationGetManaGainAmount);

	registerMethod("Vocation", "getMaxSoul", LuaScriptInterface::luaVocationGetMaxSoul);
	registerMethod("Vocation", "getSoulGainTicks", LuaScriptInterface::luaVocationGetSoulGainTicks);

	registerMethod("Vocation", "getAttackSpeed", LuaScriptInterface::luaVocationGetAttackSpeed);
	registerMethod("Vocation", "getBaseSpeed", LuaScriptInterface::luaVocationGetBaseSpeed);

	registerMethod("Vocation", "getDemotion", LuaScriptInterface::luaVocationGetDemotion);
	registerMethod("Vocation", "getPromotion", LuaScriptInterface::luaVocationGetPromotion);

	// Town
	registerClass("Town", "", LuaScriptInterface::luaTownCreate);
	registerMetaMethod("Town", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Town", "getId", LuaScriptInterface::luaTownGetId);
	registerMethod("Town", "getName", LuaScriptInterface::luaTownGetName);
	registerMethod("Town", "getTemplePosition", LuaScriptInterface::luaTownGetTemplePosition);

	// House
	registerClass("House", "", LuaScriptInterface::luaHouseCreate);
	registerMetaMethod("House", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("House", "getId", LuaScriptInterface::luaHouseGetId);
	registerMethod("House", "getName", LuaScriptInterface::luaHouseGetName);
	registerMethod("House", "getTown", LuaScriptInterface::luaHouseGetTown);
	registerMethod("House", "getExitPosition", LuaScriptInterface::luaHouseGetExitPosition);
	registerMethod("House", "getRent", LuaScriptInterface::luaHouseGetRent);

	registerMethod("House", "getOwnerGuid", LuaScriptInterface::luaHouseGetOwnerGuid);
	registerMethod("House", "setOwnerGuid", LuaScriptInterface::luaHouseSetOwnerGuid);

	registerMethod("House", "getBeds", LuaScriptInterface::luaHouseGetBeds);
	registerMethod("House", "getBedCount", LuaScriptInterface::luaHouseGetBedCount);

	registerMethod("House", "getDoors", LuaScriptInterface::luaHouseGetDoors);
	registerMethod("House", "getDoorCount", LuaScriptInterface::luaHouseGetDoorCount);

	registerMethod("House", "getTiles", LuaScriptInterface::luaHouseGetTiles);
	registerMethod("House", "getTileCount", LuaScriptInterface::luaHouseGetTileCount);

	registerMethod("House", "getAccessList", LuaScriptInterface::luaHouseGetAccessList);
	registerMethod("House", "setAccessList", LuaScriptInterface::luaHouseSetAccessList);

	// ItemType
	registerClass("ItemType", "", LuaScriptInterface::luaItemTypeCreate);
	registerMetaMethod("ItemType", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("ItemType", "isCorpse", LuaScriptInterface::luaItemTypeIsCorpse);
	registerMethod("ItemType", "isDoor", LuaScriptInterface::luaItemTypeIsDoor);
	registerMethod("ItemType", "isContainer", LuaScriptInterface::luaItemTypeIsContainer);
	registerMethod("ItemType", "isFluidContainer", LuaScriptInterface::luaItemTypeIsFluidContainer);
	registerMethod("ItemType", "isMovable", LuaScriptInterface::luaItemTypeIsMovable);
	registerMethod("ItemType", "isRune", LuaScriptInterface::luaItemTypeIsRune);
	registerMethod("ItemType", "isStackable", LuaScriptInterface::luaItemTypeIsStackable);
	registerMethod("ItemType", "isReadable", LuaScriptInterface::luaItemTypeIsReadable);
	registerMethod("ItemType", "isWritable", LuaScriptInterface::luaItemTypeIsWritable);

	registerMethod("ItemType", "getType", LuaScriptInterface::luaItemTypeGetType);
	registerMethod("ItemType", "getId", LuaScriptInterface::luaItemTypeGetId);
	registerMethod("ItemType", "getClientId", LuaScriptInterface::luaItemTypeGetClientId);
	registerMethod("ItemType", "getName", LuaScriptInterface::luaItemTypeGetName);
	registerMethod("ItemType", "getPluralName", LuaScriptInterface::luaItemTypeGetPluralName);
	registerMethod("ItemType", "getArticle", LuaScriptInterface::luaItemTypeGetArticle);
	registerMethod("ItemType", "getDescription", LuaScriptInterface::luaItemTypeGetDescription);
	registerMethod("ItemType", "getSlotPosition", LuaScriptInterface::luaItemTypeGetSlotPosition);

	registerMethod("ItemType", "getCharges", LuaScriptInterface::luaItemTypeGetCharges);
	registerMethod("ItemType", "getFluidSource", LuaScriptInterface::luaItemTypeGetFluidSource);
	registerMethod("ItemType", "getCapacity", LuaScriptInterface::luaItemTypeGetCapacity);
	registerMethod("ItemType", "getWeight", LuaScriptInterface::luaItemTypeGetWeight);

	registerMethod("ItemType", "getHitChance", LuaScriptInterface::luaItemTypeGetHitChance);
	registerMethod("ItemType", "getShootRange", LuaScriptInterface::luaItemTypeGetShootRange);

	registerMethod("ItemType", "getAttack", LuaScriptInterface::luaItemTypeGetAttack);
	registerMethod("ItemType", "getDefense", LuaScriptInterface::luaItemTypeGetDefense);
	registerMethod("ItemType", "getExtraDefense", LuaScriptInterface::luaItemTypeGetExtraDefense);
	registerMethod("ItemType", "getArmor", LuaScriptInterface::luaItemTypeGetArmor);
	registerMethod("ItemType", "getWeaponType", LuaScriptInterface::luaItemTypeGetWeaponType);

	registerMethod("ItemType", "getElementType", LuaScriptInterface::luaItemTypeGetElementType);
	registerMethod("ItemType", "getElementDamage", LuaScriptInterface::luaItemTypeGetElementDamage);

	registerMethod("ItemType", "getTransformEquipId", LuaScriptInterface::luaItemTypeGetTransformEquipId);
	registerMethod("ItemType", "getTransformDeEquipId", LuaScriptInterface::luaItemTypeGetTransformDeEquipId);
	registerMethod("ItemType", "getDestroyId", LuaScriptInterface::luaItemTypeGetDestroyId);
	registerMethod("ItemType", "getDecayId", LuaScriptInterface::luaItemTypeGetDecayId);
	registerMethod("ItemType", "getRequiredLevel", LuaScriptInterface::luaItemTypeGetRequiredLevel);

	registerMethod("ItemType", "hasSubType", LuaScriptInterface::luaItemTypeHasSubType);

	// Combat
	registerClass("Combat", "", LuaScriptInterface::luaCombatCreate);
	registerMetaMethod("Combat", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Combat", "setParameter", LuaScriptInterface::luaCombatSetParameter);
	registerMethod("Combat", "setFormula", LuaScriptInterface::luaCombatSetFormula);

	registerMethod("Combat", "setArea", LuaScriptInterface::luaCombatSetArea);
	registerMethod("Combat", "setCondition", LuaScriptInterface::luaCombatSetCondition);
	registerMethod("Combat", "setCallback", LuaScriptInterface::luaCombatSetCallback);
	registerMethod("Combat", "setOrigin", LuaScriptInterface::luaCombatSetOrigin);

	registerMethod("Combat", "execute", LuaScriptInterface::luaCombatExecute);

	// Condition
	registerClass("Condition", "", LuaScriptInterface::luaConditionCreate);
	registerMetaMethod("Condition", "__eq", LuaScriptInterface::luaUserdataCompare);
	registerMetaMethod("Condition", "__gc", LuaScriptInterface::luaConditionDelete);
	registerMethod("Condition", "delete", LuaScriptInterface::luaConditionDelete);

	registerMethod("Condition", "getId", LuaScriptInterface::luaConditionGetId);
	registerMethod("Condition", "getSubId", LuaScriptInterface::luaConditionGetSubId);
	registerMethod("Condition", "getType", LuaScriptInterface::luaConditionGetType);
	registerMethod("Condition", "getIcons", LuaScriptInterface::luaConditionGetIcons);
	registerMethod("Condition", "getEndTime", LuaScriptInterface::luaConditionGetEndTime);

	registerMethod("Condition", "clone", LuaScriptInterface::luaConditionClone);

	registerMethod("Condition", "getTicks", LuaScriptInterface::luaConditionGetTicks);
	registerMethod("Condition", "setTicks", LuaScriptInterface::luaConditionSetTicks);

	registerMethod("Condition", "setParameter", LuaScriptInterface::luaConditionSetParameter);
	registerMethod("Condition", "setFormula", LuaScriptInterface::luaConditionSetFormula);
	registerMethod("Condition", "setOutfit", LuaScriptInterface::luaConditionSetOutfit);

	registerMethod("Condition", "addDamage", LuaScriptInterface::luaConditionAddDamage);

	// MonsterType
	registerClass("MonsterType", "", LuaScriptInterface::luaMonsterTypeCreate);
	registerMetaMethod("MonsterType", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("MonsterType", "isAttackable", LuaScriptInterface::luaMonsterTypeIsAttackable);
	registerMethod("MonsterType", "isConvinceable", LuaScriptInterface::luaMonsterTypeIsConvinceable);
	registerMethod("MonsterType", "isSummonable", LuaScriptInterface::luaMonsterTypeIsSummonable);
	registerMethod("MonsterType", "isIllusionable", LuaScriptInterface::luaMonsterTypeIsIllusionable);
	registerMethod("MonsterType", "isHostile", LuaScriptInterface::luaMonsterTypeIsHostile);
	registerMethod("MonsterType", "isPassive", LuaScriptInterface::luaMonsterTypeIsPassive); //pota

	registerMethod("MonsterType", "isFlyable", LuaScriptInterface::luaMonsterTypeIsFlyable);
	registerMethod("MonsterType", "isRideable", LuaScriptInterface::luaMonsterTypeIsRideable);
	registerMethod("MonsterType", "isSurfable", LuaScriptInterface::luaMonsterTypeIsSurfable);
	registerMethod("MonsterType", "canTeleport", LuaScriptInterface::luaMonsterTypeCanTeleport);
	registerMethod("MonsterType", "catchChance", LuaScriptInterface::luaMonsterTypeCatchChance);
	registerMethod("MonsterType", "getMoveMagicAttackBase", LuaScriptInterface::luaMonsterTypeGetMoveMagicAttackBase);
	registerMethod("MonsterType", "getMoveMagicDefenseBase", LuaScriptInterface::luaMonsterTypeGetMoveMagicDefenseBase);

	registerMethod("MonsterType", "hasShiny", LuaScriptInterface::luaMonsterTypeHasShiny);
	registerMethod("MonsterType", "hasMega", LuaScriptInterface::luaMonsterTypeHasMega);
	registerMethod("MonsterType", "dexEntry", LuaScriptInterface::luaMonsterTypeDexEntry);
	registerMethod("MonsterType", "portraitId", LuaScriptInterface::luaMonsterTypePortraitId);

	registerMethod("MonsterType", "isPushable", LuaScriptInterface::luaMonsterTypeIsPushable);
	registerMethod("MonsterType", "isHealthShown", LuaScriptInterface::luaMonsterTypeIsHealthShown);

	registerMethod("MonsterType", "canPushItems", LuaScriptInterface::luaMonsterTypeCanPushItems);
	registerMethod("MonsterType", "canPushCreatures", LuaScriptInterface::luaMonsterTypeCanPushCreatures);

	registerMethod("MonsterType", "getName", LuaScriptInterface::luaMonsterTypeGetName);
	registerMethod("MonsterType", "getNameDescription", LuaScriptInterface::luaMonsterTypeGetNameDescription);

	registerMethod("MonsterType", "getHealth", LuaScriptInterface::luaMonsterTypeGetHealth);
	registerMethod("MonsterType", "getMaxHealth", LuaScriptInterface::luaMonsterTypeGetMaxHealth);
	registerMethod("MonsterType", "getRunHealth", LuaScriptInterface::luaMonsterTypeGetRunHealth);
	registerMethod("MonsterType", "getExperience", LuaScriptInterface::luaMonsterTypeGetExperience);

	registerMethod("MonsterType", "getCombatImmunities", LuaScriptInterface::luaMonsterTypeGetCombatImmunities);
	registerMethod("MonsterType", "getConditionImmunities", LuaScriptInterface::luaMonsterTypeGetConditionImmunities);

	registerMethod("MonsterType", "getAttackList", LuaScriptInterface::luaMonsterTypeGetAttackList);
	registerMethod("MonsterType", "getDefenseList", LuaScriptInterface::luaMonsterTypeGetDefenseList);
	registerMethod("MonsterType", "getElementList", LuaScriptInterface::luaMonsterTypeGetElementList);

	registerMethod("MonsterType", "getMoveList", LuaScriptInterface::luaMonsterTypeGetMoveList); //pota

	registerMethod("MonsterType", "getVoices", LuaScriptInterface::luaMonsterTypeGetVoices);
	registerMethod("MonsterType", "getLoot", LuaScriptInterface::luaMonsterTypeGetLoot);

	registerMethod("MonsterType", "getCreatureEvents", LuaScriptInterface::luaMonsterTypeGetCreatureEvents);

	registerMethod("MonsterType", "getSummonList", LuaScriptInterface::luaMonsterTypeGetSummonList);
	registerMethod("MonsterType", "getEvolutionList", LuaScriptInterface::luaMonsterTypeGetEvolutionList); //pota
	registerMethod("MonsterType", "getMaxSummons", LuaScriptInterface::luaMonsterTypeGetMaxSummons);

	registerMethod("MonsterType", "getArmor", LuaScriptInterface::luaMonsterTypeGetArmor);
	registerMethod("MonsterType", "getDefense", LuaScriptInterface::luaMonsterTypeGetDefense);
	registerMethod("MonsterType", "getOutfit", LuaScriptInterface::luaMonsterTypeGetOutfit);
	registerMethod("MonsterType", "getRace", LuaScriptInterface::luaMonsterTypeGetRace);
	registerMethod("MonsterType", "getRace2", LuaScriptInterface::luaMonsterTypeGetRace2); //pota
	registerMethod("MonsterType", "getMinLevel", LuaScriptInterface::luaMonsterTypeGetMinLevel); //pota
	registerMethod("MonsterType", "getMaxLevel", LuaScriptInterface::luaMonsterTypeGetMaxLevel); //pota
	registerMethod("MonsterType", "getCorpseId", LuaScriptInterface::luaMonsterTypeGetCorpseId);
	registerMethod("MonsterType", "getManaCost", LuaScriptInterface::luaMonsterTypeGetManaCost);
	registerMethod("MonsterType", "getBaseSpeed", LuaScriptInterface::luaMonsterTypeGetBaseSpeed);
	registerMethod("MonsterType", "getLight", LuaScriptInterface::luaMonsterTypeGetLight);

	registerMethod("MonsterType", "getStaticAttackChance", LuaScriptInterface::luaMonsterTypeGetStaticAttackChance);
	registerMethod("MonsterType", "getTargetDistance", LuaScriptInterface::luaMonsterTypeGetTargetDistance);
	registerMethod("MonsterType", "getYellChance", LuaScriptInterface::luaMonsterTypeGetYellChance);
	registerMethod("MonsterType", "getYellSpeedTicks", LuaScriptInterface::luaMonsterTypeGetYellSpeedTicks);
	registerMethod("MonsterType", "getChangeTargetChance", LuaScriptInterface::luaMonsterTypeGetChangeTargetChance);
	registerMethod("MonsterType", "getChangeTargetSpeed", LuaScriptInterface::luaMonsterTypeGetChangeTargetSpeed);
}
