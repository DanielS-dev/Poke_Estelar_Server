// This file is part of The Forgotten Server.

// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../game.hpp"
#include "../../core/pugicast.hpp"
#include "../../items/items.hpp"

#include "conjureSpell.hpp"

extern Game g_game;
std::string ConjureSpell::getScriptEventName() const
{
	return "onCastSpell";
}

bool ConjureSpell::configureEvent(const pugi::xml_node& node)
{
	if (!InstantSpell::configureEvent(node)) {
		return false;
	}

	pugi::xml_attribute attr;
	if ((attr = node.attribute("conjureId"))) {
		conjureId = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = node.attribute("conjureCount"))) {
		conjureCount = pugi::cast<uint32_t>(attr.value());
	} else if (conjureId != 0) {
		// load default charges from items.xml
		const ItemType& it = Item::items[conjureId];
		if (it.charges != 0) {
			conjureCount = it.charges;
		}
	}

	if ((attr = node.attribute("reagentId"))) {
		reagentId = pugi::cast<uint32_t>(attr.value());
	}

	return true;
}

bool ConjureSpell::loadFunction(const pugi::xml_attribute&)
{
	scripted = false;
	return true;
}

bool ConjureSpell::conjureItem(Creature* creature) const
{
	Player* player = creature->getPlayer();
	if (!player) {
		return false;
	}

	if (reagentId != 0 && !player->removeItemOfType(reagentId, 1, -1)) {
		player->sendCancelMessage(RETURNVALUE_YOUNEEDAMAGICITEMTOCASTSPELL);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		return false;
	}

	Item* newItem = Item::CreateItem(conjureId, conjureCount);
	if (!newItem) {
		return false;
	}

	ReturnValue ret = g_game.internalPlayerAddItem(player, newItem);
	if (ret != RETURNVALUE_NOERROR) {
		player->sendCancelMessage(ret);
		g_game.addMagicEffect(player->getPosition(), CONST_ME_POFF);
		delete newItem;
		return false;
	}

	g_game.startDecay(newItem);

	postCastSpell(player);
	g_game.addMagicEffect(player->getPosition(), CONST_ME_MAGIC_RED);
	return true;
}

bool ConjureSpell::playerCastInstant(Player* player, std::string& param)
{
	if (!playerSpellCheck(player)) {
		return false;
	}

	if (scripted) {
		LuaVariant var;
		var.type = VARIANT_STRING;
		var.text = param;
		return executeCastSpell(player, var);
	}
	return conjureItem(player);
}
