// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../monsters.hpp"
#include "../monster.hpp"
#include "../player.hpp"
#include "../../config/configmanager.hpp"
#include "../../core/logger.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/xmlErro.hpp"
#include "../../game/combat/combat.hpp"
#include "../../game/game.hpp"
#include "../../game/spells/spells.hpp"
#include "../../game/weapons/weapons.hpp"

extern Game g_game;
extern Spells* g_spells;
extern Monsters g_monsters;
extern ConfigManager g_config;

spellBlock_t::~spellBlock_t()
{
	if (combatSpell) {
		delete spell;
	}
}

bool Monsters::loadFromXml(bool reloading /*= false*/)
{
	allMonsters = {}; //pota
	uint32_t loadedMonsterCount = 0;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/monster/monsters.xml");
	if (!result) {
		printXMLError("Error - Monsters::loadFromXml", "data/monster/monsters.xml", result);
		return false;
	}

	loaded = true;

	std::list<std::pair<MonsterType*, std::string>> monsterScriptList;
	for (auto monsterNode : doc.child("monsters").children()) {
		std::string name = monsterNode.attribute("name").as_string(); //pota
		if (loadMonster("data/monster/" + std::string(monsterNode.attribute("file").as_string()), name, monsterScriptList, reloading)) {
			++loadedMonsterCount;
		}
		allMonsters.push_back(name); //pota
	}

	if (!monsterScriptList.empty()) {
		if (!scriptInterface) {
			scriptInterface.reset(new LuaScriptInterface("Monster Interface"));
			scriptInterface->initState();
		}

		for (const auto& scriptEntry : monsterScriptList) {
			MonsterType* mType = scriptEntry.first;
			if (scriptInterface->loadFile("data/monster/scripts/" + scriptEntry.second) == 0) {
				mType->info.scriptInterface = scriptInterface.get();
				mType->info.creatureAppearEvent = scriptInterface->getEvent("onCreatureAppear");
				mType->info.creatureDisappearEvent = scriptInterface->getEvent("onCreatureDisappear");
				mType->info.creatureMoveEvent = scriptInterface->getEvent("onCreatureMove");
				mType->info.creatureSayEvent = scriptInterface->getEvent("onCreatureSay");
				mType->info.thinkEvent = scriptInterface->getEvent("onThink");
			} else {
				LOG_WARN("Monsters", "Could not load monster script: " + scriptEntry.second);
				LOG_ERROR("Lua", scriptInterface->getLastLuaError());
			}
		}
	}
	LOG_INFO("Monsters", "Loaded " + std::to_string(loadedMonsterCount) + " monsters from data/monster/monsters.xml");
	return true;
}

bool Monsters::reload()
{
	loaded = false;

	scriptInterface.reset();

	return loadFromXml(true);
}

MonsterType* Monsters::getMonsterType(const std::string& name)
{
	auto it = monsters.find(asLowerCaseString(name));

	if (it == monsters.end()) {
		return nullptr;
	}
	return &it->second;
}
