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

Item* Player::getInventoryItem(slots_t slot) const
{
	if (slot < CONST_SLOT_FIRST || slot > CONST_SLOT_LAST) {
		return nullptr;
	}
	return inventory[slot];
}


void Player::addConditionSuppressions(uint32_t conditions)
{
	conditionSuppressions |= conditions;
}


void Player::removeConditionSuppressions(uint32_t conditions)
{
	conditionSuppressions &= ~conditions;
}


Item* Player::getWeapon(slots_t slot, bool ignoreAmmo) const
{
	Item* item = inventory[slot];
	if (!item) {
		return nullptr;
	}

	WeaponType_t weaponType = item->getWeaponType();
	if (weaponType == WEAPON_NONE || weaponType == WEAPON_SHIELD || weaponType == WEAPON_AMMO) {
		return nullptr;
	}

	if (!ignoreAmmo && weaponType == WEAPON_DISTANCE) {
		const ItemType& it = Item::items[item->getID()];
		if (it.ammoType != AMMO_NONE) {
			Item* ammoItem = inventory[CONST_SLOT_AMMO];
			if (!ammoItem || ammoItem->getAmmoType() != it.ammoType) {
				return nullptr;
			}
			item = ammoItem;
		}
	}
	return item;
}


Item* Player::getWeapon(bool ignoreAmmo/* = false*/) const
{
	Item* item = getWeapon(CONST_SLOT_LEFT, ignoreAmmo);
	if (item) {
		return item;
	}

	item = getWeapon(CONST_SLOT_RIGHT, ignoreAmmo);
	if (item) {
		return item;
	}
	return nullptr;
}


WeaponType_t Player::getWeaponType() const
{
	Item* item = getWeapon();
	if (!item) {
		return WEAPON_NONE;
	}
	return item->getWeaponType();
}

int32_t Player::getWeaponSkill(const Item* item) const
{
	if (!item) {
		return getSkillLevel(SKILL_FIST);
	}

	int32_t attackSkill;

	WeaponType_t weaponType = item->getWeaponType();
	switch (weaponType) {
		case WEAPON_SWORD: {
			attackSkill = getSkillLevel(SKILL_SWORD);
			break;
		}

		case WEAPON_CLUB: {
			attackSkill = getSkillLevel(SKILL_CLUB);
			break;
		}

		case WEAPON_AXE: {
			attackSkill = getSkillLevel(SKILL_AXE);
			break;
		}

		case WEAPON_DISTANCE: {
			attackSkill = getSkillLevel(SKILL_DISTANCE);
			break;
		}

		default: {
			attackSkill = 0;
			break;
		}
	}
	return attackSkill;
}

int32_t Player::getArmor() const
{
	int32_t armor = 0;

	static const slots_t armorSlots[] = {CONST_SLOT_HEAD, CONST_SLOT_NECKLACE, CONST_SLOT_ARMOR, CONST_SLOT_LEGS, CONST_SLOT_FEET, CONST_SLOT_RING};
	for (slots_t slot : armorSlots) {
		Item* inventoryItem = inventory[slot];
		if (inventoryItem) {
			armor += inventoryItem->getArmor();
		}
	}
	return static_cast<int32_t>(armor * vocation->armorMultiplier);
}


void Player::getShieldAndWeapon(const Item*& shield, const Item*& weapon) const
{
	shield = nullptr;
	weapon = nullptr;

	for (uint32_t slot = CONST_SLOT_RIGHT; slot <= CONST_SLOT_LEFT; slot++) {
		Item* item = inventory[slot];
		if (!item) {
			continue;
		}

		switch (item->getWeaponType()) {
			case WEAPON_NONE:
				break;

			case WEAPON_SHIELD: {
				if (!shield || item->getDefense() > shield->getDefense()) {
					shield = item;
				}
				break;
			}

			default: { // weapons that are not shields
				weapon = item;
				break;
			}
		}
	}
}

int32_t Player::getDefense() const
{
	int32_t baseDefense = 5;
	int32_t defenseValue = 0;
	int32_t defenseSkill = 0;
	int32_t extraDefense = 0;
	float defenseFactor = getDefenseFactor();
	const Item* weapon;
	const Item* shield;
	getShieldAndWeapon(shield, weapon);

	if (weapon) {
		defenseValue = baseDefense + weapon->getDefense();
		extraDefense = weapon->getExtraDefense();
		defenseSkill = getWeaponSkill(weapon);
	}

	if (shield && shield->getDefense() >= defenseValue) {
		defenseValue = baseDefense + shield->getDefense() + extraDefense;
		defenseSkill = getSkillLevel(SKILL_SHIELD);
	}

	if (defenseSkill == 0) {
		return 0;
	}

	defenseValue = static_cast<int32_t>(defenseValue * vocation->defenseMultiplier);
	return static_cast<int32_t>(std::ceil((static_cast<float>(defenseSkill * (defenseValue * 0.015)) + (defenseValue * 0.1)) * defenseFactor));
}


float Player::getAttackFactor() const
{
	switch (fightMode) {
		case FIGHTMODE_ATTACK: return 1.0f;
		case FIGHTMODE_BALANCED: return 1.2f;
		case FIGHTMODE_DEFENSE: return 2.0f;
		default: return 1.0f;
	}
}


