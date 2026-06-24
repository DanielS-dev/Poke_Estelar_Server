// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_MAGICFIELD_H_2AF4839A53294582A8F375A83B017422
#define FS_MAGICFIELD_H_2AF4839A53294582A8F375A83B017422

#include "../../core/tools/systemTools.hpp"
#include "../../items/item.hpp"

class MagicField final : public Item
{
	public:
		explicit MagicField(uint16_t type) : Item(type), createTime(OTSYS_TIME()) {}

		MagicField* getMagicField() final {
			return this;
		}
		const MagicField* getMagicField() const final {
			return this;
		}

		bool isReplaceable() const {
			return Item::items[getID()].replaceable;
		}
		CombatType_t getCombatType() const {
			const ItemType& it = items[getID()];
			return it.combatType;
		}
		void onStepInField(Creature* creature);

	private:
		int64_t createTime;
};

#endif
