// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"
#include "combat.hpp"

#include "../game.hpp"
#include "../../config/configmanager.hpp"
#include "../../scripting/events.hpp"
#include "../../entities/monster.hpp"

extern Game g_game;
extern ConfigManager g_config;
void Combat::CombatHealthFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* data)
{
	assert(data);
	CombatDamage damage = *data;
	if (g_game.combatBlockHit(damage, caster, target, params.blockedByShield, params.blockedByArmor, params.itemId != 0)) {
		return;
	}

	if ((damage.primary.value < 0 || damage.secondary.value < 0) && caster) {
		Player* targetPlayer = target->getPlayer();
		if (targetPlayer && caster->getPlayer() && targetPlayer->getSkull() != SKULL_BLACK) {
			damage.primary.value /= 2;
			damage.secondary.value /= 2;
		}
	}

	// Monster level damage bonuses 
	Monster* monster = caster ? caster->getMonster() : nullptr;
	if (monster && damage.primary.value < 0) { //pota
		double dmgBonus = g_config.getDouble(ConfigManager::MONSTERLEVEL_BONUSDMG);
		if (dmgBonus > 0) {
			damage.primary.value += damage.primary.value * (dmgBonus * monster->getLevel());
			damage.secondary.value += damage.secondary.value * (dmgBonus * monster->getLevel());
		}
	}

	if (g_game.combatChangeHealth(caster, target, damage)) {
		CombatConditionFunc(caster, target, params, nullptr);
		CombatDispelFunc(caster, target, params, nullptr);
	}
}

void Combat::CombatManaFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* data)
{
	assert(data);
	CombatDamage damage = *data;
	if (damage.primary.value < 0) {
		if (caster && caster->getPlayer() && target->getPlayer()) {
			damage.primary.value /= 2;
		}
	}

	// Monster level damage bonuses 
	Monster* monster = caster ? caster->getMonster() : nullptr;
	if (monster && damage.primary.value < 0) { //pota
		double dmgBonus = g_config.getDouble(ConfigManager::MONSTERLEVEL_BONUSDMG);
		if (dmgBonus > 0) {
			damage.primary.value += damage.primary.value * (dmgBonus * monster->getLevel());
			damage.secondary.value += damage.secondary.value * (dmgBonus * monster->getLevel());
		}
	}

	if (g_game.combatChangeMana(caster, target, damage.primary.value, damage.origin)) {
		CombatConditionFunc(caster, target, params, nullptr);
		CombatDispelFunc(caster, target, params, nullptr);
	}
}

void Combat::CombatConditionFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage*)
{
	for (const auto& condition : params.conditionList) {
		if (caster == target || !target->isImmune(condition->getType())) {
			Condition* conditionCopy = condition->clone();
			if (caster) {
				conditionCopy->setParam(CONDITION_PARAM_OWNER, caster->getID());
			}

			//TODO: infight condition until all aggressive conditions has ended
			target->addCombatCondition(conditionCopy);
		}
	}
}

void Combat::CombatDispelFunc(Creature*, Creature* target, const CombatParams& params, CombatDamage*)
{
	target->removeCombatCondition(params.dispelType);
}

void Combat::CombatNullFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage*)
{
	CombatConditionFunc(caster, target, params, nullptr);
	CombatDispelFunc(caster, target, params, nullptr);
}

