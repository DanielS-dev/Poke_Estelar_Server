// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"
#include "combat.hpp"

#include "../game.hpp"
#include "../weapons/weapons.hpp"
#include "../../config/configmanager.hpp"
#include "../../scripting/events.hpp"
#include "../../entities/monster.hpp"
#include "../../core/tools/random.hpp"

extern Game g_game;
extern Weapons* g_weapons;
extern ConfigManager g_config;
extern Events* g_events;

CombatDamage Combat::getCombatDamage(Creature* creature, Creature* target) const
{
	CombatDamage damage;
	damage.origin = params.origin;
	damage.primary.type = params.combatType;
	if (formulaType == COMBAT_FORMULA_DAMAGE) {
		damage.primary.value = normal_random(
			static_cast<int32_t>(mina),
			static_cast<int32_t>(maxa)
		);
	} else if (creature) {
		int32_t min, max;
		if (creature->getCombatValues(min, max)) {
			damage.primary.value = normal_random(min, max);
		} else if (Player* player = creature->getPlayer()) {
			if (params.valueCallback) {
				params.valueCallback->getMinMaxValues(player, damage, params.useCharges);
			} else if (formulaType == COMBAT_FORMULA_LEVELMAGIC) {
				int32_t levelFormula = player->getLevel() * 2 + player->getMagicLevel() * 3;
				damage.primary.value = normal_random(
					static_cast<int32_t>(levelFormula * mina + minb),
					static_cast<int32_t>(levelFormula * maxa + maxb)
				);
			} else if (formulaType == COMBAT_FORMULA_SKILL) {
				Item* tool = player->getWeapon();
				const Weapon* weapon = g_weapons->getWeapon(tool);
				if (weapon) {
					damage.primary.value = normal_random(
						static_cast<int32_t>(minb),
						static_cast<int32_t>(weapon->getWeaponDamage(player, target, tool, true) * maxa + maxb)
					);

					damage.secondary.type = weapon->getElementType();
					damage.secondary.value = weapon->getElementDamage(player, target, tool);
					if (params.useCharges) {
						uint16_t charges = tool->getCharges();
						if (charges != 0) {
							g_game.transformItem(tool, tool->getID(), charges - 1);
						}
					}
				} else {
					damage.primary.value = normal_random(
						static_cast<int32_t>(minb),
						static_cast<int32_t>(maxb)
					);
				}
			}
		}
	}
	return damage;
}

void Combat::getCombatArea(const Position& centerPos, const Position& targetPos, const AreaCombat* area, std::forward_list<Tile*>& list)
{
	if (targetPos.z >= MAP_MAX_LAYERS) {
		return;
	}

	if (area) {
		area->getList(centerPos, targetPos, list);
	} else {
		Tile* tile = g_game.map.getTile(targetPos);
		if (!tile) {
			tile = new StaticTile(targetPos.x, targetPos.y, targetPos.z);
			g_game.map.setTile(targetPos, tile);
		}
		list.push_front(tile);
	}
}

CombatType_t Combat::ConditionToDamageType(ConditionType_t type)
{
	switch (type) {
		case CONDITION_FIRE:
			return COMBAT_FIREDAMAGE;

		case CONDITION_ENERGY:
			return COMBAT_ENERGYDAMAGE;

		case CONDITION_BLEEDING:
			return COMBAT_PHYSICALDAMAGE;

		case CONDITION_DROWN:
			return COMBAT_DROWNDAMAGE;

		case CONDITION_POISON:
			return COMBAT_POISONDAMAGE;

		case CONDITION_FREEZING:
			return COMBAT_ICEDAMAGE;

		case CONDITION_DAZZLED:
			return COMBAT_HOLYDAMAGE;

		case CONDITION_CURSED:
			return COMBAT_DEATHDAMAGE;

		case CONDITION_SEED: //pota
			return COMBAT_GRASSDAMAGE;

		default:
			break;
	}

	return COMBAT_NONE;
}

ConditionType_t Combat::DamageToConditionType(CombatType_t type)
{
	switch (type) {
		case COMBAT_FIREDAMAGE:
			return CONDITION_FIRE;

		case COMBAT_ENERGYDAMAGE:
			return CONDITION_ENERGY;

		case COMBAT_DROWNDAMAGE:
			return CONDITION_DROWN;

		case COMBAT_POISONDAMAGE:
			return CONDITION_POISON;

		case COMBAT_ICEDAMAGE:
			return CONDITION_FREEZING;

		case COMBAT_HOLYDAMAGE:
			return CONDITION_DAZZLED;

		case COMBAT_DEATHDAMAGE:
			return CONDITION_CURSED;

		case COMBAT_PHYSICALDAMAGE:
			return CONDITION_BLEEDING;

		case COMBAT_GRASSDAMAGE: //pota
			return CONDITION_SEED;

		default:
			return CONDITION_NONE;
	}
}

