// This file is part of The Forgotten Server.

// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <sstream>

#include "../game.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../entities/monster.hpp"
#include "../../entities/monsters.hpp"

#include "instantSpell.hpp"
#include "spells.hpp"

extern Game g_game;
extern Monsters g_monsters;

House* InstantSpell::getHouseFromPos(Creature* creature)
{
	if (!creature) {
		return nullptr;
	}

	Player* player = creature->getPlayer();
	if (!player) {
		return nullptr;
	}

	HouseTile* houseTile = dynamic_cast<HouseTile*>(player->getTile());
	if (!houseTile) {
		return nullptr;
	}

	House* house = houseTile->getHouse();
	if (!house) {
		return nullptr;
	}

	return house;
}

bool InstantSpell::HouseGuestList(const InstantSpell*, Creature* creature, const std::string&)
{
	House* house = getHouseFromPos(creature);
	if (!house) {
		return false;
	}

	Player* player = creature->getPlayer();
	if (house->canEditAccessList(GUEST_LIST, player)) {
		player->setEditHouse(house, GUEST_LIST);
		player->sendHouseWindow(house, GUEST_LIST);
	} else {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
	}
	return true;
}

bool InstantSpell::HouseSubOwnerList(const InstantSpell*, Creature* creature, const std::string&)
{
	House* house = getHouseFromPos(creature);
	if (!house) {
		return false;
	}

	Player* player = creature->getPlayer();
	if (house->canEditAccessList(SUBOWNER_LIST, player)) {
		player->setEditHouse(house, SUBOWNER_LIST);
		player->sendHouseWindow(house, SUBOWNER_LIST);
	} else {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
	}
	return true;
}

bool InstantSpell::HouseDoorList(const InstantSpell*, Creature* creature, const std::string&)
{
	House* house = getHouseFromPos(creature);
	if (!house) {
		return false;
	}

	Player* player = creature->getPlayer();
	Position pos = Spells::getCasterPosition(player, player->getDirection());
	Door* door = house->getDoorByPosition(pos);
	if (door && house->canEditAccessList(door->getDoorId(), player)) {
		player->setEditHouse(house, door->getDoorId());
		player->sendHouseWindow(house, door->getDoorId());
	} else {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
	}
	return true;
}

bool InstantSpell::HouseKick(const InstantSpell*, Creature* creature, const std::string& param)
{
	Player* player = creature->getPlayer();

	Player* targetPlayer = g_game.getPlayerByName(param);
	if (!targetPlayer) {
		targetPlayer = player;
	}

	House* house = getHouseFromPos(targetPlayer);
	if (!house) {
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		return false;
	}

	if (!house->kickPlayer(player, targetPlayer)) {
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		return false;
	}
	return true;
}

