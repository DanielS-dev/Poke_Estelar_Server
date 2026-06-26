// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "configmanager.hpp"
#include "../game/game.hpp"
#include "../core/tools/auths.hpp"
#include "../core/tools/stringsTools.hpp"

#include <cerrno>
#include <cctype>
#include <cstdlib>
#include <fstream>

#if LUA_VERSION_NUM >= 502
#undef lua_strlen
#define lua_strlen lua_rawlen
#endif

extern Game g_game;

namespace {
	std::string trimEnvValue(const std::string& value)
	{
		auto start = std::find_if_not(value.begin(), value.end(), [](unsigned char ch) {
			return std::isspace(ch) != 0;
		});

		auto end = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char ch) {
			return std::isspace(ch) != 0;
		}).base();

		if (start >= end) {
			return std::string();
		}

		return std::string(start, end);
	}

	std::string parseEnvValue(std::string value)
	{
		value = trimEnvValue(value);
		if (value.empty()) {
			return value;
		}

		const char quote = value.front();
		if (quote == '"' || quote == '\'') {
			const size_t endQuote = value.find(quote, 1);
			if (endQuote != std::string::npos) {
				return value.substr(1, endQuote - 1);
			}
			return value.substr(1);
		}

		const size_t comment = value.find('#');
		if (comment != std::string::npos) {
			value.erase(comment);
		}

		return trimEnvValue(value);
	}
}

