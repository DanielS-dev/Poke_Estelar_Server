// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "services.hpp"

#include "../game/game.hpp"

#include "../persistence/market/iomarket.hpp"

#include "../config/configmanager.hpp"
#include "../scripting/scriptmanager.hpp"
#include "../security/rsa.hpp"
#include "../network/protocolold.hpp"
#include "../network/protocollogin.hpp"
#include "../network/protocolstatus.hpp"
#include "../persistence/databasemanager.hpp"
#include "../core/scheduler.hpp"
#include "../persistence/databasetasks.hpp"
#include "../core/tools/stringsTools.hpp"
#include "../core/logger.hpp"

DatabaseTasks g_databaseTasks;
Dispatcher g_dispatcher;
Scheduler g_scheduler;

Game g_game;
ConfigManager g_config;
Monsters g_monsters;
Vocations g_vocations;
RSA g_RSA;

std::mutex g_loaderLock;
std::condition_variable g_loaderSignal;
std::unique_lock<std::mutex> g_loaderUniqueLock(g_loaderLock);

void startupErrorMessage(const std::string& errorStr)
{
	LOG_FATAL("Startup", errorStr);
	g_loaderSignal.notify_all();
}

void mainLoader(int argc, char* argv[], ServiceManager* servicer);

void badAllocationHandler()
{
	// Use functions that only use stack allocation
	puts("Allocation failed, server out of memory.\nDecrease the size of your map or compile in 64 bits mode.\n");
	getchar();
	exit(-1);
}

int main(int argc, char* argv[])
{
	// Setup bad allocation handler
	std::set_new_handler(badAllocationHandler);

	Logger::getInstance().initializeFromEnv(".env");
	LOG_INFO("Startup", "Logger initialized");

	ServiceManager serviceManager;

	g_dispatcher.start();
	g_scheduler.start();

	g_dispatcher.addTask(createTask(std::bind(mainLoader, argc, argv, &serviceManager)));

	g_loaderSignal.wait(g_loaderUniqueLock);

	if (serviceManager.is_running()) {
		LOG_INFO("Startup", g_config.getString(ConfigManager::SERVER_NAME) + " Server Online!");
		serviceManager.run();
	} else {
		LOG_WARN("Startup", "No services running. The server is NOT online.");
		g_scheduler.shutdown();
		g_databaseTasks.shutdown();
		g_dispatcher.shutdown();
	}

	g_scheduler.join();
	g_databaseTasks.join();
	g_dispatcher.join();
	Logger::getInstance().shutdown();
	return 0;
}

