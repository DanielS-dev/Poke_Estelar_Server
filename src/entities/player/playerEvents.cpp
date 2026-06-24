// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <bitset>

#include "../player.hpp"
#include "../../world/bed.hpp"
#include "../../game/chat/chat.hpp"
#include "../../game/combat/combat.hpp"
#include "../../config/configmanager.hpp"
#include "../../scripting/creatureevent/creatureevent.hpp"
#include "../../scripting/events/events.hpp"
#include "../../game/game.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../monster.hpp"
#include "../../game/movement/movement.hpp"
#include "../../core/scheduler.hpp"
#include "../../game/weapons/weapons.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/returnMessageTools.hpp"
#include "../../core/tools/stringsTools.hpp"

extern ConfigManager g_config;
extern Game g_game;
extern Chat* g_chat;
extern Vocations g_vocations;
extern MoveEvents* g_moveEvents;
extern Weapons* g_weapons;
extern CreatureEvents* g_creatureEvents;
extern Events* g_events;

void Player::onUpdateTileItem(const Tile* tile, const Position& pos, const Item* oldItem,
                              const ItemType& oldType, const Item* newItem, const ItemType& newType)
{
	Creature::onUpdateTileItem(tile, pos, oldItem, oldType, newItem, newType);

	if (oldItem != newItem) {
		onRemoveTileItem(tile, pos, oldType, oldItem);
	}

	if (tradeState != TRADE_TRANSFER) {
		if (tradeItem && oldItem == tradeItem) {
			g_game.internalCloseTrade(this);
		}
	}
}


void Player::onRemoveTileItem(const Tile* tile, const Position& pos, const ItemType& iType,
                              const Item* item)
{
	Creature::onRemoveTileItem(tile, pos, iType, item);

	if (tradeState != TRADE_TRANSFER) {
		checkTradeState(item);

		if (tradeItem) {
			const Container* container = item->getContainer();
			if (container && container->isHoldingItem(tradeItem)) {
				g_game.internalCloseTrade(this);
			}
		}
	}
}


void Player::onCreatureAppear(Creature* creature, bool isLogin)
{
	Creature::onCreatureAppear(creature, isLogin);

	if (isLogin && creature == this) {
		for (int32_t slot = CONST_SLOT_FIRST; slot <= CONST_SLOT_LAST; ++slot) {
			Item* item = inventory[slot];
			if (item) {
				item->startDecaying();
				g_moveEvents->onPlayerEquip(this, item, static_cast<slots_t>(slot), false);
			}
		}

		for (Condition* condition : storedConditionList) {
			addCondition(condition);
		}
		storedConditionList.clear();

		BedItem* bed = g_game.getBedBySleeper(guid);
		if (bed) {
			bed->wakeUp(this);
		}

		std::cout << name << " has logged in." << std::endl;

		if (guild) {
			guild->addMember(this);
		}

		int32_t offlineTime;
		if (getLastLogout() != 0) {
			// Not counting more than 21 days to prevent overflow when multiplying with 1000 (for milliseconds).
			offlineTime = std::min<int32_t>(time(nullptr) - getLastLogout(), 86400 * 21);
		} else {
			offlineTime = 0;
		}

		for (Condition* condition : getMuteConditions()) {
			condition->setTicks(condition->getTicks() - (offlineTime * 1000));
			if (condition->getTicks() <= 0) {
				removeCondition(condition);
			}
		}

		g_game.checkPlayersRecord();
		IOLoginData::updateOnlineStatus(guid, true);
	}
}


void Player::onAttackedCreatureDisappear(bool isLogout)
{
	sendCancelTarget();

	if (!isLogout) {
		sendTextMessage(MESSAGE_STATUS_SMALL, "Target lost.");
	}
}


void Player::onFollowCreatureDisappear(bool isLogout)
{
	sendCancelTarget();

	if (!isLogout) {
		sendTextMessage(MESSAGE_STATUS_SMALL, "Target lost.");
	}
}


void Player::onChangeZone(ZoneType_t zone)
{
	if (zone == ZONE_PROTECTION) {
		if (attackedCreature && !hasFlag(PlayerFlag_IgnoreProtectionZone)) {
			setAttackedCreature(nullptr);
			onAttackedCreatureDisappear(false);
		}

		if (!group->access && isMounted()) {
			dismount();
			g_game.internalCreatureChangeOutfit(this, defaultOutfit);
			wasMounted = true;
		}
	} else {
		if (wasMounted) {
			toggleMount(true);
			wasMounted = false;
		}
	}

	g_game.updateCreatureWalkthrough(this);
	sendIcons();
}


void Player::onAttackedCreatureChangeZone(ZoneType_t zone)
{
	if (zone == ZONE_PROTECTION) {
		if (!hasFlag(PlayerFlag_IgnoreProtectionZone)) {
			setAttackedCreature(nullptr);
			onAttackedCreatureDisappear(false);
		}
	} else if (zone == ZONE_NOPVP) {
		if (attackedCreature->getPlayer()) {
			if (!hasFlag(PlayerFlag_IgnoreProtectionZone)) {
				setAttackedCreature(nullptr);
				onAttackedCreatureDisappear(false);
			}
		}
	} else if (zone == ZONE_NORMAL) {
		//attackedCreature can leave a pvp zone if not pzlocked
		if (g_game.getWorldType() == WORLD_TYPE_NO_PVP) {
			if (attackedCreature->getPlayer()) {
				setAttackedCreature(nullptr);
				onAttackedCreatureDisappear(false);
			}
		}
	}
}


void Player::onRemoveCreature(Creature* creature, bool isLogout)
{
	Creature::onRemoveCreature(creature, isLogout);

	if (creature == this) {
		if (isLogout) {
			loginPosition = getPosition();
		}

		lastLogout = time(nullptr);

		if (eventWalk != 0) {
			setFollowCreature(nullptr);
		}

		if (tradePartner) {
			g_game.internalCloseTrade(this);
		}

		closeShopWindow();

		clearPartyInvitations();

		if (party) {
			party->leaveParty(this);
		}

		g_chat->removeUserFromAllChannels(*this);

		std::cout << getName() << " has logged out." << std::endl;

		if (guild) {
			guild->removeMember(this);
		}

		IOLoginData::updateOnlineStatus(guid, false);

		bool saved = false;
		for (uint32_t tries = 0; tries < 3; ++tries) {
			if (IOLoginData::savePlayer(this)) {
				saved = true;
				break;
			}
		}

		if (!saved) {
			std::cout << "Error while saving player: " << getName() << std::endl;
		}
	}
}


