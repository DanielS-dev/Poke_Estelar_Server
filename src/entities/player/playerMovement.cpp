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

void Player::onWalk(Direction& dir)
{
	Creature::onWalk(dir);
	setNextActionTask(nullptr);
	setNextAction(OTSYS_TIME() + getStepDuration(dir));
}


void Player::onCreatureMove(Creature* creature, const Tile* newTile, const Position& newPos,
                            const Tile* oldTile, const Position& oldPos, bool teleport)
{
	Creature::onCreatureMove(creature, newTile, newPos, oldTile, oldPos, teleport);

	if (hasFollowPath && (creature == followCreature || (creature == this && followCreature))) {
		isUpdatingPath = false;
		g_dispatcher.addTask(createTask(std::bind(&Game::updateCreatureWalk, &g_game, getID())));
	}

	if (creature != this) {
		return;
	}

	if (tradeState != TRADE_TRANSFER) {
		//check if we should close trade
		if (tradeItem && !Position::areInRange<1, 1, 0>(tradeItem->getPosition(), getPosition())) {
			g_game.internalCloseTrade(this);
		}

		if (tradePartner && !Position::areInRange<2, 2, 0>(tradePartner->getPosition(), getPosition())) {
			g_game.internalCloseTrade(this);
		}
	}

	// close modal windows
	if (!modalWindows.empty()) {
		// TODO: This shouldn't be hardcoded
		for (uint32_t modalWindowId : modalWindows) {
			if (modalWindowId == std::numeric_limits<uint32_t>::max()) {
				sendTextMessage(MESSAGE_EVENT_ADVANCE, "Offline training aborted.");
				break;
			}
		}
		modalWindows.clear();
	}

	// leave market
	if (inMarket) {
		inMarket = false;
	}

	if (party) {
		party->updateSharedExperience();
	}

	if (teleport || oldPos.z != newPos.z) {
		int32_t ticks = g_config.getNumber(ConfigManager::STAIRHOP_DELAY);
		if (ticks > 0) {
			if (Condition* condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_PACIFIED, ticks, 0)) {
				addCondition(condition);
			}
		}
	}
}

//container

void Player::setNextWalkActionTask(SchedulerTask* task)
{
	if (walkTaskEvent != 0) {
		g_scheduler.stopEvent(walkTaskEvent);
		walkTaskEvent = 0;
	}

	delete walkTask;
	walkTask = task;
}


void Player::setNextWalkTask(SchedulerTask* task)
{
	if (nextStepEvent != 0) {
		g_scheduler.stopEvent(nextStepEvent);
		nextStepEvent = 0;
	}

	if (task) {
		nextStepEvent = g_scheduler.addEvent(task);
		resetIdleTime();
	}
}


void Player::setNextActionTask(SchedulerTask* task)
{
	if (actionTaskEvent != 0) {
		g_scheduler.stopEvent(actionTaskEvent);
		actionTaskEvent = 0;
	}

	if (task) {
		actionTaskEvent = g_scheduler.addEvent(task);
		resetIdleTime();
	}
}

uint32_t Player::getNextActionTime() const
{
	return std::max<int64_t>(SCHEDULER_MINTICKS, nextAction - OTSYS_TIME());
}


bool Player::setFollowCreature(Creature* creature)
{
	if (!Creature::setFollowCreature(creature)) {
		setFollowCreature(nullptr);
		setAttackedCreature(nullptr);

		sendCancelMessage(RETURNVALUE_THEREISNOWAY);
		sendCancelTarget();
		stopWalk();
		return false;
	}
	return true;
}


bool Player::setAttackedCreature(Creature* creature)
{
	if (!Creature::setAttackedCreature(creature)) {
		sendCancelTarget();
		return false;
	}

	if (chaseMode == CHASEMODE_FOLLOW && creature) {
		if (followCreature != creature) {
			//chase opponent
			setFollowCreature(creature);
		}
	} else if (followCreature) {
		setFollowCreature(nullptr);
	}

	if (creature) {
		g_dispatcher.addTask(createTask(std::bind(&Game::checkCreatureAttack, &g_game, getID())));
	}
	return true;
}


