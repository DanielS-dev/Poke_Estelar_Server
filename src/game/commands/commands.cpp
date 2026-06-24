// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "commandLoader.hpp"
#include "commandRules.hpp"
#include "commands.hpp"
#include "../../entities/player.hpp"
#include "../../entities/npc.hpp"
#include "../game.hpp"
#include "../../scripting/actions.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../../config/configmanager.hpp"
#include "../spells/spells.hpp"
#include "../movement/movement.hpp"
#include "../weapons/weapons.hpp"
#include "../../scripting/globalevent.hpp"
#include "../../entities/monster.hpp"
#include "../../core/scheduler.hpp"
#include "../../scripting/events.hpp"
#include "../../core/tools/stringsTools.hpp"

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

s_defcommands Commands::defined_commands[] = {
	// TODO: move all commands to talkactions

	//admin commands
	{"/reload", &Commands::reloadInfo},
	{"/raid", &Commands::forceRaid},

	// player commands
	{"!sellhouse", &Commands::sellHouse}
};

Commands::Commands()
{
	// set up command map
	for (auto& command : defined_commands) {
		commandMap[command.name] = new Command(command.f, 1, ACCOUNT_TYPE_GOD, true);
	}
}

Commands::~Commands()
{
	for (const auto& it : commandMap) {
		delete it.second;
	}
}

bool Commands::loadFromXml()
{
	return CommandLoader::loadFromXml(*this);
}

bool Commands::reload()
{
	for (const auto& it : commandMap) {
		Command* command = it.second;
		command->groupId = 1;
		command->accountType = ACCOUNT_TYPE_GOD;
		command->log = true;
	}

	g_game.resetCommandTag();
	return loadFromXml();
}

bool Commands::exeCommand(Player& player, const std::string& cmd)
{
	std::string str_command;
	std::string str_param;

	std::string::size_type loc = cmd.find(' ', 0);
	if (loc != std::string::npos) {
		str_command = std::string(cmd, 0, loc);
		str_param = std::string(cmd, (loc + 1), cmd.size() - loc - 1);
	} else {
		str_command = cmd;
	}

	//find command
	auto it = commandMap.find(str_command);
	if (it == commandMap.end()) {
		return false;
	}

	Command* command = it->second;
	if (!CommandRules::canExecute(player, *command)) {
		return false;
	}

	//execute command
	CommandFunc cfunc = command->f;
	(this->*cfunc)(player, str_param);

	if (command->log) {
		CommandRules::logCommand(player, cmd);
	}
	return true;
}

void Commands::reloadInfo(Player& player, const std::string& param)
{
	std::string tmpParam = asLowerCaseString(param);
	if (tmpParam == "action" || tmpParam == "actions") {
		g_actions->reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded actions.");
	} else if (tmpParam == "config" || tmpParam == "configuration") {
		g_config.reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded config.");
	} else if (tmpParam == "command" || tmpParam == "commands") {
		reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded commands.");
	} else if (tmpParam == "creaturescript" || tmpParam == "creaturescripts") {
		g_creatureEvents->reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded creature scripts.");
	} else if (tmpParam == "monster" || tmpParam == "monsters") {
		g_monsters.reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded monsters.");
	} else if (tmpParam == "move" || tmpParam == "movement" || tmpParam == "movements"
	           || tmpParam == "moveevents" || tmpParam == "moveevent") {
		g_moveEvents->reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded movements.");
	} else if (tmpParam == "npc" || tmpParam == "npcs") {
		Npcs::reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded npcs.");
	} else if (tmpParam == "raid" || tmpParam == "raids") {
		g_game.raids.reload();
		g_game.raids.startup();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded raids.");
	} else if (tmpParam == "spell" || tmpParam == "spells") {
		g_spells->reload();
		g_monsters.reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded spells.");
	} else if (tmpParam == "talk" || tmpParam == "talkaction" || tmpParam == "talkactions") {
		g_talkActions->reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded talk actions.");
	} else if (tmpParam == "items") {
		Item::items.reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded items.");
	} else if (tmpParam == "weapon" || tmpParam == "weapons") {
		g_weapons->reload();
		g_weapons->loadDefaults();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded weapons.");
	} else if (tmpParam == "quest" || tmpParam == "quests") {
		g_game.quests.reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded quests.");
	} else if (tmpParam == "mount" || tmpParam == "mounts") {
		g_game.mounts.reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded mounts.");
	} else if (tmpParam == "globalevents" || tmpParam == "globalevent") {
		g_globalEvents->reload();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded globalevents.");
	} else if (tmpParam == "events") {
		g_events->load();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded events.");
	} else if (tmpParam == "chat" || tmpParam == "channel" || tmpParam == "chatchannels") {
		g_chat->load();
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded chatchannels.");
	} else if (tmpParam == "global") {
		g_luaEnvironment.loadFile("data/global.lua");
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reloaded global.lua.");
	} else {
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Reload type not found.");
	}
	lua_gc(g_luaEnvironment.getLuaState(), LUA_GCCOLLECT, 0);
}

void Commands::sellHouse(Player& player, const std::string& param)
{
	Player* tradePartner = g_game.getPlayerByName(param);
	if (!tradePartner || tradePartner == &player) {
		player.sendCancelMessage("Trade player not found.");
		return;
	}

	if (!Position::areInRange<2, 2, 0>(tradePartner->getPosition(), player.getPosition())) {
		player.sendCancelMessage("Trade player is too far away.");
		return;
	}

	if (!tradePartner->isPremium()) {
		player.sendCancelMessage("Trade player does not have a premium account.");
		return;
	}

	HouseTile* houseTile = dynamic_cast<HouseTile*>(player.getTile());
	if (!houseTile) {
		player.sendCancelMessage("You must stand in your house to initiate the trade.");
		return;
	}

	House* house = houseTile->getHouse();
	if (!house || house->getOwner() != player.getGUID()) {
		player.sendCancelMessage("You don't own this house.");
		return;
	}

	if (g_game.map.houses.getHouseByPlayerId(tradePartner->getGUID())) {
		player.sendCancelMessage("Trade player already owns a house.");
		return;
	}

	if (IOLoginData::hasBiddedOnHouse(tradePartner->getGUID())) {
		player.sendCancelMessage("Trade player is currently the highest bidder of an auctioned house.");
		return;
	}

	Item* transferItem = house->getTransferItem();
	if (!transferItem) {
		player.sendCancelMessage("You can not trade this house.");
		return;
	}

	transferItem->getParent()->setParent(&player);

	if (!g_game.internalStartTrade(&player, tradePartner, transferItem)) {
		house->resetTransferItem();
	}
}

void Commands::forceRaid(Player& player, const std::string& param)
{
	Raid* raid = g_game.raids.getRaidByName(param);
	if (!raid || !raid->isLoaded()) {
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "No such raid exists.");
		return;
	}

	if (g_game.raids.getRunning()) {
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Another raid is already being executed.");
		return;
	}

	g_game.raids.setRunning(raid);

	RaidEvent* event = raid->getNextRaidEvent();
	if (!event) {
		player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "The raid does not contain any data.");
		return;
	}

	raid->setState(RAIDSTATE_EXECUTING);

	uint32_t ticks = event->getDelay();
	if (ticks > 0) {
		g_scheduler.addEvent(createSchedulerTask(ticks, std::bind(&Raid::executeRaidEvent, raid, event)));
	} else {
		g_dispatcher.addTask(createTask(std::bind(&Raid::executeRaidEvent, raid, event)));
	}

	player.sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Raid started.");
}
