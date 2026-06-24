// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_COMBATCALLBACKS_H_A27447B3B28D40D8AE416594FD950E6C
#define FS_COMBATCALLBACKS_H_A27447B3B28D40D8AE416594FD950E6C

#include "combatTypes.hpp"
#include "../../scripting/baseevents.hpp"

//for luascript callback
class ValueCallback final : public CallBack
{
	public:
		explicit ValueCallback(formulaType_t type): type(type) {}
		void getMinMaxValues(Player* player, CombatDamage& damage, bool useCharges) const;

	protected:
		formulaType_t type;
};

class TileCallback final : public CallBack
{
	public:
		void onTileCombat(Creature* creature, Tile* tile) const;

	protected:
		formulaType_t type;
};

class TargetCallback final : public CallBack
{
	public:
		void onTargetCombat(Creature* creature, Creature* target) const;

	protected:
		formulaType_t type;
};

#endif
