// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "condition.hpp"
#include "../game.hpp"
#include "../../core/tools/random.hpp"

extern Game g_game;
bool ConditionDamage::setParam(ConditionParam_t param, int32_t value)
{
	bool ret = Condition::setParam(param, value);

	switch (param) {
		case CONDITION_PARAM_OWNER:
			owner = value;
			return true;

		case CONDITION_PARAM_FORCEUPDATE:
			forceUpdate = (value != 0);
			return true;

		case CONDITION_PARAM_DELAYED:
			delayed = (value != 0);
			return true;

		case CONDITION_PARAM_MAXVALUE:
			maxDamage = std::abs(value);
			break;

		case CONDITION_PARAM_MINVALUE:
			minDamage = std::abs(value);
			break;

		case CONDITION_PARAM_STARTVALUE:
			startDamage = std::abs(value);
			break;

		case CONDITION_PARAM_TICKINTERVAL:
			tickInterval = std::abs(value);
			break;

		case CONDITION_PARAM_PERIODICDAMAGE:
			periodDamage = value;
			break;

		case CONDITION_PARAM_FIELD:
			field = (value != 0);
			break;

		default:
			return false;
	}

	return ret;
}

bool ConditionDamage::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	if (attr == CONDITIONATTR_DELAYED) {
		uint8_t value;
		if (!propStream.read<uint8_t>(value)) {
			return false;
		}

		delayed = (value != 0);
		return true;
	} else if (attr == CONDITIONATTR_PERIODDAMAGE) {
		return propStream.read<int32_t>(periodDamage);
	} else if (attr == CONDITIONATTR_OWNER) {
		return propStream.skip(4);
	} else if (attr == CONDITIONATTR_INTERVALDATA) {
		IntervalInfo damageInfo;
		if (!propStream.read<IntervalInfo>(damageInfo)) {
			return false;
		}

		damageList.push_back(damageInfo);
		if (ticks != -1) {
			setTicks(ticks + damageInfo.interval);
		}
		return true;
	}
	return Condition::unserializeProp(attr, propStream);
}

void ConditionDamage::serialize(PropWriteStream& propWriteStream)
{
	Condition::serialize(propWriteStream);

	propWriteStream.write<uint8_t>(CONDITIONATTR_DELAYED);
	propWriteStream.write<uint8_t>(delayed);

	propWriteStream.write<uint8_t>(CONDITIONATTR_PERIODDAMAGE);
	propWriteStream.write<int32_t>(periodDamage);

	for (const IntervalInfo& intervalInfo : damageList) {
		propWriteStream.write<uint8_t>(CONDITIONATTR_INTERVALDATA);
		propWriteStream.write<IntervalInfo>(intervalInfo);
	}
}

bool ConditionDamage::updateCondition(const Condition* addCondition)
{
	const ConditionDamage& conditionDamage = static_cast<const ConditionDamage&>(*addCondition);
	if (conditionDamage.doForceUpdate()) {
		return true;
	}

	if (ticks == -1 && conditionDamage.ticks > 0) {
		return false;
	}

	return conditionDamage.getTotalDamage() > getTotalDamage();
}

bool ConditionDamage::addDamage(int32_t rounds, int32_t time, int32_t value)
{
	time = std::max<int32_t>(time, EVENT_CREATURE_THINK_INTERVAL);
	if (rounds == -1) {
		//periodic damage
		periodDamage = value;
		setParam(CONDITION_PARAM_TICKINTERVAL, time);
		setParam(CONDITION_PARAM_TICKS, -1);
		return true;
	}

	if (periodDamage > 0) {
		return false;
	}

	//rounds, time, damage
	for (int32_t i = 0; i < rounds; ++i) {
		IntervalInfo damageInfo;
		damageInfo.interval = time;
		damageInfo.timeLeft = time;
		damageInfo.value = value;

		damageList.push_back(damageInfo);

		if (ticks != -1) {
			setTicks(ticks + damageInfo.interval);
		}
	}

	return true;
}

bool ConditionDamage::init()
{
	if (periodDamage != 0) {
		return true;
	}

	if (damageList.empty()) {
		setTicks(0);

		int32_t amount = uniform_random(minDamage, maxDamage);
		if (amount != 0) {
			if (startDamage > maxDamage) {
				startDamage = maxDamage;
			} else if (startDamage == 0) {
				startDamage = std::max<int32_t>(1, std::ceil(amount / 20.0));
			}

			std::list<int32_t> list;
			ConditionDamage::generateDamageList(amount, startDamage, list);
			for (int32_t value : list) {
				addDamage(1, tickInterval, -value);
			}
		}
	}
	return !damageList.empty();
}

bool ConditionDamage::startCondition(Creature* creature)
{
	if (!Condition::startCondition(creature)) {
		return false;
	}

	if (!init()) {
		return false;
	}

	if (!delayed) {
		int32_t damage;
		if (getNextDamage(damage)) {
			return doDamage(creature, damage);
		}
	}
	return true;
}

