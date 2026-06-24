// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_AREACOMBAT_H_DCC73430F6D94086A07739D1B882AF0C
#define FS_AREACOMBAT_H_DCC73430F6D94086A07739D1B882AF0C

#include <forward_list>
#include <list>
#include <map>

#include "matrixArea.hpp"
#include "../../core/position.hpp"
#include "../../world/tile.hpp"

class AreaCombat
{
	public:
		AreaCombat() = default;

		AreaCombat(const AreaCombat& rhs);
		~AreaCombat() {
			clear();
		}

		// non-assignable
		AreaCombat& operator=(const AreaCombat&) = delete;

		void getList(const Position& centerPos, const Position& targetPos, std::forward_list<Tile*>& list) const;

		void setupArea(const std::list<uint32_t>& list, uint32_t rows);
		void setupArea(int32_t length, int32_t spread);
		void setupArea(int32_t radius);
		void setupExtArea(const std::list<uint32_t>& list, uint32_t rows);
		void clear();

	protected:
		enum MatrixOperation_t {
			MATRIXOPERATION_COPY,
			MATRIXOPERATION_MIRROR,
			MATRIXOPERATION_FLIP,
			MATRIXOPERATION_ROTATE90,
			MATRIXOPERATION_ROTATE180,
			MATRIXOPERATION_ROTATE270,
		};

		MatrixArea* createArea(const std::list<uint32_t>& list, uint32_t rows);
		void copyArea(const MatrixArea* input, MatrixArea* output, MatrixOperation_t op) const;

		MatrixArea* getArea(const Position& centerPos, const Position& targetPos) const {
			int32_t dx = Position::getOffsetX(targetPos, centerPos);
			int32_t dy = Position::getOffsetY(targetPos, centerPos);

			Direction dir;
			if (dx < 0) {
				dir = DIRECTION_WEST;
			} else if (dx > 0) {
				dir = DIRECTION_EAST;
			} else if (dy < 0) {
				dir = DIRECTION_NORTH;
			} else {
				dir = DIRECTION_SOUTH;
			}

			if (hasExtArea) {
				if (dx < 0 && dy < 0) {
					dir = DIRECTION_NORTHWEST;
				} else if (dx > 0 && dy < 0) {
					dir = DIRECTION_NORTHEAST;
				} else if (dx < 0 && dy > 0) {
					dir = DIRECTION_SOUTHWEST;
				} else if (dx > 0 && dy > 0) {
					dir = DIRECTION_SOUTHEAST;
				}
			}

			auto it = areas.find(dir);
			if (it == areas.end()) {
				return nullptr;
			}
			return it->second;
		}

		std::map<Direction, MatrixArea*> areas;
		bool hasExtArea = false;
};

#endif
