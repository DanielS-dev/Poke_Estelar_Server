// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <boost/range/adaptor/reversed.hpp>

#include "../luascript.hpp"
#include "../../events/events.hpp"
#include "../../../game/chat/chat.hpp"
#include "../../../entities/player.hpp"
#include "../../../game/game.hpp"
#include "../../../network/protocolstatus.hpp"
#include "../../../game/spells/spells.hpp"
#include "../../../persistence/login/iologindata.hpp"
#include "../../../config/configmanager.hpp"
#include "../../../world/teleport.hpp"
#include "../../../persistence/databasemanager.hpp"
#include "../../../world/bed.hpp"
#include "../../../entities/monster.hpp"
#include "../../../core/scheduler.hpp"
#include "../../../persistence/databasetasks.hpp"
#include "../../../core/tools/random.hpp"
#include "../../../core/tools/gameEnumTools.hpp"
#include "../../../core/tools/returnMessageTools.hpp"
#include "../../../core/tools/stringsTools.hpp"

extern Chat* g_chat;
extern Game g_game;
extern Monsters g_monsters;
extern ConfigManager g_config;
extern Vocations g_vocations;
extern Spells* g_spells;
extern Events* g_events;

#define registerEnum(value) { std::string enumName = #value; registerGlobalVariable(enumName.substr(enumName.find_last_of(':') + 1), value); }
#define registerEnumIn(tableName, value) { std::string enumName = #value; registerVariable(tableName, enumName.substr(enumName.find_last_of(':') + 1), value); }