bool Combat::isPlayerCombat(const Creature* target)
{
	if (target->getPlayer()) {
		return true;
	}

	if (target->isSummon() && target->getMaster()->getPlayer()) {
		return true;
	}

	return false;
}

ReturnValue Combat::canTargetCreature(Player* player, Creature* target)
{
	if (player == target) {
		return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
	}

	if (!player->hasFlag(PlayerFlag_IgnoreProtectionZone)) {
		//pz-zone
		if (player->getZone() == ZONE_PROTECTION) {
			return RETURNVALUE_YOUMAYNOTATTACKAPERSONWHILEINPROTECTIONZONE;
		}

		if (target->getZone() == ZONE_PROTECTION) {
			return RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE;
		}

		//nopvp-zone
		if (isPlayerCombat(target)) {
			if (player->getZone() == ZONE_NOPVP) {
				return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
			}

			if (target->getZone() == ZONE_NOPVP) {
				return RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE;
			}
		}
	}

	if (player->hasFlag(PlayerFlag_CannotUseCombat) || !target->isAttackable()) {
		if (target->getPlayer()) {
			return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
		} else {
			return RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE;
		}
	}

	if (target->getPlayer()) {
		if (isProtected(player, target->getPlayer())) {
			return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
		}

		if (player->hasSecureMode() && !Combat::isInPvpZone(player, target) && player->getSkullClient(target->getPlayer()) == SKULL_NONE) {
			return RETURNVALUE_TURNSECUREMODETOATTACKUNMARKEDPLAYERS;
		}
	}

	return Combat::canDoCombat(player, target);
}

ReturnValue Combat::canDoCombat(Creature* caster, Tile* tile, bool aggressive)
{
	if (tile->hasProperty(CONST_PROP_BLOCKPROJECTILE)) {
		return RETURNVALUE_NOTENOUGHROOM;
	}

	if (tile->hasFlag(TILESTATE_FLOORCHANGE)) {
		return RETURNVALUE_NOTENOUGHROOM;
	}

	if (tile->getTeleportItem()) {
		return RETURNVALUE_NOTENOUGHROOM;
	}

	if (caster) {
		const Position& casterPosition = caster->getPosition();
		const Position& tilePosition = tile->getPosition();
		if (casterPosition.z < tilePosition.z) {
			return RETURNVALUE_FIRSTGODOWNSTAIRS;
		} else if (casterPosition.z > tilePosition.z) {
			return RETURNVALUE_FIRSTGOUPSTAIRS;
		}

		if (const Player* player = caster->getPlayer()) {
			if (player->hasFlag(PlayerFlag_IgnoreProtectionZone)) {
				return RETURNVALUE_NOERROR;
			}
		}
	}

	//pz-zone
	if (aggressive && tile->hasFlag(TILESTATE_PROTECTIONZONE)) {
		return RETURNVALUE_ACTIONNOTPERMITTEDINPROTECTIONZONE;
	}

	return g_events->eventCreatureOnAreaCombat(caster, tile, aggressive);
}

bool Combat::isInPvpZone(const Creature* attacker, const Creature* target)
{
	return attacker->getZone() == ZONE_PVP && target->getZone() == ZONE_PVP;
}

bool Combat::isProtected(const Player* attacker, const Player* target)
{
	uint32_t protectionLevel = g_config.getNumber(ConfigManager::PROTECTION_LEVEL);
	if (target->getLevel() < protectionLevel || attacker->getLevel() < protectionLevel) {
		return true;
	}

//	if (attacker->getVocationId() == VOCATION_NONE || target->getVocationId() == VOCATION_NONE) { //pota
//		return true;
//	}

	if (attacker->getSkull() == SKULL_BLACK && attacker->getSkullClient(target) == SKULL_NONE) {
		return true;
	}

	return false;
}

