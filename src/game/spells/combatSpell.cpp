// This file is part of The Forgotten Server.

// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../combat/combat.hpp"
#include "../game.hpp"

#include "combatSpell.hpp"
#include "spells.hpp"

extern Spells* g_spells;
extern LuaEnvironment g_luaEnvironment;
CombatSpell::CombatSpell(Combat* combat, bool needTarget, bool needDirection) :
	Event(&g_spells->getScriptInterface()),
	combat(combat),
	needDirection(needDirection),
	needTarget(needTarget)
{}

CombatSpell::~CombatSpell()
{
	if (!scripted) {
		delete combat;
	}
}

bool CombatSpell::loadScriptCombat()
{
	combat = g_luaEnvironment.getCombatObject(g_luaEnvironment.lastCombatId);
	return combat != nullptr;
}

bool CombatSpell::castSpell(Creature* creature)
{
	if (scripted) {
		LuaVariant var;
		var.type = VARIANT_POSITION;

		if (needDirection) {
			var.pos = Spells::getCasterPosition(creature, creature->getDirection());
		} else {
			var.pos = creature->getPosition();
		}

		return executeCastSpell(creature, var);
	}

	Position pos;
	if (needDirection) {
		pos = Spells::getCasterPosition(creature, creature->getDirection());
	} else {
		pos = creature->getPosition();
	}

	combat->doCombat(creature, pos);
	return true;
}

bool CombatSpell::castSpell(Creature* creature, Creature* target)
{
	if (scripted) {
		LuaVariant var;

		if (combat->hasArea()) {
			var.type = VARIANT_POSITION;

			if (needTarget) {
				var.pos = target->getPosition();
			} else if (needDirection) {
				var.pos = Spells::getCasterPosition(creature, creature->getDirection());
			} else {
				var.pos = creature->getPosition();
			}
		} else {
			var.type = VARIANT_NUMBER;
			var.number = target->getID();
		}
		return executeCastSpell(creature, var);
	}

	if (combat->hasArea()) {
		if (needTarget) {
			combat->doCombat(creature, target->getPosition());
		} else {
			return castSpell(creature);
		}
	} else {
		combat->doCombat(creature, target);
	}
	return true;
}

bool CombatSpell::executeCastSpell(Creature* creature, const LuaVariant& var)
{
	//onCastSpell(creature, var)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - CombatSpell::executeCastSpell] Call stack overflow" << std::endl;
		return false;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(scriptId, scriptInterface);

	lua_State* L = scriptInterface->getLuaState();

	scriptInterface->pushFunction(scriptId);

	LuaScriptInterface::pushUserdata<Creature>(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);

	LuaScriptInterface::pushVariant(L, var);

	return scriptInterface->callFunction(2);
}