bool ConfigManager::load()
{
	lua_State* L = luaL_newstate();
	if (!L) {
		throw std::runtime_error("Failed to allocate memory");
	}

	luaL_openlibs(L);

	if (luaL_dofile(L, "config.lua")) {
		std::cout << "[Error - ConfigManager::load] " << lua_tostring(L, -1) << std::endl;
		lua_close(L);
		return false;
	}

	const auto env = loadEnvFile(".env");

	//parse config
	if (!loaded) { //info that must be loaded one time (unless we reset the modules involved)
		boolean[BIND_ONLY_GLOBAL_ADDRESS] = getGlobalBoolean(L, "bindOnlyGlobalAddress", false);
		boolean[OPTIMIZE_DATABASE] = getGlobalBoolean(L, "startupDatabaseOptimization", true);

		string[MAP_NAME] = getGlobalString(L, "mapName", "forgotten");
		string[MAP_AUTHOR] = getGlobalString(L, "mapAuthor", "Unknown");
		string[HOUSE_RENT_PERIOD] = getGlobalString(L, "houseRentPeriod", "never");

		integer[MARKET_OFFER_DURATION] = getGlobalNumber(L, "marketOfferDuration", 30 * 24 * 60 * 60);
		loadEnvConfig(env);
	}

	boolean[ALLOW_CHANGEOUTFIT] = getGlobalBoolean(L, "allowChangeOutfit", true);
	boolean[ONE_PLAYER_ON_ACCOUNT] = getGlobalBoolean(L, "onePlayerOnlinePerAccount", true);
	boolean[AIMBOT_HOTKEY_ENABLED] = getGlobalBoolean(L, "hotkeyAimbotEnabled", true);
	boolean[REMOVE_RUNE_CHARGES] = getGlobalBoolean(L, "removeChargesFromRunes", true);
	boolean[EXPERIENCE_FROM_PLAYERS] = getGlobalBoolean(L, "experienceByKillingPlayers", false);
	boolean[FREE_PREMIUM] = getGlobalBoolean(L, "freePremium", false);
	boolean[REPLACE_KICK_ON_LOGIN] = getGlobalBoolean(L, "replaceKickOnLogin", true);
	boolean[ALLOW_CLONES] = getGlobalBoolean(L, "allowClones", false);
	boolean[MARKET_PREMIUM] = getGlobalBoolean(L, "premiumToCreateMarketOffer", true);
	boolean[EMOTE_SPELLS] = getGlobalBoolean(L, "emoteSpells", false);
	boolean[STAMINA_SYSTEM] = getGlobalBoolean(L, "staminaSystem", true);
	boolean[WARN_UNSAFE_SCRIPTS] = getGlobalBoolean(L, "warnUnsafeScripts", true);
	boolean[CONVERT_UNSAFE_SCRIPTS] = getGlobalBoolean(L, "convertUnsafeScripts", true);
	boolean[CLASSIC_EQUIPMENT_SLOTS] = getGlobalBoolean(L, "classicEquipmentSlots", false);

	string[DEFAULT_PRIORITY] = getGlobalString(L, "defaultPriority", "high");
	string[SERVER_NAME] = getGlobalString(L, "serverName", "");
	string[OWNER_NAME] = getGlobalString(L, "ownerName", "");
	string[OWNER_EMAIL] = getGlobalString(L, "ownerEmail", "");
	string[URL] = getGlobalString(L, "url", "");
	string[LOCATION] = getGlobalString(L, "location", "");
	string[MOTD] = getGlobalString(L, "motd", "");
	string[WORLD_TYPE] = getGlobalString(L, "worldType", "pvp");
	string[MONSTERLEVEL_PREFIX] = getGlobalString(L, "monsterPrefix", ""); //pota

	integer[MAX_PLAYERS] = getGlobalNumber(L, "maxPlayers");
	integer[PZ_LOCKED] = getGlobalNumber(L, "pzLocked", 60000);
	integer[DEFAULT_DESPAWNRANGE] = getGlobalNumber(L, "deSpawnRange", 2);
	integer[DEFAULT_DESPAWNRADIUS] = getGlobalNumber(L, "deSpawnRadius", 50);
	integer[RATE_EXPERIENCE] = getGlobalNumber(L, "rateExp", 5);
	integer[RATE_SKILL] = getGlobalNumber(L, "rateSkill", 3);
	integer[RATE_LOOT] = getGlobalNumber(L, "rateLoot", 2);
	integer[RATE_MAGIC] = getGlobalNumber(L, "rateMagic", 3);
	integer[RATE_SPAWN] = getGlobalNumber(L, "rateSpawn", 1);
	integer[HOUSE_PRICE] = getGlobalNumber(L, "housePriceEachSQM", 1000);
	integer[KILLS_TO_RED] = getGlobalNumber(L, "killsToRedSkull", 3);
	integer[KILLS_TO_BLACK] = getGlobalNumber(L, "killsToBlackSkull", 6);
	integer[ACTIONS_DELAY_INTERVAL] = getGlobalNumber(L, "timeBetweenActions", 200);
	integer[EX_ACTIONS_DELAY_INTERVAL] = getGlobalNumber(L, "timeBetweenExActions", 1000);
	integer[MAX_MESSAGEBUFFER] = getGlobalNumber(L, "maxMessageBuffer", 4);
	integer[KICK_AFTER_MINUTES] = getGlobalNumber(L, "kickIdlePlayerAfterMinutes", 15);
	integer[PROTECTION_LEVEL] = getGlobalNumber(L, "protectionLevel", 1);
	integer[DEATH_LOSE_PERCENT] = getGlobalNumber(L, "deathLosePercent", -1);
	integer[STATUSQUERY_TIMEOUT] = getGlobalNumber(L, "statusTimeout", 5000);
	integer[FRAG_TIME] = getGlobalNumber(L, "timeToDecreaseFrags", 24 * 60 * 60 * 1000);
	integer[WHITE_SKULL_TIME] = getGlobalNumber(L, "whiteSkullTime", 15 * 60 * 1000);
	integer[STAIRHOP_DELAY] = getGlobalNumber(L, "stairJumpExhaustion", 2000);
	integer[EXP_FROM_PLAYERS_LEVEL_RANGE] = getGlobalNumber(L, "expFromPlayersLevelRange", 75);
	integer[CHECK_EXPIRED_MARKET_OFFERS_EACH_MINUTES] = getGlobalNumber(L, "checkExpiredMarketOffersEachMinutes", 60);
	integer[MAX_MARKET_OFFERS_AT_A_TIME_PER_PLAYER] = getGlobalNumber(L, "maxMarketOffersAtATimePerPlayer", 100);
	integer[MAX_PACKETS_PER_SECOND] = getGlobalNumber(L, "maxPacketsPerSecond", 25);

	decimal[MONSTERLEVEL_BONUSDMG] = getGlobalDouble(L, "monsterLevelDamage", 0.0); //pota
	decimal[MONSTERLEVEL_BONUSEXP] = getGlobalDouble(L, "monsterLevelExp", 0.0); //pota
	decimal[MONSTERLEVEL_BONUSSPEED] = getGlobalDouble(L, "monsterLevelSpeed", 0.0); //pota
	decimal[MONSTERLEVEL_BONUSHEALTH] = getGlobalDouble(L, "monsterLevelHealth", 0.0); //pota
	decimal[MONSTERLEVEL_BONUSLOOT] = getGlobalDouble(L, "monsterLevelLoot", 0.0); //pota

	loaded = true;
	lua_close(L);
	return true;
}

bool ConfigManager::reload()
{
	bool result = load();
	if (transformToSHA1(getString(ConfigManager::MOTD)) != g_game.getMotdHash()) {
		g_game.incrementMotdNum();
	}
	return result;
}

const std::string& ConfigManager::getString(string_config_t what) const
{
	if (what >= LAST_STRING_CONFIG) {
		std::cout << "[Warning - ConfigManager::getString] Accessing invalid index: " << what << std::endl;
		return string[DUMMY_STR];
	}
	return string[what];
}

int32_t ConfigManager::getNumber(integer_config_t what) const
{
	if (what >= LAST_INTEGER_CONFIG) {
		std::cout << "[Warning - ConfigManager::getNumber] Accessing invalid index: " << what << std::endl;
		return 0;
	}
	return integer[what];
}

