// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "gameEnumTools.hpp"

struct MagicEffectNames {
	const char* name;
	MagicEffectClasses effect;
};

struct ShootTypeNames {
	const char* name;
	ShootType_t shoot;
};

struct CombatTypeNames {
	const char* name;
	CombatType_t combat;
};

struct AmmoTypeNames {
	const char* name;
	Ammo_t ammoType;
};

struct WeaponActionNames {
	const char* name;
	WeaponAction_t weaponAction;
};

struct SkullNames {
	const char* name;
	Skulls_t skull;
};

MagicEffectNames magicEffectNames[] = {
	{"redspark",		CONST_ME_DRAWBLOOD},
	{"bluebubble",		CONST_ME_LOSEENERGY},
	{"poff",		CONST_ME_POFF},
	{"yellowspark",		CONST_ME_BLOCKHIT},
	// {"explosionarea",	CONST_ME_EXPLOSIONAREA},
	// {"explosion",		CONST_ME_EXPLOSIONHIT},
	{"firearea",		CONST_ME_FIREAREA},
	{"yellowbubble",	CONST_ME_YELLOW_RINGS},
	{"greenbubble",		CONST_ME_GREEN_RINGS},
	{"blackspark",		CONST_ME_HITAREA},
	{"teleport",		CONST_ME_TELEPORT},
	{"energy",		CONST_ME_ENERGYHIT},
	{"blueshimmer",		CONST_ME_MAGIC_BLUE},
	{"redshimmer",		CONST_ME_MAGIC_RED},
	{"greenshimmer",	CONST_ME_MAGIC_GREEN},
	{"fire",		CONST_ME_HITBYFIRE},
	{"greenspark",		CONST_ME_HITBYPOISON},
	{"mortarea",		CONST_ME_MORTAREA},
	{"greennote",		CONST_ME_SOUND_GREEN},
	{"rednote",		CONST_ME_SOUND_RED},
	{"poison",		CONST_ME_POISONAREA},
	{"yellownote",		CONST_ME_SOUND_YELLOW},
	{"purplenote",		CONST_ME_SOUND_PURPLE},
	{"bluenote",		CONST_ME_SOUND_BLUE},
	{"whitenote",		CONST_ME_SOUND_WHITE},
	{"bubbles",		CONST_ME_BUBBLES},
	{"dice",		CONST_ME_CRAPS},
	{"giftwraps",		CONST_ME_GIFT_WRAPS},
	{"yellowfirework",	CONST_ME_FIREWORK_YELLOW},
	{"redfirework",		CONST_ME_FIREWORK_RED},
	{"bluefirework",	CONST_ME_FIREWORK_BLUE},
	{"stun",		CONST_ME_STUN},
	{"sleep",		CONST_ME_SLEEP},
	{"watercreature",	CONST_ME_WATERCREATURE},
	{"groundshaker",	CONST_ME_GROUNDSHAKER},
	{"hearts",		CONST_ME_HEARTS},
	{"fireattack",		CONST_ME_FIREATTACK},
	{"energyarea",		CONST_ME_ENERGYAREA},
	{"smallclouds",		CONST_ME_SMALLCLOUDS},
	{"holydamage",		CONST_ME_HOLYDAMAGE},
	{"bigclouds",		CONST_ME_BIGCLOUDS},
	{"icearea",		CONST_ME_ICEAREA},
	{"icetornado",		CONST_ME_ICETORNADO},
	{"iceattack",		CONST_ME_ICEATTACK},
	{"stones",		CONST_ME_STONES},
	{"smallplants",		CONST_ME_SMALLPLANTS},
	{"carniphila",		CONST_ME_CARNIPHILA},
	{"purpleenergy",	CONST_ME_PURPLEENERGY},
	{"yellowenergy",	CONST_ME_YELLOWENERGY},
	{"holyarea",		CONST_ME_HOLYAREA},
	{"bigplants",		CONST_ME_BIGPLANTS},
	{"cake",		CONST_ME_CAKE},
	{"giantice",		CONST_ME_GIANTICE},
	{"watersplash",		CONST_ME_WATERSPLASH},
	{"plantattack",		CONST_ME_PLANTATTACK},
	{"tutorialarrow",	CONST_ME_TUTORIALARROW},
	{"tutorialsquare",	CONST_ME_TUTORIALSQUARE},
	{"mirrorhorizontal",	CONST_ME_MIRRORHORIZONTAL},
	{"mirrorvertical",	CONST_ME_MIRRORVERTICAL},
	{"skullhorizontal",	CONST_ME_SKULLHORIZONTAL},
	{"skullvertical",	CONST_ME_SKULLVERTICAL},
	{"assassin",		CONST_ME_ASSASSIN},
	{"stepshorizontal",	CONST_ME_STEPSHORIZONTAL},
	{"bloodysteps",		CONST_ME_BLOODYSTEPS},
	{"stepsvertical",	CONST_ME_STEPSVERTICAL},
	{"yalaharighost",	CONST_ME_YALAHARIGHOST},
	{"bats",		CONST_ME_BATS},
	{"smoke",		CONST_ME_SMOKE},
	{"insects",		CONST_ME_INSECTS},
	{"dragonhead",		CONST_ME_DRAGONHEAD},
	{"orcshaman",		CONST_ME_ORCSHAMAN},
	{"orcshamanfire",	CONST_ME_ORCSHAMAN_FIRE},
	{"thunder",		CONST_ME_THUNDER},
	{"ferumbras",		CONST_ME_FERUMBRAS},
	{"confettihorizontal",	CONST_ME_CONFETTI_HORIZONTAL},
	{"confettivertical",	CONST_ME_CONFETTI_VERTICAL},
	{"blacksmoke",		CONST_ME_BLACKSMOKE},
	{"redsmoke",		CONST_ME_REDSMOKE},
	{"yellowsmoke",		CONST_ME_YELLOWSMOKE},
	{"greensmoke",		CONST_ME_GREENSMOKE},
	{"purplesmoke",		CONST_ME_PURPLESMOKE},
};