ReturnValue Combat::canDoCombat(Creature* attacker, Creature* target)
{
	if (attacker) {
		if (const Player* targetPlayer = target->getPlayer()) {
			if (targetPlayer->hasFlag(PlayerFlag_CannotBeAttacked)) {
				return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
			}

			if (const Player* attackerPlayer = attacker->getPlayer()) {
				if (attackerPlayer->hasFlag(PlayerFlag_CannotAttackPlayer)) {
					return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
				}

				if (isProtected(attackerPlayer, targetPlayer)) {
					return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
				}

				//nopvp-zone
				const Tile* targetPlayerTile = targetPlayer->getTile();
				if (targetPlayerTile->hasFlag(TILESTATE_NOPVPZONE)) {
					return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
				} else if (attackerPlayer->getTile()->hasFlag(TILESTATE_NOPVPZONE) && !targetPlayerTile->hasFlag(TILESTATE_NOPVPZONE | TILESTATE_PROTECTIONZONE)) {
					return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
				}
			}

			if (attacker->isSummon()) {
				if (const Player* masterAttackerPlayer = attacker->getMaster()->getPlayer()) {
					if (masterAttackerPlayer->hasFlag(PlayerFlag_CannotAttackPlayer)) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
					}

					if (targetPlayer->getTile()->hasFlag(TILESTATE_NOPVPZONE)) {
						return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
					}

					if (isProtected(masterAttackerPlayer, targetPlayer)) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
					}
				}
			}
		} else if (target->getMonster()) {
			if (const Player* attackerPlayer = attacker->getPlayer()) {
				if (attackerPlayer->hasFlag(PlayerFlag_CannotAttackMonster)) {
					return RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE;
				}

				if (target->isSummon() && target->getMaster()->getPlayer() && target->getZone() == ZONE_NOPVP) {
					return RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE;
				}
			} else if (attacker->getMonster()) {
				const Creature* targetMaster = target->getMaster();

				if (!targetMaster || !targetMaster->getPlayer()) {
					const Creature* attackerMaster = attacker->getMaster();

					if (!attackerMaster || !attackerMaster->getPlayer()) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE;
					}
				}
			}
		}

		if (g_game.getWorldType() == WORLD_TYPE_NO_PVP) {
			if (attacker->getPlayer() || (attacker->isSummon() && attacker->getMaster()->getPlayer())) {
				if (target->getPlayer()) {
					if (!isInPvpZone(attacker, target)) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER;
					}
				}

				if (target->isSummon() && target->getMaster()->getPlayer()) {
					if (!isInPvpZone(attacker, target)) {
						return RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE;
					}
				}
			}
		}
	}
	return g_events->eventCreatureOnTargetCombat(attacker, target);
}

void Combat::setPlayerCombatValues(formulaType_t formulaType, double mina, double minb, double maxa, double maxb)
{
	this->formulaType = formulaType;
	this->mina = mina;
	this->minb = minb;
	this->maxa = maxa;
	this->maxb = maxb;
}

bool Combat::setParam(CombatParam_t param, uint32_t value)
{
	switch (param) {
		case COMBAT_PARAM_TYPE: {
			params.combatType = static_cast<CombatType_t>(value);
			return true;
		}

		case COMBAT_PARAM_EFFECT: {
			params.impactEffect = static_cast<uint32_t>(value);
			return true;
		}

		case COMBAT_PARAM_DISTANCEEFFECT: {
			params.distanceEffect = static_cast<uint32_t>(value);
			return true;
		}

		case COMBAT_PARAM_BLOCKARMOR: {
			params.blockedByArmor = (value != 0);
			return true;
		}

		case COMBAT_PARAM_BLOCKSHIELD: {
			params.blockedByShield = (value != 0);
			return true;
		}

		case COMBAT_PARAM_TARGETCASTERORTOPMOST: {
			params.targetCasterOrTopMost = (value != 0);
			return true;
		}

		case COMBAT_PARAM_CREATEITEM: {
			params.itemId = value;
			return true;
		}

		case COMBAT_PARAM_AGGRESSIVE: {
			params.aggressive = (value != 0);
			return true;
		}

		case COMBAT_PARAM_DISPEL: {
			params.dispelType = static_cast<ConditionType_t>(value);
			return true;
		}

		case COMBAT_PARAM_USECHARGES: {
			params.useCharges = (value != 0);
			return true;
		}
	}
	return false;
}

bool Combat::setCallback(CallBackParam_t key)
{
	switch (key) {
		case CALLBACK_PARAM_LEVELMAGICVALUE: {
			params.valueCallback.reset(new ValueCallback(COMBAT_FORMULA_LEVELMAGIC));
			return true;
		}

		case CALLBACK_PARAM_SKILLVALUE: {
			params.valueCallback.reset(new ValueCallback(COMBAT_FORMULA_SKILL));
			return true;
		}

		case CALLBACK_PARAM_TARGETTILE: {
			params.tileCallback.reset(new TileCallback());
			return true;
		}

		case CALLBACK_PARAM_TARGETCREATURE: {
			params.targetCallback.reset(new TargetCallback());
			return true;
		}
	}
	return false;
}

CallBack* Combat::getCallback(CallBackParam_t key)
{
	switch (key) {
		case CALLBACK_PARAM_LEVELMAGICVALUE:
		case CALLBACK_PARAM_SKILLVALUE: {
			return params.valueCallback.get();
		}

		case CALLBACK_PARAM_TARGETTILE: {
			return params.tileCallback.get();
		}

		case CALLBACK_PARAM_TARGETCREATURE: {
			return params.targetCallback.get();
		}
	}
	return nullptr;
}
