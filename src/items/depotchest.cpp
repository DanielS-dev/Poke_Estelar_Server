// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "depotchest.hpp"
#include "../core/tools/systemTools.hpp"

DepotChest::DepotChest(uint16_t type) :
	Container(type), maxDepotItems(1500) {}

ReturnValue DepotChest::queryAdd(int32_t index, const Thing& thing, uint32_t count,
		uint32_t flags, Creature* actor/* = nullptr*/) const
{
	const Item* item = thing.getItem();
	if (item == nullptr) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	bool skipLimit = hasBitSet(FLAG_NOLIMIT, flags);
	if (!skipLimit) {
		int32_t addCount = 0;

		if ((item->isStackable() && item->getItemCount() != count)) {
			addCount = 1;
		}

		if (item->getTopParent() != this) {
			if (const Container* container = item->getContainer()) {
				addCount = container->getItemHoldingCount() + 1;
			} else {
				addCount = 1;
			}
		}

		if (getItemHoldingCount() + addCount > maxDepotItems) {
			return RETURNVALUE_DEPOTISFULL;
		}
	}

	return Container::queryAdd(index, thing, count, flags, actor);
}

void DepotChest::postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t)
{
	Cylinder* parent = getParent();
	if (parent != nullptr) {
		parent->postAddNotification(thing, oldParent, index, LINK_PARENT);
	}
}

void DepotChest::postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, cylinderlink_t)
{
	Cylinder* parent = getParent();
	if (parent != nullptr) {
		parent->postRemoveNotification(thing, newParent, index, LINK_PARENT);
	}
}

Cylinder* DepotChest::getParent() const
{
	if (parent) {
		return parent->getParent();
	}
	return nullptr;
}