ShootTypeNames shootTypeNames[] = {
	{"spear",		CONST_ANI_SPEAR},
	{"bolt",		CONST_ANI_BOLT},
	{"arrow",		CONST_ANI_ARROW},
	{"fire",		CONST_ANI_FIRE},
	{"energy",		CONST_ANI_ENERGY},
	{"poisonarrow",		CONST_ANI_POISONARROW},
	{"burstarrow",		CONST_ANI_BURSTARROW},
	{"throwingstar",	CONST_ANI_THROWINGSTAR},
	{"throwingknife",	CONST_ANI_THROWINGKNIFE},
	{"smallstone",		CONST_ANI_SMALLSTONE},
	{"death",		CONST_ANI_DEATH},
	{"largerock",		CONST_ANI_LARGEROCK},
	{"snowball",		CONST_ANI_SNOWBALL},
	{"powerbolt",		CONST_ANI_POWERBOLT},
	{"poison",		CONST_ANI_POISON},
	{"infernalbolt",	CONST_ANI_INFERNALBOLT},
	{"huntingspear",	CONST_ANI_HUNTINGSPEAR},
	{"enchantedspear",	CONST_ANI_ENCHANTEDSPEAR},
	{"redstar",		CONST_ANI_REDSTAR},
	{"greenstar",		CONST_ANI_GREENSTAR},
	{"royalspear",		CONST_ANI_ROYALSPEAR},
	{"sniperarrow",		CONST_ANI_SNIPERARROW},
	{"onyxarrow",		CONST_ANI_ONYXARROW},
	{"piercingbolt",	CONST_ANI_PIERCINGBOLT},
	{"whirlwindsword",	CONST_ANI_WHIRLWINDSWORD},
	{"whirlwindaxe",	CONST_ANI_WHIRLWINDAXE},
	{"whirlwindclub",	CONST_ANI_WHIRLWINDCLUB},
	{"etherealspear",	CONST_ANI_ETHEREALSPEAR},
	{"ice",			CONST_ANI_ICE},
	{"earth",		CONST_ANI_EARTH},
	{"holy",		CONST_ANI_HOLY},
	{"suddendeath",		CONST_ANI_SUDDENDEATH},
	{"flasharrow",		CONST_ANI_FLASHARROW},
	{"flammingarrow",	CONST_ANI_FLAMMINGARROW},
	{"shiverarrow",		CONST_ANI_SHIVERARROW},
	{"energyball",		CONST_ANI_ENERGYBALL},
	{"smallice",		CONST_ANI_SMALLICE},
	{"smallholy",		CONST_ANI_SMALLHOLY},
	{"smallearth",		CONST_ANI_SMALLEARTH},
	{"eartharrow",		CONST_ANI_EARTHARROW},
	// {"explosion",		CONST_ANI_EXPLOSION},
	{"cake",		CONST_ANI_CAKE},
	{"tarsalarrow",		CONST_ANI_TARSALARROW},
	{"vortexbolt",		CONST_ANI_VORTEXBOLT},
	{"prismaticbolt",	CONST_ANI_PRISMATICBOLT},
	{"crystallinearrow",	CONST_ANI_CRYSTALLINEARROW},
	{"drillbolt",		CONST_ANI_DRILLBOLT},
	{"envenomedarrow",	CONST_ANI_ENVENOMEDARROW},
	{"gloothspear",		CONST_ANI_GLOOTHSPEAR},
	{"simplearrow",		CONST_ANI_SIMPLEARROW},
	{"singlesting",		CONST_ANI_SINGLESTING},
	{"triplesting",		CONST_ANI_TRIPLESTING},
	{"bubbles",		CONST_ANI_BUBBLES},
	{"bluewave",		CONST_ANI_BLUEWAVE},
};

