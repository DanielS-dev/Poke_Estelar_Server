// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_BED_H_84DE19758D424C6C9789189231946BFF
#define FS_BED_H_84DE19758D424C6C9789189231946BFF

#include "../items/item.hpp"

class House;
class Player;

class BedItem final : public Item
{
	public:
		explicit BedItem(uint16_t id);

		BedItem* getBed() final {
			return this;
		}
		const BedItem* getBed() const final {
			return this;
		}

		Attr_ReadValue readAttr(AttrTypes_t attr, PropStream& propStream) final;
		void serializeAttr(PropWriteStream& propWriteStream) const final;

		bool canRemove() const final {
			return house == nullptr;
		}

		uint32_t getSleeper() const {
			return sleeperGUID;
		}

		House* getHouse() const {
			return house;
		}
		void setHouse(House* h) {
			house = h;
		}

		bool canUse(Player* player);

		bool trySleep(Player* player);
		bool sleep(Player* player);
		void wakeUp(Player* player);

		BedItem* getNextBedItem() const;

	protected:
		void updateAppearance(const Player* player);
		void regeneratePlayer(Player* player) const;
		void internalSetSleeper(const Player* player);
		void internalRemoveSleeper();

		House* house = nullptr;
		uint64_t sleepStart;
		uint32_t sleeperGUID;
};

#endif
