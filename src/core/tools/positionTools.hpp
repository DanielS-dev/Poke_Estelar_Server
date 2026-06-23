// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_POSITION_TOOLS_H_5F9A9742DA194628830AA1C64909AE43
#define FS_POSITION_TOOLS_H_5F9A9742DA194628830AA1C64909AE43

#include <string>

#include "../position.hpp"
#include "../enums.hpp"

Direction getDirection(const std::string& string);
Position getNextPosition(Direction direction, Position pos);
Direction getDirectionTo(const Position& from, const Position& to);

#endif
