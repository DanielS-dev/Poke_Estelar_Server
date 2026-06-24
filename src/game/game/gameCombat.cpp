// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../../core/pugicast.hpp"

#include "../../items/items.hpp"
#include "../commands/commands.hpp"
#include "../../entities/creature.hpp"
#include "../../entities/monster.hpp"
#include "../game.hpp"
#include "../../scripting/actions/actions.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../../persistence/market/iomarket.hpp"
#include "../../scripting/talkaction.hpp"
#include "../spells/spells.hpp"
#include "../../config/configmanager.hpp"
#include "../../app/services.hpp"
#include "../../scripting/globalevent.hpp"
#include "../../world/bed.hpp"
#include "../../core/scheduler.hpp"
#include "../../scripting/events/events.hpp"
#include "../../persistence/databasetasks.hpp"
#include "../../core/tools/auths.hpp"
#include "../../core/tools/dateTools.hpp"
#include "../../core/tools/fluidTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/xmlErro.hpp"

extern ConfigManager g_config;
extern Actions* g_actions;
extern Chat* g_chat;
extern TalkActions* g_talkActions;
extern Spells* g_spells;
extern Vocations g_vocations;
extern GlobalEvents* g_globalEvents;
extern Events* g_events;

bool Game::combatBlockHit(CombatDamage& damage, Creature* attacker, Creature* target, bool checkDefense, bool checkArmor, bool field)
{
	if (damage.primary.type == COMBAT_NONE && damage.secondary.type == COMBAT_NONE) {
		return true;
	}

	if (target->getPlayer() && target->isInGhostMode()) {
		return true;
	}

	if (damage.primary.value > 0) {
		return false;
	}

	static const auto sendBlockEffect = [this](BlockType_t blockType, CombatType_t combatType, const Position& targetPos) {
		if (blockType == BLOCK_DEFENSE) {
			addMagicEffect(targetPos, CONST_ME_POFF);
		} else if (blockType == BLOCK_ARMOR) {
			addMagicEffect(targetPos, CONST_ME_BLOCKHIT);
		} else if (blockType == BLOCK_IMMUNITY) {
			uint8_t hitEffect = 0;
			switch (combatType) {
				case COMBAT_UNDEFINEDDAMAGE: {
					return;
				}
				case COMBAT_ENERGYDAMAGE:
				case COMBAT_FIREDAMAGE:
				case COMBAT_PHYSICALDAMAGE:
				case COMBAT_ICEDAMAGE:
				case COMBAT_DEATHDAMAGE: {
					hitEffect = CONST_ME_BLOCKHIT;
					break;
				}
				case COMBAT_EARTHDAMAGE: {
					hitEffect = CONST_ME_GREEN_RINGS;
					break;
				}
				case COMBAT_HOLYDAMAGE: {
					hitEffect = CONST_ME_HOLYDAMAGE;
					break;
				}
				default: {
					hitEffect = CONST_ME_POFF;
					break;
				}
			}
			addMagicEffect(targetPos, hitEffect);
		}
	};

	BlockType_t primaryBlockType, secondaryBlockType;
	if (damage.primary.type != COMBAT_NONE) {
		damage.primary.value = -damage.primary.value;
		primaryBlockType = target->blockHit(attacker, damage.primary.type, damage.primary.value, checkDefense, checkArmor, field);

		damage.primary.value = -damage.primary.value;
		sendBlockEffect(primaryBlockType, damage.primary.type, target->getPosition());
	} else {
		primaryBlockType = BLOCK_NONE;
	}

	if (damage.secondary.type != COMBAT_NONE) {
		damage.secondary.value = -damage.secondary.value;
		secondaryBlockType = target->blockHit(attacker, damage.secondary.type, damage.secondary.value, false, false, field);

		damage.secondary.value = -damage.secondary.value;
		sendBlockEffect(secondaryBlockType, damage.secondary.type, target->getPosition());
	} else {
		secondaryBlockType = BLOCK_NONE;
	}
	return (primaryBlockType != BLOCK_NONE) && (secondaryBlockType != BLOCK_NONE);
}


