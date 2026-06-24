// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../npc.hpp"

#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/game.hpp"

extern Game g_game;
extern LuaEnvironment g_luaEnvironment;

uint32_t Npc::npcAutoID = 0x80000000;
NpcScriptInterface* Npc::scriptInterface = nullptr;

void Npcs::reload()
{
	const std::map<uint32_t, Npc*>& npcs = g_game.getNpcs();
	for (const auto& it : npcs) {
		it.second->closeAllShopWindows();
	}

	delete Npc::scriptInterface;
	Npc::scriptInterface = nullptr;

	for (const auto& it : npcs) {
		it.second->reload();
	}
}

Npc* Npc::createNpc(const std::string& name)
{
	std::unique_ptr<Npc> npc(new Npc(name));
	if (!npc->load()) {
		return nullptr;
	}
	return npc.release();
}

Npc::Npc(const std::string& name) :
	Creature(),
	filename("data/npc/" + name + ".xml"),
	npcEventHandler(nullptr),
	masterRadius(-1),
	loaded(false)
{
	reset();
}

Npc::~Npc()
{
	reset();
}

void Npc::addList()
{
	g_game.addNpc(this);
}

void Npc::removeList()
{
	g_game.removeNpc(this);
}

bool Npc::load()
{
	if (loaded) {
		return true;
	}

	reset();

	if (!scriptInterface) {
		scriptInterface = new NpcScriptInterface();
		scriptInterface->loadNpcLib("data/npc/lib/npc.lua");
	}

	loaded = loadFromXml();
	return loaded;
}

void Npc::reset()
{
	loaded = false;
	walkTicks = 1500;
	floorChange = false;
	attackable = false;
	ignoreHeight = true;
	focusCreature = 0;
	speechBubble = SPEECHBUBBLE_NONE;

	delete npcEventHandler;
	npcEventHandler = nullptr;

	parameters.clear();
	shopPlayerSet.clear();
}

void Npc::reload()
{
	reset();
	load();

	// Simulate that the creature is placed on the map again.
	if (npcEventHandler) {
		npcEventHandler->onCreatureAppear(this);
	}

	if (walkTicks > 0) {
		addEventWalk();
	}
}

bool Npc::canSee(const Position& pos) const
{
	if (pos.z != getPosition().z) {
		return false;
	}
	return Creature::canSee(getPosition(), pos, 3, 3);
}

std::string Npc::getDescription(int32_t) const
{
	std::string descr;
	descr.reserve(name.length() + 1);
	descr.assign(name);
	descr.push_back('.');
	return descr;
}

void Npc::doSay(const std::string& text)
{
	g_game.internalCreatureSay(this, TALKTYPE_SAY, text, false);
}

void Npc::doSayToPlayer(Player* player, const std::string& text)
{
	if (player) {
		player->sendCreatureSay(this, TALKTYPE_PRIVATE_NP, text);
		player->onCreatureSay(this, TALKTYPE_PRIVATE_NP, text);
	}
}

NpcScriptInterface* Npc::getScriptInterface()
{
	return scriptInterface;
}

