// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_DATABASEMANAGER_H_2B75821C555E4D1D83E32B20D683217C
#define FS_DATABASEMANAGER_H_2B75821C555E4D1D83E32B20D683217C
#include "database.hpp"

class DatabaseManager
{
	public:
		static bool tableExists(const std::string& table);

		static int32_t getDatabaseVersion();
		static bool isDatabaseSetup();

		static bool optimizeTables();
		static void updateDatabase();

		static bool getDatabaseConfig(const std::string& config, int32_t& value);
		static void registerDatabaseConfig(const std::string& config, int32_t value);
};
#endif