bool ConfigManager::getBoolean(boolean_config_t what) const
{
	if (what >= LAST_BOOLEAN_CONFIG) {
		std::cout << "[Warning - ConfigManager::getBoolean] Accessing invalid index: " << what << std::endl;
		return false;
	}
	return boolean[what];
}

double ConfigManager::getDouble(double_config_t what) const //pota
{
	if (what >= LAST_DOUBLE_CONFIG) {
		std::cout << "[Warning - ConfigManager::getDouble] Accessing invalid index: " << what << std::endl;
		return 0.0;
	}
	return decimal[what];
}

std::string ConfigManager::getGlobalString(lua_State* L, const char* identifier, const char* defaultValue)
{
	lua_getglobal(L, identifier);
	if (!lua_isstring(L, -1)) {
		return defaultValue;
	}

	size_t len = lua_strlen(L, -1);
	std::string ret(lua_tostring(L, -1), len);
	lua_pop(L, 1);
	return ret;
}

int32_t ConfigManager::getGlobalNumber(lua_State* L, const char* identifier, const int32_t defaultValue)
{
	lua_getglobal(L, identifier);
	if (!lua_isnumber(L, -1)) {
		return defaultValue;
	}

	int32_t val = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return val;
}

bool ConfigManager::getGlobalBoolean(lua_State* L, const char* identifier, const bool defaultValue)
{
	lua_getglobal(L, identifier);
	if (!lua_isboolean(L, -1)) {
		if (!lua_isstring(L, -1)) {
			return defaultValue;
		}

		size_t len = lua_strlen(L, -1);
		std::string ret(lua_tostring(L, -1), len);
		lua_pop(L, 1);
		return booleanString(ret);
	}

	int val = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return val != 0;
}

double ConfigManager::getGlobalDouble(lua_State* L, const char* identifier, const double defaultValue) //pota
{
	lua_getglobal(L, identifier);
	if (!lua_isnumber(L, -1)) {
		return defaultValue;
	}

	double val = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return val;
}

std::unordered_map<std::string, std::string> ConfigManager::loadEnvFile(const std::string& fileName)
{
	std::unordered_map<std::string, std::string> env;
	std::ifstream file(fileName);
	if (!file.is_open()) {
		return env;
	}

	std::string line;
	while (std::getline(file, line)) {
		line = trimEnvValue(line);
		if (line.empty() || line.front() == '#') {
			continue;
		}

		const size_t separator = line.find('=');
		if (separator == std::string::npos) {
			continue;
		}

		std::string key = trimEnvValue(line.substr(0, separator));
		if (key.empty()) {
			continue;
		}

		env[key] = parseEnvValue(line.substr(separator + 1));
	}

	return env;
}

std::string ConfigManager::getEnvString(const std::unordered_map<std::string, std::string>& env, const char* identifier, const char* defaultValue)
{
	auto it = env.find(identifier);
	if (it == env.end()) {
		return defaultValue;
	}
	return it->second;
}

int32_t ConfigManager::getEnvNumber(const std::unordered_map<std::string, std::string>& env, const char* identifier, const int32_t defaultValue)
{
	auto it = env.find(identifier);
	if (it == env.end()) {
		return defaultValue;
	}

	char* end = nullptr;
	errno = 0;
	const long value = std::strtol(it->second.c_str(), &end, 10);
	if (errno != 0 || end == it->second.c_str() || *end != '\0') {
		std::cout << "[Warning - ConfigManager::getEnvNumber] Invalid value for " << identifier << ": " << it->second << std::endl;
		return defaultValue;
	}

	return static_cast<int32_t>(value);
}

void ConfigManager::loadEnvConfig(const std::unordered_map<std::string, std::string>& env)
{
	string[IP] = getEnvString(env, "IP", "127.0.0.1");
	string[MYSQL_HOST] = getEnvString(env, "MYSQL_HOST", "127.0.0.1");
	string[MYSQL_USER] = getEnvString(env, "MYSQL_USER", "forgottenserver");
	string[MYSQL_PASS] = getEnvString(env, "MYSQL_PASS", "");
	string[MYSQL_DB] = getEnvString(env, "MYSQL_DB", "forgottenserver");
	string[MYSQL_SOCK] = getEnvString(env, "MYSQL_SOCK", "");
	string[RSA_P] = getEnvString(env, "RSA_P", "14299623962416399520070177382898895550795403345466153217470516082934737582776038882967213386204600674145392845853859217990626450972452084065728686565928113");
	string[RSA_Q] = getEnvString(env, "RSA_Q", "7630979195970404721891201847792002125535401292779123937207447574596692788513647179235335529307251350570728407373705564708871762033017096809910315212884101");

	integer[SQL_PORT] = getEnvNumber(env, "SQL_PORT", 3306);
	integer[GAME_PORT] = getEnvNumber(env, "GAME_PORT", 7172);
	integer[LOGIN_PORT] = getEnvNumber(env, "LOGIN_PORT", 7171);
	integer[STATUS_PORT] = getEnvNumber(env, "STATUS_PORT", 7171);
}
