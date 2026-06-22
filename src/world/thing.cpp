// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "thing.hpp"
#include "tile.hpp"

const Position& Thing::getPosition() const
{
	const Tile* tile = getTile();
	if (!tile) {
		return Tile::nullptr_tile.getPosition();
	}
	return tile->getPosition();
}

Tile* Thing::getTile()
{
	return dynamic_cast<Tile*>(this);
}

const Tile* Thing::getTile() const
{
	return dynamic_cast<const Tile*>(this);
}
