// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../container.hpp"
#include "../../game/game.hpp"

extern Game g_game;

Container::Container(uint16_t type) :
	Container(type, items[type].maxItems) {}

Container::Container(uint16_t type, uint16_t size, bool unlocked /*= true*/, bool pagination /*= false*/) :
	Item(type),
	maxSize(size),
	unlocked(unlocked),
	pagination(pagination)
{}

Container::Container(Tile* tile) : Container(ITEM_BROWSEFIELD, 30, false, true)
{
	TileItemVector* itemVector = tile->getItemList();
	if (itemVector) {
		for (Item* item : *itemVector) {
			if (item->getContainer() || item->hasProperty(CONST_PROP_MOVEABLE)) {
				itemlist.push_front(item);
				item->setParent(this);
			}
		}
	}

	setParent(tile);
}

Container::~Container()
{
	if (getID() == ITEM_BROWSEFIELD) {
		g_game.browseFields.erase(getTile());

		for (Item* item : itemlist) {
			item->setParent(parent);
		}
	} else {
		for (Item* item : itemlist) {
			item->setParent(nullptr);
			item->decrementReferenceCounter();
		}
	}
}

Item* Container::clone() const
{
	Container* clone = static_cast<Container*>(Item::clone());
	for (Item* item : itemlist) {
		clone->addItem(item->clone());
	}
	clone->totalWeight = totalWeight;
	return clone;
}

Container* Container::getParentContainer()
{
	Thing* thing = getParent();
	if (!thing) {
		return nullptr;
	}
	return thing->getContainer();
}

bool Container::hasParent() const
{
	return getID() != ITEM_BROWSEFIELD && dynamic_cast<const Player*>(getParent()) == nullptr;
}

void Container::addItem(Item* item)
{
	itemlist.push_back(item);
	item->setParent(this);
}


void Container::updateItemWeight(int32_t diff)
{
	totalWeight += diff;
	if (Container* parentContainer = getParentContainer()) {
		parentContainer->updateItemWeight(diff);
	}
}

uint32_t Container::getWeight() const
{
	return Item::getWeight() + totalWeight;
}

