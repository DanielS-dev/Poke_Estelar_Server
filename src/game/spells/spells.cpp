// This file is part of The Forgotten Server.

// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../game.hpp"
#include "../../core/logger.hpp"
#include "../../core/tools/positionTools.hpp"
#include "../../core/tools/stringsTools.hpp"

#include "spells.hpp"

extern Game g_game;
Spells::Spells()
{
	scriptInterface.initState();
}

Spells::~Spells()
{
	clear();
}

TalkActionResult_t Spells::playerSaySpell(Player* player, std::string& words)
{
	std::string str_words = words;

	//strip trailing spaces
	trimString(str_words);

	InstantSpell* instantSpell = getInstantSpell(str_words);
	if (!instantSpell) {
		return TALKACTION_CONTINUE;
	}

	std::string param;

	if (instantSpell->getHasParam()) {
		size_t spellLen = instantSpell->getWords().length();
		size_t paramLen = str_words.length() - spellLen;
		std::string paramText = str_words.substr(spellLen, paramLen);
		if (!paramText.empty() && paramText.front() == ' ') {
			size_t loc1 = paramText.find('"', 1);
			if (loc1 != std::string::npos) {
				size_t loc2 = paramText.find('"', loc1 + 1);
				if (loc2 == std::string::npos) {
					loc2 = paramText.length();
				} else if (paramText.find_last_not_of(' ') != loc2) {
					return TALKACTION_CONTINUE;
				}

				param = paramText.substr(loc1 + 1, loc2 - loc1 - 1);
			} else {
				trimString(paramText);
				loc1 = paramText.find(' ', 0);
				if (loc1 == std::string::npos) {
					param = paramText;
				} else {
					return TALKACTION_CONTINUE;
				}
			}
		}
	}

	if (instantSpell->playerCastInstant(player, param)) {
		words = instantSpell->getWords();

		if (instantSpell->getHasParam() && !param.empty()) {
			words += " \"" + param + "\"";
		}

		return TALKACTION_BREAK;
	}

	return TALKACTION_FAILED;
}

void Spells::clear()
{
	for (const auto& it : runes) {
		delete it.second;
	}
	runes.clear();

	for (const auto& it : instants) {
		delete it.second;
	}
	instants.clear();

	scriptInterface.reInitState();
}

LuaScriptInterface& Spells::getScriptInterface()
{
	return scriptInterface;
}

std::string Spells::getScriptBaseName() const
{
	return "spells";
}

Event* Spells::getEvent(const std::string& nodeName)
{
	if (strcasecmp(nodeName.c_str(), "rune") == 0) {
		return new RuneSpell(&scriptInterface);
	} else if (strcasecmp(nodeName.c_str(), "instant") == 0) {
		return new InstantSpell(&scriptInterface);
	} else if (strcasecmp(nodeName.c_str(), "conjure") == 0) {
		return new ConjureSpell(&scriptInterface);
	}
	return nullptr;
}

bool Spells::registerEvent(Event* event, const pugi::xml_node&)
{
	InstantSpell* instant = dynamic_cast<InstantSpell*>(event);
	if (instant) {
		auto result = instants.emplace(instant->getWords(), instant);
		if (!result.second) {
			LOG_WARN("Scripts", "Duplicate instant spell registration for words \"" + instant->getWords() + "\"");
		}
		return result.second;
	}

	RuneSpell* rune = dynamic_cast<RuneSpell*>(event);
	if (rune) {
		auto result = runes.emplace(rune->getRuneItemId(), rune);
		if (!result.second) {
			LOG_WARN("Scripts", "Duplicate rune registration for itemid " + std::to_string(rune->getRuneItemId()));
		}
		return result.second;
	}

	return false;
}

Spell* Spells::getSpellByName(const std::string& name)
{
	Spell* spell = getRuneSpellByName(name);
	if (!spell) {
		spell = getInstantSpellByName(name);
	}
	return spell;
}

RuneSpell* Spells::getRuneSpell(uint32_t id)
{
	auto it = runes.find(id);
	if (it == runes.end()) {
		return nullptr;
	}
	return it->second;
}

RuneSpell* Spells::getRuneSpellByName(const std::string& name)
{
	for (const auto& it : runes) {
		if (strcasecmp(it.second->getName().c_str(), name.c_str()) == 0) {
			return it.second;
		}
	}
	return nullptr;
}

InstantSpell* Spells::getInstantSpell(const std::string& words)
{
	InstantSpell* result = nullptr;

	for (const auto& it : instants) {
		InstantSpell* instantSpell = it.second;

		const std::string& instantSpellWords = instantSpell->getWords();
		size_t spellLen = instantSpellWords.length();
		if (strncasecmp(instantSpellWords.c_str(), words.c_str(), spellLen) == 0) {
			if (!result || spellLen > result->getWords().length()) {
				result = instantSpell;
				if (words.length() == spellLen) {
					break;
				}
			}
		}
	}

	if (result) {
		const std::string& resultWords = result->getWords();
		if (words.length() > resultWords.length()) {
			if (!result->getHasParam()) {
				return nullptr;
			}

			size_t spellLen = resultWords.length();
			size_t paramLen = words.length() - spellLen;
			if (paramLen < 2 || words[spellLen] != ' ') {
				return nullptr;
			}
		}
		return result;
	}
	return nullptr;
}

uint32_t Spells::getInstantSpellCount(const Player* player) const
{
	uint32_t count = 0;
	for (const auto& it : instants) {
		InstantSpell* instantSpell = it.second;
		if (instantSpell->canCast(player)) {
			++count;
		}
	}
	return count;
}

InstantSpell* Spells::getInstantSpellByIndex(const Player* player, uint32_t index)
{
	uint32_t count = 0;
	for (const auto& it : instants) {
		InstantSpell* instantSpell = it.second;
		if (instantSpell->canCast(player)) {
			if (count == index) {
				return instantSpell;
			}
			++count;
		}
	}
	return nullptr;
}

InstantSpell* Spells::getInstantSpellByName(const std::string& name)
{
	for (const auto& it : instants) {
		if (strcasecmp(it.second->getName().c_str(), name.c_str()) == 0) {
			return it.second;
		}
	}
	return nullptr;
}

Position Spells::getCasterPosition(Creature* creature, Direction dir)
{
	return getNextPosition(dir, creature->getPosition());
}
