// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_DEPOTLOCKER_H_53AD8E0606A34070B87F792611F4F3F8
#define FS_DEPOTLOCKER_H_53AD8E0606A34070B87F792611F4F3F8

#include "container.hpp"
#include "inbox.hpp"

class DepotLocker final : public Container
{
	public:
		explicit DepotLocker(uint16_t type);

		DepotLocker* getDepotLocker() final {
			return this;
		}
		const DepotLocker* getDepotLocker() const final {
			return this;
		}

		void removeInbox(Inbox* inbox);

		//serialization
		Attr_ReadValue readAttr(AttrTypes_t attr, PropStream& propStream) final;

		uint16_t getDepotId() const {
			return depotId;
		}
		void setDepotId(uint16_t depotId) {
			this->depotId = depotId;
		}

		//cylinder implementations
		ReturnValue queryAdd(int32_t index, const Thing& thing, uint32_t count,
				uint32_t flags, Creature* actor = nullptr) const final;

		void postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t link = LINK_OWNER) final;
		void postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, cylinderlink_t link = LINK_OWNER) final;

		bool canRemove() const final {
			return false;
		}

	private:
		uint16_t depotId;
};

#endif

