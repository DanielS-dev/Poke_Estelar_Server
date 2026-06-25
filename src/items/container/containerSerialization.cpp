// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../container.hpp"
#include "../../persistence/map/iomap.hpp"

Attr_ReadValue Container::readAttr(AttrTypes_t attr, PropStream& propStream)
{
	if (attr == ATTR_CONTAINER_ITEMS) {
		if (!propStream.read<uint32_t>(serializationCount)) {
			return ATTR_READ_ERROR;
		}
		return ATTR_READ_END;
	}
	return Item::readAttr(attr, propStream);
}

bool Container::unserializeItemNode(FileLoader& f, NODE node, PropStream& propStream)
{
	bool ret = Item::unserializeItemNode(f, node, propStream);
	if (!ret) {
		return false;
	}

	uint32_t type;
	NODE nodeItem = f.getChildNode(node, type);
	while (nodeItem) {
		//load container items
		if (type != OTBM_ITEM) {
			// unknown type
			return false;
		}

		PropStream itemPropStream;
		if (!f.getProps(nodeItem, itemPropStream)) {
			return false;
		}

		Item* item = Item::CreateItem(itemPropStream);
		if (!item) {
			return false;
		}

		if (!item->unserializeItemNode(f, nodeItem, itemPropStream)) {
			return false;
		}

		addItem(item);
		updateItemWeight(item->getWeight());

		nodeItem = f.getNextNode(nodeItem, type);
	}
	return true;
}

