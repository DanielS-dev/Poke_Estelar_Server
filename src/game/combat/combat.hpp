// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_COMBAT_H_B02CE79230FC43708699EE91FCC8F7CC
#define FS_COMBAT_H_B02CE79230FC43708699EE91FCC8F7CC

#include "areaCombat.hpp"
#include "combatCallbacks.hpp"
#include "combatTypes.hpp"
#include "magicField.hpp"
#include "../condition/condition.hpp"
#include "../../world/map.hpp"

class Combat
{
	public:
		Combat() = default;

		// non-copyable
		Combat(const Combat&) = delete;
		Combat& operator=(const Combat&) = delete;

		static void doCombatHealth(Creature* caster, Creature* target, CombatDamage& damage, const CombatParams& params);
		static void doCombatHealth(Creature* caster, const Position& position, const AreaCombat* area, CombatDamage& damage, const CombatParams& params);

		static void doCombatMana(Creature* caster, Creature* target, CombatDamage& damage, const CombatParams& params);
		static void doCombatMana(Creature* caster, const Position& position, const AreaCombat* area, CombatDamage& damage, const CombatParams& params);

		static void doCombatCondition(Creature* caster, Creature* target, const CombatParams& params);
		static void doCombatCondition(Creature* caster, const Position& position, const AreaCombat* area, const CombatParams& params);

		static void doCombatDispel(Creature* caster, Creature* target, const CombatParams& params);
		static void doCombatDispel(Creature* caster, const Position& position, const AreaCombat* area, const CombatParams& params);

		static void getCombatArea(const Position& centerPos, const Position& targetPos, const AreaCombat* area, std::forward_list<Tile*>& list);

		static bool isInPvpZone(const Creature* attacker, const Creature* target);
		static bool isProtected(const Player* attacker, const Player* target);
		static bool isPlayerCombat(const Creature* target);
		static CombatType_t ConditionToDamageType(ConditionType_t type);
		static ConditionType_t DamageToConditionType(CombatType_t type);
		static ReturnValue canTargetCreature(Player* attacker, Creature* target);
		static ReturnValue canDoCombat(Creature* caster, Tile* tile, bool aggressive);
		static ReturnValue canDoCombat(Creature* attacker, Creature* target);
		static void postCombatEffects(Creature* caster, const Position& pos, const CombatParams& params);

		static void addDistanceEffect(Creature* caster, const Position& fromPos, const Position& toPos, uint8_t effect);

		void doCombat(Creature* caster, Creature* target) const;
		void doCombat(Creature* caster, const Position& pos) const;

		bool setCallback(CallBackParam_t key);
		CallBack* getCallback(CallBackParam_t key);

		bool setParam(CombatParam_t param, uint32_t value);
		void setArea(AreaCombat* area) {
			this->area.reset(area);
		}
		bool hasArea() const {
			return area != nullptr;
		}
		void setCondition(const Condition* condition) {
			params.conditionList.emplace_front(condition);
		}
		void setPlayerCombatValues(formulaType_t formulaType, double mina, double minb, double maxa, double maxb);
		void postCombatEffects(Creature* caster, const Position& pos) const {
			postCombatEffects(caster, pos, params);
		}

		void setOrigin(CombatOrigin origin) {
			params.origin = origin;
		}

	protected:
		static void doCombatDefault(Creature* caster, Creature* target, const CombatParams& params);

		static void CombatFunc(Creature* caster, const Position& pos, const AreaCombat* area, const CombatParams& params, COMBATFUNC func, CombatDamage* data);

		static void CombatHealthFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* data);
		static void CombatManaFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* damage);
		static void CombatConditionFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* data);
		static void CombatDispelFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* data);
		static void CombatNullFunc(Creature* caster, Creature* target, const CombatParams& params, CombatDamage* data);

		static void combatTileEffects(const SpectatorVec& list, Creature* caster, Tile* tile, const CombatParams& params);
		CombatDamage getCombatDamage(Creature* creature, Creature* target) const;

		//configureable
		CombatParams params;

		//formula variables
		formulaType_t formulaType = COMBAT_FORMULA_UNDEFINED;
		double mina = 0.0;
		double minb = 0.0;
		double maxa = 0.0;
		double maxb = 0.0;

		std::unique_ptr<AreaCombat> area;
};

#endif
