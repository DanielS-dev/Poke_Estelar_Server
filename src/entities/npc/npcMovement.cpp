// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../npc.hpp"

#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern LuaEnvironment g_luaEnvironment;

bool Npc::getNextStep(Direction& dir, uint32_t& flags)
{
	if (Creature::getNextStep(dir, flags)) {
		return true;
	}

	if (walkTicks <= 0) {
		return false;
	}

	if (focusCreature != 0) {
		return false;
	}

	if (getTimeSinceLastMove() < walkTicks) {
		return false;
	}

	return getRandomStep(dir);
}

bool Npc::canWalkTo(const Position& fromPos, Direction dir) const
{
	if (masterRadius == 0) {
		return false;
	}

	Position toPos = getNextPosition(dir, fromPos);
	if (!Spawns::isInZone(masterPos, masterRadius, toPos)) {
		return false;
	}

	Tile* tile = g_game.map.getTile(toPos);
	if (!tile || tile->queryAdd(0, *this, 1, 0) != RETURNVALUE_NOERROR) {
		return false;
	}

	if (!floorChange && (tile->hasFlag(TILESTATE_FLOORCHANGE) || tile->getTeleportItem())) {
		return false;
	}

	if (!ignoreHeight && tile->hasHeight(1)) {
		return false;
	}

	return true;
}

bool Npc::getRandomStep(Direction& dir) const
{
	std::vector<Direction> dirList;
	const Position& creaturePos = getPosition();

	if (canWalkTo(creaturePos, DIRECTION_NORTH)) {
		dirList.push_back(DIRECTION_NORTH);
	}

	if (canWalkTo(creaturePos, DIRECTION_SOUTH)) {
		dirList.push_back(DIRECTION_SOUTH);
	}

	if (canWalkTo(creaturePos, DIRECTION_EAST)) {
		dirList.push_back(DIRECTION_EAST);
	}

	if (canWalkTo(creaturePos, DIRECTION_WEST)) {
		dirList.push_back(DIRECTION_WEST);
	}

	if (dirList.empty()) {
		return false;
	}

	dir = dirList[uniform_random(0, dirList.size() - 1)];
	return true;
}

void Npc::doMoveTo(const Position& target)
{
	std::forward_list<Direction> listDir;
	if (getPathTo(target, listDir, 1, 1, true, true)) {
		startAutoWalk(listDir);
	}
}

void Npc::turnToCreature(Creature* creature)
{
	const Position& creaturePos = creature->getPosition();
	const Position& myPos = getPosition();
	const auto dx = Position::getOffsetX(myPos, creaturePos);
	const auto dy = Position::getOffsetY(myPos, creaturePos);

	float tan;
	if (dx != 0) {
		tan = static_cast<float>(dy) / dx;
	} else {
		tan = 10;
	}

	Direction dir;
	if (std::abs(tan) < 1) {
		if (dx > 0) {
			dir = DIRECTION_WEST;
		} else {
			dir = DIRECTION_EAST;
		}
	} else {
		if (dy > 0) {
			dir = DIRECTION_NORTH;
		} else {
			dir = DIRECTION_SOUTH;
		}
	}
	g_game.internalCreatureTurn(this, dir);
}

void Npc::setCreatureFocus(Creature* creature)
{
	if (creature) {
		focusCreature = creature->getID();
		turnToCreature(creature);
	} else {
		focusCreature = 0;
	}
}