float Player::getDefenseFactor() const
{
	switch (fightMode) {
		case FIGHTMODE_ATTACK: return 1.0f;
		case FIGHTMODE_BALANCED: return 1.2f;
		case FIGHTMODE_DEFENSE: {
			if ((OTSYS_TIME() - lastAttack) < getAttackSpeed()) {
				return 1.0f;
			}

			return 2.0f;
		}
		default: return 1.0f;
	}
}

uint16_t Player::getClientIcons() const
{
	uint16_t icons = 0;
	for (Condition* condition : conditions) {
		if (!isSuppress(condition->getType())) {
			icons |= condition->getIcons();
		}
	}

	if (pzLocked) {
		icons |= ICON_REDSWORDS;
	}

	if (tile->hasFlag(TILESTATE_PROTECTIONZONE)) {
		icons |= ICON_PIGEON;

		// Don't show ICON_SWORDS if player is in protection zone.
		if (hasBitSet(ICON_SWORDS, icons)) {
			icons &= ~ICON_SWORDS;
		}
	}

	// Game client debugs with 10 or more icons
	// so let's prevent that from happening.
	std::bitset<20> icon_bitset(static_cast<uint64_t>(icons));
	for (size_t pos = 0, bits_set = icon_bitset.count(); bits_set >= 10; ++pos) {
		if (icon_bitset[pos]) {
			icon_bitset.reset(pos);
			--bits_set;
		}
	}
	return icon_bitset.to_ulong();
}


void Player::updateInventoryWeight()
{
	if (hasFlag(PlayerFlag_HasInfiniteCapacity)) {
		return;
	}

	inventoryWeight = 0;
	for (int i = CONST_SLOT_FIRST; i <= CONST_SLOT_LAST; ++i) {
		const Item* item = inventory[i];
		if (item) {
			inventoryWeight += item->getWeight();
		}
	}
}

int32_t Player::getPlayerInfo(playerinfo_t playerinfo) const
{
	switch (playerinfo) {
		case PLAYERINFO_LEVELPERCENT: return levelPercent;
		case PLAYERINFO_MAGICLEVEL: return std::max<int32_t>(0, magLevel + varStats[STAT_MAGICPOINTS]);
		case PLAYERINFO_MAGICLEVELPERCENT: return magLevelPercent;
		case PLAYERINFO_HEALTH: return health;
		case PLAYERINFO_MAXHEALTH: return std::max<int32_t>(1, healthMax + varStats[STAT_MAXHITPOINTS]);
		case PLAYERINFO_MANA: return mana;
		case PLAYERINFO_MAXMANA: return std::max<int32_t>(0, manaMax + varStats[STAT_MAXMANAPOINTS]);
		default: return 0;
	}
}


void Player::addSkillAdvance(skills_t skill, uint64_t count)
{
	uint64_t currReqTries = vocation->getReqSkillTries(skill, skills[skill].level);
	uint64_t nextReqTries = vocation->getReqSkillTries(skill, skills[skill].level + 1);
	if (currReqTries >= nextReqTries) {
		//player has reached max skill
		return;
	}

	g_events->eventPlayerOnGainSkillTries(this, skill, count);
	if (count == 0) {
		return;
	}

	bool sendUpdateSkills = false;
	while ((skills[skill].tries + count) >= nextReqTries) {
		count -= nextReqTries - skills[skill].tries;
		skills[skill].level++;
		skills[skill].tries = 0;
		skills[skill].percent = 0;

		std::ostringstream ss;
		ss << "You advanced to " << getSkillName(skill) << " level " << skills[skill].level << '.';
		sendTextMessage(MESSAGE_EVENT_ADVANCE, ss.str());

		g_creatureEvents->playerAdvance(this, skill, (skills[skill].level - 1), skills[skill].level);

		sendUpdateSkills = true;
		currReqTries = nextReqTries;
		nextReqTries = vocation->getReqSkillTries(skill, skills[skill].level + 1);
		if (currReqTries >= nextReqTries) {
			count = 0;
			break;
		}
	}

	skills[skill].tries += count;

	uint32_t newPercent;
	if (nextReqTries > currReqTries) {
		newPercent = Player::getPercentLevel(skills[skill].tries, nextReqTries);
	} else {
		newPercent = 0;
	}

	if (skills[skill].percent != newPercent) {
		skills[skill].percent = newPercent;
		sendUpdateSkills = true;
	}

	if (sendUpdateSkills) {
		sendSkills();
	}
}


void Player::setVarStats(stats_t stat, int32_t modifier)
{
	varStats[stat] += modifier;

	switch (stat) {
		case STAT_MAXHITPOINTS: {
			if (getHealth() > getMaxHealth()) {
				Creature::changeHealth(getMaxHealth() - getHealth());
			} else {
				g_game.addCreatureHealth(this);
			}
			break;
		}

		case STAT_MAXMANAPOINTS: {
			if (getMana() > getMaxMana()) {
				Creature::changeMana(getMaxMana() - getMana());
			}
			break;
		}

		default: {
			break;
		}
	}
}

int32_t Player::getDefaultStats(stats_t stat) const
{
	switch (stat) {
		case STAT_MAXHITPOINTS: return healthMax;
		case STAT_MAXMANAPOINTS: return manaMax;
		case STAT_MAGICPOINTS: return getBaseMagicLevel();
		default: return 0;
	}
}