void Combat::combatTileEffects(const SpectatorVec& list, Creature* caster, Tile* tile, const CombatParams& params)
{
	if (params.itemId != 0) {
		uint16_t itemId = params.itemId;
		switch (itemId) {
			case ITEM_FIREFIELD_PERSISTENT_FULL:
				itemId = ITEM_FIREFIELD_PVP_FULL;
				break;

			case ITEM_FIREFIELD_PERSISTENT_MEDIUM:
				itemId = ITEM_FIREFIELD_PVP_MEDIUM;
				break;

			case ITEM_FIREFIELD_PERSISTENT_SMALL:
				itemId = ITEM_FIREFIELD_PVP_SMALL;
				break;

			case ITEM_ENERGYFIELD_PERSISTENT:
				itemId = ITEM_ENERGYFIELD_PVP;
				break;

			case ITEM_POISONFIELD_PERSISTENT:
				itemId = ITEM_POISONFIELD_PVP;
				break;

			case ITEM_MAGICWALL_PERSISTENT:
				itemId = ITEM_MAGICWALL;
				break;

			case ITEM_WILDGROWTH_PERSISTENT:
				itemId = ITEM_WILDGROWTH;
				break;

			default:
				break;
		}

		if (caster) {
			Player* casterPlayer;
			if (caster->isSummon()) {
				casterPlayer = caster->getMaster()->getPlayer();
			} else {
				casterPlayer = caster->getPlayer();
			}

			if (casterPlayer) {
				if (g_game.getWorldType() == WORLD_TYPE_NO_PVP || tile->hasFlag(TILESTATE_NOPVPZONE)) {
					if (itemId == ITEM_FIREFIELD_PVP_FULL) {
						itemId = ITEM_FIREFIELD_NOPVP;
					} else if (itemId == ITEM_POISONFIELD_PVP) {
						itemId = ITEM_POISONFIELD_NOPVP;
					} else if (itemId == ITEM_ENERGYFIELD_PVP) {
						itemId = ITEM_ENERGYFIELD_NOPVP;
					}
				} else if (itemId == ITEM_FIREFIELD_PVP_FULL || itemId == ITEM_POISONFIELD_PVP || itemId == ITEM_ENERGYFIELD_PVP) {
					casterPlayer->addInFightTicks();
				}
			}
		}

		Item* item = Item::CreateItem(itemId);
		if (caster) {
			item->setOwner(caster->getID());
		}

		ReturnValue ret = g_game.internalAddItem(tile, item);
		if (ret == RETURNVALUE_NOERROR) {
			g_game.startDecay(item);
		} else {
			delete item;
		}
	}

	if (params.tileCallback) {
		params.tileCallback->onTileCombat(caster, tile);
	}

	if (params.impactEffect != CONST_ME_NONE) {
		Game::addMagicEffect(list, tile->getPosition(), params.impactEffect);
	}
}

void Combat::postCombatEffects(Creature* caster, const Position& pos, const CombatParams& params)
{
	if (caster && params.distanceEffect != CONST_ANI_NONE) {
		addDistanceEffect(caster, caster->getPosition(), pos, params.distanceEffect);
	}
}

void Combat::addDistanceEffect(Creature* caster, const Position& fromPos, const Position& toPos, uint8_t effect)
{
	if (effect == CONST_ANI_WEAPONTYPE) {
		if (!caster) {
			return;
		}

		Player* player = caster->getPlayer();
		if (!player) {
			return;
		}

		switch (player->getWeaponType()) {
			case WEAPON_AXE:
				effect = CONST_ANI_WHIRLWINDAXE;
				break;
			case WEAPON_SWORD:
				effect = CONST_ANI_WHIRLWINDSWORD;
				break;
			case WEAPON_CLUB:
				effect = CONST_ANI_WHIRLWINDCLUB;
				break;
			default:
				effect = CONST_ANI_NONE;
				break;
		}
	}

	if (effect != CONST_ANI_NONE) {
		g_game.addDistanceEffect(fromPos, toPos, effect);
	}
}

void Combat::CombatFunc(Creature* caster, const Position& pos, const AreaCombat* area, const CombatParams& params, COMBATFUNC func, CombatDamage* data)
{
	std::forward_list<Tile*> tileList;

	if (caster) {
		getCombatArea(caster->getPosition(), pos, area, tileList);
	} else {
		getCombatArea(pos, pos, area, tileList);
	}

	SpectatorVec list;
	uint32_t maxX = 0;
	uint32_t maxY = 0;

	//calculate the max viewable range
	for (Tile* tile : tileList) {
		const Position& tilePos = tile->getPosition();

		uint32_t diff = Position::getDistanceX(tilePos, pos);
		if (diff > maxX) {
			maxX = diff;
		}

		diff = Position::getDistanceY(tilePos, pos);
		if (diff > maxY) {
			maxY = diff;
		}
	}

	const int32_t rangeX = maxX + Map::maxViewportX;
	const int32_t rangeY = maxY + Map::maxViewportY;
	g_game.map.getSpectators(list, pos, true, true, rangeX, rangeX, rangeY, rangeY);

	for (Tile* tile : tileList) {
		if (canDoCombat(caster, tile, params.aggressive) != RETURNVALUE_NOERROR) {
			continue;
		}

		if (CreatureVector* creatures = tile->getCreatures()) {
			const Creature* topCreature = tile->getTopCreature();
			for (Creature* creature : *creatures) {
				if (params.targetCasterOrTopMost) {
					if (caster && caster->getTile() == tile) {
						if (creature != caster) {
							continue;
						}
					} else if (creature != topCreature) {
						continue;
					}
				}

				if (!params.aggressive || (caster != creature && Combat::canDoCombat(caster, creature) == RETURNVALUE_NOERROR)) {
					func(caster, creature, params, data);
					if (params.targetCallback) {
						params.targetCallback->onTargetCombat(caster, creature);
					}

					if (params.targetCasterOrTopMost) {
						break;
					}
				}
			}
		}
		combatTileEffects(list, caster, tile, params);
	}
	postCombatEffects(caster, pos, params);
}

