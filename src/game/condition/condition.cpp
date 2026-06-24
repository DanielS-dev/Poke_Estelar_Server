// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "condition.hpp"
#include "../game.hpp"
#include "../../core/tools/random.hpp"

extern Game g_game;
bool Condition::setParam(ConditionParam_t param, int32_t value)
{
	switch (param) {
		case CONDITION_PARAM_TICKS: {
			ticks = value;
			return true;
		}

		case CONDITION_PARAM_BUFF_SPELL: {
			isBuff = (value != 0);
			return true;
		}

		case CONDITION_PARAM_SUBID: {
			subId = value;
			return true;
		}

		default: {
			return false;
		}
	}
}

bool Condition::unserialize(PropStream& propStream)
{
	uint8_t attr_type;
	while (propStream.read<uint8_t>(attr_type) && attr_type != CONDITIONATTR_END) {
		if (!unserializeProp(static_cast<ConditionAttr_t>(attr_type), propStream)) {
			return false;
		}
	}
	return true;
}

bool Condition::unserializeProp(ConditionAttr_t attr, PropStream& propStream)
{
	switch (attr) {
		case CONDITIONATTR_TYPE: {
			int32_t value;
			if (!propStream.read<int32_t>(value)) {
				return false;
			}

			conditionType = static_cast<ConditionType_t>(value);
			return true;
		}

		case CONDITIONATTR_ID: {
			int32_t value;
			if (!propStream.read<int32_t>(value)) {
				return false;
			}

			id = static_cast<ConditionId_t>(value);
			return true;
		}

		case CONDITIONATTR_TICKS: {
			return propStream.read<int32_t>(ticks);
		}

		case CONDITIONATTR_ISBUFF: {
			uint8_t value;
			if (!propStream.read<uint8_t>(value)) {
				return false;
			}

			isBuff = (value != 0);
			return true;
		}

		case CONDITIONATTR_SUBID: {
			return propStream.read<uint32_t>(subId);
		}

		case CONDITIONATTR_END:
			return true;

		default:
			return false;
	}
}

void Condition::serialize(PropWriteStream& propWriteStream)
{
	propWriteStream.write<uint8_t>(CONDITIONATTR_TYPE);
	propWriteStream.write<uint32_t>(conditionType);

	propWriteStream.write<uint8_t>(CONDITIONATTR_ID);
	propWriteStream.write<uint32_t>(id);

	propWriteStream.write<uint8_t>(CONDITIONATTR_TICKS);
	propWriteStream.write<uint32_t>(ticks);

	propWriteStream.write<uint8_t>(CONDITIONATTR_ISBUFF);
	propWriteStream.write<uint8_t>(isBuff);

	propWriteStream.write<uint8_t>(CONDITIONATTR_SUBID);
	propWriteStream.write<uint32_t>(subId);
}

void Condition::setTicks(int32_t newTicks)
{
	ticks = newTicks;
	endTime = ticks + OTSYS_TIME();
}

bool Condition::executeCondition(Creature*, int32_t interval)
{
	if (ticks == -1) {
		return true;
	}

	//Not using set ticks here since it would reset endTime
	ticks = std::max<int32_t>(0, ticks - interval);
	return getEndTime() >= OTSYS_TIME();
}

Condition* Condition::createCondition(ConditionId_t id, ConditionType_t type, int32_t ticks, int32_t param/* = 0*/, bool buff/* = false*/, uint32_t subId/* = 0*/)
{
	switch (type) {
		case CONDITION_POISON:
		case CONDITION_FIRE:
		case CONDITION_ENERGY:
		case CONDITION_DROWN:
		case CONDITION_FREEZING:
		case CONDITION_DAZZLED:
		case CONDITION_CURSED:
		case CONDITION_BLEEDING:
		case CONDITION_SEED: //pota
			return new ConditionDamage(id, type, buff, subId);

		case CONDITION_HASTE:
		case CONDITION_SLEEP: //pota
		case CONDITION_SILENCE: //helena
		case CONDITION_PARALYZE:
			return new ConditionSpeed(id, type, ticks, buff, subId, param);

		case CONDITION_MOVING: //pota
			return new ConditionStatus(id, type, ticks, buff, subId);

		case CONDITION_INVISIBLE:
			return new ConditionInvisible(id, type, ticks, buff, subId);

		case CONDITION_OUTFIT:
			return new ConditionOutfit(id, type, ticks, buff, subId);

		case CONDITION_LIGHT:
			return new ConditionLight(id, type, ticks, buff, subId, param & 0xFF, (param & 0xFF00) >> 8);

		case CONDITION_REGENERATION:
			return new ConditionRegeneration(id, type, ticks, buff, subId);

		case CONDITION_SOUL:
			return new ConditionSoul(id, type, ticks, buff, subId);

		case CONDITION_ATTRIBUTES:
			return new ConditionAttributes(id, type, ticks, buff, subId);

		case CONDITION_SPELLCOOLDOWN:
			return new ConditionSpellCooldown(id, type, ticks, buff, subId);

		case CONDITION_SPELLGROUPCOOLDOWN:
			return new ConditionSpellGroupCooldown(id, type, ticks, buff, subId);

		case CONDITION_INFIGHT:
		case CONDITION_DRUNK:
		case CONDITION_EXHAUST_WEAPON:
		case CONDITION_EXHAUST_COMBAT:
		case CONDITION_EXHAUST_HEAL:
		case CONDITION_MUTED:
		case CONDITION_CHANNELMUTEDTICKS:
		case CONDITION_YELLTICKS:
		case CONDITION_PACIFIED:
		case CONDITION_REFLECT:
		case CONDITION_COAT:
		case CONDITION_FOCUS:
		case CONDITION_EVASION:
		case CONDITION_DEFENSEPLUS:
		case CONDITION_DEFENSEMINUS:
		case CONDITION_ATTACKPLUS:
		case CONDITION_ATTACKMINUS:
		case CONDITION_IMMUNE:
		case CONDITION_STURDY:
		case CONDITION_SAFFARI:
		case CONDITION_FISHING:
		case CONDITION_PARK:
		case CONDITION_MANASHIELD:
			return new ConditionGeneric(id, type, ticks, buff, subId);

		default:
			return nullptr;
	}
}

