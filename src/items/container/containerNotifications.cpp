// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../container.hpp"
#include "../../game/game.hpp"

extern Game g_game;

void Container::onAddContainerItem(Item* item)
{
	SpectatorVec list;
	g_game.map.getSpectators(list, getPosition(), false, true, 2, 2, 2, 2);

	//send to client
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendAddContainerItem(this, item);
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->getPlayer()->onAddContainerItem(item);
	}
}

void Container::onUpdateContainerItem(uint32_t index, Item* oldItem, Item* newItem)
{
	SpectatorVec list;
	g_game.map.getSpectators(list, getPosition(), false, true, 2, 2, 2, 2);

	//send to client
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendUpdateContainerItem(this, index, newItem);
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->getPlayer()->onUpdateContainerItem(this, oldItem, newItem);
	}
}

void Container::onRemoveContainerItem(uint32_t index, Item* item)
{
	SpectatorVec list;
	g_game.map.getSpectators(list, getPosition(), false, true, 2, 2, 2, 2);

	//send change to client
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendRemoveContainerItem(this, index);
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->getPlayer()->onRemoveContainerItem(this, item);
	}
}


void Container::postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t)
{
	Cylinder* topParent = getTopParent();
	if (topParent->getCreature()) {
		topParent->postAddNotification(thing, oldParent, index, LINK_TOPPARENT);
	} else if (topParent == this) {
		//let the tile class notify surrounding players
		if (topParent->getParent()) {
			topParent->getParent()->postAddNotification(thing, oldParent, index, LINK_NEAR);
		}
	} else {
		topParent->postAddNotification(thing, oldParent, index, LINK_PARENT);
	}
}

void Container::postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, cylinderlink_t)
{
	Cylinder* topParent = getTopParent();
	if (topParent->getCreature()) {
		topParent->postRemoveNotification(thing, newParent, index, LINK_TOPPARENT);
	} else if (topParent == this) {
		//let the tile class notify surrounding players
		if (topParent->getParent()) {
			topParent->getParent()->postRemoveNotification(thing, newParent, index, LINK_NEAR);
		}
	} else {
		topParent->postRemoveNotification(thing, newParent, index, LINK_PARENT);
	}
}

