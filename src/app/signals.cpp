// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.h"
#include <csignal>

#include "signals.h"
#include "../core/tasks.h"
#include "../game/game.h"
#include "../scripting/actions.h"
#include "../config/configmanager.h"
#include "../game/spells.h"
#include "../scripting/talkaction.h"
#include "../game/movement.h"
#include "../game/weapons.h"
#include "../game/raids.h"
#include "../game/quests.h"
#include "../entities/mounts.h"
#include "../scripting/globalevent.h"
#include "../entities/monster.h"
#include "../scripting/events.h"
#include "../core/scheduler.h"
#include "../persistence/databasetasks.h"


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
	std::cout << "SIGBREAK received, shutting game server down..." << std::endl;
	g_game.setGameState(GAME_STATE_SHUTDOWN);
}

void Signals::sigtermHandler()
{
	//Dispatcher thread
	std::cout << "SIGTERM received, shutting game server down..." << std::endl;
	g_game.setGameState(GAME_STATE_SHUTDOWN);
}

void Signals::sigusr1Handler()
{
	//Dispatcher thread
	std::cout << "SIGUSR1 received, saving the game state..." << std::endl;
	g_game.saveGameState();
}

void Signals::sighupHandler()
{
	//Dispatcher thread
	std::cout << "SIGHUP received, reloading config files..." << std::endl;

	g_actions->reload();
	std::cout << "Reloaded actions." << std::endl;

	g_config.reload();
	std::cout << "Reloaded config." << std::endl;

	g_creatureEvents->reload();
	std::cout << "Reloaded creature scripts." << std::endl;

	g_moveEvents->reload();
	std::cout << "Reloaded movements." << std::endl;

	Npcs::reload();
	std::cout << "Reloaded npcs." << std::endl;

	g_game.raids.reload();
	g_game.raids.startup();
	std::cout << "Reloaded raids." << std::endl;

	g_spells->reload();
	std::cout << "Reloaded monsters." << std::endl;

	g_monsters.reload();
	std::cout << "Reloaded spells." << std::endl;

	g_talkActions->reload();
	std::cout << "Reloaded talk actions." << std::endl;

	Item::items.reload();
	std::cout << "Reloaded items." << std::endl;

	g_weapons->reload();
	g_weapons->loadDefaults();
	std::cout << "Reloaded weapons." << std::endl;

	g_game.quests.reload();
	std::cout << "Reloaded quests." << std::endl;

	g_game.mounts.reload();
	std::cout << "Reloaded mounts." << std::endl;

	g_globalEvents->reload();
	std::cout << "Reloaded globalevents." << std::endl;

	g_events->load();
	std::cout << "Reloaded events." << std::endl;

	g_chat->load();
	std::cout << "Reloaded chatchannels." << std::endl;

	g_luaEnvironment.loadFile("data/global.lua");
	std::cout << "Reloaded global.lua." << std::endl;

	lua_gc(g_luaEnvironment.getLuaState(), LUA_GCCOLLECT, 0);
}

void Signals::sigintHandler()
{
	//Dispatcher thread
	std::cout << "SIGINT received, shutting game server down..." << std::endl;
	g_game.setGameState(GAME_STATE_SHUTDOWN);
}
