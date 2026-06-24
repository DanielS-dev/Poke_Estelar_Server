// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_IOMAP_H_8085D4B1037A44288494A52FDBB775E4
#define FS_IOMAP_H_8085D4B1037A44288494A52FDBB775E4

#include "../../items/item.hpp"
#include "../../world/map.hpp"
#include "../../world/house.hpp"
#include "../../world/spawn.hpp"
#include "../../config/configmanager.hpp"

extern ConfigManager g_config;

#include "otbmTypes.hpp"

class IOMap
{
	static Tile* createTile(Item*& ground, Item* item, uint16_t x, uint16_t y, uint8_t z);

	public:
		bool loadMap(Map* map, const std::string& identifier);

		/* Load the spawns
		 * \param map pointer to the Map class
		 * \returns Returns true if the spawns were loaded successfully
		 */
		static bool loadSpawns(Map* map) {
			if (map->spawnfile.empty()) {
				//OTBM file doesn't tell us about the spawnfile,
				//lets guess it is mapname-spawn.xml.
				map->spawnfile = g_config.getString(ConfigManager::MAP_NAME);
				map->spawnfile += "-spawn.xml";
			}

			return map->spawns.loadFromXml(map->spawnfile);
		}

		/* Load the houses (not house tile-data)
		 * \param map pointer to the Map class
		 * \returns Returns true if the houses were loaded successfully
		 */
		static bool loadHouses(Map* map) {
			if (map->housefile.empty()) {
				//OTBM file doesn't tell us about the housefile,
				//lets guess it is mapname-house.xml.
				map->housefile = g_config.getString(ConfigManager::MAP_NAME);
				map->housefile += "-house.xml";
			}

			return map->houses.loadHousesXML(map->housefile);
		}

		const std::string& getLastErrorString() const {
			return errorString;
		}

		void setLastErrorString(std::string error) {
			errorString = error;
		}

	protected:
		std::string errorString;
};

#endif