CombatTypeNames combatTypeNames[] = {
	{"physical",		COMBAT_PHYSICALDAMAGE},
	{"energy",		COMBAT_ENERGYDAMAGE},
	{"earth",		COMBAT_EARTHDAMAGE},
	{"fire",		COMBAT_FIREDAMAGE},
	{"undefined",		COMBAT_UNDEFINEDDAMAGE},
	{"lifedrain",		COMBAT_LIFEDRAIN},
	{"manadrain",		COMBAT_MANADRAIN},
	{"healing",		COMBAT_HEALING},
	{"drown",		COMBAT_DROWNDAMAGE},
	{"ice",			COMBAT_ICEDAMAGE},
	{"holy",		COMBAT_HOLYDAMAGE},
	{"death",		COMBAT_DEATHDAMAGE},
	{"psychic",		COMBAT_PSYCHICDAMAGE},
	{"grass",		COMBAT_GRASSDAMAGE},
	{"normal",		COMBAT_NORMALDAMAGE},
	{"water",		COMBAT_WATERDAMAGE},
	{"flying",		COMBAT_FLYINGDAMAGE},
	{"poison",		COMBAT_POISONDAMAGE},
	{"electric",		COMBAT_ELECTRICDAMAGE},
	{"ground",		COMBAT_GROUNDDAMAGE},
	{"rock",		COMBAT_ROCKDAMAGE},
	{"bug",			COMBAT_BUGDAMAGE},
	{"dragon",		COMBAT_DRAGONDAMAGE},
	{"ghost",		COMBAT_GHOSTDAMAGE},
	{"dark",		COMBAT_DARKDAMAGE},
	{"steel",		COMBAT_STEELDAMAGE},
	{"fairy",		COMBAT_FAIRYDAMAGE},
	{"fighting",		COMBAT_FIGHTINGDAMAGE},
};

AmmoTypeNames ammoTypeNames[] = {
	{"spear",		AMMO_SPEAR},
	{"bolt",		AMMO_BOLT},
	{"arrow",		AMMO_ARROW},
	{"poisonarrow",		AMMO_ARROW},
	{"burstarrow",		AMMO_ARROW},
	{"throwingstar",	AMMO_THROWINGSTAR},
	{"throwingknife",	AMMO_THROWINGKNIFE},
	{"smallstone",		AMMO_STONE},
	{"largerock",		AMMO_STONE},
	{"snowball",		AMMO_SNOWBALL},
	{"powerbolt",		AMMO_BOLT},
	{"infernalbolt",	AMMO_BOLT},
	{"huntingspear",	AMMO_SPEAR},
	{"enchantedspear",	AMMO_SPEAR},
	{"royalspear",		AMMO_SPEAR},
	{"sniperarrow",		AMMO_ARROW},
	{"onyxarrow",		AMMO_ARROW},
	{"piercingbolt",	AMMO_BOLT},
	{"etherealspear",	AMMO_SPEAR},
	{"flasharrow",		AMMO_ARROW},
	{"flammingarrow",	AMMO_ARROW},
	{"shiverarrow",		AMMO_ARROW},
	{"eartharrow",		AMMO_ARROW},
};

