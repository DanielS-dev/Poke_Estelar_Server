// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_DEPOTCHEST_H_6538526014684E3DBC92CC12815B6766
#define FS_DEPOTCHEST_H_6538526014684E3DBC92CC12815B6766

#include "container.h"

class DepotChest final : public Container
{
	public:
		explicit DepotChest(uint16_t type);

		//serialization
		void setMaxDepotItems(uint32_t maxitems) {
			maxDepotItems = maxitems;
		}

		//cylinder implementations
		ReturnValue queryAdd(int32_t index, const Thing& thing, uint32_t count,
				uint32_t flags, Creature* actor = nullptr) const;

		void postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t link = LINK_OWNER);
		void postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, cylinderlink_t link = LINK_OWNER);

		//overrides
		bool canRemove() const {
			return false;
		}

		Cylinder* getParent() const;
		Cylinder* getRealParent() const {
			return parent;
		}

	private:
		uint32_t maxDepotItems;
};

#endif

