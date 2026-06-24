// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <boost/range/adaptor/reversed.hpp>

#include "../tile.hpp"

#include "../../entities/creature.hpp"
#include "../../entities/monster.hpp"
#include "../../game/combat/combat.hpp"
#include "../../game/game.hpp"
#include "../../game/movement/movement.hpp"
#include "../../items/mailbox.hpp"
#include "../../items/trashholder.hpp"
#include "../teleport.hpp"

extern Game g_game;
extern MoveEvents* g_moveEvents;
void Tile::onAddTileItem(Item* item)
{
	if (item->hasProperty(CONST_PROP_MOVEABLE) || item->getContainer()) {
		auto it = g_game.browseFields.find(this);
		if (it != g_game.browseFields.end()) {
			it->second->addItemBack(item);
			item->setParent(this);
		}
	}

	setTileFlags(item);

	const Position& cylinderMapPos = getPosition();

	SpectatorVec list;
	g_game.map.getSpectators(list, cylinderMapPos, true);

	//send to client
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendAddTileItem(this, cylinderMapPos, item);
		}
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->onAddTileItem(this, cylinderMapPos);
	}
}

void Tile::onUpdateTileItem(Item* oldItem, const ItemType& oldType, Item* newItem, const ItemType& newType)
{
	if (newItem->hasProperty(CONST_PROP_MOVEABLE) || newItem->getContainer()) {
		auto it = g_game.browseFields.find(this);
		if (it != g_game.browseFields.end()) {
			int32_t index = it->second->getThingIndex(oldItem);
			if (index != -1) {
				it->second->replaceThing(index, newItem);
				newItem->setParent(this);
			}
		}
	} else if (oldItem->hasProperty(CONST_PROP_MOVEABLE) || oldItem->getContainer()) {
		auto it = g_game.browseFields.find(this);
		if (it != g_game.browseFields.end()) {
			Cylinder* oldParent = oldItem->getParent();
			it->second->removeThing(oldItem, oldItem->getItemCount());
			oldItem->setParent(oldParent);
		}
	}

	const Position& cylinderMapPos = getPosition();

	SpectatorVec list;
	g_game.map.getSpectators(list, cylinderMapPos, true);

	//send to client
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendUpdateTileItem(this, cylinderMapPos, newItem);
		}
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->onUpdateTileItem(this, cylinderMapPos, oldItem, oldType, newItem, newType);
	}
}

void Tile::onRemoveTileItem(const SpectatorVec& list, const std::vector<int32_t>& oldStackPosVector, Item* item)
{
	if (item->hasProperty(CONST_PROP_MOVEABLE) || item->getContainer()) {
		auto it = g_game.browseFields.find(this);
		if (it != g_game.browseFields.end()) {
			it->second->removeThing(item, item->getItemCount());
		}
	}

	resetTileFlags(item);

	const Position& cylinderMapPos = getPosition();
	const ItemType& iType = Item::items[item->getID()];

	//send to client
	size_t i = 0;
	for (Creature* spectator : list) {
		if (Player* tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendRemoveTileThing(cylinderMapPos, oldStackPosVector[i++]);
		}
	}

	//event methods
	for (Creature* spectator : list) {
		spectator->onRemoveTileItem(this, cylinderMapPos, iType, item);
	}
}

void Tile::onUpdateTile(const SpectatorVec& list)
{
	const Position& cylinderMapPos = getPosition();

	//send to clients
	for (Creature* spectator : list) {
		spectator->getPlayer()->sendUpdateTile(this, cylinderMapPos);
	}
}

void Tile::postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t link /*= LINK_OWNER*/)
{
	SpectatorVec list;
	g_game.map.getSpectators(list, getPosition(), true, true);
	for (Creature* spectator : list) {
		spectator->getPlayer()->postAddNotification(thing, oldParent, index, LINK_NEAR);
	}

	//add a reference to this item, it may be deleted after being added (mailbox for example)
	Creature* creature = thing->getCreature();
	Item* item;
	if (creature) {
		creature->incrementReferenceCounter();
		item = nullptr;
	} else {
		item = thing->getItem();
		if (item) {
			item->incrementReferenceCounter();
		}
	}

	if (link == LINK_OWNER) { //pota
		//calling movement scripts
		bool postScript = false;

		if (creature) {
			postScript = g_moveEvents->onCreatureMove(creature, this, MOVE_EVENT_STEP_IN);
		} else if (item) {
			g_moveEvents->onItemMove(item, this, true);
		}

		if (hasFlag(TILESTATE_TELEPORT)) {
			if (postScript) {
				Teleport* teleport = getTeleportItem();
				if (teleport) {
					teleport->addThing(thing);
				}
			}
		} else if (hasFlag(TILESTATE_TRASHHOLDER)) {
			TrashHolder* trashholder = getTrashHolder();
			if (trashholder) {
				trashholder->addThing(thing);
			}
		} else if (hasFlag(TILESTATE_MAILBOX)) {
			Mailbox* mailbox = getMailbox();
			if (mailbox) {
				mailbox->addThing(thing);
			}
		}
	}

	//release the reference to this item onces we are finished
	if (creature) {
		g_game.ReleaseCreature(creature);
	} else if (item) {
		g_game.ReleaseItem(item);
	}
}

void Tile::postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, cylinderlink_t)
{
	SpectatorVec list;
	g_game.map.getSpectators(list, getPosition(), true, true);

	if (getThingCount() > 8) {
		onUpdateTile(list);
	}

	for (Creature* spectator : list) {
		spectator->getPlayer()->postRemoveNotification(thing, newParent, index, LINK_NEAR);
	}

	//calling movement scripts
	Creature* creature = thing->getCreature();
	if (creature) {
		g_moveEvents->onCreatureMove(creature, this, MOVE_EVENT_STEP_OUT);
	} else {
		Item* item = thing->getItem();
		if (item) {
			g_moveEvents->onItemMove(item, this, false);
		}
	}
}

