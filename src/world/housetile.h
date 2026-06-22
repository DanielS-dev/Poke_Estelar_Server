// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_HOUSETILE_H_57D59BEC1CE741D9B142BFC54634505B
#define FS_HOUSETILE_H_57D59BEC1CE741D9B142BFC54634505B

#include "tile.h"

class House;

class HouseTile final : public DynamicTile
{
	public:
		HouseTile(int32_t x, int32_t y, int32_t z, House* house);

		//cylinder implementations
		ReturnValue queryAdd(int32_t index, const Thing& thing, uint32_t count,
				uint32_t flags, Creature* actor = nullptr) const final;

		Tile* queryDestination(int32_t& index, const Thing& thing, Item** destItem,
				uint32_t& flags) final;

		void addThing(int32_t index, Thing* thing) final;
		void internalAddThing(uint32_t index, Thing* thing) final;

		House* getHouse() {
			return house;
		}

	private:
		void updateHouse(Item* item);

		House* house;
};

#endif
