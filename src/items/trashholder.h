// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_TRASHHOLDER_H_BA162024D67B4D388147F5EE06F33098
#define FS_TRASHHOLDER_H_BA162024D67B4D388147F5EE06F33098

#include "item.h"
#include "../world/cylinder.h"
#include "../core/const.h"

class TrashHolder final : public Item, public Cylinder
{
	public:
		explicit TrashHolder(uint16_t itemId) : Item(itemId) {}

		TrashHolder* getTrashHolder() final {
			return this;
		}
		const TrashHolder* getTrashHolder() const final {
			return this;
		}

		//cylinder implementations
		ReturnValue queryAdd(int32_t index, const Thing& thing, uint32_t count, uint32_t flags, Creature* actor = nullptr) const final;
		ReturnValue queryMaxCount(int32_t index, const Thing& thing, uint32_t count, uint32_t& maxQueryCount, uint32_t flags) const final;
		ReturnValue queryRemove(const Thing& thing, uint32_t count, uint32_t flags) const final;
		Cylinder* queryDestination(int32_t& index, const Thing& thing, Item** destItem, uint32_t& flags) final;

		void addThing(Thing* thing) final;
		void addThing(int32_t index, Thing* thing) final;

		void updateThing(Thing* thing, uint16_t itemId, uint32_t count) final;
		void replaceThing(uint32_t index, Thing* thing) final;

		void removeThing(Thing* thing, uint32_t count) final;

		void postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t link = LINK_OWNER) final;
		void postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, cylinderlink_t link = LINK_OWNER) final;
};

#endif