void Game::combatGetTypeInfo(CombatType_t combatType, Creature* target, TextColor_t& color, uint8_t& effect)
{
	switch (combatType) {
		case COMBAT_PHYSICALDAMAGE: {
			Item* splash = nullptr;
			switch (target->getRace()) {
				case RACE_VENOM:
					color = TEXT_COLORPOISON;
					effect = CONST_ME_HITBYPOISON;
					splash = Item::CreateItem(ITEM_SMALLSPLASH, FLUID_GREEN);
					break;
				case RACE_BLOOD:
					color = TEXTCOLOR_RED;
					effect = CONST_ME_DRAWBLOOD;
					splash = Item::CreateItem(ITEM_SMALLSPLASH, FLUID_BLOOD);
					break;
				case RACE_UNDEAD:
					color = TEXTCOLOR_LIGHTGREY;
					effect = CONST_ME_HITAREA;
					break;
				case RACE_FIRE:
					color = TEXTCOLOR_ORANGE;
					effect = CONST_ME_DRAWBLOOD;
					break;
				case RACE_ENERGY:
					color = TEXTCOLOR_PURPLE;
					effect = CONST_ME_ENERGYHIT;
					break;
				default:
					color = TEXTCOLOR_WHITE;
					effect = 100;
					break;
			}

			if (splash) {
				internalAddItem(target->getTile(), splash, INDEX_WHEREEVER, FLAG_NOLIMIT);
				startDecay(splash);
			}

			break;
		}

		case COMBAT_ENERGYDAMAGE: {
			color = TEXTCOLOR_PURPLE;
			effect = CONST_ME_ENERGYHIT;
			break;
		}

		case COMBAT_EARTHDAMAGE: {
			color = TEXT_COLORPOISON;
			effect = CONST_ME_GREEN_RINGS;
			break;
		}

		case COMBAT_DROWNDAMAGE: {
			color = TEXTCOLOR_LIGHTBLUE;
			effect = CONST_ME_LOSEENERGY;
			break;
		}
		case COMBAT_FIREDAMAGE: {
			color = TEXTCOLOR_RED;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_ICEDAMAGE: {
			color = TEXT_COLORICE;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_HOLYDAMAGE: {
			color = TEXTCOLOR_YELLOW;
			effect = CONST_ME_HOLYDAMAGE;
			break;
		}
		case COMBAT_DEATHDAMAGE: {
			color = TEXTCOLOR_DARKRED;
			effect = CONST_ME_SMALLCLOUDS;
			break;
		}
		case COMBAT_PSYCHICDAMAGE: { //pota
			color = TEXTCOLOR_MEDIUMORCHID;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_GRASSDAMAGE: { //pota
			color = TEXT_COLORGRASS;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_NORMALDAMAGE: { //pota
			color = TEXTCOLOR_WHITE;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_WATERDAMAGE: { //pota
			color = TEXTCOLOR_LIGHTAQUA;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_FLYINGDAMAGE: { //pota
			color = TEXT_COLORFLYING;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_POISONDAMAGE: { //pota
			color = TEXT_COLORPOISON;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_ELECTRICDAMAGE: { //pota
			color = TEXT_COLORELECTRIC;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_GROUNDDAMAGE: { //pota
			color = TEXT_COLORGROUND;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_ROCKDAMAGE: { //pota
			color = TEXT_COLORROCK;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_BUGDAMAGE: { //pota
			color = TEXT_COLORBUG;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_DRAGONDAMAGE: { //pota
			color = TEXT_COLORDRAGON;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_GHOSTDAMAGE: { //pota
			color = TEXT_COLORGHOST;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_DARKDAMAGE: { //pota
			color = TEXT_COLORDARK;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_STEELDAMAGE: { //pota
			color = TEXT_COLORSTEEL;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_FAIRYDAMAGE: { //pota
			color = TEXT_COLORFAIRY;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_FIGHTINGDAMAGE: { //pota
			color = TEXT_COLORFIGHTING;
			effect = CONST_ME_NONE;
			break;
		}
		case COMBAT_LIFEDRAIN: {
			color = TEXTCOLOR_RED;
			effect = CONST_ME_MAGIC_RED;
			break;
		}
		default: {
			color = TEXTCOLOR_PURPLE;
			effect = CONST_ME_NONE;
			break;
		}
	}
}


bool Game::combatChangeHealth(Creature* attacker, Creature* target, CombatDamage& damage)
{
	const Position& targetPos = target->getPosition();
	if (damage.primary.value > 0) {
		if (target->getHealth() <= 0) {
			return false;
		}

		Player* attackerPlayer;
		if (attacker) {
			attackerPlayer = attacker->getPlayer();
		} else {
			attackerPlayer = nullptr;
		}

		Player* targetPlayer = target->getPlayer();
		if (attackerPlayer && targetPlayer && attackerPlayer->getSkull() == SKULL_BLACK && attackerPlayer->getSkullClient(targetPlayer) == SKULL_NONE) {
			return false;
		}

		if (damage.origin != ORIGIN_NONE) {
			const auto& events = target->getCreatureEvents(CREATURE_EVENT_HEALTHCHANGE);
			if (!events.empty()) {
				for (CreatureEvent* creatureEvent : events) {
					creatureEvent->executeHealthChange(target, attacker, damage);
				}
				damage.origin = ORIGIN_NONE;
				return combatChangeHealth(attacker, target, damage);
			}
		}

		int32_t realHealthChange = target->getHealth();
		target->gainHealth(attacker, damage.primary.value);
		realHealthChange = target->getHealth() - realHealthChange;

		if (realHealthChange > 0 && !target->isInGhostMode()) {
			std::string damageString = std::to_string(realHealthChange) + (realHealthChange != 1 ? " hitpoints." : " hitpoint.");

			std::string spectatorMessage;
			if (!attacker) {
				spectatorMessage += ucfirst(target->getNameDescription());
				spectatorMessage += " was healed for " + damageString;
			} else {
				spectatorMessage += ucfirst(attacker->getNameDescription());
				spectatorMessage += " healed ";
				if (attacker == target) {
					spectatorMessage += (targetPlayer ? (targetPlayer->getSex() == PLAYERSEX_FEMALE ? "herself" : "himself") : "itself");
				} else {
					spectatorMessage += target->getNameDescription();
				}
				spectatorMessage += " for " + damageString;
			}

			TextMessage message;
			message.position = targetPos;
			message.primary.value = realHealthChange;
			message.primary.color = TEXTCOLOR_MAYABLUE;

			SpectatorVec list;
			map.getSpectators(list, targetPos, false, true);
			for (Creature* spectator : list) {
				Player* tmpPlayer = spectator->getPlayer();
				if (tmpPlayer == attackerPlayer && attackerPlayer != targetPlayer) {
					message.type = MESSAGE_HEALED;
					message.text = "You heal " + target->getNameDescription() + " for " + damageString;
				} else if (tmpPlayer == targetPlayer) {
					message.type = MESSAGE_HEALED;
					if (!attacker) {
						message.text = "You were healed for " + damageString;
					} else if (targetPlayer == attackerPlayer) {
						message.text = "You heal yourself for " + damageString;
					} else {
						message.text = "You were healed by " + attacker->getNameDescription() + " for " + damageString;
					}
				} else {
					message.type = MESSAGE_HEALED_OTHERS;
					message.text = spectatorMessage;
				}
				tmpPlayer->sendTextMessage(message);
			}
		}
	} else {
		if (!target->isAttackable()) {
			if (!target->isInGhostMode()) {
				addMagicEffect(targetPos, CONST_ME_POFF);
			}
			return true;
		}

		Player* attackerPlayer;
		if (attacker) {
			attackerPlayer = attacker->getPlayer();
		} else {
			attackerPlayer = nullptr;
		}

		Player* targetPlayer = target->getPlayer();
		if (attackerPlayer && targetPlayer && attackerPlayer->getSkull() == SKULL_BLACK && attackerPlayer->getSkullClient(targetPlayer) == SKULL_NONE) {
			return false;
		}

		damage.primary.value = std::abs(damage.primary.value);
		damage.secondary.value = std::abs(damage.secondary.value);

		int32_t healthChange = damage.primary.value + damage.secondary.value;
		if (healthChange == 0) {
			return true;
		}

		TextMessage message;
		message.position = targetPos;

		SpectatorVec list;
		if (target->hasCondition(CONDITION_MANASHIELD) && damage.primary.type != COMBAT_UNDEFINEDDAMAGE) {
			int32_t manaDamage = std::min<int32_t>(target->getMana(), healthChange);
			if (manaDamage != 0) {
				if (damage.origin != ORIGIN_NONE) {
					const auto& events = target->getCreatureEvents(CREATURE_EVENT_MANACHANGE);
					if (!events.empty()) {
						for (CreatureEvent* creatureEvent : events) {
							creatureEvent->executeManaChange(target, attacker, healthChange, damage.origin);
						}
						if (healthChange == 0) {
							return true;
						}
						manaDamage = std::min<int32_t>(target->getMana(), healthChange);
					}
				}

				target->drainMana(attacker, manaDamage);
				map.getSpectators(list, targetPos, true, true);
				addMagicEffect(list, targetPos, CONST_ME_LOSEENERGY);

				std::string damageString = std::to_string(manaDamage);
				std::string spectatorMessage = ucfirst(target->getNameDescription()) + " loses " + damageString + " mana";
				if (attacker) {
					spectatorMessage += " due to ";
					if (attacker == target) {
						spectatorMessage += (targetPlayer ? (targetPlayer->getSex() == PLAYERSEX_FEMALE ? "her own attack" : "his own attack") : "its own attack");
					} else {
						spectatorMessage += "an attack by " + attacker->getNameDescription();
					}
				}
				spectatorMessage += '.';

				message.primary.value = manaDamage;
				message.primary.color = TEXTCOLOR_BLUE;

				for (Creature* spectator : list) {
					Player* tmpPlayer = spectator->getPlayer();
					if (tmpPlayer->getPosition().z != targetPos.z) {
						continue;
					}

					if (tmpPlayer == attackerPlayer && attackerPlayer != targetPlayer) {
						message.type = MESSAGE_DAMAGE_DEALT;
						message.text = ucfirst(target->getNameDescription()) + " loses " + damageString + " mana due to your attack.";
					} else if (tmpPlayer == targetPlayer) {
						message.type = MESSAGE_DAMAGE_RECEIVED;
						if (!attacker) {
							message.text = "You lose " + damageString + " mana.";
						} else if (targetPlayer == attackerPlayer) {
							message.text = "You lose " + damageString + " mana due to your own attack.";
						} else {
							message.text = "You lose " + damageString + " mana due to an attack by " + attacker->getNameDescription() + '.';
						}
					} else {
						message.type = MESSAGE_DAMAGE_OTHERS;
						message.text = spectatorMessage;
					}
					tmpPlayer->sendTextMessage(message);
				}

				damage.primary.value -= manaDamage;
				if (damage.primary.value < 0) {
					damage.secondary.value = std::max<int32_t>(0, damage.secondary.value + damage.primary.value);
					damage.primary.value = 0;
				}
			}
		}

		int32_t realDamage = damage.primary.value + damage.secondary.value;
		if (realDamage == 0) {
			return true;
		}

		if (damage.origin != ORIGIN_NONE) {
			const auto& events = target->getCreatureEvents(CREATURE_EVENT_HEALTHCHANGE);
			if (!events.empty()) {
				for (CreatureEvent* creatureEvent : events) {
					creatureEvent->executeHealthChange(target, attacker, damage);
				}
				damage.origin = ORIGIN_NONE;
				return combatChangeHealth(attacker, target, damage);
			}
		}

		int32_t targetHealth = target->getHealth();
		if (damage.primary.value >= targetHealth) {
			damage.primary.value = targetHealth;
			damage.secondary.value = 0;
		} else if (damage.secondary.value) {
			damage.secondary.value = std::min<int32_t>(damage.secondary.value, targetHealth - damage.primary.value);
		}

		realDamage = damage.primary.value + damage.secondary.value;
		if (realDamage == 0) {
			return true;
		} else if (realDamage >= targetHealth) {
			for (CreatureEvent* creatureEvent : target->getCreatureEvents(CREATURE_EVENT_PREPAREDEATH)) {
				if (!creatureEvent->executeOnPrepareDeath(target, attacker)) {
					return false;
				}
			}
		}

		target->drainHealth(attacker, realDamage);
		if (list.empty()) {
			map.getSpectators(list, targetPos, true, true);
		}
		addCreatureHealth(list, target);

		message.primary.value = damage.primary.value;
		message.secondary.value = damage.secondary.value;

		uint8_t hitEffect;
		if (message.primary.value) {
			combatGetTypeInfo(damage.primary.type, target, message.primary.color, hitEffect);
			if (hitEffect != CONST_ME_NONE) {
				addMagicEffect(list, targetPos, hitEffect);
			}
		}

		if (message.secondary.value) {
			combatGetTypeInfo(damage.secondary.type, target, message.secondary.color, hitEffect);
			if (hitEffect != CONST_ME_NONE) {
				addMagicEffect(list, targetPos, hitEffect);
			}
		}

		if (message.primary.color != TEXTCOLOR_NONE || message.secondary.color != TEXTCOLOR_NONE) {
			std::string damageString = std::to_string(realDamage) + (realDamage != 1 ? " hitpoints" : " hitpoint");
			std::string spectatorMessage = ucfirst(target->getNameDescription()) + " loses " + damageString;
			if (attacker) {
				spectatorMessage += " due to ";
				if (attacker == target) {
					spectatorMessage += (targetPlayer ? (targetPlayer->getSex() == PLAYERSEX_FEMALE ? "her own attack" : "his own attack") : "its own attack");
				} else {
					spectatorMessage += "an attack by " + attacker->getNameDescription();
				}
			}
			spectatorMessage += '.';

			for (Creature* spectator : list) {
				Player* tmpPlayer = spectator->getPlayer();
				if (tmpPlayer->getPosition().z != targetPos.z) {
					continue;
				}

				if (tmpPlayer == attackerPlayer && attackerPlayer != targetPlayer) {
					message.type = MESSAGE_DAMAGE_DEALT;
					message.text = ucfirst(target->getNameDescription()) + " loses " + damageString + " due to your attack.";
				} else if (tmpPlayer == targetPlayer) {
					message.type = MESSAGE_DAMAGE_RECEIVED;
					if (!attacker) {
						message.text = "You lose " + damageString + '.';
					} else if (targetPlayer == attackerPlayer) {
						message.text = "You lose " + damageString + " due to your own attack.";
					} else {
						message.text = "You lose " + damageString + " due to an attack by " + attacker->getNameDescription() + '.';
					}
				} else {
					message.type = MESSAGE_DAMAGE_OTHERS;
					// TODO: Avoid copying spectatorMessage everytime we send to a spectator
					message.text = spectatorMessage;
				}
				tmpPlayer->sendTextMessage(message);
			}
		}
	}

	return true;
}


bool Game::combatChangeMana(Creature* attacker, Creature* target, int32_t manaChange, CombatOrigin origin)
{
	if (manaChange > 0) {
		if (attacker) {
			const Player* attackerPlayer = attacker->getPlayer();
			if (attackerPlayer && attackerPlayer->getSkull() == SKULL_BLACK && target->getPlayer() && attackerPlayer->getSkullClient(target) == SKULL_NONE) {
				return false;
			}
		}

		if (origin != ORIGIN_NONE) {
			const auto& events = target->getCreatureEvents(CREATURE_EVENT_MANACHANGE);
			if (!events.empty()) {
				for (CreatureEvent* creatureEvent : events) {
					creatureEvent->executeManaChange(target, attacker, manaChange, origin);
				}
				return combatChangeMana(attacker, target, manaChange, ORIGIN_NONE);
			}
		}

		target->changeMana(manaChange);
	} else {
		const Position& targetPos = target->getPosition();
		if (!target->isAttackable()) {
			if (!target->isInGhostMode()) {
				addMagicEffect(targetPos, CONST_ME_POFF);
			}
			return false;
		}

		Player* attackerPlayer;
		if (attacker) {
			attackerPlayer = attacker->getPlayer();
		} else {
			attackerPlayer = nullptr;
		}

		Player* targetPlayer = target->getPlayer();
		if (attackerPlayer && targetPlayer && attackerPlayer->getSkull() == SKULL_BLACK && attackerPlayer->getSkullClient(targetPlayer) == SKULL_NONE) {
			return false;
		}

		int32_t manaLoss = std::min<int32_t>(target->getMana(), -manaChange);
		BlockType_t blockType = target->blockHit(attacker, COMBAT_MANADRAIN, manaLoss);
		if (blockType != BLOCK_NONE) {
			addMagicEffect(targetPos, CONST_ME_POFF);
			return false;
		}

		if (manaLoss <= 0) {
			return true;
		}

		if (origin != ORIGIN_NONE) {
			const auto& events = target->getCreatureEvents(CREATURE_EVENT_MANACHANGE);
			if (!events.empty()) {
				for (CreatureEvent* creatureEvent : events) {
					creatureEvent->executeManaChange(target, attacker, manaChange, origin);
				}
				return combatChangeMana(attacker, target, manaChange, ORIGIN_NONE);
			}
		}

		target->drainMana(attacker, manaLoss);

		std::string damageString = std::to_string(manaLoss);
		std::string spectatorMessage = ucfirst(target->getNameDescription()) + " loses " + damageString + " mana";
		if (attacker) {
			spectatorMessage += " due to ";
			if (attacker == target) {
				spectatorMessage += (targetPlayer ? (targetPlayer->getSex() == PLAYERSEX_FEMALE ? "her own attack" : "his own attack") : "its own attack");
			} else {
				spectatorMessage += "an attack by " + attacker->getNameDescription();
			}
		}
		spectatorMessage += '.';

		TextMessage message;
		message.position = targetPos;
		message.primary.value = manaLoss;
		message.primary.color = TEXTCOLOR_BLUE;

		SpectatorVec list;
		map.getSpectators(list, targetPos, false, true);
		for (Creature* spectator : list) {
			Player* tmpPlayer = spectator->getPlayer();
			if (tmpPlayer == attackerPlayer && attackerPlayer != targetPlayer) {
				message.type = MESSAGE_DAMAGE_DEALT;
				message.text = ucfirst(target->getNameDescription()) + " loses " + damageString + " mana due to your attack.";
			} else if (tmpPlayer == targetPlayer) {
				message.type = MESSAGE_DAMAGE_RECEIVED;
				if (!attacker) {
					message.text = "You lose " + damageString + " mana.";
				} else if (targetPlayer == attackerPlayer) {
					message.text = "You lose " + damageString + " mana due to your own attack.";
				} else {
					message.text = "You lose " + damageString + " mana due to an attack by " + attacker->getNameDescription() + '.';
				}
			} else {
				message.type = MESSAGE_DAMAGE_OTHERS;
				message.text = spectatorMessage;
			}
			tmpPlayer->sendTextMessage(message);
		}
	}

	return true;
}