void mainLoader(int, char*[], ServiceManager* services)
{
	//dispatcher thread
	g_game.setGameState(GAME_STATE_STARTUP);

	srand(static_cast<unsigned int>(OTSYS_TIME()));
#ifdef _WIN32
	SetConsoleTitle(STATUS_SERVER_NAME);
#endif
	LOG_INFO("Startup", std::string(STATUS_SERVER_NAME) + " - Version " + STATUS_SERVER_VERSION);
	LOG_INFO("Startup", std::string("Compiled with ") + BOOST_COMPILER);

	std::string platform;
#if defined(__amd64__) || defined(_M_X64)
	platform = "x64";
#elif defined(__i386__) || defined(_M_IX86) || defined(_X86_)
	platform = "x86";
#elif defined(__arm__)
	platform = "ARM";
#else
	platform = "unknown";
#endif
	LOG_INFO("Startup", std::string("Compiled on ") + __DATE__ + ' ' + __TIME__ + " for platform " + platform);

	LOG_INFO("Startup", std::string("A server developed by ") + STATUS_SERVER_DEVELOPERS);

	// read global config
	LOG_INFO("Startup", "Loading config");
	if (!g_config.load()) {
		startupErrorMessage("Unable to load config.lua!");
		return;
	}

#ifdef _WIN32
	const std::string& defaultPriority = g_config.getString(ConfigManager::DEFAULT_PRIORITY);
	if (strcasecmp(defaultPriority.c_str(), "high") == 0) {
		SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	} else if (strcasecmp(defaultPriority.c_str(), "above-normal") == 0) {
		SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
	}
#endif

	//set RSA key
	g_RSA.setKey(g_config.getString(ConfigManager::RSA_P).c_str(), g_config.getString(ConfigManager::RSA_Q).c_str());

	LOG_INFO("Database", "Establishing database connection...");

	Database* db = Database::getInstance();
	if (!db->connect()) {
		startupErrorMessage("Failed to connect to database.");
		return;
	}

	LOG_INFO("Database", std::string("Connected to MySQL ") + Database::getClientVersion());

	// run database manager
	LOG_INFO("Database", "Running database manager");

	if (!DatabaseManager::isDatabaseSetup()) {
		startupErrorMessage("The database you have specified in config.lua is empty, please import the schema.sql to your database.");
		return;
	}
	g_databaseTasks.start();

	DatabaseManager::updateDatabase();

	if (g_config.getBoolean(ConfigManager::OPTIMIZE_DATABASE) && !DatabaseManager::optimizeTables()) {
		LOG_WARN("Database", "No tables were optimized.");
	}

	//load vocations
	LOG_INFO("Startup", "Loading vocations");
	if (!g_vocations.loadFromXml()) {
		startupErrorMessage("Unable to load vocations!");
		return;
	}

	// load item data
	LOG_INFO("Startup", "Loading items");
	if (Item::items.loadFromOtb("data/items/items.otb") != ERROR_NONE) {
		startupErrorMessage("Unable to load items (OTB)!");
		return;
	}

	if (!Item::items.loadFromXml()) {
		startupErrorMessage("Unable to load items (XML)!");
		return;
	}

	LOG_INFO("Startup", "Loading script systems");
	if (!ScriptingManager::getInstance()->loadScriptSystems()) {
		startupErrorMessage("Failed to load script systems");
		return;
	}

	LOG_INFO("Startup", "Loading monsters");
	if (!g_monsters.loadFromXml()) {
		startupErrorMessage("Unable to load monsters!");
		return;
	}

	LOG_INFO("Startup", "Loading outfits");
	Outfits* outfits = Outfits::getInstance();
	if (!outfits->loadFromXml()) {
		startupErrorMessage("Unable to load outfits!");
		return;
	}

	LOG_INFO("Startup", "Checking world type");
	std::string worldType = asLowerCaseString(g_config.getString(ConfigManager::WORLD_TYPE));
	if (worldType == "pvp") {
		g_game.setWorldType(WORLD_TYPE_PVP);
	} else if (worldType == "no-pvp") {
		g_game.setWorldType(WORLD_TYPE_NO_PVP);
	} else if (worldType == "pvp-enforced") {
		g_game.setWorldType(WORLD_TYPE_PVP_ENFORCED);
	} else {
		std::ostringstream ss;
		ss << "Unknown world type: " << g_config.getString(ConfigManager::WORLD_TYPE) << ", valid world types are: pvp, no-pvp and pvp-enforced.";
		startupErrorMessage(ss.str());
		return;
	}
	LOG_INFO("Startup", "World type: " + asUpperCaseString(worldType));

	LOG_INFO("Startup", "Loading map");
	if (!g_game.loadMainMap(g_config.getString(ConfigManager::MAP_NAME))) {
		startupErrorMessage("Failed to load map");
		return;
	}

	LOG_INFO("Startup", "Initializing gamestate");
	g_game.setGameState(GAME_STATE_INIT);

	// Game client protocols
	services->add<ProtocolGame>(g_config.getNumber(ConfigManager::GAME_PORT));
	services->add<ProtocolLogin>(g_config.getNumber(ConfigManager::LOGIN_PORT));

	// OT protocols
	services->add<ProtocolStatus>(g_config.getNumber(ConfigManager::STATUS_PORT));

	// Legacy login protocol
	services->add<ProtocolOld>(g_config.getNumber(ConfigManager::LOGIN_PORT));

	RentPeriod_t rentPeriod;
	std::string strRentPeriod = asLowerCaseString(g_config.getString(ConfigManager::HOUSE_RENT_PERIOD));

	if (strRentPeriod == "yearly") {
		rentPeriod = RENTPERIOD_YEARLY;
	} else if (strRentPeriod == "weekly") {
		rentPeriod = RENTPERIOD_WEEKLY;
	} else if (strRentPeriod == "monthly") {
		rentPeriod = RENTPERIOD_MONTHLY;
	} else if (strRentPeriod == "daily") {
		rentPeriod = RENTPERIOD_DAILY;
	} else {
		rentPeriod = RENTPERIOD_NEVER;
	}

	g_game.map.houses.payHouses(rentPeriod);

	IOMarket::checkExpiredOffers();
	IOMarket::getInstance()->updateStatistics();

	LOG_INFO("Startup", "Loaded all modules, server starting up...");

#ifndef _WIN32
	if (getuid() == 0 || geteuid() == 0) {
		LOG_WARN("Startup", std::string(STATUS_SERVER_NAME) + " has been executed as root user, please consider running it as a normal user.");
	}
#endif

	g_game.start(services);
	g_game.setGameState(GAME_STATE_NORMAL);
	g_loaderSignal.notify_all();
}
