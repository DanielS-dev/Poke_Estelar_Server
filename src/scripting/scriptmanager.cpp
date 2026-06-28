// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "scriptmanager.hpp"

#include "actions/actions.hpp"
#include "../core/logger.hpp"
#include "../game/chat/chat.hpp"
#include "talkaction.hpp"
#include "../game/spells/spells.hpp"
#include "../game/movement/movement.hpp"
#include "../game/weapons/weapons.hpp"
#include "globalevent.hpp"
#include "events/events.hpp"

Actions* g_actions = nullptr;
CreatureEvents* g_creatureEvents = nullptr;
Chat* g_chat = nullptr;
Events* g_events = nullptr;
GlobalEvents* g_globalEvents = nullptr;
Spells* g_spells = nullptr;
TalkActions* g_talkActions = nullptr;
MoveEvents* g_moveEvents = nullptr;
Weapons* g_weapons = nullptr;

extern LuaEnvironment g_luaEnvironment;

ScriptingManager::~ScriptingManager()
{
	delete g_events;
	delete g_weapons;
	delete g_spells;
	delete g_actions;
	delete g_talkActions;
	delete g_moveEvents;
	delete g_chat;
	delete g_creatureEvents;
	delete g_globalEvents;
}

bool ScriptingManager::loadScriptSystems()
{
	if (g_luaEnvironment.loadFile("data/global.lua") == -1) {
		LOG_WARN("Scripts", "Could not load data/global.lua");
	}

	g_chat = new Chat();

	g_weapons = new Weapons();
	if (!g_weapons->loadFromXml()) {
		LOG_FATAL("Scripts", "Unable to load weapons.");
		return false;
	}

	g_weapons->loadDefaults();

	g_spells = new Spells();
	if (!g_spells->loadFromXml()) {
		LOG_FATAL("Scripts", "Unable to load spells.");
		return false;
	}

	g_actions = new Actions();
	if (!g_actions->loadFromXml()) {
		LOG_FATAL("Scripts", "Unable to load actions.");
		return false;
	}

	g_talkActions = new TalkActions();
	if (!g_talkActions->loadFromXml()) {
		LOG_FATAL("Scripts", "Unable to load talk actions.");
		return false;
	}

	g_moveEvents = new MoveEvents();
	if (!g_moveEvents->loadFromXml()) {
		LOG_FATAL("Scripts", "Unable to load move events.");
		return false;
	}

	g_creatureEvents = new CreatureEvents();
	if (!g_creatureEvents->loadFromXml()) {
		LOG_FATAL("Scripts", "Unable to load creature events.");
		return false;
	}

	g_globalEvents = new GlobalEvents();
	if (!g_globalEvents->loadFromXml()) {
		LOG_FATAL("Scripts", "Unable to load global events.");
		return false;
	}

	g_events = new Events();
	if (!g_events->load()) {
		LOG_FATAL("Scripts", "Unable to load events.");
		return false;
	}

	return true;
}
