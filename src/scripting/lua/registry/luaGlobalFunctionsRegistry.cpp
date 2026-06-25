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

	registerGameWorldBindings();
	registerItemCreatureBindings();
	registerPlayerMonsterNpcBindings();
	registerSocialCombatBindings();
	registerPartyBindings();
}

#undef registerEnum
#undef registerEnumIn

