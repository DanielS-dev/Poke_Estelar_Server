// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"
#include <csignal>

#include "signals.hpp"
#include "../core/tasks.hpp"
#include "../game/game.hpp"
#include "../scripting/actions/actions.hpp"
#include "../config/configmanager.hpp"
#include "../game/spells/spells.hpp"
#include "../scripting/talkaction.hpp"
#include "../game/movement/movement.hpp"
#include "../game/weapons/weapons.hpp"
#include "../game/raids/raids.hpp"
#include "../game/quests/quests.hpp"
#include "../entities/mounts.hpp"
#include "../scripting/globalevent.hpp"
#include "../entities/monster.hpp"
#include "../scripting/events/events.hpp"
#include "../core/scheduler.hpp"
#include "../core/logger.hpp"
#include "../persistence/databasetasks.hpp"


extern Scheduler g_scheduler;
extern DatabaseTasks g_databaseTasks;
extern Dispatcher g_dispatcher;

extern ConfigManager g_config;
extern Actions* g_actions;
extern Monsters g_monsters;
extern TalkActions* g_talkActions;
extern MoveEvents* g_moveEvents;
extern Spells* g_spells;
extern Weapons* g_weapons;
extern Game g_game;
extern CreatureEvents* g_creatureEvents;
extern GlobalEvents* g_globalEvents;
extern Events* g_events;
extern Chat* g_chat;
extern LuaEnvironment g_luaEnvironment;

using ErrorCode = boost::system::error_code;

Signals::Signals(boost::asio::io_context& service) :
	set(service)
{
	set.add(SIGINT);
	set.add(SIGTERM);
#ifndef _WIN32
	set.add(SIGUSR1);
	set.add(SIGHUP);
#else
	// This must be a blocking call as Windows calls it in a new thread and terminates
	// the process when the handler returns (or after 5 seconds, whichever is earlier).
	// On Windows it is called in a new thread.
	signal(SIGBREAK, dispatchSignalHandler);
#endif

	asyncWait();
}

void Signals::asyncWait()
{
	set.async_wait([this] (ErrorCode err, int signal) {
		if (err) {
			std::cerr << "Signal handling error: "  << err.message() << std::endl;
			return;
		}
		dispatchSignalHandler(signal);
		asyncWait();
	});
}

// On Windows this function does not need to be signal-safe,
// as it is called in a new thread.
// https://github.com/otland/forgottenserver/pull/2473
void Signals::dispatchSignalHandler(int signal)
{
	switch(signal) {
		case SIGINT: //Shuts the server down
			g_dispatcher.addTask(createTask(sigintHandler));
			break;
		case SIGTERM: //Shuts the server down
			g_dispatcher.addTask(createTask(sigtermHandler));
			break;
#ifndef _WIN32
		case SIGHUP: //Reload config/data
			g_dispatcher.addTask(createTask(sighupHandler));
			break;
		case SIGUSR1: //Saves game state
			g_dispatcher.addTask(createTask(sigusr1Handler));
			break;
#else
		case SIGBREAK: //Shuts the server down
			g_dispatcher.addTask(createTask(sigbreakHandler));
			// hold the thread until other threads end
			g_scheduler.join();
			g_databaseTasks.join();
			g_dispatcher.join();
			break;
#endif
		default:
			break;
	}
}

void Signals::sigbreakHandler()
{
	//Dispatcher thread
	LOG_INFO("Server", "SIGBREAK received, shutting game server down.");
	g_game.setGameState(GAME_STATE_SHUTDOWN);
}

void Signals::sigtermHandler()
{
	//Dispatcher thread
	LOG_INFO("Server", "SIGTERM received, shutting game server down.");
	g_game.setGameState(GAME_STATE_SHUTDOWN);
}

void Signals::sigusr1Handler()
{
	//Dispatcher thread
	LOG_INFO("Server", "SIGUSR1 received, saving the game state.");
	g_game.saveGameState();
}

void Signals::sighupHandler()
{
	//Dispatcher thread
	LOG_INFO("Server", "SIGHUP received, reloading config files.");

	g_actions->reload();
	LOG_INFO("Server", "Reloaded actions.");

	g_config.reload();
	LOG_INFO("Server", "Reloaded config.");

	g_creatureEvents->reload();
	LOG_INFO("Server", "Reloaded creature scripts.");

	g_moveEvents->reload();
	LOG_INFO("Server", "Reloaded movements.");

	Npcs::reload();
	LOG_INFO("Server", "Reloaded NPCs.");

	g_game.raids.reload();
	g_game.raids.startup();
	LOG_INFO("Server", "Reloaded raids.");

	g_spells->reload();
	LOG_INFO("Server", "Reloaded spells.");

	g_monsters.reload();
	LOG_INFO("Server", "Reloaded monsters.");

	g_talkActions->reload();
	LOG_INFO("Server", "Reloaded talk actions.");

	Item::items.reload();
	LOG_INFO("Server", "Reloaded items.");

	g_weapons->reload();
	g_weapons->loadDefaults();
	LOG_INFO("Server", "Reloaded weapons.");

	g_game.quests.reload();
	LOG_INFO("Server", "Reloaded quests.");

	g_game.mounts.reload();
	LOG_INFO("Server", "Reloaded mounts.");

	g_globalEvents->reload();
	LOG_INFO("Server", "Reloaded globalevents.");

	g_events->load();
	LOG_INFO("Server", "Reloaded events.");

	g_chat->load();
	LOG_INFO("Server", "Reloaded chat channels.");

	g_luaEnvironment.loadFile("data/global.lua");
	LOG_INFO("Server", "Reloaded global.lua.");

	lua_gc(g_luaEnvironment.getLuaState(), LUA_GCCOLLECT, 0);
}

void Signals::sigintHandler()
{
	//Dispatcher thread
	LOG_INFO("Server", "SIGINT received, shutting game server down.");
	g_game.setGameState(GAME_STATE_SHUTDOWN);
}