void LuaScriptInterface::registerFunctions()
{

	//doCreatureCastSpell(creature, spellName)
	lua_register(luaState, "doCreatureCastSpell", LuaScriptInterface::luaDoCreatureCastSpell);

	//getMonstersName()
	lua_register(luaState, "getMonstersName", LuaScriptInterface::luaGetMonstersName); //pota

	//getPlayerFlagValue(cid, flag)
	lua_register(luaState, "getPlayerFlagValue", LuaScriptInterface::luaGetPlayerFlagValue);

	//getPlayerInstantSpellCount(cid)
	lua_register(luaState, "getPlayerInstantSpellCount", LuaScriptInterface::luaGetPlayerInstantSpellCount);

	//getPlayerInstantSpellInfo(cid, index)
	lua_register(luaState, "getPlayerInstantSpellInfo", LuaScriptInterface::luaGetPlayerInstantSpellInfo);

	//doPlayerAddItem(uid, itemid, <optional: default: 1> count/subtype)
	//doPlayerAddItem(cid, itemid, <optional: default: 1> count, <optional: default: 1> canDropOnMap, <optional: default: 1>subtype)
	//Returns uid of the created item
	lua_register(luaState, "doPlayerAddItem", LuaScriptInterface::luaDoPlayerAddItem);

	//doCreateItem(itemid, type/count, pos)
	//Returns uid of the created item, only works on tiles.
	lua_register(luaState, "doCreateItem", LuaScriptInterface::luaDoCreateItem);

	//doCreateItemEx(itemid, <optional> count/subtype)
	lua_register(luaState, "doCreateItemEx", LuaScriptInterface::luaDoCreateItemEx);

	//doTileAddItemEx(pos, uid)
	lua_register(luaState, "doTileAddItemEx", LuaScriptInterface::luaDoTileAddItemEx);

	//doMoveCreature(cid, direction)
	lua_register(luaState, "doMoveCreature", LuaScriptInterface::luaDoMoveCreature);

	//doSetCreatureLight(cid, lightLevel, lightColor, time)
	lua_register(luaState, "doSetCreatureLight", LuaScriptInterface::luaDoSetCreatureLight);

	//getCreatureCondition(cid, condition[, subId])
	lua_register(luaState, "getCreatureCondition", LuaScriptInterface::luaGetCreatureCondition);

	//getCombatName(COMBAT_TYPE)
	lua_register(luaState, "getCombatName", LuaScriptInterface::luaGetCombatName);

	//isValidUID(uid)
	lua_register(luaState, "isValidUID", LuaScriptInterface::luaIsValidUID);

	//isDepot(uid)
	lua_register(luaState, "isDepot", LuaScriptInterface::luaIsDepot);

	//isMovable(uid)
	lua_register(luaState, "isMovable", LuaScriptInterface::luaIsMoveable);

	//doAddContainerItem(uid, itemid, <optional> count/subtype)
	lua_register(luaState, "doAddContainerItem", LuaScriptInterface::luaDoAddContainerItem);

	//getDepotId(uid)
	lua_register(luaState, "getDepotId", LuaScriptInterface::luaGetDepotId);

	//getWorldTime()
	lua_register(luaState, "getWorldTime", LuaScriptInterface::luaGetWorldTime);

	//getWorldLight()
	lua_register(luaState, "getWorldLight", LuaScriptInterface::luaGetWorldLight);

	//getWorldUpTime()
	lua_register(luaState, "getWorldUpTime", LuaScriptInterface::luaGetWorldUpTime);

	//createCombatArea( {area}, <optional> {extArea} )
	lua_register(luaState, "createCombatArea", LuaScriptInterface::luaCreateCombatArea);

	//doAreaCombatHealth(cid, type, pos, area, min, max, effect)
	lua_register(luaState, "doAreaCombatHealth", LuaScriptInterface::luaDoAreaCombatHealth);

	//doTargetCombatHealth(cid, target, type, min, max, effect)
	lua_register(luaState, "doTargetCombatHealth", LuaScriptInterface::luaDoTargetCombatHealth);

	//doAreaCombatMana(cid, pos, area, min, max, effect)
	lua_register(luaState, "doAreaCombatMana", LuaScriptInterface::luaDoAreaCombatMana);

	//doTargetCombatMana(cid, target, min, max, effect)
	lua_register(luaState, "doTargetCombatMana", LuaScriptInterface::luaDoTargetCombatMana);

	//doAreaCombatCondition(cid, pos, area, condition, effect)
	lua_register(luaState, "doAreaCombatCondition", LuaScriptInterface::luaDoAreaCombatCondition);

	//doTargetCombatCondition(cid, target, condition, effect)
	lua_register(luaState, "doTargetCombatCondition", LuaScriptInterface::luaDoTargetCombatCondition);

	//doAreaCombatDispel(cid, pos, area, type, effect)
	lua_register(luaState, "doAreaCombatDispel", LuaScriptInterface::luaDoAreaCombatDispel);

	//doTargetCombatDispel(cid, target, type, effect)
	lua_register(luaState, "doTargetCombatDispel", LuaScriptInterface::luaDoTargetCombatDispel);

	//doChallengeCreature(cid, target)
	lua_register(luaState, "doChallengeCreature", LuaScriptInterface::luaDoChallengeCreature);

	//doSetMonsterOutfit(cid, name, time)
	lua_register(luaState, "doSetMonsterOutfit", LuaScriptInterface::luaSetMonsterOutfit);

	//doSetItemOutfit(cid, item, time)
	lua_register(luaState, "doSetItemOutfit", LuaScriptInterface::luaSetItemOutfit);

	//doSetCreatureOutfit(cid, outfit, time)
	lua_register(luaState, "doSetCreatureOutfit", LuaScriptInterface::luaSetCreatureOutfit);

	//isInArray(array, value)
	lua_register(luaState, "isInArray", LuaScriptInterface::luaIsInArray);

	//addEvent(callback, delay, ...)
	lua_register(luaState, "addEvent", LuaScriptInterface::luaAddEvent);

	//stopEvent(eventid)
	lua_register(luaState, "stopEvent", LuaScriptInterface::luaStopEvent);

	//saveServer()
	lua_register(luaState, "saveServer", LuaScriptInterface::luaSaveServer);

	//cleanMap()
	lua_register(luaState, "cleanMap", LuaScriptInterface::luaCleanMap);

	//debugPrint(text)
	lua_register(luaState, "debugPrint", LuaScriptInterface::luaDebugPrint);

	//isInWar(cid, target)
	lua_register(luaState, "isInWar", LuaScriptInterface::luaIsInWar);

	//getWaypointPosition(name)
	lua_register(luaState, "getWaypointPositionByName", LuaScriptInterface::luaGetWaypointPositionByName);

	//sendChannelMessage(channelId, type, message)
	lua_register(luaState, "sendChannelMessage", LuaScriptInterface::luaSendChannelMessage);

	//sendGuildChannelMessage(guildId, type, message)
	lua_register(luaState, "sendGuildChannelMessage", LuaScriptInterface::luaSendGuildChannelMessage);

#ifndef LUAJIT_VERSION
	//bit operations for Lua, based on bitlib project release 24
	//bit.bnot, bit.band, bit.bor, bit.bxor, bit.lshift, bit.rshift
	luaL_register(luaState, "bit", LuaScriptInterface::luaBitReg);
#endif

	//configManager table
	luaL_register(luaState, "configManager", LuaScriptInterface::luaConfigManagerTable);

	//db table
	luaL_register(luaState, "db", LuaScriptInterface::luaDatabaseTable);

	//result table
	luaL_register(luaState, "result", LuaScriptInterface::luaResultTable);

	/* New functions */
	//registerClass(className, baseClass, newFunction)
	//registerTable(tableName)
	//registerMethod(className, functionName, function)
	//registerMetaMethod(className, functionName, function)
	//registerGlobalMethod(functionName, function)
	//registerVariable(tableName, name, value)
	//registerGlobalVariable(name, value)
	//registerEnum(value)
	//registerEnumIn(tableName, value)

	// Enums
	registerEnum(ACCOUNT_TYPE_NORMAL)
	registerEnum(ACCOUNT_TYPE_TUTOR)
	registerEnum(ACCOUNT_TYPE_SENIORTUTOR)
	registerEnum(ACCOUNT_TYPE_GAMEMASTER)
	registerEnum(ACCOUNT_TYPE_GOD)

	registerEnum(CALLBACK_PARAM_LEVELMAGICVALUE)
	registerEnum(CALLBACK_PARAM_SKILLVALUE)
	registerEnum(CALLBACK_PARAM_TARGETTILE)
	registerEnum(CALLBACK_PARAM_TARGETCREATURE)

	registerEnum(COMBAT_FORMULA_UNDEFINED)
	registerEnum(COMBAT_FORMULA_LEVELMAGIC)
	registerEnum(COMBAT_FORMULA_SKILL)
	registerEnum(COMBAT_FORMULA_DAMAGE)

	registerEnum(DIRECTION_NORTH)
	registerEnum(DIRECTION_EAST)
	registerEnum(DIRECTION_SOUTH)
	registerEnum(DIRECTION_WEST)
	registerEnum(DIRECTION_SOUTHWEST)
	registerEnum(DIRECTION_SOUTHEAST)
	registerEnum(DIRECTION_NORTHWEST)
	registerEnum(DIRECTION_NORTHEAST)

	registerEnum(COMBAT_NONE)
	registerEnum(COMBAT_PHYSICALDAMAGE)
	registerEnum(COMBAT_ENERGYDAMAGE)
	registerEnum(COMBAT_EARTHDAMAGE)
	registerEnum(COMBAT_FIREDAMAGE)
	registerEnum(COMBAT_UNDEFINEDDAMAGE)
	registerEnum(COMBAT_LIFEDRAIN)
	registerEnum(COMBAT_MANADRAIN)
	registerEnum(COMBAT_HEALING)
	registerEnum(COMBAT_DROWNDAMAGE)
	registerEnum(COMBAT_ICEDAMAGE)
	registerEnum(COMBAT_HOLYDAMAGE)
	registerEnum(COMBAT_DEATHDAMAGE)
	registerEnum(COMBAT_PSYCHICDAMAGE) //pota
	registerEnum(COMBAT_GRASSDAMAGE) //pota
	registerEnum(COMBAT_NORMALDAMAGE) //pota
	registerEnum(COMBAT_WATERDAMAGE) //pota
	registerEnum(COMBAT_FLYINGDAMAGE) //pota
	registerEnum(COMBAT_POISONDAMAGE) //pota
	registerEnum(COMBAT_ELECTRICDAMAGE) //pota
	registerEnum(COMBAT_GROUNDDAMAGE) //pota
	registerEnum(COMBAT_ROCKDAMAGE) //pota
	registerEnum(COMBAT_BUGDAMAGE) //pota
	registerEnum(COMBAT_DRAGONDAMAGE) //pota
	registerEnum(COMBAT_GHOSTDAMAGE) //pota
	registerEnum(COMBAT_DARKDAMAGE) //pota
	registerEnum(COMBAT_STEELDAMAGE) //pota
	registerEnum(COMBAT_FAIRYDAMAGE) //pota
	registerEnum(COMBAT_FIGHTINGDAMAGE) //pota

	registerEnum(COMBAT_PARAM_TYPE)
	registerEnum(COMBAT_PARAM_EFFECT)
	registerEnum(COMBAT_PARAM_DISTANCEEFFECT)
	registerEnum(COMBAT_PARAM_BLOCKSHIELD)
	registerEnum(COMBAT_PARAM_BLOCKARMOR)
	registerEnum(COMBAT_PARAM_TARGETCASTERORTOPMOST)
	registerEnum(COMBAT_PARAM_CREATEITEM)
	registerEnum(COMBAT_PARAM_AGGRESSIVE)
	registerEnum(COMBAT_PARAM_DISPEL)
	registerEnum(COMBAT_PARAM_USECHARGES)

	registerEnum(CONDITION_NONE)
	registerEnum(CONDITION_POISON)
	registerEnum(CONDITION_FIRE)
	registerEnum(CONDITION_ENERGY)
	registerEnum(CONDITION_BLEEDING)
	registerEnum(CONDITION_HASTE)
	registerEnum(CONDITION_PARALYZE)
	registerEnum(CONDITION_OUTFIT)
	registerEnum(CONDITION_INVISIBLE)
	registerEnum(CONDITION_LIGHT)
	registerEnum(CONDITION_MANASHIELD)
	registerEnum(CONDITION_INFIGHT)
	registerEnum(CONDITION_DRUNK)
	registerEnum(CONDITION_EXHAUST_WEAPON)
	registerEnum(CONDITION_REGENERATION)
	registerEnum(CONDITION_SOUL)
	registerEnum(CONDITION_DROWN)
	registerEnum(CONDITION_MUTED)
	registerEnum(CONDITION_CHANNELMUTEDTICKS)
	registerEnum(CONDITION_YELLTICKS)
	registerEnum(CONDITION_ATTRIBUTES)
	registerEnum(CONDITION_FREEZING)
	registerEnum(CONDITION_DAZZLED)
	registerEnum(CONDITION_CURSED)
	registerEnum(CONDITION_EXHAUST_COMBAT)
	registerEnum(CONDITION_EXHAUST_HEAL)
	registerEnum(CONDITION_PACIFIED)
	registerEnum(CONDITION_SPELLCOOLDOWN)
	registerEnum(CONDITION_SPELLGROUPCOOLDOWN)
	registerEnum(CONDITION_SLEEP) //pota
	registerEnum(CONDITION_SEED) //pota
	registerEnum(CONDITION_MOVING) //pota
	registerEnum(CONDITION_SILENCE) //helena
	registerEnum(CONDITION_REFLECT) //helena
	registerEnum(CONDITION_COAT) //helena
	registerEnum(CONDITION_FOCUS) //helena
	registerEnum(CONDITION_EVASION) //helena
	registerEnum(CONDITION_DEFENSEPLUS) //helena
	registerEnum(CONDITION_DEFENSEMINUS) //helena
	registerEnum(CONDITION_ATTACKPLUS) //helena
	registerEnum(CONDITION_ATTACKMINUS) //helena
	registerEnum(CONDITION_IMMUNE) //helena
	registerEnum(CONDITION_STURDY) //helena
	registerEnum(CONDITION_SAFFARI) //helena
	registerEnum(CONDITION_PARK) //helena
	registerEnum(CONDITION_FISHING) //helena

	registerEnum(CONDITIONID_DEFAULT)
	registerEnum(CONDITIONID_COMBAT)
	registerEnum(CONDITIONID_HEAD)
	registerEnum(CONDITIONID_NECKLACE)
	registerEnum(CONDITIONID_BACKPACK)
	registerEnum(CONDITIONID_ARMOR)
	registerEnum(CONDITIONID_RIGHT)
	registerEnum(CONDITIONID_LEFT)
	registerEnum(CONDITIONID_LEGS)
	registerEnum(CONDITIONID_FEET)
	registerEnum(CONDITIONID_RING)
	registerEnum(CONDITIONID_AMMO)
	registerEnum(CONDITIONID_ORDER) //pota
	registerEnum(CONDITIONID_INFO) //pota

	registerEnum(CONDITION_PARAM_OWNER)
	registerEnum(CONDITION_PARAM_TICKS)
	registerEnum(CONDITION_PARAM_HEALTHGAIN)
	registerEnum(CONDITION_PARAM_HEALTHTICKS)
	registerEnum(CONDITION_PARAM_MANAGAIN)
	registerEnum(CONDITION_PARAM_MANATICKS)
	registerEnum(CONDITION_PARAM_DELAYED)
	registerEnum(CONDITION_PARAM_SPEED)
	registerEnum(CONDITION_PARAM_LIGHT_LEVEL)
	registerEnum(CONDITION_PARAM_LIGHT_COLOR)
	registerEnum(CONDITION_PARAM_SOULGAIN)
	registerEnum(CONDITION_PARAM_SOULTICKS)
	registerEnum(CONDITION_PARAM_MINVALUE)
	registerEnum(CONDITION_PARAM_MAXVALUE)
	registerEnum(CONDITION_PARAM_STARTVALUE)
	registerEnum(CONDITION_PARAM_TICKINTERVAL)
	registerEnum(CONDITION_PARAM_FORCEUPDATE)
	registerEnum(CONDITION_PARAM_SKILL_MELEE)
	registerEnum(CONDITION_PARAM_SKILL_FIST)
	registerEnum(CONDITION_PARAM_SKILL_CLUB)
	registerEnum(CONDITION_PARAM_SKILL_SWORD)
	registerEnum(CONDITION_PARAM_SKILL_AXE)
	registerEnum(CONDITION_PARAM_SKILL_DISTANCE)
	registerEnum(CONDITION_PARAM_SKILL_SHIELD)
	registerEnum(CONDITION_PARAM_SKILL_FISHING)
	registerEnum(CONDITION_PARAM_STAT_MAXHITPOINTS)
	registerEnum(CONDITION_PARAM_STAT_MAXMANAPOINTS)
	registerEnum(CONDITION_PARAM_STAT_MAGICPOINTS)
	registerEnum(CONDITION_PARAM_STAT_MAXHITPOINTSPERCENT)
	registerEnum(CONDITION_PARAM_STAT_MAXMANAPOINTSPERCENT)
	registerEnum(CONDITION_PARAM_STAT_MAGICPOINTSPERCENT)
	registerEnum(CONDITION_PARAM_PERIODICDAMAGE)
	registerEnum(CONDITION_PARAM_SKILL_MELEEPERCENT)
	registerEnum(CONDITION_PARAM_SKILL_FISTPERCENT)
	registerEnum(CONDITION_PARAM_SKILL_CLUBPERCENT)
	registerEnum(CONDITION_PARAM_SKILL_SWORDPERCENT)
	registerEnum(CONDITION_PARAM_SKILL_AXEPERCENT)
	registerEnum(CONDITION_PARAM_SKILL_DISTANCEPERCENT)
	registerEnum(CONDITION_PARAM_SKILL_SHIELDPERCENT)
	registerEnum(CONDITION_PARAM_SKILL_FISHINGPERCENT)
	registerEnum(CONDITION_PARAM_BUFF_SPELL)
	registerEnum(CONDITION_PARAM_SUBID)
	registerEnum(CONDITION_PARAM_FIELD)

	registerEnum(CONST_ME_NONE)
	registerEnum(CONST_ME_DRAWBLOOD)
	registerEnum(CONST_ME_LOSEENERGY)
	registerEnum(CONST_ME_POFF)
	registerEnum(CONST_ME_BLOCKHIT)
	// registerEnum(CONST_ME_EXPLOSIONAREA)
	// registerEnum(CONST_ME_EXPLOSIONHIT)
	registerEnum(CONST_ME_FIREAREA)
	registerEnum(CONST_ME_YELLOW_RINGS)
	registerEnum(CONST_ME_GREEN_RINGS)
	registerEnum(CONST_ME_HITAREA)
	registerEnum(CONST_ME_TELEPORT)
	registerEnum(CONST_ME_ENERGYHIT)
	registerEnum(CONST_ME_MAGIC_BLUE)
	registerEnum(CONST_ME_MAGIC_RED)
	registerEnum(CONST_ME_MAGIC_GREEN)
	registerEnum(CONST_ME_HITBYFIRE)
	registerEnum(CONST_ME_HITBYPOISON)
	registerEnum(CONST_ME_MORTAREA)
	registerEnum(CONST_ME_SOUND_GREEN)
	registerEnum(CONST_ME_SOUND_RED)
	registerEnum(CONST_ME_POISONAREA)
	registerEnum(CONST_ME_SOUND_YELLOW)
	registerEnum(CONST_ME_SOUND_PURPLE)
	registerEnum(CONST_ME_SOUND_BLUE)
	registerEnum(CONST_ME_SOUND_WHITE)
	registerEnum(CONST_ME_BUBBLES)
	registerEnum(CONST_ME_CRAPS)
	registerEnum(CONST_ME_GIFT_WRAPS)
	registerEnum(CONST_ME_FIREWORK_YELLOW)
	registerEnum(CONST_ME_FIREWORK_RED)
	registerEnum(CONST_ME_FIREWORK_BLUE)
	registerEnum(CONST_ME_STUN)
	registerEnum(CONST_ME_SLEEP)
	registerEnum(CONST_ME_WATERCREATURE)
	registerEnum(CONST_ME_GROUNDSHAKER)
	registerEnum(CONST_ME_HEARTS)
	registerEnum(CONST_ME_FIREATTACK)
	registerEnum(CONST_ME_ENERGYAREA)
	registerEnum(CONST_ME_SMALLCLOUDS)
	registerEnum(CONST_ME_HOLYDAMAGE)
	registerEnum(CONST_ME_BIGCLOUDS)
	registerEnum(CONST_ME_ICEAREA)
	registerEnum(CONST_ME_ICETORNADO)
	registerEnum(CONST_ME_ICEATTACK)
	registerEnum(CONST_ME_STONES)
	registerEnum(CONST_ME_SMALLPLANTS)
	registerEnum(CONST_ME_CARNIPHILA)
	registerEnum(CONST_ME_PURPLEENERGY)
	registerEnum(CONST_ME_YELLOWENERGY)
	registerEnum(CONST_ME_HOLYAREA)
	registerEnum(CONST_ME_BIGPLANTS)
	registerEnum(CONST_ME_CAKE)
	registerEnum(CONST_ME_GIANTICE)
	registerEnum(CONST_ME_WATERSPLASH)
	registerEnum(CONST_ME_PLANTATTACK)
	registerEnum(CONST_ME_TUTORIALARROW)
	registerEnum(CONST_ME_TUTORIALSQUARE)
	registerEnum(CONST_ME_MIRRORHORIZONTAL)
	registerEnum(CONST_ME_MIRRORVERTICAL)
	registerEnum(CONST_ME_SKULLHORIZONTAL)
	registerEnum(CONST_ME_SKULLVERTICAL)
	registerEnum(CONST_ME_ASSASSIN)
	registerEnum(CONST_ME_STEPSHORIZONTAL)
	registerEnum(CONST_ME_BLOODYSTEPS)
	registerEnum(CONST_ME_STEPSVERTICAL)
	registerEnum(CONST_ME_YALAHARIGHOST)
	registerEnum(CONST_ME_BATS)
	registerEnum(CONST_ME_SMOKE)
	registerEnum(CONST_ME_INSECTS)
	registerEnum(CONST_ME_DRAGONHEAD)
	registerEnum(CONST_ME_ORCSHAMAN)
	registerEnum(CONST_ME_ORCSHAMAN_FIRE)
	registerEnum(CONST_ME_THUNDER)
	registerEnum(CONST_ME_FERUMBRAS)
	registerEnum(CONST_ME_CONFETTI_HORIZONTAL)
	registerEnum(CONST_ME_CONFETTI_VERTICAL)
	registerEnum(CONST_ME_BLACKSMOKE)
	registerEnum(CONST_ME_REDSMOKE)
	registerEnum(CONST_ME_YELLOWSMOKE)
	registerEnum(CONST_ME_GREENSMOKE)
	registerEnum(CONST_ME_PURPLESMOKE)

	registerEnum(CONST_ANI_NONE)
	registerEnum(CONST_ANI_SPEAR)
	registerEnum(CONST_ANI_BOLT)
	registerEnum(CONST_ANI_ARROW)
	registerEnum(CONST_ANI_FIRE)
	registerEnum(CONST_ANI_ENERGY)
	registerEnum(CONST_ANI_POISONARROW)
	registerEnum(CONST_ANI_BURSTARROW)
	registerEnum(CONST_ANI_THROWINGSTAR)
	registerEnum(CONST_ANI_THROWINGKNIFE)
	registerEnum(CONST_ANI_SMALLSTONE)
	registerEnum(CONST_ANI_DEATH)
	registerEnum(CONST_ANI_LARGEROCK)
	registerEnum(CONST_ANI_SNOWBALL)
	registerEnum(CONST_ANI_POWERBOLT)
	registerEnum(CONST_ANI_POISON)
	registerEnum(CONST_ANI_INFERNALBOLT)
	registerEnum(CONST_ANI_HUNTINGSPEAR)
	registerEnum(CONST_ANI_ENCHANTEDSPEAR)
	registerEnum(CONST_ANI_REDSTAR)
	registerEnum(CONST_ANI_GREENSTAR)
	registerEnum(CONST_ANI_ROYALSPEAR)
	registerEnum(CONST_ANI_SNIPERARROW)
	registerEnum(CONST_ANI_ONYXARROW)
	registerEnum(CONST_ANI_PIERCINGBOLT)
	registerEnum(CONST_ANI_WHIRLWINDSWORD)
	registerEnum(CONST_ANI_WHIRLWINDAXE)
	registerEnum(CONST_ANI_WHIRLWINDCLUB)
	registerEnum(CONST_ANI_ETHEREALSPEAR)
	registerEnum(CONST_ANI_ICE)
	registerEnum(CONST_ANI_EARTH)
	registerEnum(CONST_ANI_HOLY)
	registerEnum(CONST_ANI_SUDDENDEATH)
	registerEnum(CONST_ANI_FLASHARROW)
	registerEnum(CONST_ANI_FLAMMINGARROW)
	registerEnum(CONST_ANI_SHIVERARROW)
	registerEnum(CONST_ANI_ENERGYBALL)
	registerEnum(CONST_ANI_SMALLICE)
	registerEnum(CONST_ANI_SMALLHOLY)
	registerEnum(CONST_ANI_SMALLEARTH)
	registerEnum(CONST_ANI_EARTHARROW)
	// registerEnum(CONST_ANI_EXPLOSION)
	registerEnum(CONST_ANI_CAKE)
	registerEnum(CONST_ANI_TARSALARROW)
	registerEnum(CONST_ANI_VORTEXBOLT)
	registerEnum(CONST_ANI_PRISMATICBOLT)
	registerEnum(CONST_ANI_CRYSTALLINEARROW)
	registerEnum(CONST_ANI_DRILLBOLT)
	registerEnum(CONST_ANI_ENVENOMEDARROW)
	registerEnum(CONST_ANI_GLOOTHSPEAR)
	registerEnum(CONST_ANI_SIMPLEARROW)
	registerEnum(CONST_ANI_SINGLESTING)//Helena
	registerEnum(CONST_ANI_TRIPLESTING)//Helena
	registerEnum(CONST_ANI_BUBBLES)//Helena
	registerEnum(CONST_ANI_BLUEWAVE)//Helena
	registerEnum(CONST_ANI_WEAPONTYPE)

	registerEnum(CONST_PROP_BLOCKSOLID)
	registerEnum(CONST_PROP_HASHEIGHT)
	registerEnum(CONST_PROP_BLOCKPROJECTILE)
	registerEnum(CONST_PROP_BLOCKPATH)
	registerEnum(CONST_PROP_ISVERTICAL)
	registerEnum(CONST_PROP_ISHORIZONTAL)
	registerEnum(CONST_PROP_MOVEABLE)
	registerEnum(CONST_PROP_IMMOVABLEBLOCKSOLID)
	registerEnum(CONST_PROP_IMMOVABLEBLOCKPATH)
	registerEnum(CONST_PROP_IMMOVABLENOFIELDBLOCKPATH)
	registerEnum(CONST_PROP_NOFIELDBLOCKPATH)
	registerEnum(CONST_PROP_SUPPORTHANGABLE)

	registerEnum(CONST_SLOT_HEAD)
	registerEnum(CONST_SLOT_NECKLACE)
	registerEnum(CONST_SLOT_BACKPACK)
	registerEnum(CONST_SLOT_ARMOR)
	registerEnum(CONST_SLOT_RIGHT)
	registerEnum(CONST_SLOT_LEFT)
	registerEnum(CONST_SLOT_LEGS)
	registerEnum(CONST_SLOT_FEET)
	registerEnum(CONST_SLOT_RING)
	registerEnum(CONST_SLOT_AMMO)
	registerEnum(CONST_SLOT_ORDER)  //pota
	registerEnum(CONST_SLOT_INFO)  //pota

	registerEnum(CREATURE_EVENT_NONE)
	registerEnum(CREATURE_EVENT_LOGIN)
	registerEnum(CREATURE_EVENT_LOGOUT)
	registerEnum(CREATURE_EVENT_THINK)
	registerEnum(CREATURE_EVENT_PREPAREDEATH)
	registerEnum(CREATURE_EVENT_DEATH)
	registerEnum(CREATURE_EVENT_KILL)
	registerEnum(CREATURE_EVENT_ADVANCE)
	registerEnum(CREATURE_EVENT_MODALWINDOW)
	registerEnum(CREATURE_EVENT_TEXTEDIT)
	registerEnum(CREATURE_EVENT_HEALTHCHANGE)
	registerEnum(CREATURE_EVENT_MANACHANGE)
	registerEnum(CREATURE_EVENT_EXTENDED_OPCODE)
	registerEnum(CREATURE_EVENT_POSTDEATH) //pota

	registerEnum(GAME_STATE_STARTUP)
	registerEnum(GAME_STATE_INIT)
	registerEnum(GAME_STATE_NORMAL)
	registerEnum(GAME_STATE_CLOSED)
	registerEnum(GAME_STATE_SHUTDOWN)
	registerEnum(GAME_STATE_CLOSING)
	registerEnum(GAME_STATE_MAINTAIN)

	registerEnum(MESSAGE_STATUS_CONSOLE_BLUE)
	registerEnum(MESSAGE_STATUS_CONSOLE_RED)
	registerEnum(MESSAGE_STATUS_DEFAULT)
	registerEnum(MESSAGE_STATUS_WARNING)
	registerEnum(MESSAGE_EVENT_ADVANCE)
	registerEnum(MESSAGE_STATUS_SMALL)
	registerEnum(MESSAGE_INFO_DESCR)
	registerEnum(MESSAGE_DAMAGE_DEALT)
	registerEnum(MESSAGE_DAMAGE_RECEIVED)
	registerEnum(MESSAGE_HEALED)
	registerEnum(MESSAGE_EXPERIENCE)
	registerEnum(MESSAGE_DAMAGE_OTHERS)
	registerEnum(MESSAGE_HEALED_OTHERS)
	registerEnum(MESSAGE_EXPERIENCE_OTHERS)
	registerEnum(MESSAGE_EVENT_DEFAULT)
	registerEnum(MESSAGE_EVENT_ORANGE)
	registerEnum(MESSAGE_STATUS_CONSOLE_ORANGE)

	registerEnum(CREATURETYPE_PLAYER)
	registerEnum(CREATURETYPE_MONSTER)
	registerEnum(CREATURETYPE_NPC)
	registerEnum(CREATURETYPE_SUMMON_OWN)
	registerEnum(CREATURETYPE_SUMMON_OTHERS)

	registerEnum(CLIENTOS_LINUX)
	registerEnum(CLIENTOS_WINDOWS)
	registerEnum(CLIENTOS_FLASH)
	registerEnum(CLIENTOS_OTCLIENT_LINUX)
	registerEnum(CLIENTOS_OTCLIENT_WINDOWS)
	registerEnum(CLIENTOS_OTCLIENT_MAC)

	registerEnum(ITEM_ATTRIBUTE_NONE)
	registerEnum(ITEM_ATTRIBUTE_ACTIONID)
	registerEnum(ITEM_ATTRIBUTE_UNIQUEID)
	registerEnum(ITEM_ATTRIBUTE_DESCRIPTION)
	registerEnum(ITEM_ATTRIBUTE_TEXT)
	registerEnum(ITEM_ATTRIBUTE_DATE)
	registerEnum(ITEM_ATTRIBUTE_WRITER)
	registerEnum(ITEM_ATTRIBUTE_NAME)
	registerEnum(ITEM_ATTRIBUTE_ARTICLE)
	registerEnum(ITEM_ATTRIBUTE_PLURALNAME)
	registerEnum(ITEM_ATTRIBUTE_WEIGHT)
	registerEnum(ITEM_ATTRIBUTE_ATTACK)
	registerEnum(ITEM_ATTRIBUTE_DEFENSE)
	registerEnum(ITEM_ATTRIBUTE_EXTRADEFENSE)
	registerEnum(ITEM_ATTRIBUTE_ARMOR)
	registerEnum(ITEM_ATTRIBUTE_HITCHANCE)
	registerEnum(ITEM_ATTRIBUTE_SHOOTRANGE)
	registerEnum(ITEM_ATTRIBUTE_OWNER)
	registerEnum(ITEM_ATTRIBUTE_DURATION)
	registerEnum(ITEM_ATTRIBUTE_DECAYSTATE)
	registerEnum(ITEM_ATTRIBUTE_CORPSEOWNER)
	registerEnum(ITEM_ATTRIBUTE_CHARGES)
	registerEnum(ITEM_ATTRIBUTE_FLUIDTYPE)
	registerEnum(ITEM_ATTRIBUTE_DOORID)
	registerEnum(ITEM_ATTRIBUTE_SPECIAL)

	registerEnum(ITEM_TYPE_DEPOT)
	registerEnum(ITEM_TYPE_MAILBOX)
	registerEnum(ITEM_TYPE_TRASHHOLDER)
	registerEnum(ITEM_TYPE_CONTAINER)
	registerEnum(ITEM_TYPE_DOOR)
	registerEnum(ITEM_TYPE_MAGICFIELD)
	registerEnum(ITEM_TYPE_TELEPORT)
	registerEnum(ITEM_TYPE_BED)
	registerEnum(ITEM_TYPE_KEY)
	registerEnum(ITEM_TYPE_RUNE)

	registerEnum(ITEM_BAG)
	registerEnum(ITEM_GOLD_COIN)
	registerEnum(ITEM_PLATINUM_COIN)
	registerEnum(ITEM_CRYSTAL_COIN)
	registerEnum(ITEM_AMULETOFLOSS)
	registerEnum(ITEM_PARCEL)
	registerEnum(ITEM_LABEL)
	registerEnum(ITEM_FIREFIELD_PVP_FULL)
	registerEnum(ITEM_FIREFIELD_PVP_MEDIUM)
	registerEnum(ITEM_FIREFIELD_PVP_SMALL)
	registerEnum(ITEM_FIREFIELD_PERSISTENT_FULL)
	registerEnum(ITEM_FIREFIELD_PERSISTENT_MEDIUM)
	registerEnum(ITEM_FIREFIELD_PERSISTENT_SMALL)
	registerEnum(ITEM_FIREFIELD_NOPVP)
	registerEnum(ITEM_POISONFIELD_PVP)
	registerEnum(ITEM_POISONFIELD_PERSISTENT)
	registerEnum(ITEM_POISONFIELD_NOPVP)
	registerEnum(ITEM_ENERGYFIELD_PVP)
	registerEnum(ITEM_ENERGYFIELD_PERSISTENT)
	registerEnum(ITEM_ENERGYFIELD_NOPVP)
	registerEnum(ITEM_MAGICWALL)
	registerEnum(ITEM_MAGICWALL_PERSISTENT)
	registerEnum(ITEM_MAGICWALL_SAFE)
	registerEnum(ITEM_WILDGROWTH)
	registerEnum(ITEM_WILDGROWTH_PERSISTENT)
	registerEnum(ITEM_WILDGROWTH_SAFE)

	registerEnum(PlayerFlag_CannotUseCombat)
	registerEnum(PlayerFlag_CannotAttackPlayer)
	registerEnum(PlayerFlag_CannotAttackMonster)
	registerEnum(PlayerFlag_CannotBeAttacked)
	registerEnum(PlayerFlag_CanConvinceAll)
	registerEnum(PlayerFlag_CanSummonAll)
	registerEnum(PlayerFlag_CanIllusionAll)
	registerEnum(PlayerFlag_CanSenseInvisibility)
	registerEnum(PlayerFlag_IgnoredByMonsters)
	registerEnum(PlayerFlag_NotGainInFight)
	registerEnum(PlayerFlag_HasInfiniteMana)
	registerEnum(PlayerFlag_HasInfiniteSoul)
	registerEnum(PlayerFlag_HasNoExhaustion)
	registerEnum(PlayerFlag_CannotUseSpells)
	registerEnum(PlayerFlag_CannotPickupItem)
	registerEnum(PlayerFlag_CanAlwaysLogin)
	registerEnum(PlayerFlag_CanBroadcast)
	registerEnum(PlayerFlag_CanEditHouses)
	registerEnum(PlayerFlag_CannotBeBanned)
	registerEnum(PlayerFlag_CannotBePushed)
	registerEnum(PlayerFlag_HasInfiniteCapacity)
	registerEnum(PlayerFlag_CanPushAllCreatures)
	registerEnum(PlayerFlag_CanTalkRedPrivate)
	registerEnum(PlayerFlag_CanTalkRedChannel)
	registerEnum(PlayerFlag_TalkOrangeHelpChannel)
	registerEnum(PlayerFlag_NotGainExperience)
	registerEnum(PlayerFlag_NotGainMana)
	registerEnum(PlayerFlag_NotGainHealth)
	registerEnum(PlayerFlag_NotGainSkill)
	registerEnum(PlayerFlag_SetMaxSpeed)
	registerEnum(PlayerFlag_SpecialVIP)
	registerEnum(PlayerFlag_NotGenerateLoot)
	registerEnum(PlayerFlag_CanTalkRedChannelAnonymous)
	registerEnum(PlayerFlag_IgnoreProtectionZone)
	registerEnum(PlayerFlag_IgnoreSpellCheck)
	registerEnum(PlayerFlag_IgnoreWeaponCheck)
	registerEnum(PlayerFlag_CannotBeMuted)
	registerEnum(PlayerFlag_IsAlwaysPremium)

	registerEnum(PLAYERSEX_FEMALE)
	registerEnum(PLAYERSEX_MALE)

	registerEnum(VOCATION_NONE)

	registerEnum(SKILL_FIST)
	registerEnum(SKILL_CLUB)
	registerEnum(SKILL_SWORD)
	registerEnum(SKILL_AXE)
	registerEnum(SKILL_DISTANCE)
	registerEnum(SKILL_SHIELD)
	registerEnum(SKILL_FISHING)
	registerEnum(SKILL_MAGLEVEL)
	registerEnum(SKILL_LEVEL)

	registerEnum(SKULL_NONE)
	registerEnum(SKULL_YELLOW)
	registerEnum(SKULL_GREEN)
	registerEnum(SKULL_WHITE)
	registerEnum(SKULL_RED)
	registerEnum(SKULL_BLACK)
	registerEnum(SKULL_ORANGE)

	registerEnum(TALKTYPE_SAY)
	registerEnum(TALKTYPE_WHISPER)
	registerEnum(TALKTYPE_YELL)
	registerEnum(TALKTYPE_PRIVATE_FROM)
	registerEnum(TALKTYPE_PRIVATE_TO)
	registerEnum(TALKTYPE_CHANNEL_Y)
	registerEnum(TALKTYPE_CHANNEL_O)
	registerEnum(TALKTYPE_PRIVATE_NP)
	registerEnum(TALKTYPE_PRIVATE_PN)
	registerEnum(TALKTYPE_BROADCAST)
	registerEnum(TALKTYPE_CHANNEL_R1)
	registerEnum(TALKTYPE_PRIVATE_RED_FROM)
	registerEnum(TALKTYPE_PRIVATE_RED_TO)
	registerEnum(TALKTYPE_MONSTER_SAY)
	registerEnum(TALKTYPE_MONSTER_YELL)
	registerEnum(TALKTYPE_CHANNEL_R2)

	registerEnum(TEXTCOLOR_BLUE)
	registerEnum(TEXTCOLOR_LIGHTBLUE)
	registerEnum(TEXTCOLOR_MAYABLUE)
	registerEnum(TEXTCOLOR_DARKRED)
	registerEnum(TEXTCOLOR_LIGHTGREY)
	registerEnum(TEXTCOLOR_SKYBLUE)
	registerEnum(TEXTCOLOR_PURPLE)
	registerEnum(TEXTCOLOR_RED)
	registerEnum(TEXTCOLOR_ORANGE)
	registerEnum(TEXTCOLOR_YELLOW)
	registerEnum(TEXTCOLOR_WHITE_EXP)
	registerEnum(TEXTCOLOR_NONE)
	registerEnum(TEXTCOLOR_WHITE)
	registerEnum(TEXTCOLOR_MEDIUMORCHID)
	registerEnum(TEXTCOLOR_LIGHTAQUA)
	registerEnum(TEXT_COLORICE)
	registerEnum(TEXT_COLORFLYING)
	registerEnum(TEXT_COLORPOISON)
	registerEnum(TEXT_COLORELECTRIC)
	registerEnum(TEXT_COLORGROUND)
	registerEnum(TEXT_COLORROCK)
	registerEnum(TEXT_COLORBUG)
	registerEnum(TEXT_COLORDRAGON)
	registerEnum(TEXT_COLORGHOST)
	registerEnum(TEXT_COLORDARK)
	registerEnum(TEXT_COLORSTEEL)
	registerEnum(TEXT_COLORFAIRY)
	registerEnum(TEXT_COLORFIGHTING)
	registerEnum(TEXT_COLORGRASS)

	registerEnum(TILESTATE_NONE)
	registerEnum(TILESTATE_PROTECTIONZONE)
	registerEnum(TILESTATE_NOPVPZONE)
	registerEnum(TILESTATE_NOLOGOUT)
	registerEnum(TILESTATE_PVPZONE)
	registerEnum(TILESTATE_FLOORCHANGE)
	registerEnum(TILESTATE_FLOORCHANGE_DOWN)
	registerEnum(TILESTATE_FLOORCHANGE_NORTH)
	registerEnum(TILESTATE_FLOORCHANGE_SOUTH)
	registerEnum(TILESTATE_FLOORCHANGE_EAST)
	registerEnum(TILESTATE_FLOORCHANGE_WEST)
	registerEnum(TILESTATE_TELEPORT)
	registerEnum(TILESTATE_MAGICFIELD)
	registerEnum(TILESTATE_MAILBOX)
	registerEnum(TILESTATE_TRASHHOLDER)
	registerEnum(TILESTATE_BED)
	registerEnum(TILESTATE_DEPOT)
	registerEnum(TILESTATE_BLOCKSOLID)
	registerEnum(TILESTATE_BLOCKPATH)
	registerEnum(TILESTATE_IMMOVABLEBLOCKSOLID)
	registerEnum(TILESTATE_IMMOVABLEBLOCKPATH)
	registerEnum(TILESTATE_IMMOVABLENOFIELDBLOCKPATH)
	registerEnum(TILESTATE_NOFIELDBLOCKPATH)
	registerEnum(TILESTATE_FLOORCHANGE_SOUTH_ALT)
	registerEnum(TILESTATE_FLOORCHANGE_EAST_ALT)
	registerEnum(TILESTATE_SUPPORTS_HANGABLE)

	registerEnum(WEAPON_NONE)
	registerEnum(WEAPON_SWORD)
	registerEnum(WEAPON_CLUB)
	registerEnum(WEAPON_AXE)
	registerEnum(WEAPON_SHIELD)
	registerEnum(WEAPON_DISTANCE)
	registerEnum(WEAPON_WAND)
	registerEnum(WEAPON_AMMO)

	registerEnum(WORLD_TYPE_NO_PVP)
	registerEnum(WORLD_TYPE_PVP)
	registerEnum(WORLD_TYPE_PVP_ENFORCED)

	// Use with container:addItem, container:addItemEx and possibly other functions.
	registerEnum(FLAG_NOLIMIT)
	registerEnum(FLAG_IGNOREBLOCKITEM)
	registerEnum(FLAG_IGNOREBLOCKCREATURE)
	registerEnum(FLAG_CHILDISOWNER)
	registerEnum(FLAG_PATHFINDING)
	registerEnum(FLAG_IGNOREFIELDDAMAGE)
	registerEnum(FLAG_IGNORENOTMOVEABLE)
	registerEnum(FLAG_IGNOREAUTOSTACK)

	// Use with itemType:getSlotPosition
	registerEnum(SLOTP_WHEREEVER)
	registerEnum(SLOTP_HEAD)
	registerEnum(SLOTP_NECKLACE)
	registerEnum(SLOTP_BACKPACK)
	registerEnum(SLOTP_ARMOR)
	registerEnum(SLOTP_RIGHT)
	registerEnum(SLOTP_LEFT)
	registerEnum(SLOTP_LEGS)
	registerEnum(SLOTP_FEET)
	registerEnum(SLOTP_RING)
	registerEnum(SLOTP_AMMO)
	registerEnum(SLOTP_DEPOT)
	registerEnum(SLOTP_TWO_HAND)
	registerEnum(SLOTP_ORDER) //pota
	registerEnum(SLOTP_INFO) //pota

	// Use with combat functions
	registerEnum(ORIGIN_NONE)
	registerEnum(ORIGIN_CONDITION)
	registerEnum(ORIGIN_SPELL)
	registerEnum(ORIGIN_MELEE)
	registerEnum(ORIGIN_RANGED)

	// Use with house:getAccessList, house:setAccessList
	registerEnum(GUEST_LIST)
	registerEnum(SUBOWNER_LIST)

	// Use with npc:setSpeechBubble
	registerEnum(SPEECHBUBBLE_NONE)
	registerEnum(SPEECHBUBBLE_NORMAL)
	registerEnum(SPEECHBUBBLE_TRADE)
	registerEnum(SPEECHBUBBLE_QUEST)
	registerEnum(SPEECHBUBBLE_QUESTTRADER)

	// Use with player:addMapMark
	registerEnum(MAPMARK_TICK)
	registerEnum(MAPMARK_QUESTION)
	registerEnum(MAPMARK_EXCLAMATION)
	registerEnum(MAPMARK_STAR)
	registerEnum(MAPMARK_CROSS)
	registerEnum(MAPMARK_TEMPLE)
	registerEnum(MAPMARK_KISS)
	registerEnum(MAPMARK_SHOVEL)
	registerEnum(MAPMARK_SWORD)
	registerEnum(MAPMARK_FLAG)
	registerEnum(MAPMARK_LOCK)
	registerEnum(MAPMARK_BAG)
	registerEnum(MAPMARK_SKULL)
	registerEnum(MAPMARK_DOLLAR)
	registerEnum(MAPMARK_REDNORTH)
	registerEnum(MAPMARK_REDSOUTH)
	registerEnum(MAPMARK_REDEAST)
	registerEnum(MAPMARK_REDWEST)
	registerEnum(MAPMARK_GREENNORTH)
	registerEnum(MAPMARK_GREENSOUTH)

	// Use with Game.getReturnMessage
	registerEnum(RETURNVALUE_NOERROR)
	registerEnum(RETURNVALUE_NOTPOSSIBLE)
	registerEnum(RETURNVALUE_NOTENOUGHROOM)
	registerEnum(RETURNVALUE_PLAYERISPZLOCKED)
	registerEnum(RETURNVALUE_PLAYERISNOTINVITED)
	registerEnum(RETURNVALUE_CANNOTTHROW)
	registerEnum(RETURNVALUE_THEREISNOWAY)
	registerEnum(RETURNVALUE_DESTINATIONOUTOFREACH)
	registerEnum(RETURNVALUE_CREATUREBLOCK)
	registerEnum(RETURNVALUE_NOTMOVEABLE)
	registerEnum(RETURNVALUE_DROPTWOHANDEDITEM)
	registerEnum(RETURNVALUE_BOTHHANDSNEEDTOBEFREE)
	registerEnum(RETURNVALUE_CANONLYUSEONEWEAPON)
	registerEnum(RETURNVALUE_NEEDEXCHANGE)
	registerEnum(RETURNVALUE_CANNOTBEDRESSED)
	registerEnum(RETURNVALUE_PUTTHISOBJECTINYOURHAND)
	registerEnum(RETURNVALUE_PUTTHISOBJECTINBOTHHANDS)
	registerEnum(RETURNVALUE_TOOFARAWAY)
	registerEnum(RETURNVALUE_FIRSTGODOWNSTAIRS)
	registerEnum(RETURNVALUE_FIRSTGOUPSTAIRS)
	registerEnum(RETURNVALUE_CONTAINERNOTENOUGHROOM)
	registerEnum(RETURNVALUE_NOTENOUGHCAPACITY)
	registerEnum(RETURNVALUE_CANNOTPICKUP)
	registerEnum(RETURNVALUE_THISISIMPOSSIBLE)
	registerEnum(RETURNVALUE_DEPOTISFULL)
	registerEnum(RETURNVALUE_CREATUREDOESNOTEXIST)
	registerEnum(RETURNVALUE_CANNOTUSETHISOBJECT)
	registerEnum(RETURNVALUE_PLAYERWITHTHISNAMEISNOTONLINE)
	registerEnum(RETURNVALUE_NOTREQUIREDLEVELTOUSERUNE)
	registerEnum(RETURNVALUE_YOUAREALREADYTRADING)
	registerEnum(RETURNVALUE_THISPLAYERISALREADYTRADING)
	registerEnum(RETURNVALUE_YOUMAYNOTLOGOUTDURINGAFIGHT)
	registerEnum(RETURNVALUE_DIRECTPLAYERSHOOT)
	registerEnum(RETURNVALUE_NOTENOUGHLEVEL)
	registerEnum(RETURNVALUE_NOTENOUGHMAGICLEVEL)
	registerEnum(RETURNVALUE_NOTENOUGHMANA)
	registerEnum(RETURNVALUE_NOTENOUGHSOUL)
	registerEnum(RETURNVALUE_YOUAREEXHAUSTED)
	registerEnum(RETURNVALUE_PLAYERISNOTREACHABLE)
	registerEnum(RETURNVALUE_CANONLYUSETHISRUNEONCREATURES)
	registerEnum(RETURNVALUE_ACTIONNOTPERMITTEDINPROTECTIONZONE)
	registerEnum(RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER)
	registerEnum(RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE)
	registerEnum(RETURNVALUE_YOUMAYNOTATTACKAPERSONWHILEINPROTECTIONZONE)
	registerEnum(RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE)
	registerEnum(RETURNVALUE_YOUCANONLYUSEITONCREATURES)
	registerEnum(RETURNVALUE_CREATUREISNOTREACHABLE)
	registerEnum(RETURNVALUE_TURNSECUREMODETOATTACKUNMARKEDPLAYERS)
	registerEnum(RETURNVALUE_YOUNEEDPREMIUMACCOUNT)
	registerEnum(RETURNVALUE_YOUNEEDTOLEARNTHISSPELL)
	registerEnum(RETURNVALUE_YOURVOCATIONCANNOTUSETHISSPELL)
	registerEnum(RETURNVALUE_YOUNEEDAWEAPONTOUSETHISSPELL)
	registerEnum(RETURNVALUE_PLAYERISPZLOCKEDLEAVEPVPZONE)
	registerEnum(RETURNVALUE_PLAYERISPZLOCKEDENTERPVPZONE)
	registerEnum(RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE)
	registerEnum(RETURNVALUE_YOUCANNOTLOGOUTHERE)
	registerEnum(RETURNVALUE_YOUNEEDAMAGICITEMTOCASTSPELL)
	registerEnum(RETURNVALUE_CANNOTCONJUREITEMHERE)
	registerEnum(RETURNVALUE_YOUNEEDTOSPLITYOURSPEARS)
	registerEnum(RETURNVALUE_NAMEISTOOAMBIGIOUS)
	registerEnum(RETURNVALUE_CANONLYUSEONESHIELD)
	registerEnum(RETURNVALUE_NOPARTYMEMBERSINRANGE)
	registerEnum(RETURNVALUE_YOUARENOTTHEOWNER)

	// _G
	registerGlobalVariable("INDEX_WHEREEVER", INDEX_WHEREEVER);
	registerGlobalBoolean("VIRTUAL_PARENT", true);

	registerGlobalMethod("isType", LuaScriptInterface::luaIsType);
	registerGlobalMethod("rawgetmetatable", LuaScriptInterface::luaRawGetMetatable);

	// configKeys
	registerTable("configKeys");

	registerEnumIn("configKeys", ConfigManager::ALLOW_CHANGEOUTFIT)
	registerEnumIn("configKeys", ConfigManager::ONE_PLAYER_ON_ACCOUNT)
	registerEnumIn("configKeys", ConfigManager::AIMBOT_HOTKEY_ENABLED)
	registerEnumIn("configKeys", ConfigManager::REMOVE_RUNE_CHARGES)
	registerEnumIn("configKeys", ConfigManager::EXPERIENCE_FROM_PLAYERS)
	registerEnumIn("configKeys", ConfigManager::FREE_PREMIUM)
	registerEnumIn("configKeys", ConfigManager::REPLACE_KICK_ON_LOGIN)
	registerEnumIn("configKeys", ConfigManager::ALLOW_CLONES)
	registerEnumIn("configKeys", ConfigManager::BIND_ONLY_GLOBAL_ADDRESS)
	registerEnumIn("configKeys", ConfigManager::OPTIMIZE_DATABASE)
	registerEnumIn("configKeys", ConfigManager::MARKET_PREMIUM)
	registerEnumIn("configKeys", ConfigManager::EMOTE_SPELLS)
	registerEnumIn("configKeys", ConfigManager::STAMINA_SYSTEM)
	registerEnumIn("configKeys", ConfigManager::WARN_UNSAFE_SCRIPTS)
	registerEnumIn("configKeys", ConfigManager::CONVERT_UNSAFE_SCRIPTS)
	registerEnumIn("configKeys", ConfigManager::CLASSIC_EQUIPMENT_SLOTS)

	registerEnumIn("configKeys", ConfigManager::MAP_NAME)
	registerEnumIn("configKeys", ConfigManager::HOUSE_RENT_PERIOD)
	registerEnumIn("configKeys", ConfigManager::SERVER_NAME)
	registerEnumIn("configKeys", ConfigManager::OWNER_NAME)
	registerEnumIn("configKeys", ConfigManager::OWNER_EMAIL)
	registerEnumIn("configKeys", ConfigManager::URL)
	registerEnumIn("configKeys", ConfigManager::LOCATION)
	registerEnumIn("configKeys", ConfigManager::IP)
	registerEnumIn("configKeys", ConfigManager::MOTD)
	registerEnumIn("configKeys", ConfigManager::WORLD_TYPE)
	registerEnumIn("configKeys", ConfigManager::MYSQL_HOST)
	registerEnumIn("configKeys", ConfigManager::MYSQL_USER)
	registerEnumIn("configKeys", ConfigManager::MYSQL_PASS)
	registerEnumIn("configKeys", ConfigManager::MYSQL_DB)
	registerEnumIn("configKeys", ConfigManager::MYSQL_SOCK)
	registerEnumIn("configKeys", ConfigManager::DEFAULT_PRIORITY)
	registerEnumIn("configKeys", ConfigManager::MAP_AUTHOR)

	registerEnumIn("configKeys", ConfigManager::SQL_PORT)
	registerEnumIn("configKeys", ConfigManager::MAX_PLAYERS)
	registerEnumIn("configKeys", ConfigManager::PZ_LOCKED)
	registerEnumIn("configKeys", ConfigManager::DEFAULT_DESPAWNRANGE)
	registerEnumIn("configKeys", ConfigManager::DEFAULT_DESPAWNRADIUS)
	registerEnumIn("configKeys", ConfigManager::RATE_EXPERIENCE)
	registerEnumIn("configKeys", ConfigManager::RATE_SKILL)
	registerEnumIn("configKeys", ConfigManager::RATE_LOOT)
	registerEnumIn("configKeys", ConfigManager::RATE_MAGIC)
	registerEnumIn("configKeys", ConfigManager::RATE_SPAWN)
	registerEnumIn("configKeys", ConfigManager::HOUSE_PRICE)
	registerEnumIn("configKeys", ConfigManager::KILLS_TO_RED)
	registerEnumIn("configKeys", ConfigManager::KILLS_TO_BLACK)
	registerEnumIn("configKeys", ConfigManager::MAX_MESSAGEBUFFER)
	registerEnumIn("configKeys", ConfigManager::ACTIONS_DELAY_INTERVAL)
	registerEnumIn("configKeys", ConfigManager::EX_ACTIONS_DELAY_INTERVAL)
	registerEnumIn("configKeys", ConfigManager::KICK_AFTER_MINUTES)
	registerEnumIn("configKeys", ConfigManager::PROTECTION_LEVEL)
	registerEnumIn("configKeys", ConfigManager::DEATH_LOSE_PERCENT)
	registerEnumIn("configKeys", ConfigManager::STATUSQUERY_TIMEOUT)
	registerEnumIn("configKeys", ConfigManager::FRAG_TIME)
	registerEnumIn("configKeys", ConfigManager::WHITE_SKULL_TIME)
	registerEnumIn("configKeys", ConfigManager::GAME_PORT)
	registerEnumIn("configKeys", ConfigManager::LOGIN_PORT)
	registerEnumIn("configKeys", ConfigManager::STATUS_PORT)
	registerEnumIn("configKeys", ConfigManager::STAIRHOP_DELAY)
	registerEnumIn("configKeys", ConfigManager::MARKET_OFFER_DURATION)
	registerEnumIn("configKeys", ConfigManager::CHECK_EXPIRED_MARKET_OFFERS_EACH_MINUTES)
	registerEnumIn("configKeys", ConfigManager::MAX_MARKET_OFFERS_AT_A_TIME_PER_PLAYER)
	registerEnumIn("configKeys", ConfigManager::EXP_FROM_PLAYERS_LEVEL_RANGE)
	registerEnumIn("configKeys", ConfigManager::MAX_PACKETS_PER_SECOND)

	// os
	registerMethod("os", "mtime", LuaScriptInterface::luaSystemTime);

	// table
	registerMethod("table", "create", LuaScriptInterface::luaTableCreate);

	// Game
	registerTable("Game");

	registerMethod("Game", "getSpectators", LuaScriptInterface::luaGameGetSpectators);
	registerMethod("Game", "getPlayers", LuaScriptInterface::luaGameGetPlayers);
	registerMethod("Game", "loadMap", LuaScriptInterface::luaGameLoadMap);

	registerMethod("Game", "getExperienceStage", LuaScriptInterface::luaGameGetExperienceStage);
	registerMethod("Game", "getMonsterCount", LuaScriptInterface::luaGameGetMonsterCount);
	registerMethod("Game", "getPlayerCount", LuaScriptInterface::luaGameGetPlayerCount);
	registerMethod("Game", "getNpcCount", LuaScriptInterface::luaGameGetNpcCount);

	registerMethod("Game", "getTowns", LuaScriptInterface::luaGameGetTowns);
	registerMethod("Game", "getHouses", LuaScriptInterface::luaGameGetHouses);

	registerMethod("Game", "getGameState", LuaScriptInterface::luaGameGetGameState);
	registerMethod("Game", "setGameState", LuaScriptInterface::luaGameSetGameState);

	registerMethod("Game", "getWorldType", LuaScriptInterface::luaGameGetWorldType);
	registerMethod("Game", "setWorldType", LuaScriptInterface::luaGameSetWorldType);

	registerMethod("Game", "getReturnMessage", LuaScriptInterface::luaGameGetReturnMessage);

	registerMethod("Game", "createItem", LuaScriptInterface::luaGameCreateItem);
	registerMethod("Game", "createContainer", LuaScriptInterface::luaGameCreateContainer);
	registerMethod("Game", "createMonster", LuaScriptInterface::luaGameCreateMonster);
	registerMethod("Game", "createNpc", LuaScriptInterface::luaGameCreateNpc);
	registerMethod("Game", "createTile", LuaScriptInterface::luaGameCreateTile);

	registerMethod("Game", "startRaid", LuaScriptInterface::luaGameStartRaid);
	registerMethod("Game", "sendAnimatedText", LuaScriptInterface::luaGameSendAnimatedText); //pota

	// Variant
	registerClass("Variant", "", LuaScriptInterface::luaVariantCreate);

	registerMethod("Variant", "getNumber", LuaScriptInterface::luaVariantGetNumber);
	registerMethod("Variant", "getString", LuaScriptInterface::luaVariantGetString);
	registerMethod("Variant", "getPosition", LuaScriptInterface::luaVariantGetPosition);

	// Position
	registerClass("Position", "", LuaScriptInterface::luaPositionCreate);
	registerMetaMethod("Position", "__add", LuaScriptInterface::luaPositionAdd);
	registerMetaMethod("Position", "__sub", LuaScriptInterface::luaPositionSub);
	registerMetaMethod("Position", "__eq", LuaScriptInterface::luaPositionCompare);

	registerMethod("Position", "getDistance", LuaScriptInterface::luaPositionGetDistance);
	registerMethod("Position", "isSightClear", LuaScriptInterface::luaPositionIsSightClear);

	registerMethod("Position", "sendMagicEffect", LuaScriptInterface::luaPositionSendMagicEffect);
	registerMethod("Position", "sendDistanceEffect", LuaScriptInterface::luaPositionSendDistanceEffect);

	// Tile
	registerClass("Tile", "", LuaScriptInterface::luaTileCreate);
	registerMetaMethod("Tile", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Tile", "getPosition", LuaScriptInterface::luaTileGetPosition);
	registerMethod("Tile", "getGround", LuaScriptInterface::luaTileGetGround);
	registerMethod("Tile", "getThing", LuaScriptInterface::luaTileGetThing);
	registerMethod("Tile", "getThingCount", LuaScriptInterface::luaTileGetThingCount);
	registerMethod("Tile", "getTopVisibleThing", LuaScriptInterface::luaTileGetTopVisibleThing);

	registerMethod("Tile", "getTopTopItem", LuaScriptInterface::luaTileGetTopTopItem);
	registerMethod("Tile", "getTopDownItem", LuaScriptInterface::luaTileGetTopDownItem);
	registerMethod("Tile", "getFieldItem", LuaScriptInterface::luaTileGetFieldItem);

	registerMethod("Tile", "getItemById", LuaScriptInterface::luaTileGetItemById);
	registerMethod("Tile", "getItemByType", LuaScriptInterface::luaTileGetItemByType);
	registerMethod("Tile", "getItemByTopOrder", LuaScriptInterface::luaTileGetItemByTopOrder);
	registerMethod("Tile", "getItemCountById", LuaScriptInterface::luaTileGetItemCountById);

	registerMethod("Tile", "getBottomCreature", LuaScriptInterface::luaTileGetBottomCreature);
	registerMethod("Tile", "getTopCreature", LuaScriptInterface::luaTileGetTopCreature);
	registerMethod("Tile", "getBottomVisibleCreature", LuaScriptInterface::luaTileGetBottomVisibleCreature);
	registerMethod("Tile", "getTopVisibleCreature", LuaScriptInterface::luaTileGetTopVisibleCreature);

	registerMethod("Tile", "getItems", LuaScriptInterface::luaTileGetItems);
	registerMethod("Tile", "getItemCount", LuaScriptInterface::luaTileGetItemCount);
	registerMethod("Tile", "getDownItemCount", LuaScriptInterface::luaTileGetDownItemCount);
	registerMethod("Tile", "getTopItemCount", LuaScriptInterface::luaTileGetTopItemCount);

	registerMethod("Tile", "getCreatures", LuaScriptInterface::luaTileGetCreatures);
	registerMethod("Tile", "getCreatureCount", LuaScriptInterface::luaTileGetCreatureCount);

	registerMethod("Tile", "getThingIndex", LuaScriptInterface::luaTileGetThingIndex);

	registerMethod("Tile", "hasProperty", LuaScriptInterface::luaTileHasProperty);
	registerMethod("Tile", "hasFlag", LuaScriptInterface::luaTileHasFlag);

	registerMethod("Tile", "queryAdd", LuaScriptInterface::luaTileQueryAdd);

	registerMethod("Tile", "getHouse", LuaScriptInterface::luaTileGetHouse);

	// NetworkMessage
	registerClass("NetworkMessage", "", LuaScriptInterface::luaNetworkMessageCreate);
	registerMetaMethod("NetworkMessage", "__eq", LuaScriptInterface::luaUserdataCompare);
	registerMetaMethod("NetworkMessage", "__gc", LuaScriptInterface::luaNetworkMessageDelete);
	registerMethod("NetworkMessage", "delete", LuaScriptInterface::luaNetworkMessageDelete);

	registerMethod("NetworkMessage", "getByte", LuaScriptInterface::luaNetworkMessageGetByte);
	registerMethod("NetworkMessage", "getU16", LuaScriptInterface::luaNetworkMessageGetU16);
	registerMethod("NetworkMessage", "getU32", LuaScriptInterface::luaNetworkMessageGetU32);
	registerMethod("NetworkMessage", "getU64", LuaScriptInterface::luaNetworkMessageGetU64);
	registerMethod("NetworkMessage", "getString", LuaScriptInterface::luaNetworkMessageGetString);
	registerMethod("NetworkMessage", "getPosition", LuaScriptInterface::luaNetworkMessageGetPosition);

	registerMethod("NetworkMessage", "addByte", LuaScriptInterface::luaNetworkMessageAddByte);
	registerMethod("NetworkMessage", "addU16", LuaScriptInterface::luaNetworkMessageAddU16);
	registerMethod("NetworkMessage", "addU32", LuaScriptInterface::luaNetworkMessageAddU32);
	registerMethod("NetworkMessage", "addU64", LuaScriptInterface::luaNetworkMessageAddU64);
	registerMethod("NetworkMessage", "addString", LuaScriptInterface::luaNetworkMessageAddString);
	registerMethod("NetworkMessage", "addPosition", LuaScriptInterface::luaNetworkMessageAddPosition);
	registerMethod("NetworkMessage", "addDouble", LuaScriptInterface::luaNetworkMessageAddDouble);
	registerMethod("NetworkMessage", "addItem", LuaScriptInterface::luaNetworkMessageAddItem);
	registerMethod("NetworkMessage", "addItemId", LuaScriptInterface::luaNetworkMessageAddItemId);

	registerMethod("NetworkMessage", "reset", LuaScriptInterface::luaNetworkMessageReset);
	registerMethod("NetworkMessage", "skipBytes", LuaScriptInterface::luaNetworkMessageSkipBytes);
	registerMethod("NetworkMessage", "sendToPlayer", LuaScriptInterface::luaNetworkMessageSendToPlayer);

	// ModalWindow
	registerClass("ModalWindow", "", LuaScriptInterface::luaModalWindowCreate);
	registerMetaMethod("ModalWindow", "__eq", LuaScriptInterface::luaUserdataCompare);
	registerMetaMethod("ModalWindow", "__gc", LuaScriptInterface::luaModalWindowDelete);
	registerMethod("ModalWindow", "delete", LuaScriptInterface::luaModalWindowDelete);

	registerMethod("ModalWindow", "getId", LuaScriptInterface::luaModalWindowGetId);
	registerMethod("ModalWindow", "getTitle", LuaScriptInterface::luaModalWindowGetTitle);
	registerMethod("ModalWindow", "getMessage", LuaScriptInterface::luaModalWindowGetMessage);

	registerMethod("ModalWindow", "setTitle", LuaScriptInterface::luaModalWindowSetTitle);
	registerMethod("ModalWindow", "setMessage", LuaScriptInterface::luaModalWindowSetMessage);

	registerMethod("ModalWindow", "getButtonCount", LuaScriptInterface::luaModalWindowGetButtonCount);
	registerMethod("ModalWindow", "getChoiceCount", LuaScriptInterface::luaModalWindowGetChoiceCount);

	registerMethod("ModalWindow", "addButton", LuaScriptInterface::luaModalWindowAddButton);
	registerMethod("ModalWindow", "addChoice", LuaScriptInterface::luaModalWindowAddChoice);

	registerMethod("ModalWindow", "getDefaultEnterButton", LuaScriptInterface::luaModalWindowGetDefaultEnterButton);
	registerMethod("ModalWindow", "setDefaultEnterButton", LuaScriptInterface::luaModalWindowSetDefaultEnterButton);

	registerMethod("ModalWindow", "getDefaultEscapeButton", LuaScriptInterface::luaModalWindowGetDefaultEscapeButton);
	registerMethod("ModalWindow", "setDefaultEscapeButton", LuaScriptInterface::luaModalWindowSetDefaultEscapeButton);

	registerMethod("ModalWindow", "hasPriority", LuaScriptInterface::luaModalWindowHasPriority);
	registerMethod("ModalWindow", "setPriority", LuaScriptInterface::luaModalWindowSetPriority);

	registerMethod("ModalWindow", "sendToPlayer", LuaScriptInterface::luaModalWindowSendToPlayer);

	// Item
	registerClass("Item", "", LuaScriptInterface::luaItemCreate);
	registerMetaMethod("Item", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Item", "isItem", LuaScriptInterface::luaItemIsItem);

	registerMethod("Item", "getParent", LuaScriptInterface::luaItemGetParent);
	registerMethod("Item", "getTopParent", LuaScriptInterface::luaItemGetTopParent);

	registerMethod("Item", "getId", LuaScriptInterface::luaItemGetId);

	registerMethod("Item", "clone", LuaScriptInterface::luaItemClone);
	registerMethod("Item", "split", LuaScriptInterface::luaItemSplit);
	registerMethod("Item", "remove", LuaScriptInterface::luaItemRemove);

	registerMethod("Item", "getUniqueId", LuaScriptInterface::luaItemGetUniqueId);
	registerMethod("Item", "getActionId", LuaScriptInterface::luaItemGetActionId);
	registerMethod("Item", "setActionId", LuaScriptInterface::luaItemSetActionId);

	registerMethod("Item", "getCount", LuaScriptInterface::luaItemGetCount);
	registerMethod("Item", "getCharges", LuaScriptInterface::luaItemGetCharges);
	registerMethod("Item", "getFluidType", LuaScriptInterface::luaItemGetFluidType);
	registerMethod("Item", "getWeight", LuaScriptInterface::luaItemGetWeight);

	registerMethod("Item", "getSubType", LuaScriptInterface::luaItemGetSubType);

	registerMethod("Item", "getName", LuaScriptInterface::luaItemGetName);
	registerMethod("Item", "getPluralName", LuaScriptInterface::luaItemGetPluralName);
	registerMethod("Item", "getArticle", LuaScriptInterface::luaItemGetArticle);

	registerMethod("Item", "getPosition", LuaScriptInterface::luaItemGetPosition);
	registerMethod("Item", "getTile", LuaScriptInterface::luaItemGetTile);

	registerMethod("Item", "hasAttribute", LuaScriptInterface::luaItemHasAttribute);
	registerMethod("Item", "getAttribute", LuaScriptInterface::luaItemGetAttribute);
	registerMethod("Item", "setAttribute", LuaScriptInterface::luaItemSetAttribute);
	registerMethod("Item", "removeAttribute", LuaScriptInterface::luaItemRemoveAttribute);

	registerMethod("Item", "moveTo", LuaScriptInterface::luaItemMoveTo);
	registerMethod("Item", "transform", LuaScriptInterface::luaItemTransform);
	registerMethod("Item", "decay", LuaScriptInterface::luaItemDecay);

	registerMethod("Item", "getDescription", LuaScriptInterface::luaItemGetDescription);

	registerMethod("Item", "hasProperty", LuaScriptInterface::luaItemHasProperty);

	// Container
	registerClass("Container", "Item", LuaScriptInterface::luaContainerCreate);
	registerMetaMethod("Container", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Container", "getSize", LuaScriptInterface::luaContainerGetSize);
	registerMethod("Container", "getCapacity", LuaScriptInterface::luaContainerGetCapacity);
	registerMethod("Container", "getEmptySlots", LuaScriptInterface::luaContainerGetEmptySlots);

	registerMethod("Container", "getItemHoldingCount", LuaScriptInterface::luaContainerGetItemHoldingCount);
	registerMethod("Container", "getItemCountById", LuaScriptInterface::luaContainerGetItemCountById);

	registerMethod("Container", "getItem", LuaScriptInterface::luaContainerGetItem);
	registerMethod("Container", "hasItem", LuaScriptInterface::luaContainerHasItem);
	registerMethod("Container", "addItem", LuaScriptInterface::luaContainerAddItem);
	registerMethod("Container", "addItemEx", LuaScriptInterface::luaContainerAddItemEx);

	// Teleport
	registerClass("Teleport", "Item", LuaScriptInterface::luaTeleportCreate);
	registerMetaMethod("Teleport", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Teleport", "getDestination", LuaScriptInterface::luaTeleportGetDestination);
	registerMethod("Teleport", "setDestination", LuaScriptInterface::luaTeleportSetDestination);

	// Creature
	registerClass("Creature", "", LuaScriptInterface::luaCreatureCreate);
	registerMetaMethod("Creature", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Creature", "getEvents", LuaScriptInterface::luaCreatureGetEvents);
	registerMethod("Creature", "registerEvent", LuaScriptInterface::luaCreatureRegisterEvent);
	registerMethod("Creature", "unregisterEvent", LuaScriptInterface::luaCreatureUnregisterEvent);

	registerMethod("Creature", "isRemoved", LuaScriptInterface::luaCreatureIsRemoved);
	registerMethod("Creature", "isCreature", LuaScriptInterface::luaCreatureIsCreature);
	registerMethod("Creature", "isInGhostMode", LuaScriptInterface::luaCreatureIsInGhostMode);
	registerMethod("Creature", "isHealthHidden", LuaScriptInterface::luaCreatureIsHealthHidden);

	registerMethod("Creature", "canSee", LuaScriptInterface::luaCreatureCanSee);
	registerMethod("Creature", "canSeeCreature", LuaScriptInterface::luaCreatureCanSeeCreature);

	registerMethod("Creature", "getParent", LuaScriptInterface::luaCreatureGetParent);

	registerMethod("Creature", "getId", LuaScriptInterface::luaCreatureGetId);
	registerMethod("Creature", "getName", LuaScriptInterface::luaCreatureGetName);

	registerMethod("Creature", "getTarget", LuaScriptInterface::luaCreatureGetTarget);
	registerMethod("Creature", "setTarget", LuaScriptInterface::luaCreatureSetTarget);

	registerMethod("Creature", "getFollowCreature", LuaScriptInterface::luaCreatureGetFollowCreature);
	registerMethod("Creature", "setFollowCreature", LuaScriptInterface::luaCreatureSetFollowCreature);

	registerMethod("Creature", "getMaster", LuaScriptInterface::luaCreatureGetMaster);
	registerMethod("Creature", "setMaster", LuaScriptInterface::luaCreatureSetMaster);

	registerMethod("Creature", "getLight", LuaScriptInterface::luaCreatureGetLight);
	registerMethod("Creature", "setLight", LuaScriptInterface::luaCreatureSetLight);

	registerMethod("Creature", "getSpeed", LuaScriptInterface::luaCreatureGetSpeed);
	registerMethod("Creature", "getBaseSpeed", LuaScriptInterface::luaCreatureGetBaseSpeed);
	registerMethod("Creature", "changeSpeed", LuaScriptInterface::luaCreatureChangeSpeed);

	registerMethod("Creature", "setDropLoot", LuaScriptInterface::luaCreatureSetDropLoot);

	registerMethod("Creature", "getPosition", LuaScriptInterface::luaCreatureGetPosition);
	registerMethod("Creature", "getTile", LuaScriptInterface::luaCreatureGetTile);
	registerMethod("Creature", "getDirection", LuaScriptInterface::luaCreatureGetDirection);
	registerMethod("Creature", "setDirection", LuaScriptInterface::luaCreatureSetDirection);

	registerMethod("Creature", "getHealth", LuaScriptInterface::luaCreatureGetHealth);
	registerMethod("Creature", "setHealth", LuaScriptInterface::luaCreatureSetHealth);
	registerMethod("Creature", "addHealth", LuaScriptInterface::luaCreatureAddHealth);
	registerMethod("Creature", "getMaxHealth", LuaScriptInterface::luaCreatureGetMaxHealth);

	registerMethod("Creature", "setMaxHealth", LuaScriptInterface::luaCreatureSetMaxHealth);
	registerMethod("Creature", "setHiddenHealth", LuaScriptInterface::luaCreatureSetHiddenHealth);

	registerMethod("Creature", "getMana", LuaScriptInterface::luaCreatureGetMana);
	registerMethod("Creature", "addMana", LuaScriptInterface::luaCreatureAddMana);
	registerMethod("Creature", "getMaxMana", LuaScriptInterface::luaCreatureGetMaxMana);

	registerMethod("Creature", "getSkull", LuaScriptInterface::luaCreatureGetSkull);
	registerMethod("Creature", "setSkull", LuaScriptInterface::luaCreatureSetSkull);

	registerMethod("Creature", "getOutfit", LuaScriptInterface::luaCreatureGetOutfit);
	registerMethod("Creature", "setOutfit", LuaScriptInterface::luaCreatureSetOutfit);

	registerMethod("Creature", "getCondition", LuaScriptInterface::luaCreatureGetCondition);
	registerMethod("Creature", "addCondition", LuaScriptInterface::luaCreatureAddCondition);
	registerMethod("Creature", "removeCondition", LuaScriptInterface::luaCreatureRemoveCondition);

	registerMethod("Creature", "remove", LuaScriptInterface::luaCreatureRemove);
	registerMethod("Creature", "teleportTo", LuaScriptInterface::luaCreatureTeleportTo);
	registerMethod("Creature", "say", LuaScriptInterface::luaCreatureSay);

	registerMethod("Creature", "getDamageMap", LuaScriptInterface::luaCreatureGetDamageMap);

	registerMethod("Creature", "getSummons", LuaScriptInterface::luaCreatureGetSummons);

	registerMethod("Creature", "getDescription", LuaScriptInterface::luaCreatureGetDescription);

	registerMethod("Creature", "getPathTo", LuaScriptInterface::luaCreatureGetPathTo);
	registerMethod("Creature", "move", LuaScriptInterface::luaCreatureMove);
	registerMethod("Creature", "getWalkDelay", LuaScriptInterface::luaCreatureGetWalkDelay);

	// Player
	registerClass("Player", "Creature", LuaScriptInterface::luaPlayerCreate);
	registerMetaMethod("Player", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Player", "isPlayer", LuaScriptInterface::luaPlayerIsPlayer);

	registerMethod("Player", "getGuid", LuaScriptInterface::luaPlayerGetGuid);
	registerMethod("Player", "getIp", LuaScriptInterface::luaPlayerGetIp);
	registerMethod("Player", "getAccountId", LuaScriptInterface::luaPlayerGetAccountId);
	registerMethod("Player", "getLastLoginSaved", LuaScriptInterface::luaPlayerGetLastLoginSaved);
	registerMethod("Player", "getLastLogout", LuaScriptInterface::luaPlayerGetLastLogout);

	registerMethod("Player", "getAccountType", LuaScriptInterface::luaPlayerGetAccountType);
	registerMethod("Player", "setAccountType", LuaScriptInterface::luaPlayerSetAccountType);

	registerMethod("Player", "getCapacity", LuaScriptInterface::luaPlayerGetCapacity);
	registerMethod("Player", "setCapacity", LuaScriptInterface::luaPlayerSetCapacity);

	registerMethod("Player", "getFreeCapacity", LuaScriptInterface::luaPlayerGetFreeCapacity);

	registerMethod("Player", "getDepotChest", LuaScriptInterface::luaPlayerGetDepotChest);
	registerMethod("Player", "getInbox", LuaScriptInterface::luaPlayerGetInbox);

	registerMethod("Player", "getSkullTime", LuaScriptInterface::luaPlayerGetSkullTime);
	registerMethod("Player", "setSkullTime", LuaScriptInterface::luaPlayerSetSkullTime);
	registerMethod("Player", "getDeathPenalty", LuaScriptInterface::luaPlayerGetDeathPenalty);

	registerMethod("Player", "getExperience", LuaScriptInterface::luaPlayerGetExperience);
	registerMethod("Player", "addExperience", LuaScriptInterface::luaPlayerAddExperience);
	registerMethod("Player", "removeExperience", LuaScriptInterface::luaPlayerRemoveExperience);
	registerMethod("Player", "getLevel", LuaScriptInterface::luaPlayerGetLevel);

	registerMethod("Player", "getMagicLevel", LuaScriptInterface::luaPlayerGetMagicLevel);
	registerMethod("Player", "getBaseMagicLevel", LuaScriptInterface::luaPlayerGetBaseMagicLevel);
	registerMethod("Player", "setMaxMana", LuaScriptInterface::luaPlayerSetMaxMana);
	registerMethod("Player", "getManaSpent", LuaScriptInterface::luaPlayerGetManaSpent);
	registerMethod("Player", "addManaSpent", LuaScriptInterface::luaPlayerAddManaSpent);

	registerMethod("Player", "getBaseMaxHealth", LuaScriptInterface::luaPlayerGetBaseMaxHealth);
	registerMethod("Player", "getBaseMaxMana", LuaScriptInterface::luaPlayerGetBaseMaxMana);

	registerMethod("Player", "getSkillLevel", LuaScriptInterface::luaPlayerGetSkillLevel);
	registerMethod("Player", "getEffectiveSkillLevel", LuaScriptInterface::luaPlayerGetEffectiveSkillLevel);
	registerMethod("Player", "getSkillPercent", LuaScriptInterface::luaPlayerGetSkillPercent);
	registerMethod("Player", "getSkillTries", LuaScriptInterface::luaPlayerGetSkillTries);
	registerMethod("Player", "addSkillTries", LuaScriptInterface::luaPlayerAddSkillTries);

	registerMethod("Player", "addOfflineTrainingTime", LuaScriptInterface::luaPlayerAddOfflineTrainingTime);
	registerMethod("Player", "getOfflineTrainingTime", LuaScriptInterface::luaPlayerGetOfflineTrainingTime);
	registerMethod("Player", "removeOfflineTrainingTime", LuaScriptInterface::luaPlayerRemoveOfflineTrainingTime);

	registerMethod("Player", "addOfflineTrainingTries", LuaScriptInterface::luaPlayerAddOfflineTrainingTries);

	registerMethod("Player", "getOfflineTrainingSkill", LuaScriptInterface::luaPlayerGetOfflineTrainingSkill);
	registerMethod("Player", "setOfflineTrainingSkill", LuaScriptInterface::luaPlayerSetOfflineTrainingSkill);

	registerMethod("Player", "getItemCount", LuaScriptInterface::luaPlayerGetItemCount);
	registerMethod("Player", "getItemById", LuaScriptInterface::luaPlayerGetItemById);

	registerMethod("Player", "getVocation", LuaScriptInterface::luaPlayerGetVocation);
	registerMethod("Player", "setVocation", LuaScriptInterface::luaPlayerSetVocation);

	registerMethod("Player", "getSex", LuaScriptInterface::luaPlayerGetSex);
	registerMethod("Player", "setSex", LuaScriptInterface::luaPlayerSetSex);

	registerMethod("Player", "getTown", LuaScriptInterface::luaPlayerGetTown);
	registerMethod("Player", "setTown", LuaScriptInterface::luaPlayerSetTown);

	registerMethod("Player", "getGuild", LuaScriptInterface::luaPlayerGetGuild);
	registerMethod("Player", "setGuild", LuaScriptInterface::luaPlayerSetGuild);

	registerMethod("Player", "getGuildLevel", LuaScriptInterface::luaPlayerGetGuildLevel);
	registerMethod("Player", "setGuildLevel", LuaScriptInterface::luaPlayerSetGuildLevel);

	registerMethod("Player", "getGuildNick", LuaScriptInterface::luaPlayerGetGuildNick);
	registerMethod("Player", "setGuildNick", LuaScriptInterface::luaPlayerSetGuildNick);

	registerMethod("Player", "getGroup", LuaScriptInterface::luaPlayerGetGroup);
	registerMethod("Player", "setGroup", LuaScriptInterface::luaPlayerSetGroup);

	registerMethod("Player", "getStamina", LuaScriptInterface::luaPlayerGetStamina);
	registerMethod("Player", "setStamina", LuaScriptInterface::luaPlayerSetStamina);

	registerMethod("Player", "getSoul", LuaScriptInterface::luaPlayerGetSoul);
	registerMethod("Player", "addSoul", LuaScriptInterface::luaPlayerAddSoul);
	registerMethod("Player", "getMaxSoul", LuaScriptInterface::luaPlayerGetMaxSoul);

	registerMethod("Player", "getBankBalance", LuaScriptInterface::luaPlayerGetBankBalance);
	registerMethod("Player", "setBankBalance", LuaScriptInterface::luaPlayerSetBankBalance);

	registerMethod("Player", "getStorageValue", LuaScriptInterface::luaPlayerGetStorageValue);
	registerMethod("Player", "setStorageValue", LuaScriptInterface::luaPlayerSetStorageValue);

	registerMethod("Player", "addItem", LuaScriptInterface::luaPlayerAddItem);
	registerMethod("Player", "addItemEx", LuaScriptInterface::luaPlayerAddItemEx);
	registerMethod("Player", "removeItem", LuaScriptInterface::luaPlayerRemoveItem);

	registerMethod("Player", "getMoney", LuaScriptInterface::luaPlayerGetMoney);
	registerMethod("Player", "addMoney", LuaScriptInterface::luaPlayerAddMoney);
	registerMethod("Player", "removeMoney", LuaScriptInterface::luaPlayerRemoveMoney);

	registerMethod("Player", "showTextDialog", LuaScriptInterface::luaPlayerShowTextDialog);

	registerMethod("Player", "sendTextMessage", LuaScriptInterface::luaPlayerSendTextMessage);
	registerMethod("Player", "sendChannelMessage", LuaScriptInterface::luaPlayerSendChannelMessage);
	registerMethod("Player", "sendPrivateMessage", LuaScriptInterface::luaPlayerSendPrivateMessage);
	registerMethod("Player", "channelSay", LuaScriptInterface::luaPlayerChannelSay);
	registerMethod("Player", "openChannel", LuaScriptInterface::luaPlayerOpenChannel);

	registerMethod("Player", "getSlotItem", LuaScriptInterface::luaPlayerGetSlotItem);

	registerMethod("Player", "getParty", LuaScriptInterface::luaPlayerGetParty);

	registerMethod("Player", "addOutfit", LuaScriptInterface::luaPlayerAddOutfit);
	registerMethod("Player", "addOutfitAddon", LuaScriptInterface::luaPlayerAddOutfitAddon);
	registerMethod("Player", "removeOutfit", LuaScriptInterface::luaPlayerRemoveOutfit);
	registerMethod("Player", "removeOutfitAddon", LuaScriptInterface::luaPlayerRemoveOutfitAddon);
	registerMethod("Player", "hasOutfit", LuaScriptInterface::luaPlayerHasOutfit);
	registerMethod("Player", "sendOutfitWindow", LuaScriptInterface::luaPlayerSendOutfitWindow);

	registerMethod("Player", "addMount", LuaScriptInterface::luaPlayerAddMount);
	registerMethod("Player", "removeMount", LuaScriptInterface::luaPlayerRemoveMount);
	registerMethod("Player", "hasMount", LuaScriptInterface::luaPlayerHasMount);

	registerMethod("Player", "getPremiumDays", LuaScriptInterface::luaPlayerGetPremiumDays);
	registerMethod("Player", "addPremiumDays", LuaScriptInterface::luaPlayerAddPremiumDays);
	registerMethod("Player", "removePremiumDays", LuaScriptInterface::luaPlayerRemovePremiumDays);

	registerMethod("Player", "hasBlessing", LuaScriptInterface::luaPlayerHasBlessing);
	registerMethod("Player", "addBlessing", LuaScriptInterface::luaPlayerAddBlessing);
	registerMethod("Player", "removeBlessing", LuaScriptInterface::luaPlayerRemoveBlessing);

	registerMethod("Player", "canLearnSpell", LuaScriptInterface::luaPlayerCanLearnSpell);
	registerMethod("Player", "learnSpell", LuaScriptInterface::luaPlayerLearnSpell);
	registerMethod("Player", "forgetSpell", LuaScriptInterface::luaPlayerForgetSpell);
	registerMethod("Player", "hasLearnedSpell", LuaScriptInterface::luaPlayerHasLearnedSpell);

	registerMethod("Player", "sendTutorial", LuaScriptInterface::luaPlayerSendTutorial);
	registerMethod("Player", "addMapMark", LuaScriptInterface::luaPlayerAddMapMark);

	registerMethod("Player", "save", LuaScriptInterface::luaPlayerSave);
	registerMethod("Player", "popupFYI", LuaScriptInterface::luaPlayerPopupFYI);

	registerMethod("Player", "isPzLocked", LuaScriptInterface::luaPlayerIsPzLocked);

	registerMethod("Player", "getClient", LuaScriptInterface::luaPlayerGetClient);
	registerMethod("Player", "getHouse", LuaScriptInterface::luaPlayerGetHouse);

	registerMethod("Player", "setGhostMode", LuaScriptInterface::luaPlayerSetGhostMode);

	registerMethod("Player", "getContainerId", LuaScriptInterface::luaPlayerGetContainerId);
	registerMethod("Player", "getContainerById", LuaScriptInterface::luaPlayerGetContainerById);
	registerMethod("Player", "getContainerIndex", LuaScriptInterface::luaPlayerGetContainerIndex);

	// Monster
	registerClass("Monster", "Creature", LuaScriptInterface::luaMonsterCreate);
	registerMetaMethod("Monster", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Monster", "isMonster", LuaScriptInterface::luaMonsterIsMonster);

	registerMethod("Monster", "getType", LuaScriptInterface::luaMonsterGetType);

	registerMethod("Monster", "getSpawnPosition", LuaScriptInterface::luaMonsterGetSpawnPosition);
	registerMethod("Monster", "isInSpawnRange", LuaScriptInterface::luaMonsterIsInSpawnRange);

	registerMethod("Monster", "isIdle", LuaScriptInterface::luaMonsterIsIdle);
	registerMethod("Monster", "setIdle", LuaScriptInterface::luaMonsterSetIdle);

	registerMethod("Monster", "isTarget", LuaScriptInterface::luaMonsterIsTarget);
	registerMethod("Monster", "isOpponent", LuaScriptInterface::luaMonsterIsOpponent);
	registerMethod("Monster", "isFriend", LuaScriptInterface::luaMonsterIsFriend);

	registerMethod("Monster", "addFriend", LuaScriptInterface::luaMonsterAddFriend);
	registerMethod("Monster", "removeFriend", LuaScriptInterface::luaMonsterRemoveFriend);
	registerMethod("Monster", "getFriendList", LuaScriptInterface::luaMonsterGetFriendList);
	registerMethod("Monster", "getFriendCount", LuaScriptInterface::luaMonsterGetFriendCount);

	registerMethod("Monster", "addTarget", LuaScriptInterface::luaMonsterAddTarget);
	registerMethod("Monster", "removeTarget", LuaScriptInterface::luaMonsterRemoveTarget);
	registerMethod("Monster", "getTargetList", LuaScriptInterface::luaMonsterGetTargetList);
	registerMethod("Monster", "getTargetCount", LuaScriptInterface::luaMonsterGetTargetCount);

	registerMethod("Monster", "selectTarget", LuaScriptInterface::luaMonsterSelectTarget);
	registerMethod("Monster", "searchTarget", LuaScriptInterface::luaMonsterSearchTarget);

	//get exp from monsters
	registerMethod("Monster", "getExperience", LuaScriptInterface::luaMonsterGetExperience); //pota
	registerMethod("Monster", "setExperience", LuaScriptInterface::luaMonsterSetExperience); //pota
	registerMethod("Monster", "getLevel", LuaScriptInterface::luaMonsterGetLevel); //pota
	registerMethod("Monster", "getBoost", LuaScriptInterface::luaMonsterGetBoost); //pota

	// Npc
	registerClass("Npc", "Creature", LuaScriptInterface::luaNpcCreate);
	registerMetaMethod("Npc", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Npc", "isNpc", LuaScriptInterface::luaNpcIsNpc);

	registerMethod("Npc", "setMasterPos", LuaScriptInterface::luaNpcSetMasterPos);

	registerMethod("Npc", "getSpeechBubble", LuaScriptInterface::luaNpcGetSpeechBubble);
	registerMethod("Npc", "setSpeechBubble", LuaScriptInterface::luaNpcSetSpeechBubble);

	// Guild
	registerClass("Guild", "", LuaScriptInterface::luaGuildCreate);
	registerMetaMethod("Guild", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Guild", "getId", LuaScriptInterface::luaGuildGetId);
	registerMethod("Guild", "getName", LuaScriptInterface::luaGuildGetName);
	registerMethod("Guild", "getMembersOnline", LuaScriptInterface::luaGuildGetMembersOnline);

	registerMethod("Guild", "addRank", LuaScriptInterface::luaGuildAddRank);
	registerMethod("Guild", "getRankById", LuaScriptInterface::luaGuildGetRankById);
	registerMethod("Guild", "getRankByLevel", LuaScriptInterface::luaGuildGetRankByLevel);

	registerMethod("Guild", "getMotd", LuaScriptInterface::luaGuildGetMotd);
	registerMethod("Guild", "setMotd", LuaScriptInterface::luaGuildSetMotd);

	// Group
	registerClass("Group", "", LuaScriptInterface::luaGroupCreate);
	registerMetaMethod("Group", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Group", "getId", LuaScriptInterface::luaGroupGetId);
	registerMethod("Group", "getName", LuaScriptInterface::luaGroupGetName);
	registerMethod("Group", "getFlags", LuaScriptInterface::luaGroupGetFlags);
	registerMethod("Group", "getAccess", LuaScriptInterface::luaGroupGetAccess);
	registerMethod("Group", "getMaxDepotItems", LuaScriptInterface::luaGroupGetMaxDepotItems);
	registerMethod("Group", "getMaxVipEntries", LuaScriptInterface::luaGroupGetMaxVipEntries);

	// Vocation
	registerClass("Vocation", "", LuaScriptInterface::luaVocationCreate);
	registerMetaMethod("Vocation", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Vocation", "getId", LuaScriptInterface::luaVocationGetId);
	registerMethod("Vocation", "getClientId", LuaScriptInterface::luaVocationGetClientId);
	registerMethod("Vocation", "getName", LuaScriptInterface::luaVocationGetName);
	registerMethod("Vocation", "getDescription", LuaScriptInterface::luaVocationGetDescription);

	registerMethod("Vocation", "getRequiredSkillTries", LuaScriptInterface::luaVocationGetRequiredSkillTries);
	registerMethod("Vocation", "getRequiredManaSpent", LuaScriptInterface::luaVocationGetRequiredManaSpent);

	registerMethod("Vocation", "getCapacityGain", LuaScriptInterface::luaVocationGetCapacityGain);

	registerMethod("Vocation", "getHealthGain", LuaScriptInterface::luaVocationGetHealthGain);
	registerMethod("Vocation", "getHealthGainTicks", LuaScriptInterface::luaVocationGetHealthGainTicks);
	registerMethod("Vocation", "getHealthGainAmount", LuaScriptInterface::luaVocationGetHealthGainAmount);

	registerMethod("Vocation", "getManaGain", LuaScriptInterface::luaVocationGetManaGain);
	registerMethod("Vocation", "getManaGainTicks", LuaScriptInterface::luaVocationGetManaGainTicks);
	registerMethod("Vocation", "getManaGainAmount", LuaScriptInterface::luaVocationGetManaGainAmount);

	registerMethod("Vocation", "getMaxSoul", LuaScriptInterface::luaVocationGetMaxSoul);
	registerMethod("Vocation", "getSoulGainTicks", LuaScriptInterface::luaVocationGetSoulGainTicks);

	registerMethod("Vocation", "getAttackSpeed", LuaScriptInterface::luaVocationGetAttackSpeed);
	registerMethod("Vocation", "getBaseSpeed", LuaScriptInterface::luaVocationGetBaseSpeed);

	registerMethod("Vocation", "getDemotion", LuaScriptInterface::luaVocationGetDemotion);
	registerMethod("Vocation", "getPromotion", LuaScriptInterface::luaVocationGetPromotion);

	// Town
	registerClass("Town", "", LuaScriptInterface::luaTownCreate);
	registerMetaMethod("Town", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Town", "getId", LuaScriptInterface::luaTownGetId);
	registerMethod("Town", "getName", LuaScriptInterface::luaTownGetName);
	registerMethod("Town", "getTemplePosition", LuaScriptInterface::luaTownGetTemplePosition);

	// House
	registerClass("House", "", LuaScriptInterface::luaHouseCreate);
	registerMetaMethod("House", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("House", "getId", LuaScriptInterface::luaHouseGetId);
	registerMethod("House", "getName", LuaScriptInterface::luaHouseGetName);
	registerMethod("House", "getTown", LuaScriptInterface::luaHouseGetTown);
	registerMethod("House", "getExitPosition", LuaScriptInterface::luaHouseGetExitPosition);
	registerMethod("House", "getRent", LuaScriptInterface::luaHouseGetRent);

	registerMethod("House", "getOwnerGuid", LuaScriptInterface::luaHouseGetOwnerGuid);
	registerMethod("House", "setOwnerGuid", LuaScriptInterface::luaHouseSetOwnerGuid);

	registerMethod("House", "getBeds", LuaScriptInterface::luaHouseGetBeds);
	registerMethod("House", "getBedCount", LuaScriptInterface::luaHouseGetBedCount);

	registerMethod("House", "getDoors", LuaScriptInterface::luaHouseGetDoors);
	registerMethod("House", "getDoorCount", LuaScriptInterface::luaHouseGetDoorCount);

	registerMethod("House", "getTiles", LuaScriptInterface::luaHouseGetTiles);
	registerMethod("House", "getTileCount", LuaScriptInterface::luaHouseGetTileCount);

	registerMethod("House", "getAccessList", LuaScriptInterface::luaHouseGetAccessList);
	registerMethod("House", "setAccessList", LuaScriptInterface::luaHouseSetAccessList);

	// ItemType
	registerClass("ItemType", "", LuaScriptInterface::luaItemTypeCreate);
	registerMetaMethod("ItemType", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("ItemType", "isCorpse", LuaScriptInterface::luaItemTypeIsCorpse);
	registerMethod("ItemType", "isDoor", LuaScriptInterface::luaItemTypeIsDoor);
	registerMethod("ItemType", "isContainer", LuaScriptInterface::luaItemTypeIsContainer);
	registerMethod("ItemType", "isFluidContainer", LuaScriptInterface::luaItemTypeIsFluidContainer);
	registerMethod("ItemType", "isMovable", LuaScriptInterface::luaItemTypeIsMovable);
	registerMethod("ItemType", "isRune", LuaScriptInterface::luaItemTypeIsRune);
	registerMethod("ItemType", "isStackable", LuaScriptInterface::luaItemTypeIsStackable);
	registerMethod("ItemType", "isReadable", LuaScriptInterface::luaItemTypeIsReadable);
	registerMethod("ItemType", "isWritable", LuaScriptInterface::luaItemTypeIsWritable);

	registerMethod("ItemType", "getType", LuaScriptInterface::luaItemTypeGetType);
	registerMethod("ItemType", "getId", LuaScriptInterface::luaItemTypeGetId);
	registerMethod("ItemType", "getClientId", LuaScriptInterface::luaItemTypeGetClientId);
	registerMethod("ItemType", "getName", LuaScriptInterface::luaItemTypeGetName);
	registerMethod("ItemType", "getPluralName", LuaScriptInterface::luaItemTypeGetPluralName);
	registerMethod("ItemType", "getArticle", LuaScriptInterface::luaItemTypeGetArticle);
	registerMethod("ItemType", "getDescription", LuaScriptInterface::luaItemTypeGetDescription);
	registerMethod("ItemType", "getSlotPosition", LuaScriptInterface::luaItemTypeGetSlotPosition);

	registerMethod("ItemType", "getCharges", LuaScriptInterface::luaItemTypeGetCharges);
	registerMethod("ItemType", "getFluidSource", LuaScriptInterface::luaItemTypeGetFluidSource);
	registerMethod("ItemType", "getCapacity", LuaScriptInterface::luaItemTypeGetCapacity);
	registerMethod("ItemType", "getWeight", LuaScriptInterface::luaItemTypeGetWeight);

	registerMethod("ItemType", "getHitChance", LuaScriptInterface::luaItemTypeGetHitChance);
	registerMethod("ItemType", "getShootRange", LuaScriptInterface::luaItemTypeGetShootRange);

	registerMethod("ItemType", "getAttack", LuaScriptInterface::luaItemTypeGetAttack);
	registerMethod("ItemType", "getDefense", LuaScriptInterface::luaItemTypeGetDefense);
	registerMethod("ItemType", "getExtraDefense", LuaScriptInterface::luaItemTypeGetExtraDefense);
	registerMethod("ItemType", "getArmor", LuaScriptInterface::luaItemTypeGetArmor);
	registerMethod("ItemType", "getWeaponType", LuaScriptInterface::luaItemTypeGetWeaponType);

	registerMethod("ItemType", "getElementType", LuaScriptInterface::luaItemTypeGetElementType);
	registerMethod("ItemType", "getElementDamage", LuaScriptInterface::luaItemTypeGetElementDamage);

	registerMethod("ItemType", "getTransformEquipId", LuaScriptInterface::luaItemTypeGetTransformEquipId);
	registerMethod("ItemType", "getTransformDeEquipId", LuaScriptInterface::luaItemTypeGetTransformDeEquipId);
	registerMethod("ItemType", "getDestroyId", LuaScriptInterface::luaItemTypeGetDestroyId);
	registerMethod("ItemType", "getDecayId", LuaScriptInterface::luaItemTypeGetDecayId);
	registerMethod("ItemType", "getRequiredLevel", LuaScriptInterface::luaItemTypeGetRequiredLevel);

	registerMethod("ItemType", "hasSubType", LuaScriptInterface::luaItemTypeHasSubType);

	// Combat
	registerClass("Combat", "", LuaScriptInterface::luaCombatCreate);
	registerMetaMethod("Combat", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Combat", "setParameter", LuaScriptInterface::luaCombatSetParameter);
	registerMethod("Combat", "setFormula", LuaScriptInterface::luaCombatSetFormula);

	registerMethod("Combat", "setArea", LuaScriptInterface::luaCombatSetArea);
	registerMethod("Combat", "setCondition", LuaScriptInterface::luaCombatSetCondition);
	registerMethod("Combat", "setCallback", LuaScriptInterface::luaCombatSetCallback);
	registerMethod("Combat", "setOrigin", LuaScriptInterface::luaCombatSetOrigin);

	registerMethod("Combat", "execute", LuaScriptInterface::luaCombatExecute);

	// Condition
	registerClass("Condition", "", LuaScriptInterface::luaConditionCreate);
	registerMetaMethod("Condition", "__eq", LuaScriptInterface::luaUserdataCompare);
	registerMetaMethod("Condition", "__gc", LuaScriptInterface::luaConditionDelete);
	registerMethod("Condition", "delete", LuaScriptInterface::luaConditionDelete);

	registerMethod("Condition", "getId", LuaScriptInterface::luaConditionGetId);
	registerMethod("Condition", "getSubId", LuaScriptInterface::luaConditionGetSubId);
	registerMethod("Condition", "getType", LuaScriptInterface::luaConditionGetType);
	registerMethod("Condition", "getIcons", LuaScriptInterface::luaConditionGetIcons);
	registerMethod("Condition", "getEndTime", LuaScriptInterface::luaConditionGetEndTime);

	registerMethod("Condition", "clone", LuaScriptInterface::luaConditionClone);

	registerMethod("Condition", "getTicks", LuaScriptInterface::luaConditionGetTicks);
	registerMethod("Condition", "setTicks", LuaScriptInterface::luaConditionSetTicks);

	registerMethod("Condition", "setParameter", LuaScriptInterface::luaConditionSetParameter);
	registerMethod("Condition", "setFormula", LuaScriptInterface::luaConditionSetFormula);
	registerMethod("Condition", "setOutfit", LuaScriptInterface::luaConditionSetOutfit);

	registerMethod("Condition", "addDamage", LuaScriptInterface::luaConditionAddDamage);

	// MonsterType
	registerClass("MonsterType", "", LuaScriptInterface::luaMonsterTypeCreate);
	registerMetaMethod("MonsterType", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("MonsterType", "isAttackable", LuaScriptInterface::luaMonsterTypeIsAttackable);
	registerMethod("MonsterType", "isConvinceable", LuaScriptInterface::luaMonsterTypeIsConvinceable);
	registerMethod("MonsterType", "isSummonable", LuaScriptInterface::luaMonsterTypeIsSummonable);
	registerMethod("MonsterType", "isIllusionable", LuaScriptInterface::luaMonsterTypeIsIllusionable);
	registerMethod("MonsterType", "isHostile", LuaScriptInterface::luaMonsterTypeIsHostile);
	registerMethod("MonsterType", "isPassive", LuaScriptInterface::luaMonsterTypeIsPassive); //pota

	registerMethod("MonsterType", "isFlyable", LuaScriptInterface::luaMonsterTypeIsFlyable);
	registerMethod("MonsterType", "isRideable", LuaScriptInterface::luaMonsterTypeIsRideable);
	registerMethod("MonsterType", "isSurfable", LuaScriptInterface::luaMonsterTypeIsSurfable);
	registerMethod("MonsterType", "canTeleport", LuaScriptInterface::luaMonsterTypeCanTeleport);
	registerMethod("MonsterType", "catchChance", LuaScriptInterface::luaMonsterTypeCatchChance);
	registerMethod("MonsterType", "getMoveMagicAttackBase", LuaScriptInterface::luaMonsterTypeGetMoveMagicAttackBase);
	registerMethod("MonsterType", "getMoveMagicDefenseBase", LuaScriptInterface::luaMonsterTypeGetMoveMagicDefenseBase);

	registerMethod("MonsterType", "hasShiny", LuaScriptInterface::luaMonsterTypeHasShiny);
	registerMethod("MonsterType", "hasMega", LuaScriptInterface::luaMonsterTypeHasMega);
	registerMethod("MonsterType", "dexEntry", LuaScriptInterface::luaMonsterTypeDexEntry);
	registerMethod("MonsterType", "portraitId", LuaScriptInterface::luaMonsterTypePortraitId);

	registerMethod("MonsterType", "isPushable", LuaScriptInterface::luaMonsterTypeIsPushable);
	registerMethod("MonsterType", "isHealthShown", LuaScriptInterface::luaMonsterTypeIsHealthShown);

	registerMethod("MonsterType", "canPushItems", LuaScriptInterface::luaMonsterTypeCanPushItems);
	registerMethod("MonsterType", "canPushCreatures", LuaScriptInterface::luaMonsterTypeCanPushCreatures);

	registerMethod("MonsterType", "getName", LuaScriptInterface::luaMonsterTypeGetName);
	registerMethod("MonsterType", "getNameDescription", LuaScriptInterface::luaMonsterTypeGetNameDescription);

	registerMethod("MonsterType", "getHealth", LuaScriptInterface::luaMonsterTypeGetHealth);
	registerMethod("MonsterType", "getMaxHealth", LuaScriptInterface::luaMonsterTypeGetMaxHealth);
	registerMethod("MonsterType", "getRunHealth", LuaScriptInterface::luaMonsterTypeGetRunHealth);
	registerMethod("MonsterType", "getExperience", LuaScriptInterface::luaMonsterTypeGetExperience);

	registerMethod("MonsterType", "getCombatImmunities", LuaScriptInterface::luaMonsterTypeGetCombatImmunities);
	registerMethod("MonsterType", "getConditionImmunities", LuaScriptInterface::luaMonsterTypeGetConditionImmunities);

	registerMethod("MonsterType", "getAttackList", LuaScriptInterface::luaMonsterTypeGetAttackList);
	registerMethod("MonsterType", "getDefenseList", LuaScriptInterface::luaMonsterTypeGetDefenseList);
	registerMethod("MonsterType", "getElementList", LuaScriptInterface::luaMonsterTypeGetElementList);

	registerMethod("MonsterType", "getMoveList", LuaScriptInterface::luaMonsterTypeGetMoveList); //pota

	registerMethod("MonsterType", "getVoices", LuaScriptInterface::luaMonsterTypeGetVoices);
	registerMethod("MonsterType", "getLoot", LuaScriptInterface::luaMonsterTypeGetLoot);

	registerMethod("MonsterType", "getCreatureEvents", LuaScriptInterface::luaMonsterTypeGetCreatureEvents);

	registerMethod("MonsterType", "getSummonList", LuaScriptInterface::luaMonsterTypeGetSummonList);
	registerMethod("MonsterType", "getEvolutionList", LuaScriptInterface::luaMonsterTypeGetEvolutionList); //pota
	registerMethod("MonsterType", "getMaxSummons", LuaScriptInterface::luaMonsterTypeGetMaxSummons);

	registerMethod("MonsterType", "getArmor", LuaScriptInterface::luaMonsterTypeGetArmor);
	registerMethod("MonsterType", "getDefense", LuaScriptInterface::luaMonsterTypeGetDefense);
	registerMethod("MonsterType", "getOutfit", LuaScriptInterface::luaMonsterTypeGetOutfit);
	registerMethod("MonsterType", "getRace", LuaScriptInterface::luaMonsterTypeGetRace);
	registerMethod("MonsterType", "getRace2", LuaScriptInterface::luaMonsterTypeGetRace2); //pota
	registerMethod("MonsterType", "getMinLevel", LuaScriptInterface::luaMonsterTypeGetMinLevel); //pota
	registerMethod("MonsterType", "getMaxLevel", LuaScriptInterface::luaMonsterTypeGetMaxLevel); //pota
	registerMethod("MonsterType", "getCorpseId", LuaScriptInterface::luaMonsterTypeGetCorpseId);
	registerMethod("MonsterType", "getManaCost", LuaScriptInterface::luaMonsterTypeGetManaCost);
	registerMethod("MonsterType", "getBaseSpeed", LuaScriptInterface::luaMonsterTypeGetBaseSpeed);
	registerMethod("MonsterType", "getLight", LuaScriptInterface::luaMonsterTypeGetLight);

	registerMethod("MonsterType", "getStaticAttackChance", LuaScriptInterface::luaMonsterTypeGetStaticAttackChance);
	registerMethod("MonsterType", "getTargetDistance", LuaScriptInterface::luaMonsterTypeGetTargetDistance);
	registerMethod("MonsterType", "getYellChance", LuaScriptInterface::luaMonsterTypeGetYellChance);
	registerMethod("MonsterType", "getYellSpeedTicks", LuaScriptInterface::luaMonsterTypeGetYellSpeedTicks);
	registerMethod("MonsterType", "getChangeTargetChance", LuaScriptInterface::luaMonsterTypeGetChangeTargetChance);
	registerMethod("MonsterType", "getChangeTargetSpeed", LuaScriptInterface::luaMonsterTypeGetChangeTargetSpeed);

	// Party
	registerClass("Party", "", nullptr);
	registerMetaMethod("Party", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Party", "disband", LuaScriptInterface::luaPartyDisband);

	registerMethod("Party", "getLeader", LuaScriptInterface::luaPartyGetLeader);
	registerMethod("Party", "setLeader", LuaScriptInterface::luaPartySetLeader);

	registerMethod("Party", "getMembers", LuaScriptInterface::luaPartyGetMembers);
	registerMethod("Party", "getMemberCount", LuaScriptInterface::luaPartyGetMemberCount);

	registerMethod("Party", "getInvitees", LuaScriptInterface::luaPartyGetInvitees);
	registerMethod("Party", "getInviteeCount", LuaScriptInterface::luaPartyGetInviteeCount);

	registerMethod("Party", "addInvite", LuaScriptInterface::luaPartyAddInvite);
	registerMethod("Party", "removeInvite", LuaScriptInterface::luaPartyRemoveInvite);

	registerMethod("Party", "addMember", LuaScriptInterface::luaPartyAddMember);
	registerMethod("Party", "removeMember", LuaScriptInterface::luaPartyRemoveMember);

	registerMethod("Party", "isSharedExperienceActive", LuaScriptInterface::luaPartyIsSharedExperienceActive);
	registerMethod("Party", "isSharedExperienceEnabled", LuaScriptInterface::luaPartyIsSharedExperienceEnabled);
	registerMethod("Party", "shareExperience", LuaScriptInterface::luaPartyShareExperience);
	registerMethod("Party", "setSharedExperience", LuaScriptInterface::luaPartySetSharedExperience);
}

#undef registerEnum
#undef registerEnumIn