bool InstantSpell::SearchPlayer(const InstantSpell*, Creature* creature, const std::string& param)
{
	//a. From 1 to 4 sq's [Person] is standing next to you.
	//b. From 5 to 100 sq's [Person] is to the south, north, east, west.
	//c. From 101 to 274 sq's [Person] is far to the south, north, east, west.
	//d. From 275 to infinite sq's [Person] is very far to the south, north, east, west.
	//e. South-west, s-e, n-w, n-e (corner coordinates): this phrase appears if the player you're looking for has moved five squares in any direction from the south, north, east or west.
	//f. Lower level to the (direction): this phrase applies if the person you're looking for is from 1-25 squares up/down the actual floor you're in.
	//g. Higher level to the (direction): this phrase applies if the person you're looking for is from 1-25 squares up/down the actual floor you're in.

	Player* player = creature->getPlayer();
	if (!player) {
		return false;
	}

	enum distance_t {
		DISTANCE_BESIDE,
		DISTANCE_CLOSE,
		DISTANCE_FAR,
		DISTANCE_VERYFAR,
	};

	enum direction_t {
		DIR_N, DIR_S, DIR_E, DIR_W,
		DIR_NE, DIR_NW, DIR_SE, DIR_SW,
	};

	enum level_t {
		LEVEL_HIGHER,
		LEVEL_LOWER,
		LEVEL_SAME,
	};

	Player* playerExiva = g_game.getPlayerByName(param);
	if (!playerExiva) {
		return false;
	}

	if (playerExiva->isAccessPlayer() && !player->isAccessPlayer()) {
		player->sendCancelMessage(RETURNVALUE_PLAYERWITHTHISNAMEISNOTONLINE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	const Position& lookPos = player->getPosition();
	const Position& searchPos = playerExiva->getPosition();

	int32_t dx = Position::getOffsetX(lookPos, searchPos);
	int32_t dy = Position::getOffsetY(lookPos, searchPos);
	int32_t dz = Position::getOffsetZ(lookPos, searchPos);

	distance_t distance;

	direction_t direction;

	level_t level;

	//getting floor
	if (dz > 0) {
		level = LEVEL_HIGHER;
	} else if (dz < 0) {
		level = LEVEL_LOWER;
	} else {
		level = LEVEL_SAME;
	}

	//getting distance
	if (std::abs(dx) < 4 && std::abs(dy) < 4) {
		distance = DISTANCE_BESIDE;
	} else {
		int32_t distance2 = dx * dx + dy * dy;
		if (distance2 < 10000) {
			distance = DISTANCE_CLOSE;
		} else if (distance2 < 75076) {
			distance = DISTANCE_FAR;
		} else {
			distance = DISTANCE_VERYFAR;
		}
	}

	//getting direction
	float tan;
	if (dx != 0) {
		tan = static_cast<float>(dy) / dx;
	} else {
		tan = 10.;
	}

	if (std::abs(tan) < 0.4142) {
		if (dx > 0) {
			direction = DIR_W;
		} else {
			direction = DIR_E;
		}
	} else if (std::abs(tan) < 2.4142) {
		if (tan > 0) {
			if (dy > 0) {
				direction = DIR_NW;
			} else {
				direction = DIR_SE;
			}
		} else {
			if (dx > 0) {
				direction = DIR_SW;
			} else {
				direction = DIR_NE;
			}
		}
	} else {
		if (dy > 0) {
			direction = DIR_N;
		} else {
			direction = DIR_S;
		}
	}

	std::ostringstream ss;
	ss << playerExiva->getName();

	if (distance == DISTANCE_BESIDE) {
		if (level == LEVEL_SAME) {
			ss << " is standing next to you.";
		} else if (level == LEVEL_HIGHER) {
			ss << " is above you.";
		} else if (level == LEVEL_LOWER) {
			ss << " is below you.";
		}
	} else {
		switch (distance) {
			case DISTANCE_CLOSE:
				if (level == LEVEL_SAME) {
					ss << " is to the ";
				} else if (level == LEVEL_HIGHER) {
					ss << " is on a higher level to the ";
				} else if (level == LEVEL_LOWER) {
					ss << " is on a lower level to the ";
				}
				break;
			case DISTANCE_FAR:
				ss << " is far to the ";
				break;
			case DISTANCE_VERYFAR:
				ss << " is very far to the ";
				break;
			default:
				break;
		}

		switch (direction) {
			case DIR_N:
				ss << "north.";
				break;
			case DIR_S:
				ss << "south.";
				break;
			case DIR_E:
				ss << "east.";
				break;
			case DIR_W:
				ss << "west.";
				break;
			case DIR_NE:
				ss << "north-east.";
				break;
			case DIR_NW:
				ss << "north-west.";
				break;
			case DIR_SE:
				ss << "south-east.";
				break;
			case DIR_SW:
				ss << "south-west.";
				break;
		}
	}
	player->sendTextMessage(MESSAGE_INFO_DESCR, ss.str());
	g_game.addMagicEffect(player->getPosition(), CONST_ME_MAGIC_BLUE);
	return true;
}

bool InstantSpell::SummonMonster(const InstantSpell* spell, Creature* creature, const std::string& param)
{
	Player* player = creature->getPlayer();
	if (!player) {
		return false;
	}

	MonsterType* mType = g_monsters.getMonsterType(param);
	if (!mType) {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	if (!player->hasFlag(PlayerFlag_CanSummonAll)) {
		if (!mType->info.isSummonable) {
			player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
			g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
			return false;
		}

		if (player->getMana() < mType->info.manaCost) {
			player->sendCancelMessage(RETURNVALUE_NOTENOUGHMANA);
			g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
			return false;
		}

		if (player->getSummonCount() >= 2) {
			player->sendCancelMessage("You cannot summon more creatures.");
			g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
			return false;
		}
	}

	Monster* monster = Monster::createMonster(param, 0, 0); //pota
	if (!monster) {
		player->sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	// Place the monster
	creature->addSummon(monster);

	if (!g_game.placeCreature(monster, creature->getPosition(), true)) {
		creature->removeSummon(monster);
		player->sendCancelMessage(RETURNVALUE_NOTENOUGHROOM);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	Spell::postCastSpell(player, mType->info.manaCost, spell->getSoulCost());
	g_game.addMagicEffect(player->getPosition(), CONST_ME_MAGIC_BLUE);
	g_game.addMagicEffect(monster->getPosition(), CONST_ME_TELEPORT);
	return true;
}

bool InstantSpell::Levitate(const InstantSpell*, Creature* creature, const std::string& param)
{
	Player* player = creature->getPlayer();
	if (!player) {
		return false;
	}

	const Position& currentPos = creature->getPosition();
	const Position& destPos = Spells::getCasterPosition(creature, creature->getDirection());

	ReturnValue ret = RETURNVALUE_NOTPOSSIBLE;

	if (strcasecmp(param.c_str(), "up") == 0) {
		if (currentPos.z != 8) {
			Tile* tmpTile = g_game.map.getTile(currentPos.x, currentPos.y, currentPos.getZ() - 1);
			if (tmpTile == nullptr || (tmpTile->getGround() == nullptr && !tmpTile->hasFlag(TILESTATE_IMMOVABLEBLOCKSOLID))) {
				tmpTile = g_game.map.getTile(destPos.x, destPos.y, destPos.getZ() - 1);
				if (tmpTile && tmpTile->getGround() && !tmpTile->hasFlag(TILESTATE_IMMOVABLEBLOCKSOLID | TILESTATE_FLOORCHANGE)) {
					ret = g_game.internalMoveCreature(*player, *tmpTile, FLAG_IGNOREBLOCKITEM | FLAG_IGNOREBLOCKCREATURE);
				}
			}
		}
	} else if (strcasecmp(param.c_str(), "down") == 0) {
		if (currentPos.z != 7) {
			Tile* tmpTile = g_game.map.getTile(destPos);
			if (tmpTile == nullptr || (tmpTile->getGround() == nullptr && !tmpTile->hasFlag(TILESTATE_BLOCKSOLID))) {
				tmpTile = g_game.map.getTile(destPos.x, destPos.y, destPos.z + 1);
				if (tmpTile && tmpTile->getGround() && !tmpTile->hasFlag(TILESTATE_IMMOVABLEBLOCKSOLID | TILESTATE_FLOORCHANGE)) {
					ret = g_game.internalMoveCreature(*player, *tmpTile, FLAG_IGNOREBLOCKITEM | FLAG_IGNOREBLOCKCREATURE);
				}
			}
		}
	}

	if (ret != RETURNVALUE_NOERROR) {
		player->sendCancelMessage(ret);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	g_game.addMagicEffect(player->getPosition(), CONST_ME_TELEPORT);
	return true;
}

bool InstantSpell::Illusion(const InstantSpell*, Creature* creature, const std::string& param)
{
	Player* player = creature->getPlayer();
	if (!player) {
		return false;
	}

	ReturnValue ret = Spell::CreateIllusion(creature, param, 180000);
	if (ret != RETURNVALUE_NOERROR) {
		player->sendCancelMessage(ret);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	g_game.addMagicEffect(player->getPosition(), CONST_ME_MAGIC_RED);
	return true;
}
