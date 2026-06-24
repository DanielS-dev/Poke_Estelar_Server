// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_COMBATTYPES_H_EA04C4AC38B747B1863F61687E8E30F4
#define FS_COMBATTYPES_H_EA04C4AC38B747B1863F61687E8E30F4

#include <forward_list>
#include <memory>

#include "../../core/const.hpp"
#include "../condition/condition.hpp"

class Creature;
class Player;
class TargetCallback;
class Tile;
class TileCallback;
class ValueCallback;

struct CombatParams {
	std::forward_list<std::unique_ptr<const Condition>> conditionList;

	std::unique_ptr<ValueCallback> valueCallback;
	std::unique_ptr<TileCallback> tileCallback;
	std::unique_ptr<TargetCallback> targetCallback;

	uint16_t itemId = 0;

	ConditionType_t dispelType = CONDITION_NONE;
	CombatType_t combatType = COMBAT_NONE;
	CombatOrigin origin = ORIGIN_SPELL;

	uint16_t impactEffect = CONST_ME_NONE; //pota
	uint8_t distanceEffect = CONST_ANI_NONE;

	bool blockedByArmor = false;
	bool blockedByShield = false;
	bool targetCasterOrTopMost = false;
	bool aggressive = true;
	bool useCharges = false;
};

typedef void (*COMBATFUNC)(Creature*, Creature*, const CombatParams&, CombatDamage*);

#endif
