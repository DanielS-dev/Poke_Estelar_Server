// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../creature.hpp"

#include "../monster.hpp"
#include "../../config/configmanager.hpp"
#include "../../core/scheduler.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern ConfigManager g_config;
extern CreatureEvents* g_creatureEvents;

void Creature::onAddCondition(ConditionType_t type)
{
	if (type == CONDITION_PARALYZE && hasCondition(CONDITION_HASTE)) {
		removeCondition(CONDITION_HASTE);
	} else if (type == CONDITION_HASTE && hasCondition(CONDITION_PARALYZE)) {
		removeCondition(CONDITION_PARALYZE);
	}
}

void Creature::onAddCombatCondition(ConditionType_t)
{
	//
}

void Creature::onEndCondition(ConditionType_t)
{
	//
}

void Creature::onTickCondition(ConditionType_t type, bool& bRemove)
{
	const MagicField* field = getTile()->getFieldItem();
	if (!field) {
		return;
	}

	switch (type) {
		case CONDITION_FIRE:
			bRemove = (field->getCombatType() != COMBAT_FIREDAMAGE);
			break;
		case CONDITION_ENERGY:
			bRemove = (field->getCombatType() != COMBAT_ENERGYDAMAGE);
			break;
		case CONDITION_POISON:
			bRemove = (field->getCombatType() != COMBAT_POISONDAMAGE);
			break;
		case CONDITION_FREEZING:
			bRemove = (field->getCombatType() != COMBAT_ICEDAMAGE);
			break;
		case CONDITION_DAZZLED:
			bRemove = (field->getCombatType() != COMBAT_HOLYDAMAGE);
			break;
		case CONDITION_CURSED:
			bRemove = (field->getCombatType() != COMBAT_DEATHDAMAGE);
			break;
		case CONDITION_DROWN:
			bRemove = (field->getCombatType() != COMBAT_DROWNDAMAGE);
			break;
		case CONDITION_BLEEDING:
			bRemove = (field->getCombatType() != COMBAT_PHYSICALDAMAGE);
			break;
		default:
			break;
	}
}

void Creature::onCombatRemoveCondition(Condition* condition)
{
	removeCondition(condition);
}

void Creature::onAttacked()
{
	//
}

void Creature::onAttackedCreatureDrainHealth(Creature* target, int32_t points)
{
	target->addDamagePoints(this, points);
}

bool Creature::onKilledCreature(Creature* target, bool)
{
	if (master) {
		master->onKilledCreature(target);
	}

	//scripting event - onKill
	const CreatureEventList& killEvents = getCreatureEvents(CREATURE_EVENT_KILL);
	for (CreatureEvent* killEvent : killEvents) {
		killEvent->executeOnKill(this, target);
	}
	return false;
}

void Creature::onGainExperience(uint64_t gainExp, Creature* target)
{
	if (gainExp == 0 || !master) {
		return;
	}

	//do not give exp to summons //pota
	//gainExp /= 2; 

	master->onGainExperience(gainExp, target);

	SpectatorVec list;
	g_game.map.getSpectators(list, position, false, true);
	if (list.empty()) {
		return;
	}
	//do not give exp to summons //pota
	if (this->getMonster() || master->getMonster()) {
		//master->onGainExperience(gainExp, target);
        	return;
    	}

	TextMessage message(MESSAGE_EXPERIENCE_OTHERS, ucfirst(getNameDescription()) + " gained " + std::to_string(gainExp) + (gainExp != 1 ? " experience points." : " experience point."));
	message.position = position;
	message.primary.color = TEXTCOLOR_WHITE_EXP;
	message.primary.value = gainExp;

	for (Creature* spectator : list) {
		spectator->getPlayer()->sendTextMessage(message);
	}
}

void Creature::addSummon(Creature* creature)
{
	creature->setDropLoot(false);
	creature->setLossSkill(false);
	creature->setMaster(this);
	creature->incrementReferenceCounter();
	summons.push_back(creature);
}

void Creature::removeSummon(Creature* creature)
{
	auto cit = std::find(summons.begin(), summons.end(), creature);
	if (cit != summons.end()) {
		creature->setDropLoot(false);
		creature->setLossSkill(true);
		creature->setMaster(nullptr);
		creature->decrementReferenceCounter();
		summons.erase(cit);
	}
}

bool Creature::addCondition(Condition* condition, bool force/* = false*/)
{
	if (condition == nullptr) {
		return false;
	}

	if (!force && condition->getType() == CONDITION_HASTE && hasCondition(CONDITION_PARALYZE)) {
		int64_t walkDelay = getWalkDelay();
		if (walkDelay > 0) {
			g_scheduler.addEvent(createSchedulerTask(walkDelay, std::bind(&Game::forceAddCondition, &g_game, getID(), condition)));
			return false;
		}
	}

	Condition* prevCond = getCondition(condition->getType(), condition->getId(), condition->getSubId());
	if (prevCond) {
		prevCond->addCondition(this, condition);
		delete condition;
		return true;
	}

	if (condition->startCondition(this)) {
		conditions.push_back(condition);
		onAddCondition(condition->getType());
		return true;
	}

	delete condition;
	return false;
}

