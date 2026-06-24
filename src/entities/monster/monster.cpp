// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../monster.hpp"

#include "../../config/configmanager.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../game/game.hpp"
#include "../../game/spells/spells.hpp"

extern Game g_game;
extern Monsters g_monsters;
extern ConfigManager g_config;

int32_t Monster::despawnRange;
int32_t Monster::despawnRadius;

uint32_t Monster::monsterAutoID = 0x40000000;

Monster* Monster::createMonster(const std::string& name, uint16_t lvl, uint16_t bst) //pota
{
	MonsterType* mType = g_monsters.getMonsterType(name);
	if (!mType) {
		return nullptr;
	}
	return new Monster(mType, lvl, bst);
}

Monster::Monster(MonsterType* mtype, uint16_t lvl, uint16_t bst) : //pota
	Creature(),
	strDescription(asLowerCaseString(mtype->nameDescription)),
	mType(mtype)
{
	if (lvl == 0) { //pota
		level = uniform_random(mType->info.minLevel, mType->info.maxLevel);
		health = mType->info.health + (mType->info.health * (g_config.getDouble(ConfigManager::MONSTERLEVEL_BONUSHEALTH) * level)); //pota
		healthMax = mType->info.healthMax + (mType->info.healthMax * (g_config.getDouble(ConfigManager::MONSTERLEVEL_BONUSHEALTH) * level)); //pota
		baseSpeed = mType->info.baseSpeed + (mType->info.baseSpeed * (g_config.getDouble(ConfigManager::MONSTERLEVEL_BONUSSPEED) * level)); //pota
		boost = 0;
	} else {
		health = mType->info.health;
		healthMax = mType->info.healthMax;
		baseSpeed = mType->info.baseSpeed;
		level = lvl;
		boost = bst;
	}
	defaultOutfit = mType->info.outfit;
	currentOutfit = mType->info.outfit;
	skull = mType->info.skull;
	internalLight = mType->info.light;
	hiddenHealth = mType->info.hiddenHealth;

	// register creature events
	for (const std::string& scriptName : mType->info.scripts) {
		if (!registerCreatureEvent(scriptName)) {
			std::cout << "[Warning - Monster::Monster] Unknown event name: " << scriptName << std::endl;
		}
	}
}

Monster::~Monster()
{
	clearTargetList();
	clearFriendList();
}

void Monster::addList()
{
	g_game.addMonster(this);
}

void Monster::removeList()
{
	g_game.removeMonster(this);
}

bool Monster::canSee(const Position& pos) const
{
	return Creature::canSee(getPosition(), pos, 9, 9);
}

void Monster::onAttackedCreatureDisappear(bool)
{
	attackTicks = 0;
	extraMeleeAttack = true;
}