WeaponActionNames weaponActionNames[] = {
	{"move",		WEAPONACTION_MOVE},
	{"removecharge",	WEAPONACTION_REMOVECHARGE},
	{"removecount",		WEAPONACTION_REMOVECOUNT},
};

SkullNames skullNames[] = {
	{"none",	SKULL_NONE},
	{"yellow",	SKULL_YELLOW},
	{"green",	SKULL_GREEN},
	{"white",	SKULL_WHITE},
	{"red",		SKULL_RED},
	{"black",	SKULL_BLACK},
	{"orange",	SKULL_ORANGE},
};

MagicEffectClasses getMagicEffect(const std::string& strValue)
{
	for (auto& magicEffectName : magicEffectNames) {
		if (strcasecmp(strValue.c_str(), magicEffectName.name) == 0) {
			return magicEffectName.effect;
		}
	}
	return CONST_ME_NONE;
}

ShootType_t getShootType(const std::string& strValue)
{
	for (size_t i = 0, size = sizeof(shootTypeNames) / sizeof(ShootTypeNames); i < size; ++i) {
		if (strcasecmp(strValue.c_str(), shootTypeNames[i].name) == 0) {
			return shootTypeNames[i].shoot;
		}
	}
	return CONST_ANI_NONE;
}

CombatType_t getCombatType(const std::string& strValue)
{
	for (size_t i = 0, size = sizeof(combatTypeNames) / sizeof(CombatTypeNames); i < size; ++i) {
		if (strcasecmp(strValue.c_str(), combatTypeNames[i].name) == 0) {
			return combatTypeNames[i].combat;
		}
	}
	return COMBAT_NONE;
}

std::string getCombatName(CombatType_t combatType)
{
	for (size_t i = 0, size = sizeof(combatTypeNames) / sizeof(CombatTypeNames); i < size; ++i) {
		if (combatTypeNames[i].combat == combatType) {
			return combatTypeNames[i].name;
		}
	}
	return "unknown";
}

Ammo_t getAmmoType(const std::string& strValue)
{
	for (size_t i = 0, size = sizeof(ammoTypeNames) / sizeof(AmmoTypeNames); i < size; ++i) {
		if (strcasecmp(strValue.c_str(), ammoTypeNames[i].name) == 0) {
			return ammoTypeNames[i].ammoType;
		}
	}
	return AMMO_NONE;
}

WeaponAction_t getWeaponAction(const std::string& strValue)
{
	for (size_t i = 0, size = sizeof(weaponActionNames) / sizeof(WeaponActionNames); i < size; ++i) {
		if (strcasecmp(strValue.c_str(), weaponActionNames[i].name) == 0) {
			return weaponActionNames[i].weaponAction;
		}
	}
	return WEAPONACTION_NONE;
}

Skulls_t getSkullType(const std::string& strValue)
{
	for (size_t i = 0, size = sizeof(skullNames) / sizeof(SkullNames); i < size; ++i) {
		if (strcasecmp(strValue.c_str(), skullNames[i].name) == 0) {
			return skullNames[i].skull;
		}
	}
	return SKULL_NONE;
}

std::string getSkillName(uint8_t skillid)
{
	switch (skillid) {
		case SKILL_FIST: return "fist fighting";
		case SKILL_CLUB: return "club fighting";
		case SKILL_SWORD: return "sword fighting";
		case SKILL_AXE: return "axe fighting";
		case SKILL_DISTANCE: return "distance fighting";
		case SKILL_SHIELD: return "shielding";
		case SKILL_FISHING: return "fishing";
		case SKILL_MAGLEVEL: return "magic level";
		case SKILL_LEVEL: return "level";
		default: return "unknown";
	}
}

std::string getWeaponName(WeaponType_t weaponType)
{
	switch (weaponType) {
		case WEAPON_SWORD: return "sword";
		case WEAPON_CLUB: return "club";
		case WEAPON_AXE: return "axe";
		case WEAPON_DISTANCE: return "distance";
		case WEAPON_WAND: return "wand";
		case WEAPON_AMMO: return "ammunition";
		default: return std::string();
	}
}

