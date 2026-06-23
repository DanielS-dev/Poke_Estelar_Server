// This file is part of The Forgotten Server.

// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../combat.hpp"
#include "../game.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/monsters.hpp"
#include "../../entities/vocation.hpp"
#include "../../items/items.hpp"

#include "spell.hpp"

extern Game g_game;
extern Monsters g_monsters;
extern Vocations g_vocations;

void Spell::postCastSpell(Player* player, bool finishedCast /*= true*/, bool payCost /*= true*/) const
{
	if (finishedCast) {
		if (!player->hasFlag(PlayerFlag_HasNoExhaustion)) {
			if (cooldown > 0) {
				Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLCOOLDOWN, cooldown, 0, false, spellId);
				player->addCondition(condition);
			}

			if (groupCooldown > 0) {
				Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLGROUPCOOLDOWN, groupCooldown, 0, false, group);
				player->addCondition(condition);
			}

			if (secondaryGroupCooldown > 0) {
				Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_SPELLGROUPCOOLDOWN, secondaryGroupCooldown, 0, false, secondaryGroup);
				player->addCondition(condition);
			}
		}

		if (aggressive) {
			player->addInFightTicks();
		}
	}

	if (payCost) {
		Spell::postCastSpell(player, getManaCost(player), getSoulCost());
	}
}

void Spell::postCastSpell(Player* player, uint32_t manaCost, uint32_t soulCost)
{
	if (manaCost > 0) {
		player->addManaSpent(manaCost);
		player->changeMana(-static_cast<int32_t>(manaCost));
	}

	if (!player->hasFlag(PlayerFlag_HasInfiniteSoul)) {
		if (soulCost > 0) {
			player->changeSoul(-static_cast<int32_t>(soulCost));
		}
	}
}

uint32_t Spell::getManaCost(const Player* player) const
{
	if (mana != 0) {
		return mana;
	}

	if (manaPercent != 0) {
		uint32_t maxMana = player->getMaxMana();
		uint32_t manaCost = (maxMana * manaPercent) / 100;
		return manaCost;
	}

	return 0;
}

ReturnValue Spell::CreateIllusion(Creature* creature, const Outfit_t& outfit, int32_t time)
{
	ConditionOutfit* outfitCondition = new ConditionOutfit(CONDITIONID_COMBAT, CONDITION_OUTFIT, time);
	outfitCondition->setOutfit(outfit);
	creature->addCondition(outfitCondition);
	return RETURNVALUE_NOERROR;
}

ReturnValue Spell::CreateIllusion(Creature* creature, const std::string& name, int32_t time)
{
	MonsterType* mType = g_monsters.getMonsterType(name);
	if (mType == nullptr) {
		return RETURNVALUE_CREATUREDOESNOTEXIST;
	}

	Player* player = creature->getPlayer();
	if (player && !player->hasFlag(PlayerFlag_CanIllusionAll)) {
		if (!mType->info.isIllusionable) {
			return RETURNVALUE_NOTPOSSIBLE;
		}
	}

	return CreateIllusion(creature, mType->info.outfit, time);
}

ReturnValue Spell::CreateIllusion(Creature* creature, uint32_t itemId, int32_t time)
{
	const ItemType& it = Item::items[itemId];
	if (it.id == 0) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	Outfit_t outfit;
	outfit.lookTypeEx = itemId;

	return CreateIllusion(creature, outfit, time);
}