void Combat::doCombat(Creature* caster, Creature* target) const
{
	//target combat callback function
	if (params.combatType != COMBAT_NONE) {
		CombatDamage damage = getCombatDamage(caster, target);
		if (damage.primary.type != COMBAT_MANADRAIN) {
			doCombatHealth(caster, target, damage, params);
		} else {
			doCombatMana(caster, target, damage, params);
		}
	} else {
		doCombatDefault(caster, target, params);
	}
}

void Combat::doCombat(Creature* caster, const Position& position) const
{
	//area combat callback function
	if (params.combatType != COMBAT_NONE) {
		CombatDamage damage = getCombatDamage(caster, nullptr);
		if (damage.primary.type != COMBAT_MANADRAIN) {
			doCombatHealth(caster, position, area.get(), damage, params);
		} else {
			doCombatMana(caster, position, area.get(), damage, params);
		}
	} else {
		CombatFunc(caster, position, area.get(), params, CombatNullFunc, nullptr);
	}
}

void Combat::doCombatHealth(Creature* caster, Creature* target, CombatDamage& damage, const CombatParams& params)
{
	bool canCombat = !params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR);
	if ((caster == target || canCombat) && params.impactEffect != CONST_ME_NONE) {
		g_game.addMagicEffect(target->getPosition(), params.impactEffect);
	}

	if (canCombat) {
		CombatHealthFunc(caster, target, params, &damage);
		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster, caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

void Combat::doCombatHealth(Creature* caster, const Position& position, const AreaCombat* area, CombatDamage& damage, const CombatParams& params)
{
	CombatFunc(caster, position, area, params, CombatHealthFunc, &damage);
}

void Combat::doCombatMana(Creature* caster, Creature* target, CombatDamage& damage, const CombatParams& params)
{
	bool canCombat = !params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR);
	if ((caster == target || canCombat) && params.impactEffect != CONST_ME_NONE) {
		g_game.addMagicEffect(target->getPosition(), params.impactEffect);
	}

	if (canCombat) {
		CombatManaFunc(caster, target, params, &damage);
		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster, caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

void Combat::doCombatMana(Creature* caster, const Position& position, const AreaCombat* area, CombatDamage& damage, const CombatParams& params)
{
	CombatFunc(caster, position, area, params, CombatManaFunc, &damage);
}

void Combat::doCombatCondition(Creature* caster, const Position& position, const AreaCombat* area, const CombatParams& params)
{
	CombatFunc(caster, position, area, params, CombatConditionFunc, nullptr);
}

void Combat::doCombatCondition(Creature* caster, Creature* target, const CombatParams& params)
{
	bool canCombat = !params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR);
	if ((caster == target || canCombat) && params.impactEffect != CONST_ME_NONE) {
		g_game.addMagicEffect(target->getPosition(), params.impactEffect);
	}

	if (canCombat) {
		CombatConditionFunc(caster, target, params, nullptr);
		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster, caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

void Combat::doCombatDispel(Creature* caster, const Position& position, const AreaCombat* area, const CombatParams& params)
{
	CombatFunc(caster, position, area, params, CombatDispelFunc, nullptr);
}

void Combat::doCombatDispel(Creature* caster, Creature* target, const CombatParams& params)
{
	bool canCombat = !params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR);
	if ((caster == target || canCombat) && params.impactEffect != CONST_ME_NONE) {
		g_game.addMagicEffect(target->getPosition(), params.impactEffect);
	}

	if (canCombat) {
		CombatDispelFunc(caster, target, params, nullptr);
		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster, caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

void Combat::doCombatDefault(Creature* caster, Creature* target, const CombatParams& params)
{
	if (!params.aggressive || (caster != target && Combat::canDoCombat(caster, target) == RETURNVALUE_NOERROR)) {
		SpectatorVec list;
		g_game.map.getSpectators(list, target->getPosition(), true, true);

		CombatNullFunc(caster, target, params, nullptr);
		combatTileEffects(list, caster, target->getTile(), params);

		if (params.targetCallback) {
			params.targetCallback->onTargetCombat(caster, target);
		}

		/*
		if (params.impactEffect != CONST_ME_NONE) {
			g_game.addMagicEffect(target->getPosition(), params.impactEffect);
		}
		*/

		if (caster && params.distanceEffect != CONST_ANI_NONE) {
			addDistanceEffect(caster, caster->getPosition(), target->getPosition(), params.distanceEffect);
		}
	}
}

//**********************************************************//
