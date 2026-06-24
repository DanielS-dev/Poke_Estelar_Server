// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../map.hpp"

#include "../../entities/creature.hpp"
#include "../../game/combat/combat.hpp"
#include "../../game/game.hpp"
#include "../../persistence/map/iomap.hpp"
#include "../../persistence/map/iomapserialize.hpp"
#include "../../core/tools/random.hpp"

extern Game g_game;

uint32_t Map::clean() const
{
	uint64_t start = OTSYS_TIME();
	size_t count = 0, tiles = 0;

	if (g_game.getGameState() == GAME_STATE_NORMAL) {
		g_game.setGameState(GAME_STATE_MAINTAIN);
	}

	std::vector<const QTreeNode*> nodes {
		&root
	};
	std::vector<Item*> toRemove;
	do {
		const QTreeNode* node = nodes.back();
		nodes.pop_back();
		if (node->isLeaf()) {
			const QTreeLeafNode* leafNode = static_cast<const QTreeLeafNode*>(node);
			for (uint8_t z = 0; z < MAP_MAX_LAYERS; ++z) {
				Floor* floor = leafNode->getFloor(z);
				if (!floor) {
					continue;
				}

				for (auto& row : floor->tiles) {
					for (auto tile : row) {
						if (!tile || tile->hasFlag(TILESTATE_PROTECTIONZONE)) {
							continue;
						}

						TileItemVector* itemList = tile->getItemList();
						if (!itemList) {
							continue;
						}

						++tiles;
						for (Item* item : *itemList) {
							if (item->isCleanable()) {
								toRemove.push_back(item);
							}
						}

						for (Item* item : toRemove) {
							g_game.internalRemoveItem(item, -1);
						}
						count += toRemove.size();
						toRemove.clear();
					}
				}
			}
		} else {
			for (auto childNode : node->child) {
				if (childNode) {
					nodes.push_back(childNode);
				}
			}
		}
	} while (!nodes.empty());

	if (g_game.getGameState() == GAME_STATE_MAINTAIN) {
		g_game.setGameState(GAME_STATE_NORMAL);
	}

	std::cout << "> CLEAN: Removed " << count << " item" << (count != 1 ? "s" : "")
	          << " from " << tiles << " tile" << (tiles != 1 ? "s" : "") << " in "
	          << (OTSYS_TIME() - start) / (1000.) << " seconds." << std::endl;
	return count;
}
