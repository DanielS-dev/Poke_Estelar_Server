// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../combat/combat.hpp"
#include "../game.hpp"
#include "../../items/items.hpp"

#include "movementEvent.hpp"

extern Game g_game;

uint32_t MoveEvent::StepInField(Creature* creature, Item* item, const Position&)
{
	MagicField* field = item->getMagicField();
	if (field) {
		field->onStepInField(creature);
		return 1;
	}

	return LUA_ERROR_ITEM_NOT_FOUND;
}

uint32_t MoveEvent::StepOutField(Creature*, Item*, const Position&)
{
	return 1;
}

uint32_t MoveEvent::AddItemField(Item* item, Item*, const Position&)
{
	if (MagicField* field = item->getMagicField()) {
		Tile* tile = item->getTile();
		if (CreatureVector* creatures = tile->getCreatures()) {
			for (Creature* creature : *creatures) {
				field->onStepInField(creature);
			}
		}
		return 1;
	}
	return LUA_ERROR_ITEM_NOT_FOUND;
}

uint32_t MoveEvent::RemoveItemField(Item*, Item*, const Position&)
{
	return 1;
}

uint32_t MoveEvent::EquipItem(MoveEvent* moveEvent, Player* player, Item* item, slots_t slot, bool isCheck)
{
	if (player->isItemAbilityEnabled(slot)) {
		return 1;
	}

	if (!player->hasFlag(PlayerFlag_IgnoreWeaponCheck) && moveEvent->getWieldInfo() != 0) {
		if (player->getLevel() < moveEvent->getReqLevel() || player->getMagicLevel() < moveEvent->getReqMagLv()) {
			return 0;
		}

		if (moveEvent->isPremium() && !player->isPremium()) {
			return 0;
		}

		const VocEquipMap& vocEquipMap = moveEvent->getVocEquipMap();
		if (!vocEquipMap.empty() && vocEquipMap.find(player->getVocationId()) == vocEquipMap.end()) {
			return 0;
		}
	}

	if (isCheck) {
		return 1;
	}

	const ItemType& it = Item::items[item->getID()];
	if (it.transformEquipTo != 0) {
		Item* newItem = g_game.transformItem(item, it.transformEquipTo);
		g_game.startDecay(newItem);
	} else {
		player->setItemAbility(slot, true);
	}

	if (!it.abilities) {
		return 1;
	}

	if (it.abilities->invisible) {
		Condition* condition = Condition::createCondition(static_cast<ConditionId_t>(slot), CONDITION_INVISIBLE, -1, 0);
		player->addCondition(condition);
	}

	if (it.abilities->manaShield) {
		Condition* condition = Condition::createCondition(static_cast<ConditionId_t>(slot), CONDITION_MANASHIELD, -1, 0);
		player->addCondition(condition);
	}

	if (it.abilities->speed != 0) {
		g_game.changeSpeed(player, it.abilities->speed);
	}

	if (it.abilities->conditionSuppressions != 0) {
		player->addConditionSuppressions(it.abilities->conditionSuppressions);
		player->sendIcons();
	}

	if (it.abilities->regeneration) {
		Condition* condition = Condition::createCondition(static_cast<ConditionId_t>(slot), CONDITION_REGENERATION, -1, 0);

		if (it.abilities->healthGain != 0) {
			condition->setParam(CONDITION_PARAM_HEALTHGAIN, it.abilities->healthGain);
		}

		if (it.abilities->healthTicks != 0) {
			condition->setParam(CONDITION_PARAM_HEALTHTICKS, it.abilities->healthTicks);
		}

		if (it.abilities->manaGain != 0) {
			condition->setParam(CONDITION_PARAM_MANAGAIN, it.abilities->manaGain);
		}

		if (it.abilities->manaTicks != 0) {
			condition->setParam(CONDITION_PARAM_MANATICKS, it.abilities->manaTicks);
		}

		player->addCondition(condition);
	}

	//skill modifiers
	bool needUpdateSkills = false;

	for (int32_t i = SKILL_FIRST; i <= SKILL_LAST; ++i) {
		if (it.abilities->skills[i]) {
			needUpdateSkills = true;
			player->setVarSkill(static_cast<skills_t>(i), it.abilities->skills[i]);
		}
	}

	if (needUpdateSkills) {
		player->sendSkills();
	}

	//stat modifiers
	bool needUpdateStats = false;

	for (int32_t s = STAT_FIRST; s <= STAT_LAST; ++s) {
		if (it.abilities->stats[s]) {
			needUpdateStats = true;
			player->setVarStats(static_cast<stats_t>(s), it.abilities->stats[s]);
		}

		if (it.abilities->statsPercent[s]) {
			needUpdateStats = true;
			player->setVarStats(static_cast<stats_t>(s), static_cast<int32_t>(player->getDefaultStats(static_cast<stats_t>(s)) * ((it.abilities->statsPercent[s] - 100) / 100.f)));
		}
	}

	if (needUpdateStats) {
		player->sendStats();
	}

	return 1;
}

uint32_t MoveEvent::DeEquipItem(MoveEvent*, Player* player, Item* item, slots_t slot, bool)
{
	if (!player->isItemAbilityEnabled(slot)) {
		return 1;
	}

	player->setItemAbility(slot, false);

	const ItemType& it = Item::items[item->getID()];
	if (it.transformDeEquipTo != 0) {
		g_game.transformItem(item, it.transformDeEquipTo);
		g_game.startDecay(item);
	}

	if (!it.abilities) {
		return 1;
	}

	if (it.abilities->invisible) {
		player->removeCondition(CONDITION_INVISIBLE, static_cast<ConditionId_t>(slot));
	}

	if (it.abilities->manaShield) {
		player->removeCondition(CONDITION_MANASHIELD, static_cast<ConditionId_t>(slot));
	}

	if (it.abilities->speed != 0) {
		g_game.changeSpeed(player, -it.abilities->speed);
	}

	if (it.abilities->conditionSuppressions != 0) {
		player->removeConditionSuppressions(it.abilities->conditionSuppressions);
		player->sendIcons();
	}

	if (it.abilities->regeneration) {
		player->removeCondition(CONDITION_REGENERATION, static_cast<ConditionId_t>(slot));
	}

	//skill modifiers
	bool needUpdateSkills = false;

	for (int32_t i = SKILL_FIRST; i <= SKILL_LAST; ++i) {
		if (it.abilities->skills[i] != 0) {
			needUpdateSkills = true;
			player->setVarSkill(static_cast<skills_t>(i), -it.abilities->skills[i]);
		}
	}

	if (needUpdateSkills) {
		player->sendSkills();
	}

	//stat modifiers
	bool needUpdateStats = false;

	for (int32_t s = STAT_FIRST; s <= STAT_LAST; ++s) {
		if (it.abilities->stats[s]) {
			needUpdateStats = true;
			player->setVarStats(static_cast<stats_t>(s), -it.abilities->stats[s]);
		}

		if (it.abilities->statsPercent[s]) {
			needUpdateStats = true;
			player->setVarStats(static_cast<stats_t>(s), -static_cast<int32_t>(player->getDefaultStats(static_cast<stats_t>(s)) * ((it.abilities->statsPercent[s] - 100) / 100.f)));
		}
	}

	if (needUpdateStats) {
		player->sendStats();
	}

	return 1;
}
