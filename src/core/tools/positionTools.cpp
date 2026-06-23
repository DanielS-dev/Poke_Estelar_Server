// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "positionTools.hpp"

Direction getDirection(const std::string& string)
{
	Direction direction = DIRECTION_NORTH;

	if (string == "north" || string == "n" || string == "0") {
		direction = DIRECTION_NORTH;
	} else if (string == "east" || string == "e" || string == "1") {
		direction = DIRECTION_EAST;
	} else if (string == "south" || string == "s" || string == "2") {
		direction = DIRECTION_SOUTH;
	} else if (string == "west" || string == "w" || string == "3") {
		direction = DIRECTION_WEST;
	} else if (string == "southwest" || string == "south west" || string == "south-west" || string == "sw" || string == "4") {
		direction = DIRECTION_SOUTHWEST;
	} else if (string == "southeast" || string == "south east" || string == "south-east" || string == "se" || string == "5") {
		direction = DIRECTION_SOUTHEAST;
	} else if (string == "northwest" || string == "north west" || string == "north-west" || string == "nw" || string == "6") {
		direction = DIRECTION_NORTHWEST;
	} else if (string == "northeast" || string == "north east" || string == "north-east" || string == "ne" || string == "7") {
		direction = DIRECTION_NORTHEAST;
	}

	return direction;
}

Position getNextPosition(Direction direction, Position pos)
{
	switch (direction) {
		case DIRECTION_NORTH:
			pos.y--;
			break;

		case DIRECTION_SOUTH:
			pos.y++;
			break;

		case DIRECTION_WEST:
			pos.x--;
			break;

		case DIRECTION_EAST:
			pos.x++;
			break;

		case DIRECTION_SOUTHWEST:
			pos.x--;
			pos.y++;
			break;

		case DIRECTION_NORTHWEST:
			pos.x--;
			pos.y--;
			break;

		case DIRECTION_NORTHEAST:
			pos.x++;
			pos.y--;
			break;

		case DIRECTION_SOUTHEAST:
			pos.x++;
			pos.y++;
			break;

		default:
			break;
	}

	return pos;
}

Direction getDirectionTo(const Position& from, const Position& to)
{
	Direction dir;

	int32_t x_offset = Position::getOffsetX(from, to);
	if (x_offset < 0) {
		dir = DIRECTION_EAST;
		x_offset = std::abs(x_offset);
	} else {
		dir = DIRECTION_WEST;
	}

	int32_t y_offset = Position::getOffsetY(from, to);
	if (y_offset >= 0) {
		if (y_offset > x_offset) {
			dir = DIRECTION_NORTH;
		} else if (y_offset == x_offset) {
			if (dir == DIRECTION_EAST) {
				dir = DIRECTION_NORTHEAST;
			} else {
				dir = DIRECTION_NORTHWEST;
			}
		}
	} else {
		y_offset = std::abs(y_offset);
		if (y_offset > x_offset) {
			dir = DIRECTION_SOUTH;
		} else if (y_offset == x_offset) {
			if (dir == DIRECTION_EAST) {
				dir = DIRECTION_SOUTHEAST;
			} else {
				dir = DIRECTION_SOUTHWEST;
			}
		}
	}
	return dir;
}