Condition* Condition::createCondition(PropStream& propStream)
{
	uint8_t attr;
	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_TYPE) {
		return nullptr;
	}

	uint32_t type;
	if (!propStream.read<uint32_t>(type)) {
		return nullptr;
	}

	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_ID) {
		return nullptr;
	}

	uint32_t id;
	if (!propStream.read<uint32_t>(id)) {
		return nullptr;
	}

	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_TICKS) {
		return nullptr;
	}

	uint32_t ticks;
	if (!propStream.read<uint32_t>(ticks)) {
		return nullptr;
	}

	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_ISBUFF) {
		return nullptr;
	}

	uint8_t buff;
	if (!propStream.read<uint8_t>(buff)) {
		return nullptr;
	}

	if (!propStream.read<uint8_t>(attr) || attr != CONDITIONATTR_SUBID) {
		return nullptr;
	}

	uint32_t subId;
	if (!propStream.read<uint32_t>(subId)) {
		return nullptr;
	}

	return createCondition(static_cast<ConditionId_t>(id), static_cast<ConditionType_t>(type), ticks, 0, buff != 0, subId);
}

bool Condition::startCondition(Creature*)
{
	if (ticks > 0) {
		endTime = ticks + OTSYS_TIME();
	}
	return true;
}

bool Condition::isPersistent() const
{
	if (ticks == -1) {
		return false;
	}

	if (!(id == CONDITIONID_DEFAULT || id == CONDITIONID_COMBAT)) {
		return false;
	}

	return true;
}

uint32_t Condition::getIcons() const
{
	return isBuff ? ICON_PARTY_BUFF : 0;
}

bool Condition::updateCondition(const Condition* addCondition)
{
	if (conditionType != addCondition->getType()) {
		return false;
	}

	if (ticks == -1 && addCondition->getTicks() > 0) {
		return false;
	}

	if (addCondition->getTicks() >= 0 && getEndTime() > (OTSYS_TIME() + addCondition->getTicks())) {
		return false;
	}

	return true;
}

bool ConditionGeneric::startCondition(Creature* creature)
{
	return Condition::startCondition(creature);
}

bool ConditionGeneric::executeCondition(Creature* creature, int32_t interval)
{
	return Condition::executeCondition(creature, interval);
}

void ConditionGeneric::endCondition(Creature*)
{
	//
}

void ConditionGeneric::addCondition(Creature*, const Condition* addCondition)
{
	if (updateCondition(addCondition)) {
		setTicks(addCondition->getTicks());
	}
}

uint32_t ConditionGeneric::getIcons() const
{
	uint32_t icons = Condition::getIcons();

	switch (conditionType) {
		case CONDITION_MANASHIELD:
			icons |= ICON_MANASHIELD;
			break;
		
		case CONDITION_REFLECT:
			icons |= ICON_MANASHIELD;
			break;
		
		case CONDITION_COAT:
			icons |= ICON_MANASHIELD;
			break;
			
		case CONDITION_FOCUS:
			icons |= ICON_MANASHIELD;
			break;
		
		case CONDITION_EVASION:
			icons |= ICON_MANASHIELD;
			break;
		
		case CONDITION_DEFENSEPLUS:
			icons |= ICON_MANASHIELD;
			break;
		
		case CONDITION_DEFENSEMINUS:
			icons |= ICON_MANASHIELD;
			break;
		
		case CONDITION_ATTACKPLUS:
			icons |= ICON_MANASHIELD;
			break;
		
		case CONDITION_ATTACKMINUS:
			icons |= ICON_MANASHIELD;
			break;
		
		case CONDITION_STURDY:
			icons |= ICON_MANASHIELD;
			break;

		case CONDITION_SAFFARI:
			break;

		case CONDITION_FISHING:
			break;
		
		case CONDITION_PARK:
			break;
		
		case CONDITION_IMMUNE:
			icons |= ICON_MANASHIELD;
			break;

		case CONDITION_INFIGHT:
			icons |= ICON_SWORDS;
			break;

		case CONDITION_DRUNK:
			icons |= ICON_DRUNK;
			break;

		default:
			break;
	}

	return icons;
}
