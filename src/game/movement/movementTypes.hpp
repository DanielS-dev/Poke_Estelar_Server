// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_MOVEMENTTYPES_H_A9C47E9AC5D04536A8A94407B89754A43
#define FS_MOVEMENTTYPES_H_A9C47E9AC5D04536A8A94407B89754A43

#include <cstdint>
#include <map>

#include "../../core/position.hpp"
#include "../../entities/creature.hpp"
#include "../../items/items.hpp"

class Item;
class MoveEvent;
class Player;

enum MoveEvent_t {
	MOVE_EVENT_STEP_IN,
	MOVE_EVENT_STEP_OUT,
	MOVE_EVENT_EQUIP,
	MOVE_EVENT_DEEQUIP,
	MOVE_EVENT_ADD_ITEM,
	MOVE_EVENT_REMOVE_ITEM,
	MOVE_EVENT_ADD_ITEM_ITEMTILE,
	MOVE_EVENT_REMOVE_ITEM_ITEMTILE,

	MOVE_EVENT_LAST,
	MOVE_EVENT_NONE
};

typedef std::map<uint16_t, bool> VocEquipMap;

typedef uint32_t (StepFunction)(Creature* creature, Item* item, const Position& pos);
typedef uint32_t (MoveFunction)(Item* item, Item* tileItem, const Position& pos);
typedef uint32_t (EquipFunction)(MoveEvent* moveEvent, Player* player, Item* item, slots_t slot, bool boolean);

#endif