void Player::goToFollowCreature()
{
	if (!walkTask) {
		if ((OTSYS_TIME() - lastFailedFollow) < 2000) {
			return;
		}

		Creature::goToFollowCreature();

		if (followCreature && !hasFollowPath) {
			lastFailedFollow = OTSYS_TIME();
		}
	}
}


void Player::getPathSearchParams(const Creature* creature, FindPathParams& fpp) const
{
	Creature::getPathSearchParams(creature, fpp);
	fpp.fullPathSearch = true;
}


void Player::doAttacking(uint32_t)
{
	if (lastAttack == 0) {
		lastAttack = OTSYS_TIME() - getAttackSpeed() - 1;
	}

	if (hasCondition(CONDITION_PACIFIED)) {
		return;
	}

	if ((OTSYS_TIME() - lastAttack) >= getAttackSpeed()) {
		bool result = false;

		Item* tool = getWeapon();
		const Weapon* weapon = g_weapons->getWeapon(tool);
		if (weapon) {
			if (!weapon->interruptSwing()) {
				result = weapon->useWeapon(this, tool, attackedCreature);
			} else if (!canDoAction()) {
				uint32_t delay = getNextActionTime();
				SchedulerTask* task = createSchedulerTask(delay, std::bind(&Game::checkCreatureAttack,
				                      &g_game, getID()));
				setNextActionTask(task);
			} else {
				result = weapon->useWeapon(this, tool, attackedCreature);
			}
		} else {
			result = Weapon::useFist(this, attackedCreature);
		}

		if (result) {
			lastAttack = OTSYS_TIME();
		}
	}
}

uint64_t Player::getGainedExperience(Creature* attacker) const
{
	if (g_config.getBoolean(ConfigManager::EXPERIENCE_FROM_PLAYERS)) {
		Player* attackerPlayer = attacker->getPlayer();
		if (attackerPlayer && attackerPlayer != this && skillLoss && std::abs(static_cast<int32_t>(attackerPlayer->getLevel() - level)) <= g_config.getNumber(ConfigManager::EXP_FROM_PLAYERS_LEVEL_RANGE)) {
			return std::max<uint64_t>(0, std::floor(getLostExperience() * getDamageRatio(attacker) * 0.75));
		}
	}
	return 0;
}


void Player::onFollowCreature(const Creature* creature)
{
	if (!creature) {
		stopWalk();
	}
}


void Player::setChaseMode(chaseMode_t mode)
{
	chaseMode_t prevChaseMode = chaseMode;
	chaseMode = mode;

	if (prevChaseMode != chaseMode) {
		if (chaseMode == CHASEMODE_FOLLOW) {
			if (!followCreature && attackedCreature) {
				//chase opponent
				setFollowCreature(attackedCreature);
			}
		} else if (attackedCreature) {
			setFollowCreature(nullptr);
			cancelNextWalk = true;
		}
	}
}


void Player::onWalkAborted()
{
	setNextWalkActionTask(nullptr);
	sendCancelWalk();
}


void Player::onWalkComplete()
{
	if (walkTask) {
		walkTaskEvent = g_scheduler.addEvent(walkTask);
		walkTask = nullptr;
	}
}


void Player::stopWalk()
{
	cancelNextWalk = true;
}


void Player::getCreatureLight(LightInfo& light) const
{
	if (internalLight.level > itemsLight.level) {
		light = internalLight;
	} else {
		light = itemsLight;
	}
}


void Player::updateItemsLight(bool internal /*=false*/)
{
	LightInfo maxLight;
	LightInfo curLight;

	for (int32_t i = CONST_SLOT_FIRST; i <= CONST_SLOT_LAST; ++i) {
		Item* item = inventory[i];
		if (item) {
			item->getLight(curLight);

			if (curLight.level > maxLight.level) {
				maxLight = curLight;
			}
		}
	}

	if (itemsLight.level != maxLight.level || itemsLight.color != maxLight.color) {
		itemsLight = maxLight;

		if (!internal) {
			g_game.changeLight(this);
		}
	}
}


