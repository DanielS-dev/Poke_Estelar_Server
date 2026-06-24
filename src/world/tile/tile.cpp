// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../tile.hpp"

StaticTile real_nullptr_tile(0xFFFF, 0xFFFF, 0xFF);
Tile& Tile::nullptr_tile = real_nullptr_tile;

std::string Tile::getDescription(int32_t) const
{
	return "You dont know why, but you cant see anything!";
}