size_t combatTypeToIndex(CombatType_t combatType)
{
	switch (combatType) {
		case COMBAT_PHYSICALDAMAGE: return 0;
		case COMBAT_ENERGYDAMAGE: return 1;
		case COMBAT_EARTHDAMAGE: return 2;
		case COMBAT_FIREDAMAGE: return 3;
		case COMBAT_UNDEFINEDDAMAGE: return 4;
		case COMBAT_LIFEDRAIN: return 5;
		case COMBAT_MANADRAIN: return 6;
		case COMBAT_HEALING: return 7;
		case COMBAT_DROWNDAMAGE: return 8;
		case COMBAT_ICEDAMAGE: return 9;
		case COMBAT_HOLYDAMAGE: return 10;
		case COMBAT_DEATHDAMAGE: return 11;
		case COMBAT_PSYCHICDAMAGE: return 12;
		case COMBAT_GRASSDAMAGE: return 13;
		case COMBAT_NORMALDAMAGE: return 14;
		case COMBAT_WATERDAMAGE: return 15;
		case COMBAT_FLYINGDAMAGE: return 16;
		case COMBAT_POISONDAMAGE: return 17;
		case COMBAT_ELECTRICDAMAGE: return 18;
		case COMBAT_GROUNDDAMAGE: return 19;
		case COMBAT_ROCKDAMAGE: return 20;
		case COMBAT_BUGDAMAGE: return 21;
		case COMBAT_DRAGONDAMAGE: return 22;
		case COMBAT_GHOSTDAMAGE: return 23;
		case COMBAT_DARKDAMAGE: return 24;
		case COMBAT_STEELDAMAGE: return 25;
		case COMBAT_FAIRYDAMAGE: return 26;
		case COMBAT_FIGHTINGDAMAGE: return 27;
		default: return 0;
	}
}

CombatType_t indexToCombatType(size_t v)
{
	return static_cast<CombatType_t>(1 << v);
}

itemAttrTypes stringToItemAttribute(const std::string& str)
{
	if (str == "aid") {
		return ITEM_ATTRIBUTE_ACTIONID;
	} else if (str == "uid") {
		return ITEM_ATTRIBUTE_UNIQUEID;
	} else if (str == "description") {
		return ITEM_ATTRIBUTE_DESCRIPTION;
	} else if (str == "text") {
		return ITEM_ATTRIBUTE_TEXT;
	} else if (str == "date") {
		return ITEM_ATTRIBUTE_DATE;
	} else if (str == "writer") {
		return ITEM_ATTRIBUTE_WRITER;
	} else if (str == "name") {
		return ITEM_ATTRIBUTE_NAME;
	} else if (str == "article") {
		return ITEM_ATTRIBUTE_ARTICLE;
	} else if (str == "pluralname") {
		return ITEM_ATTRIBUTE_PLURALNAME;
	} else if (str == "weight") {
		return ITEM_ATTRIBUTE_WEIGHT;
	} else if (str == "attack") {
		return ITEM_ATTRIBUTE_ATTACK;
	} else if (str == "defense") {
		return ITEM_ATTRIBUTE_DEFENSE;
	} else if (str == "extradefense") {
		return ITEM_ATTRIBUTE_EXTRADEFENSE;
	} else if (str == "armor") {
		return ITEM_ATTRIBUTE_ARMOR;
	} else if (str == "hitchance") {
		return ITEM_ATTRIBUTE_HITCHANCE;
	} else if (str == "shootrange") {
		return ITEM_ATTRIBUTE_SHOOTRANGE;
	} else if (str == "owner") {
		return ITEM_ATTRIBUTE_OWNER;
	} else if (str == "duration") {
		return ITEM_ATTRIBUTE_DURATION;
	} else if (str == "decaystate") {
		return ITEM_ATTRIBUTE_DECAYSTATE;
	} else if (str == "corpseowner") {
		return ITEM_ATTRIBUTE_CORPSEOWNER;
	} else if (str == "charges") {
		return ITEM_ATTRIBUTE_CHARGES;
	} else if (str == "fluidtype") {
		return ITEM_ATTRIBUTE_FLUIDTYPE;
	} else if (str == "doorid") {
		return ITEM_ATTRIBUTE_DOORID;
	}
	return ITEM_ATTRIBUTE_NONE;
}
