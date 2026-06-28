// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../npc.hpp"

#include "../../core/logger.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern LuaEnvironment g_luaEnvironment;

NpcEventsHandler::NpcEventsHandler(const std::string& file, Npc* npc) :
	npc(npc), scriptInterface(npc->getScriptInterface())
{
	loaded = scriptInterface->loadFile("data/npc/scripts/" + file, npc) == 0;
	if (!loaded) {
		LOG_WARN("Scripts", "Could not load NPC script: " + file);
		LOG_ERROR("Lua", scriptInterface->getLastLuaError());
	} else {
		creatureSayEvent = scriptInterface->getEvent("onCreatureSay");
		creatureDisappearEvent = scriptInterface->getEvent("onCreatureDisappear");
		creatureAppearEvent = scriptInterface->getEvent("onCreatureAppear");
		creatureMoveEvent = scriptInterface->getEvent("onCreatureMove");
		playerCloseChannelEvent = scriptInterface->getEvent("onPlayerCloseChannel");
		playerEndTradeEvent = scriptInterface->getEvent("onPlayerEndTrade");
		thinkEvent = scriptInterface->getEvent("onThink");
	}
}

bool NpcEventsHandler::isLoaded() const
{
	return loaded;
}

void NpcEventsHandler::onCreatureAppear(Creature* creature)
{
	if (creatureAppearEvent == -1) {
		return;
	}

	//onCreatureAppear(creature)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - NpcScript::onCreatureAppear] Call stack overflow" << std::endl;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(creatureAppearEvent, scriptInterface);
	env->setNpc(npc);

	lua_State* L = scriptInterface->getLuaState();
	scriptInterface->pushFunction(creatureAppearEvent);
	LuaScriptInterface::pushUserdata<Creature>(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	scriptInterface->callFunction(1);
}

void NpcEventsHandler::onCreatureDisappear(Creature* creature)
{
	if (creatureDisappearEvent == -1) {
		return;
	}

	//onCreatureDisappear(creature)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - NpcScript::onCreatureDisappear] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(creatureDisappearEvent, scriptInterface);
	env->setNpc(npc);

	lua_State* L = scriptInterface->getLuaState();
	scriptInterface->pushFunction(creatureDisappearEvent);
	LuaScriptInterface::pushUserdata<Creature>(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	scriptInterface->callFunction(1);
}

void NpcEventsHandler::onCreatureMove(Creature* creature, const Position& oldPos, const Position& newPos)
{
	if (creatureMoveEvent == -1) {
		return;
	}

	//onCreatureMove(creature, oldPos, newPos)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - NpcScript::onCreatureMove] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(creatureMoveEvent, scriptInterface);
	env->setNpc(npc);

	lua_State* L = scriptInterface->getLuaState();
	scriptInterface->pushFunction(creatureMoveEvent);
	LuaScriptInterface::pushUserdata<Creature>(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	LuaScriptInterface::pushPosition(L, oldPos);
	LuaScriptInterface::pushPosition(L, newPos);
	scriptInterface->callFunction(3);
}

void NpcEventsHandler::onCreatureSay(Creature* creature, SpeakClasses type, const std::string& text)
{
	if (creatureSayEvent == -1) {
		return;
	}

	//onCreatureSay(creature, type, msg)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - NpcScript::onCreatureSay] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(creatureSayEvent, scriptInterface);
	env->setNpc(npc);

	lua_State* L = scriptInterface->getLuaState();
	scriptInterface->pushFunction(creatureSayEvent);
	LuaScriptInterface::pushUserdata<Creature>(L, creature);
	LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	lua_pushnumber(L, type);
	LuaScriptInterface::pushString(L, text);
	scriptInterface->callFunction(3);
}

void NpcEventsHandler::onPlayerTrade(Player* player, int32_t callback, uint16_t itemid,
                              uint8_t count, uint8_t amount, bool ignore, bool inBackpacks)
{
	if (callback == -1) {
		return;
	}

	//onBuy(player, itemid, count, amount, ignore, inbackpacks)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - NpcScript::onPlayerTrade] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(-1, scriptInterface);
	env->setNpc(npc);

	lua_State* L = scriptInterface->getLuaState();
	LuaScriptInterface::pushCallback(L, callback);
	LuaScriptInterface::pushUserdata<Player>(L, player);
	LuaScriptInterface::setMetatable(L, -1, "Player");
	lua_pushnumber(L, itemid);
	lua_pushnumber(L, count);
	lua_pushnumber(L, amount);
	LuaScriptInterface::pushBoolean(L, ignore);
	LuaScriptInterface::pushBoolean(L, inBackpacks);
	scriptInterface->callFunction(6);
}

void NpcEventsHandler::onPlayerCloseChannel(Player* player)
{
	if (playerCloseChannelEvent == -1) {
		return;
	}

	//onPlayerCloseChannel(player)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - NpcScript::onPlayerCloseChannel] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(playerCloseChannelEvent, scriptInterface);
	env->setNpc(npc);

	lua_State* L = scriptInterface->getLuaState();
	scriptInterface->pushFunction(playerCloseChannelEvent);
	LuaScriptInterface::pushUserdata<Player>(L, player);
	LuaScriptInterface::setMetatable(L, -1, "Player");
	scriptInterface->callFunction(1);
}

void NpcEventsHandler::onPlayerEndTrade(Player* player)
{
	if (playerEndTradeEvent == -1) {
		return;
	}

	//onPlayerEndTrade(player)
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - NpcScript::onPlayerEndTrade] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(playerEndTradeEvent, scriptInterface);
	env->setNpc(npc);

	lua_State* L = scriptInterface->getLuaState();
	scriptInterface->pushFunction(playerEndTradeEvent);
	LuaScriptInterface::pushUserdata<Player>(L, player);
	LuaScriptInterface::setMetatable(L, -1, "Player");
	scriptInterface->callFunction(1);
}

void NpcEventsHandler::onThink()
{
	if (thinkEvent == -1) {
		return;
	}

	//onThink()
	if (!scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - NpcScript::onThink] Call stack overflow" << std::endl;
		return;
	}

	ScriptEnvironment* env = scriptInterface->getScriptEnv();
	env->setScriptId(thinkEvent, scriptInterface);
	env->setNpc(npc);

	scriptInterface->pushFunction(thinkEvent);
	scriptInterface->callFunction(0);
}