bool Creature::addCombatCondition(Condition* condition)
{
	//Caution: condition variable could be deleted after the call to addCondition
	ConditionType_t type = condition->getType();

	if (!addCondition(condition)) {
		return false;
	}

	onAddCombatCondition(type);
	return true;
}

void Creature::removeCondition(ConditionType_t type, bool force/* = false*/)
{
	auto it = conditions.begin(), end = conditions.end();
	while (it != end) {
		Condition* condition = *it;
		if (condition->getType() != type) {
			++it;
			continue;
		}

		if (!force && type == CONDITION_PARALYZE) {
			int64_t walkDelay = getWalkDelay();
			if (walkDelay > 0) {
				g_scheduler.addEvent(createSchedulerTask(walkDelay, std::bind(&Game::forceRemoveCondition, &g_game, getID(), type)));
				return;
			}
		}

		it = conditions.erase(it);

		condition->endCondition(this);
		delete condition;

		onEndCondition(type);
	}
}

void Creature::removeCondition(ConditionType_t type, ConditionId_t conditionId, bool force/* = false*/)
{
	auto it = conditions.begin(), end = conditions.end();
	while (it != end) {
		Condition* condition = *it;
		if (condition->getType() != type || condition->getId() != conditionId) {
			++it;
			continue;
		}

		if (!force && type == CONDITION_PARALYZE) {
			int64_t walkDelay = getWalkDelay();
			if (walkDelay > 0) {
				g_scheduler.addEvent(createSchedulerTask(walkDelay, std::bind(&Game::forceRemoveCondition, &g_game, getID(), type)));
				return;
			}
		}

		it = conditions.erase(it);

		condition->endCondition(this);
		delete condition;

		onEndCondition(type);
	}
}

void Creature::removeCombatCondition(ConditionType_t type)
{
	std::vector<Condition*> removeConditions;
	for (Condition* condition : conditions) {
		if (condition->getType() == type) {
			removeConditions.push_back(condition);
		}
	}

	for (Condition* condition : removeConditions) {
		onCombatRemoveCondition(condition);
	}
}

void Creature::removeCondition(Condition* condition, bool force/* = false*/)
{
	auto it = std::find(conditions.begin(), conditions.end(), condition);
	if (it == conditions.end()) {
		return;
	}

	if (!force && condition->getType() == CONDITION_PARALYZE) {
		int64_t walkDelay = getWalkDelay();
		if (walkDelay > 0) {
			g_scheduler.addEvent(createSchedulerTask(walkDelay, std::bind(&Game::forceRemoveCondition, &g_game, getID(), condition->getType())));
			return;
		}
	}

	conditions.erase(it);

	condition->endCondition(this);
	onEndCondition(condition->getType());
	delete condition;
}

Condition* Creature::getCondition(ConditionType_t type) const
{
	for (Condition* condition : conditions) {
		if (condition->getType() == type) {
			return condition;
		}
	}
	return nullptr;
}

Condition* Creature::getCondition(ConditionType_t type, ConditionId_t conditionId, uint32_t subId/* = 0*/) const
{
	for (Condition* condition : conditions) {
		if (condition->getType() == type && condition->getId() == conditionId && condition->getSubId() == subId) {
			return condition;
		}
	}
	return nullptr;
}

void Creature::executeConditions(uint32_t interval)
{
	auto it = conditions.begin(), end = conditions.end();
	while (it != end) {
		Condition* condition = *it;
		if (!condition->executeCondition(this, interval)) {
			ConditionType_t type = condition->getType();

			it = conditions.erase(it);

			condition->endCondition(this);
			delete condition;

			onEndCondition(type);
		} else {
			++it;
		}
	}
}

bool Creature::hasCondition(ConditionType_t type, uint32_t subId/* = 0*/) const
{
	if (isSuppress(type)) {
		return false;
	}

	int64_t timeNow = OTSYS_TIME();
	for (Condition* condition : conditions) {
		if (condition->getType() != type || condition->getSubId() != subId) {
			continue;
		}

		if (condition->getEndTime() >= timeNow) {
			return true;
		}
	}
	return false;
}

bool Creature::isImmune(CombatType_t type) const
{
	return hasBitSet(static_cast<uint32_t>(type), getDamageImmunities());
}

bool Creature::isImmune(ConditionType_t type) const
{
	return hasBitSet(static_cast<uint32_t>(type), getConditionImmunities());
}

bool Creature::isSuppress(ConditionType_t type) const
{
	return hasBitSet(static_cast<uint32_t>(type), getConditionSuppressions());
}

