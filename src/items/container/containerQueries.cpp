// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../container.hpp"
#include "../inbox.hpp"
#include "../../core/tools/systemTools.hpp"

ReturnValue Container::queryAdd(int32_t index, const Thing& thing, uint32_t count,
		uint32_t flags, Creature* actor/* = nullptr*/) const
{
	bool childIsOwner = hasBitSet(FLAG_CHILDISOWNER, flags);
	if (childIsOwner) {
		//a child container is querying, since we are the top container (not carried by a player)
		//just return with no error.
		return RETURNVALUE_NOERROR;
	}

	if (!unlocked) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	const Item* item = thing.getItem();
	if (item == nullptr) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (!item->isPickupable()) {
		return RETURNVALUE_CANNOTPICKUP;
	}

	if (item == this) {
		return RETURNVALUE_THISISIMPOSSIBLE;
	}

	const Cylinder* cylinder = getParent();
	if (!hasBitSet(FLAG_NOLIMIT, flags)) {
		while (cylinder) {
			if (cylinder == &thing) {
				return RETURNVALUE_THISISIMPOSSIBLE;
			}

			if (dynamic_cast<const Inbox*>(cylinder)) {
				return RETURNVALUE_CONTAINERNOTENOUGHROOM;
			}

			cylinder = cylinder->getParent();
		}

		if (index == INDEX_WHEREEVER && size() >= capacity()) {
			return RETURNVALUE_CONTAINERNOTENOUGHROOM;
		}
	} else {
		while (cylinder) {
			if (cylinder == &thing) {
				return RETURNVALUE_THISISIMPOSSIBLE;
			}

			cylinder = cylinder->getParent();
		}
	}

	const Cylinder* topParent = getTopParent();
	if (topParent != this) {
		return topParent->queryAdd(INDEX_WHEREEVER, *item, count, flags | FLAG_CHILDISOWNER, actor);
	} else {
		return RETURNVALUE_NOERROR;
	}
}

ReturnValue Container::queryMaxCount(int32_t index, const Thing& thing, uint32_t count,
		uint32_t& maxQueryCount, uint32_t flags) const
{
	const Item* item = thing.getItem();
	if (item == nullptr) {
		maxQueryCount = 0;
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (hasBitSet(FLAG_NOLIMIT, flags)) {
		maxQueryCount = std::max<uint32_t>(1, count);
		return RETURNVALUE_NOERROR;
	}

	int32_t freeSlots = std::max<int32_t>(capacity() - size(), 0);

	if (item->isStackable()) {
		uint32_t n = 0;

		if (index == INDEX_WHEREEVER) {
			//Iterate through every item and check how much free stackable slots there is.
			uint32_t slotIndex = 0;
			for (Item* containerItem : itemlist) {
				if (containerItem != item && containerItem->equals(item) && containerItem->getItemCount() < 100) {
					uint32_t remainder = (100 - containerItem->getItemCount());
					if (queryAdd(slotIndex++, *item, remainder, flags) == RETURNVALUE_NOERROR) {
						n += remainder;
					}
				}
			}
		} else {
			const Item* destItem = getItemByIndex(index);
			if (item->equals(destItem) && destItem->getItemCount() < 100) {
				uint32_t remainder = 100 - destItem->getItemCount();
				if (queryAdd(index, *item, remainder, flags) == RETURNVALUE_NOERROR) {
					n = remainder;
				}
			}
		}

		maxQueryCount = freeSlots * 100 + n;
		if (maxQueryCount < count) {
			return RETURNVALUE_CONTAINERNOTENOUGHROOM;
		}
	} else {
		maxQueryCount = freeSlots;
		if (maxQueryCount == 0) {
			return RETURNVALUE_CONTAINERNOTENOUGHROOM;
		}
	}
	return RETURNVALUE_NOERROR;
}

ReturnValue Container::queryRemove(const Thing& thing, uint32_t count, uint32_t flags) const
{
	int32_t index = getThingIndex(&thing);
	if (index == -1) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	const Item* item = thing.getItem();
	if (item == nullptr) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (count == 0 || (item->isStackable() && count > item->getItemCount())) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (!item->isMoveable() && !hasBitSet(FLAG_IGNORENOTMOVEABLE, flags)) {
		return RETURNVALUE_NOTMOVEABLE;
	}
	return RETURNVALUE_NOERROR;
}

Cylinder* Container::queryDestination(int32_t& index, const Thing &thing, Item** destItem,
		uint32_t& flags)
{
	if (!unlocked) {
		*destItem = nullptr;
		return this;
	}

	if (index == 254 /*move up*/) {
		index = INDEX_WHEREEVER;
		*destItem = nullptr;

		Container* parentContainer = dynamic_cast<Container*>(getParent());
		if (parentContainer) {
			return parentContainer;
		}
		return this;
	}

	if (index == 255 /*add wherever*/) {
		index = INDEX_WHEREEVER;
		*destItem = nullptr;
	} else if (index >= static_cast<int32_t>(capacity())) {
		/*
		if you have a container, maximize it to show all 20 slots
		then you open a bag that is inside the container you will have a bag with 8 slots
		and a "grey" area where the other 12 slots where from the container
		if you drop the item on that grey area
		the client calculates the slot position as if the bag has 20 slots
		*/
		index = INDEX_WHEREEVER;
		*destItem = nullptr;
	}

	const Item* item = thing.getItem();
	if (!item) {
		return this;
	}

	bool autoStack = !hasBitSet(FLAG_IGNOREAUTOSTACK, flags);
	if (autoStack && item->isStackable() && item->getParent() != this) {
		//try find a suitable item to stack with
		uint32_t n = 0;
		for (Item* listItem : itemlist) {
			if (listItem != item && listItem->equals(item) && listItem->getItemCount() < 100) {
				*destItem = listItem;
				index = n;
				return this;
			}
			++n;
		}
	}

	if (index != INDEX_WHEREEVER) {
		Item* itemFromIndex = getItemByIndex(index);
		if (itemFromIndex) {
			*destItem = itemFromIndex;
		}

		Cylinder* subCylinder = dynamic_cast<Cylinder*>(*destItem);
		if (subCylinder) {
			index = INDEX_WHEREEVER;
			*destItem = nullptr;
			return subCylinder;
		}
	}
	return this;
}

