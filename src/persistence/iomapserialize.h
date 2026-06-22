// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_IOMAPSERIALIZE_H_7E903658F34E44F9BE03A713B55A3D6D
#define FS_IOMAPSERIALIZE_H_7E903658F34E44F9BE03A713B55A3D6D

#include "database.h"
#include "../world/map.h"

class IOMapSerialize
{
	public:
		static void loadHouseItems(Map* map);
		static bool saveHouseItems();
		static bool loadHouseInfo();
		static bool saveHouseInfo();

	protected:
		static void saveItem(PropWriteStream& stream, const Item* item);
		static void saveTile(PropWriteStream& stream, const Tile* tile);

		static bool loadContainer(PropStream& propStream, Container* container);
		static bool loadItem(PropStream& propStream, Cylinder* parent);
};

#endif
