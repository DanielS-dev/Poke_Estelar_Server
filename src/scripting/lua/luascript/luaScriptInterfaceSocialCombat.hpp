// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

// Included inside LuaScriptInterface class declaration by ../luascript.hpp.

		// Guild
		static int luaGuildCreate(lua_State* L);

		static int luaGuildGetId(lua_State* L);
		static int luaGuildGetName(lua_State* L);
		static int luaGuildGetMembersOnline(lua_State* L);

		static int luaGuildAddRank(lua_State* L);
		static int luaGuildGetRankById(lua_State* L);
		static int luaGuildGetRankByLevel(lua_State* L);

		static int luaGuildGetMotd(lua_State* L);
		static int luaGuildSetMotd(lua_State* L);

		// Group
		static int luaGroupCreate(lua_State* L);

		static int luaGroupGetId(lua_State* L);
		static int luaGroupGetName(lua_State* L);
		static int luaGroupGetFlags(lua_State* L);
		static int luaGroupGetAccess(lua_State* L);
		static int luaGroupGetMaxDepotItems(lua_State* L);
		static int luaGroupGetMaxVipEntries(lua_State* L);

		// Vocation
		static int luaVocationCreate(lua_State* L);

		static int luaVocationGetId(lua_State* L);
		static int luaVocationGetClientId(lua_State* L);
		static int luaVocationGetName(lua_State* L);
		static int luaVocationGetDescription(lua_State* L);

		static int luaVocationGetRequiredSkillTries(lua_State* L);
		static int luaVocationGetRequiredManaSpent(lua_State* L);

		static int luaVocationGetCapacityGain(lua_State* L);

		static int luaVocationGetHealthGain(lua_State* L);
		static int luaVocationGetHealthGainTicks(lua_State* L);
		static int luaVocationGetHealthGainAmount(lua_State* L);

		static int luaVocationGetManaGain(lua_State* L);
		static int luaVocationGetManaGainTicks(lua_State* L);
		static int luaVocationGetManaGainAmount(lua_State* L);

		static int luaVocationGetMaxSoul(lua_State* L);
		static int luaVocationGetSoulGainTicks(lua_State* L);

		static int luaVocationGetAttackSpeed(lua_State* L);
		static int luaVocationGetBaseSpeed(lua_State* L);

		static int luaVocationGetDemotion(lua_State* L);
		static int luaVocationGetPromotion(lua_State* L);

		// Town
		static int luaTownCreate(lua_State* L);

		static int luaTownGetId(lua_State* L);
		static int luaTownGetName(lua_State* L);
		static int luaTownGetTemplePosition(lua_State* L);

		// House
		static int luaHouseCreate(lua_State* L);

		static int luaHouseGetId(lua_State* L);
		static int luaHouseGetName(lua_State* L);
		static int luaHouseGetTown(lua_State* L);
		static int luaHouseGetExitPosition(lua_State* L);
		static int luaHouseGetRent(lua_State* L);

		static int luaHouseGetOwnerGuid(lua_State* L);
		static int luaHouseSetOwnerGuid(lua_State* L);

		static int luaHouseGetBeds(lua_State* L);
		static int luaHouseGetBedCount(lua_State* L);

		static int luaHouseGetDoors(lua_State* L);
		static int luaHouseGetDoorCount(lua_State* L);

		static int luaHouseGetTiles(lua_State* L);
		static int luaHouseGetTileCount(lua_State* L);

		static int luaHouseGetAccessList(lua_State* L);
		static int luaHouseSetAccessList(lua_State* L);

		// ItemType
		static int luaItemTypeCreate(lua_State* L);

		static int luaItemTypeIsCorpse(lua_State* L);
		static int luaItemTypeIsDoor(lua_State* L);
		static int luaItemTypeIsContainer(lua_State* L);
		static int luaItemTypeIsFluidContainer(lua_State* L);
		static int luaItemTypeIsMovable(lua_State* L);
		static int luaItemTypeIsRune(lua_State* L);
		static int luaItemTypeIsStackable(lua_State* L);
		static int luaItemTypeIsReadable(lua_State* L);
		static int luaItemTypeIsWritable(lua_State* L);

		static int luaItemTypeGetType(lua_State* L);
		static int luaItemTypeGetId(lua_State* L);
		static int luaItemTypeGetClientId(lua_State* L);
		static int luaItemTypeGetName(lua_State* L);
		static int luaItemTypeGetPluralName(lua_State* L);
		static int luaItemTypeGetArticle(lua_State* L);
		static int luaItemTypeGetDescription(lua_State* L);
		static int luaItemTypeGetSlotPosition(lua_State *L);

		static int luaItemTypeGetCharges(lua_State* L);
		static int luaItemTypeGetFluidSource(lua_State* L);
		static int luaItemTypeGetCapacity(lua_State* L);
		static int luaItemTypeGetWeight(lua_State* L);

		static int luaItemTypeGetHitChance(lua_State* L);
		static int luaItemTypeGetShootRange(lua_State* L);
		static int luaItemTypeGetAttack(lua_State* L);
		static int luaItemTypeGetDefense(lua_State* L);
		static int luaItemTypeGetExtraDefense(lua_State* L);
		static int luaItemTypeGetArmor(lua_State* L);
		static int luaItemTypeGetWeaponType(lua_State* L);

		static int luaItemTypeGetElementType(lua_State* L);
		static int luaItemTypeGetElementDamage(lua_State* L);

		static int luaItemTypeGetTransformEquipId(lua_State* L);
		static int luaItemTypeGetTransformDeEquipId(lua_State* L);
		static int luaItemTypeGetDestroyId(lua_State* L);
		static int luaItemTypeGetDecayId(lua_State* L);
		static int luaItemTypeGetRequiredLevel(lua_State* L);

		static int luaItemTypeHasSubType(lua_State* L);

		// Combat
		static int luaCombatCreate(lua_State* L);

		static int luaCombatSetParameter(lua_State* L);
		static int luaCombatSetFormula(lua_State* L);

		static int luaCombatSetArea(lua_State* L);
		static int luaCombatSetCondition(lua_State* L);
		static int luaCombatSetCallback(lua_State* L);
		static int luaCombatSetOrigin(lua_State* L);

		static int luaCombatExecute(lua_State* L);

		// Condition
		static int luaConditionCreate(lua_State* L);
		static int luaConditionDelete(lua_State* L);

		static int luaConditionGetId(lua_State* L);
		static int luaConditionGetSubId(lua_State* L);
		static int luaConditionGetType(lua_State* L);
		static int luaConditionGetIcons(lua_State* L);
		static int luaConditionGetEndTime(lua_State* L);

		static int luaConditionClone(lua_State* L);

		static int luaConditionGetTicks(lua_State* L);
		static int luaConditionSetTicks(lua_State* L);

		static int luaConditionSetParameter(lua_State* L);
		static int luaConditionSetFormula(lua_State* L);
		static int luaConditionSetOutfit(lua_State* L);

		static int luaConditionAddDamage(lua_State* L);

		// MonsterType
		static int luaMonsterTypeCreate(lua_State* L);

		static int luaMonsterTypeIsAttackable(lua_State* L);
		static int luaMonsterTypeIsConvinceable(lua_State* L);
		static int luaMonsterTypeIsSummonable(lua_State* L);
		static int luaMonsterTypeIsIllusionable(lua_State* L);
		static int luaMonsterTypeIsHostile(lua_State* L);
		static int luaMonsterTypeIsPassive(lua_State* L); //pota

		static int luaMonsterTypeIsFlyable(lua_State* L);
		static int luaMonsterTypeIsRideable(lua_State* L);
		static int luaMonsterTypeIsSurfable(lua_State* L);
		static int luaMonsterTypeCanTeleport(lua_State* L);
		static int luaMonsterTypeCatchChance(lua_State* L);
		static int luaMonsterTypeGetMoveMagicAttackBase(lua_State* L);
		static int luaMonsterTypeGetMoveMagicDefenseBase(lua_State* L);

		static int luaMonsterTypeHasShiny(lua_State* L);
		static int luaMonsterTypeHasMega(lua_State* L);
		static int luaMonsterTypeDexEntry(lua_State* L);
		static int luaMonsterTypePortraitId(lua_State* L);


		static int luaMonsterTypeIsPushable(lua_State* L);
		static int luaMonsterTypeIsHealthShown(lua_State* L);

		static int luaMonsterTypeCanPushItems(lua_State* L);
		static int luaMonsterTypeCanPushCreatures(lua_State* L);

		static int luaMonsterTypeGetName(lua_State* L);
		static int luaMonsterTypeGetNameDescription(lua_State* L);

		static int luaMonsterTypeGetHealth(lua_State* L);
		static int luaMonsterTypeGetMaxHealth(lua_State* L);
		static int luaMonsterTypeGetRunHealth(lua_State* L);
		static int luaMonsterTypeGetExperience(lua_State* L);

		static int luaMonsterTypeGetCombatImmunities(lua_State* L);
		static int luaMonsterTypeGetConditionImmunities(lua_State* L);

		static int luaMonsterTypeGetAttackList(lua_State* L);
		static int luaMonsterTypeGetDefenseList(lua_State* L);
		static int luaMonsterTypeGetElementList(lua_State* L);

		static int luaMonsterTypeGetMoveList(lua_State* L); //pota

		static int luaMonsterTypeGetVoices(lua_State* L);
		static int luaMonsterTypeGetLoot(lua_State* L);

		static int luaMonsterTypeGetCreatureEvents(lua_State* L);

		static int luaMonsterTypeGetSummonList(lua_State* L);
		static int luaMonsterTypeGetEvolutionList(lua_State* L); //pota
		static int luaMonsterTypeGetMaxSummons(lua_State* L);

		static int luaMonsterTypeGetArmor(lua_State* L);
		static int luaMonsterTypeGetDefense(lua_State* L);
		static int luaMonsterTypeGetOutfit(lua_State* L);
		static int luaMonsterTypeGetRace(lua_State* L);
		static int luaMonsterTypeGetRace2(lua_State* L); //pota
		static int luaMonsterTypeGetMinLevel(lua_State* L); //pota
		static int luaMonsterTypeGetMaxLevel(lua_State* L); //pota
		static int luaMonsterTypeGetCorpseId(lua_State* L);
		static int luaMonsterTypeGetManaCost(lua_State* L);
		static int luaMonsterTypeGetBaseSpeed(lua_State* L);
		static int luaMonsterTypeGetLight(lua_State* L);

		static int luaMonsterTypeGetStaticAttackChance(lua_State* L);
		static int luaMonsterTypeGetTargetDistance(lua_State* L);
		static int luaMonsterTypeGetYellChance(lua_State* L);
		static int luaMonsterTypeGetYellSpeedTicks(lua_State* L);
		static int luaMonsterTypeGetChangeTargetChance(lua_State* L);
		static int luaMonsterTypeGetChangeTargetSpeed(lua_State* L);