bool ConditionDamage::executeCondition(Creature* creature, int32_t interval)
{
	if (periodDamage != 0) {
		periodDamageTick += interval;

		if (periodDamageTick >= tickInterval) {
			periodDamageTick = 0;
			doDamage(creature, periodDamage);
		}
	} else if (!damageList.empty()) {
		IntervalInfo& damageInfo = damageList.front();

		bool bRemove = (ticks != -1);
		creature->onTickCondition(getType(), bRemove);
		damageInfo.timeLeft -= interval;

		if (damageInfo.timeLeft <= 0) {
			int32_t damage = damageInfo.value;

			if (bRemove) {
				damageList.pop_front();
			} else {
				damageInfo.timeLeft = damageInfo.interval;
			}

			doDamage(creature, damage);
		}

		if (!bRemove) {
			if (ticks > 0) {
				endTime += interval;
			}

			interval = 0;
		}
	}

	return Condition::executeCondition(creature, interval);
}

bool ConditionDamage::getNextDamage(int32_t& damage)
{
	if (periodDamage != 0) {
		damage = periodDamage;
		return true;
	} else if (!damageList.empty()) {
		IntervalInfo& damageInfo = damageList.front();
		damage = damageInfo.value;
		if (ticks != -1) {
			damageList.pop_front();
		}
		return true;
	}
	return false;
}

bool ConditionDamage::doDamage(Creature* creature, int32_t healthChange)
{
	if (creature->isSuppress(getType())) {
		return true;
	}

	CombatDamage damage;
	damage.origin = ORIGIN_CONDITION;
	damage.primary.value = healthChange;
	damage.primary.type = Combat::ConditionToDamageType(conditionType);

	Creature* attacker = g_game.getCreatureByID(owner);
	if (field && creature->getPlayer() && attacker && attacker->getPlayer()) {
		damage.primary.value = static_cast<int32_t>(std::round(damage.primary.value / 2.));
	}

	if (!creature->isAttackable() || Combat::canDoCombat(attacker, creature) != RETURNVALUE_NOERROR) {
		if (!creature->isInGhostMode()) {
			g_game.addMagicEffect(creature->getPosition(), CONST_ME_POFF);
		}
		return false;
	}

	if (g_game.combatBlockHit(damage, attacker, creature, false, false, field)) {
		return false;
	}
	return g_game.combatChangeHealth(attacker, creature, damage);
}

void ConditionDamage::endCondition(Creature*)
{
	//
}

void ConditionDamage::addCondition(Creature* creature, const Condition* addCondition)
{
	if (addCondition->getType() != conditionType) {
		return;
	}

	if (!updateCondition(addCondition)) {
		return;
	}

	const ConditionDamage& conditionDamage = static_cast<const ConditionDamage&>(*addCondition);

	setTicks(addCondition->getTicks());
	owner = conditionDamage.owner;
	maxDamage = conditionDamage.maxDamage;
	minDamage = conditionDamage.minDamage;
	startDamage = conditionDamage.startDamage;
	tickInterval = conditionDamage.tickInterval;
	periodDamage = conditionDamage.periodDamage;
	int32_t nextTimeLeft = tickInterval;

	if (!damageList.empty()) {
		//save previous timeLeft
		IntervalInfo& damageInfo = damageList.front();
		nextTimeLeft = damageInfo.timeLeft;
		damageList.clear();
	}

	damageList = conditionDamage.damageList;

	if (init()) {
		if (!damageList.empty()) {
			//restore last timeLeft
			IntervalInfo& damageInfo = damageList.front();
			damageInfo.timeLeft = nextTimeLeft;
		}

		if (!delayed) {
			int32_t damage;
			if (getNextDamage(damage)) {
				doDamage(creature, damage);
			}
		}
	}
}

int32_t ConditionDamage::getTotalDamage() const
{
	int32_t result;
	if (!damageList.empty()) {
		result = 0;
		for (const IntervalInfo& intervalInfo : damageList) {
			result += intervalInfo.value;
		}
	} else {
		result = minDamage + (maxDamage - minDamage) / 2;
	}
	return std::abs(result);
}

uint32_t ConditionDamage::getIcons() const
{
	uint32_t icons = Condition::getIcons();
	switch (conditionType) {
		case CONDITION_FIRE:
			icons |= ICON_BURN;
			break;

		case CONDITION_ENERGY:
			icons |= ICON_ENERGY;
			break;

		case CONDITION_DROWN:
			icons |= ICON_DROWNING;
			break;

		case CONDITION_POISON:
			icons |= ICON_POISON;
			break;

		case CONDITION_FREEZING:
			icons |= ICON_FREEZING;
			break;

		case CONDITION_DAZZLED:
			icons |= ICON_DAZZLED;
			break;

		case CONDITION_CURSED:
			icons |= ICON_CURSED;
			break;

		case CONDITION_BLEEDING:
			icons |= ICON_BLEEDING;
			break;

		default:
			break;
	}
	return icons;
}

void ConditionDamage::generateDamageList(int32_t amount, int32_t start, std::list<int32_t>& list)
{
	amount = std::abs(amount);
	int32_t sum = 0;
	double x1, x2;

	for (int32_t i = start; i > 0; --i) {
		int32_t n = start + 1 - i;
		int32_t med = (n * amount) / start;

		do {
			sum += i;
			list.push_back(i);

			x1 = std::fabs(1.0 - ((static_cast<float>(sum)) + i) / med);
			x2 = std::fabs(1.0 - (static_cast<float>(sum) / med));
		} while (x1 < x2);
	}
}
