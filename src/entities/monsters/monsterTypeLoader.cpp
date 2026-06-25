// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../monsters.hpp"
#include "../monster.hpp"
#include "../player.hpp"
#include "../../config/configmanager.hpp"
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

namespace {

struct RaceTypeMapping {
	const char* name;
	uint16_t id;
	RaceType_t type;
};

const RaceTypeMapping raceTypeMappings[] = {
	{"venom", 1, RACE_VENOM},
	{"blood", 2, RACE_BLOOD},
	{"undead", 3, RACE_UNDEAD},
	{"fire", 4, RACE_FIRE},
	{"energy", 5, RACE_ENERGY},
	{"grass", 6, RACE_GRASS},
	{"normal", 7, RACE_NORMAL},
	{"water", 8, RACE_WATER},
	{"flying", 9, RACE_FLYING},
	{"poison", 10, RACE_POISON},
	{"electric", 11, RACE_ELECTRIC},
	{"ground", 12, RACE_GROUND},
	{"psychic", 13, RACE_PSYCHIC},
	{"rock", 14, RACE_ROCK},
	{"ice", 15, RACE_ICE},
	{"bug", 16, RACE_BUG},
	{"dragon", 17, RACE_DRAGON},
	{"ghost", 18, RACE_GHOST},
	{"dark", 19, RACE_DARK},
	{"steel", 20, RACE_STEEL},
	{"fairy", 21, RACE_FAIRY},
	{"fighting", 22, RACE_FIGHTING},
	{"none", 23, RACE_NONE},
};

bool getRaceType(const pugi::xml_attribute& attr, RaceType_t& raceType)
{
	const std::string raceName = asLowerCaseString(attr.as_string());
	const uint16_t raceId = pugi::cast<uint16_t>(attr.value());

	for (const RaceTypeMapping& mapping : raceTypeMappings) {
		if (raceName == mapping.name || raceId == mapping.id) {
			raceType = mapping.type;
			return true;
		}
	}
	return false;
}

void loadRaceType(const pugi::xml_node& monsterNode, const char* attributeName, RaceType_t& raceType, const std::string& file)
{
	const pugi::xml_attribute attr = monsterNode.attribute(attributeName);
	if (!attr) {
		return;
	}

	if (!getRaceType(attr, raceType)) {
		std::cout << "[Warning - Monsters::loadMonster] Unknown " << attributeName << " type " << attr.as_string() << ". " << file << std::endl;
	}
}

}

bool Monsters::loadMonster(const std::string& file, const std::string& monsterName, std::list<std::pair<MonsterType*, std::string>>& monsterScriptList, bool reloading /*= false*/)
{
	MonsterType* mType = nullptr;
	bool new_mType = true;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file.c_str());
	if (!result) {
		printXMLError("Error - Monsters::loadMonster", file, result);
		return false;
	}

	pugi::xml_node monsterNode = doc.child("monster");
	if (!monsterNode) {
		std::cout << "[Error - Monsters::loadMonster] Missing monster node in: " << file << std::endl;
		return false;
	}

	pugi::xml_attribute attr;
	if (!(attr = monsterNode.attribute("name"))) {
		std::cout << "[Error - Monsters::loadMonster] Missing name in: " << file << std::endl;
		return false;
	}

	if (reloading) {
		mType = getMonsterType(monsterName);
		if (mType != nullptr) {
			new_mType = false;
			mType->info = {};
		}
	}

	if (new_mType) {
		mType = &monsters[asLowerCaseString(monsterName)];
	}

	mType->name = attr.as_string();

	if ((attr = monsterNode.attribute("nameDescription"))) {
		mType->nameDescription = attr.as_string();
	} else {
		mType->nameDescription = "a " + asLowerCaseString(mType->name);
	}

	loadRaceType(monsterNode, "race", mType->info.race, file); //pota
	loadRaceType(monsterNode, "race2", mType->info.race2, file); //pota

	if ((attr = monsterNode.attribute("experience"))) {
		mType->info.experience = pugi::cast<uint64_t>(attr.value());
	}

	if ((attr = monsterNode.attribute("speed"))) {
		mType->info.baseSpeed = pugi::cast<int32_t>(attr.value());
	}

	if ((attr = monsterNode.attribute("manacost"))) {
		mType->info.manaCost = pugi::cast<uint32_t>(attr.value());
	}

	if ((attr = monsterNode.attribute("skull"))) {
		mType->info.skull = getSkullType(attr.as_string());
	}

	if ((attr = monsterNode.attribute("script"))) {
		monsterScriptList.emplace_back(mType, attr.as_string());
	}

	pugi::xml_node node;
	if ((node = monsterNode.child("health"))) {
		if ((attr = node.attribute("now"))) {
			mType->info.health = pugi::cast<int32_t>(attr.value());
		} else {
			std::cout << "[Error - Monsters::loadMonster] Missing health now. " << file << std::endl;
		}

		if ((attr = node.attribute("max"))) {
			mType->info.healthMax = pugi::cast<int32_t>(attr.value());
		} else {
			std::cout << "[Error - Monsters::loadMonster] Missing health max. " << file << std::endl;
		}
	}

	if ((node = monsterNode.child("level"))) { //pota
		if ((attr = node.attribute("min"))) {
			mType->info.minLevel = pugi::cast<uint16_t>(attr.value());

		} else {
			std::cout << "[Error - Monsters::loadMonster] Missing level min. " << file << std::endl;

		}

		if ((attr = node.attribute("max"))) {
			mType->info.maxLevel = pugi::cast<uint16_t>(attr.value());

		} else {
			std::cout << "[Error - Monsters::loadMonster] Missing level max. " << file << std::endl;

		}
	}

	if ((node = monsterNode.child("flags"))) {
		for (auto flagNode : node.children()) {
			attr = flagNode.first_attribute();
			const char* attrName = attr.name();
			if (strcasecmp(attrName, "summonable") == 0) {
				mType->info.isSummonable = attr.as_bool();
			} else if (strcasecmp(attrName, "attackable") == 0) {
				mType->info.isAttackable = attr.as_bool();
			} else if (strcasecmp(attrName, "hostile") == 0) {
				mType->info.isHostile = attr.as_bool();
			} else if (strcasecmp(attrName, "passive") == 0) {
				mType->info.isPassive = attr.as_bool();

			} else if (strcasecmp(attrName, "flyable") == 0) {
				mType->info.isFlyable = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "rideable") == 0) {
				mType->info.isRideable = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "surfable") == 0) {
				mType->info.isSurfable = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "canteleport") == 0) {
				mType->info.canTeleport = attr.as_bool();
			} else if (strcasecmp(attrName, "catchchance") == 0) {
				mType->info.catchChance = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "moveMagicAttackBase") == 0) {
				mType->info.moveMagicAttackBase = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "moveMagicDefenseBase") == 0) {
				mType->info.moveMagicDefenseBase = pugi::cast<int32_t>(attr.value());

			} else if (strcasecmp(attrName, "hasshiny") == 0) {
				mType->info.hasShiny = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "hasmega") == 0) {
				mType->info.hasMega = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "dexentry") == 0) {
				mType->info.dexEntry = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "portraitid") == 0) {
				mType->info.portraitId = pugi::cast<int32_t>(attr.value());


			} else if (strcasecmp(attrName, "illusionable") == 0) {
				mType->info.isIllusionable = attr.as_bool();
			} else if (strcasecmp(attrName, "convinceable") == 0) {
				mType->info.isConvinceable = attr.as_bool();
			} else if (strcasecmp(attrName, "pushable") == 0) {
				mType->info.pushable = attr.as_bool();
			} else if (strcasecmp(attrName, "canpushitems") == 0) {
				mType->info.canPushItems = attr.as_bool();
			} else if (strcasecmp(attrName, "canpushcreatures") == 0) {
				mType->info.canPushCreatures = attr.as_bool();
			} else if (strcasecmp(attrName, "staticattack") == 0) {
				uint32_t staticAttack = pugi::cast<uint32_t>(attr.value());
				if (staticAttack > 100) {
					std::cout << "[Warning - Monsters::loadMonster] staticattack greater than 100. " << file << std::endl;
					staticAttack = 100;
				}

				mType->info.staticAttackChance = staticAttack;
			} else if (strcasecmp(attrName, "lightlevel") == 0) {
				mType->info.light.level = pugi::cast<uint16_t>(attr.value());
			} else if (strcasecmp(attrName, "lightcolor") == 0) {
				mType->info.light.color = pugi::cast<uint16_t>(attr.value());
			} else if (strcasecmp(attrName, "targetdistance") == 0) {
				mType->info.targetDistance = std::max<int32_t>(1, pugi::cast<int32_t>(attr.value()));
			} else if (strcasecmp(attrName, "runonhealth") == 0) {
				mType->info.runAwayHealth = pugi::cast<int32_t>(attr.value());
			} else if (strcasecmp(attrName, "hidehealth") == 0) {
				mType->info.hiddenHealth = attr.as_bool();
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Unknown flag attribute: " << attrName << ". " << file << std::endl;
			}
		}

		//if a monster can push creatures,
		// it should not be pushable
		if (mType->info.canPushCreatures) {
			mType->info.pushable = false;
		}
	}

	if ((node = monsterNode.child("targetchange"))) {
		if ((attr = node.attribute("speed")) || (attr = node.attribute("interval"))) {
			mType->info.changeTargetSpeed = pugi::cast<uint32_t>(attr.value());
		} else {
			std::cout << "[Warning - Monsters::loadMonster] Missing targetchange speed. " << file << std::endl;
		}

		if ((attr = node.attribute("chance"))) {
			mType->info.changeTargetChance = pugi::cast<int32_t>(attr.value());
		} else {
			std::cout << "[Warning - Monsters::loadMonster] Missing targetchange chance. " << file << std::endl;
		}
	}

	if ((node = monsterNode.child("look"))) {
		if ((attr = node.attribute("type"))) {
			mType->info.outfit.lookType = pugi::cast<uint16_t>(attr.value());

			if ((attr = node.attribute("head"))) {
				mType->info.outfit.lookHead = pugi::cast<uint16_t>(attr.value());
			}

			if ((attr = node.attribute("body"))) {
				mType->info.outfit.lookBody = pugi::cast<uint16_t>(attr.value());
			}

			if ((attr = node.attribute("legs"))) {
				mType->info.outfit.lookLegs = pugi::cast<uint16_t>(attr.value());
			}

			if ((attr = node.attribute("feet"))) {
				mType->info.outfit.lookFeet = pugi::cast<uint16_t>(attr.value());
			}

			if ((attr = node.attribute("addons"))) {
				mType->info.outfit.lookAddons = pugi::cast<uint16_t>(attr.value());
			}
		} else if ((attr = node.attribute("typeex"))) {
			mType->info.outfit.lookTypeEx = pugi::cast<uint16_t>(attr.value());
		} else {
			std::cout << "[Warning - Monsters::loadMonster] Missing look type/typeex. " << file << std::endl;
		}

		if ((attr = node.attribute("mount"))) {
			mType->info.outfit.lookMount = pugi::cast<uint16_t>(attr.value());
		}

		if ((attr = node.attribute("corpse"))) {
			mType->info.lookcorpse = pugi::cast<uint16_t>(attr.value());
		}
	}

	if ((node = monsterNode.child("attacks"))) {
		for (auto attackNode : node.children()) {
			spellBlock_t sb;
			if (deserializeSpell(attackNode, sb, monsterName)) {
				mType->info.attackSpells.emplace_back(std::move(sb));
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Cant load spell. " << file << std::endl;
			}
		}
	}


	if ((node = monsterNode.child("moves"))) { //pota
		for (auto attackNode : node.children()) {
			spellBlock_t sb;
			if (deserializeSpell(attackNode, sb, monsterName)) {
				mType->info.moves.emplace_back(std::move(sb));
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Cant load move spell. " << file << std::endl;
			}
		}
	}




	if ((node = monsterNode.child("evolutions"))) { //pota
		for (auto evolutionNode : node.children()) {
			int32_t level = 1000;
			int32_t love = 0;
			int32_t count = 100;
			std::string itemName = "none";

			if ((attr = evolutionNode.attribute("level"))) {
				level = std::max<int32_t>(1, pugi::cast<int32_t>(attr.value()));
			}

			if ((attr = evolutionNode.attribute("love"))) {
				love = pugi::cast<int32_t>(attr.value());
			}

			if ((attr = evolutionNode.attribute("count"))) {
				count = pugi::cast<uint32_t>(attr.value());
			}

			if ((attr = evolutionNode.attribute("itemName"))) {
				itemName = attr.as_string();
			}

			if ((attr = evolutionNode.attribute("name"))) {
				evolutionBlock_t eb;
				eb.name = attr.as_string();
				eb.itemName = itemName;
				eb.level = level;
				eb.love = love;
				eb.count = count;
				mType->info.evolutions.emplace_back(eb);
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Missing evolution name. " << file << std::endl;
			}
		}
	}





	if ((node = monsterNode.child("defenses"))) {
		if ((attr = node.attribute("defense"))) {
			mType->info.defense = pugi::cast<int32_t>(attr.value());
		}

		if ((attr = node.attribute("armor"))) {
			mType->info.armor = pugi::cast<int32_t>(attr.value());
		}

		for (auto defenseNode : node.children()) {
			spellBlock_t sb;
			if (deserializeSpell(defenseNode, sb, monsterName)) {
				mType->info.defenseSpells.emplace_back(std::move(sb));
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Cant load spell. " << file << std::endl;
			}
		}
	}

	if ((node = monsterNode.child("immunities"))) {
		for (auto immunityNode : node.children()) {
			if ((attr = immunityNode.attribute("name"))) {
				std::string tmpStrValue = asLowerCaseString(attr.as_string());
				if (tmpStrValue == "physical") {
					mType->info.damageImmunities |= COMBAT_PHYSICALDAMAGE;
					mType->info.conditionImmunities |= CONDITION_BLEEDING;
				} else if (tmpStrValue == "energy") {
					mType->info.damageImmunities |= COMBAT_ENERGYDAMAGE;
					mType->info.conditionImmunities |= CONDITION_ENERGY;
				} else if (tmpStrValue == "fire") {
					mType->info.damageImmunities |= COMBAT_FIREDAMAGE;
					mType->info.conditionImmunities |= CONDITION_FIRE;
				} else if (tmpStrValue == "poison") {
					mType->info.damageImmunities |= COMBAT_POISONDAMAGE;
					mType->info.conditionImmunities |= CONDITION_POISON;
				} else if (tmpStrValue == "drown") {
					mType->info.damageImmunities |= COMBAT_DROWNDAMAGE;
					mType->info.conditionImmunities |= CONDITION_DROWN;
				} else if (tmpStrValue == "ice") {
					mType->info.damageImmunities |= COMBAT_ICEDAMAGE;
					mType->info.conditionImmunities |= CONDITION_FREEZING;
				} else if (tmpStrValue == "holy") {
					mType->info.damageImmunities |= COMBAT_HOLYDAMAGE;
					mType->info.conditionImmunities |= CONDITION_DAZZLED;
				} else if (tmpStrValue == "death") {
					mType->info.damageImmunities |= COMBAT_DEATHDAMAGE;
					mType->info.conditionImmunities |= CONDITION_CURSED;
				} else if (tmpStrValue == "psychic") { //pota
					mType->info.damageImmunities |= COMBAT_PSYCHICDAMAGE;
				} else if (tmpStrValue == "grass") { //pota
					mType->info.damageImmunities |= COMBAT_GRASSDAMAGE;
				} else if (tmpStrValue == "normal") { //pota
					mType->info.damageImmunities |= COMBAT_NORMALDAMAGE;
				} else if (tmpStrValue == "water") { //pota
					mType->info.damageImmunities |= COMBAT_WATERDAMAGE;
				} else if (tmpStrValue == "flying") { //pota
					mType->info.damageImmunities |= COMBAT_FLYINGDAMAGE;
				} else if (tmpStrValue == "poison") { //pota
					mType->info.damageImmunities |= COMBAT_POISONDAMAGE;
				} else if (tmpStrValue == "electric") { //pota
					mType->info.damageImmunities |= COMBAT_ELECTRICDAMAGE;
				} else if (tmpStrValue == "ground") { //pota
					mType->info.damageImmunities |= COMBAT_GROUNDDAMAGE;
				} else if (tmpStrValue == "rock") { //pota
					mType->info.damageImmunities |= COMBAT_ROCKDAMAGE;
				} else if (tmpStrValue == "bug") { //pota
					mType->info.damageImmunities |= COMBAT_BUGDAMAGE;
				} else if (tmpStrValue == "dragon") { //pota
					mType->info.damageImmunities |= COMBAT_DRAGONDAMAGE;
				} else if (tmpStrValue == "ghost") { //pota
					mType->info.damageImmunities |= COMBAT_GHOSTDAMAGE;
				} else if (tmpStrValue == "dark") { //pota
					mType->info.damageImmunities |= COMBAT_DARKDAMAGE;
				} else if (tmpStrValue == "steel") { //pota
					mType->info.damageImmunities |= COMBAT_STEELDAMAGE;
				} else if (tmpStrValue == "fairy") { //pota
					mType->info.damageImmunities |= COMBAT_FAIRYDAMAGE;
				} else if (tmpStrValue == "fighting") { //pota
					mType->info.damageImmunities |= COMBAT_FIGHTINGDAMAGE;
				} else if (tmpStrValue == "lifedrain") {
					mType->info.damageImmunities |= COMBAT_LIFEDRAIN;
				} else if (tmpStrValue == "manadrain") {
					mType->info.damageImmunities |= COMBAT_MANADRAIN;
				} else if (tmpStrValue == "paralyze") {
					mType->info.conditionImmunities |= CONDITION_PARALYZE;
				} else if (tmpStrValue == "sleep") { //pota
					mType->info.conditionImmunities |= CONDITION_SLEEP;
				} else if (tmpStrValue == "sleep") { //helena
					mType->info.conditionImmunities |= CONDITION_SILENCE;
				} else if (tmpStrValue == "outfit") {
					mType->info.conditionImmunities |= CONDITION_OUTFIT;
				} else if (tmpStrValue == "drunk") {
					mType->info.conditionImmunities |= CONDITION_DRUNK;
				} else if (tmpStrValue == "invisible" || tmpStrValue == "invisibility") {
					mType->info.conditionImmunities |= CONDITION_INVISIBLE;
				} else if (tmpStrValue == "bleed") {
					mType->info.conditionImmunities |= CONDITION_BLEEDING;
				} else {
					std::cout << "[Warning - Monsters::loadMonster] Unknown immunity name " << attr.as_string() << ". " << file << std::endl;
				}
			} else if ((attr = immunityNode.attribute("physical"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_PHYSICALDAMAGE;
					mType->info.conditionImmunities |= CONDITION_BLEEDING;
				}
			} else if ((attr = immunityNode.attribute("energy"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_ENERGYDAMAGE;
					mType->info.conditionImmunities |= CONDITION_ENERGY;
				}
			} else if ((attr = immunityNode.attribute("fire"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_FIREDAMAGE;
					mType->info.conditionImmunities |= CONDITION_FIRE;
				}
			} else if ((attr = immunityNode.attribute("poison"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_POISONDAMAGE;
					mType->info.conditionImmunities |= CONDITION_POISON;
				}
			} else if ((attr = immunityNode.attribute("drown"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_DROWNDAMAGE;
					mType->info.conditionImmunities |= CONDITION_DROWN;
				}
			} else if ((attr = immunityNode.attribute("ice"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_ICEDAMAGE;
					mType->info.conditionImmunities |= CONDITION_FREEZING;
				}
			} else if ((attr = immunityNode.attribute("holy"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_HOLYDAMAGE;
					mType->info.conditionImmunities |= CONDITION_DAZZLED;
				}
			} else if ((attr = immunityNode.attribute("death"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_DEATHDAMAGE;
					mType->info.conditionImmunities |= CONDITION_CURSED;
				}
			} else if ((attr = immunityNode.attribute("psychic"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_PSYCHICDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("grass"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_GRASSDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("normal"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_NORMALDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("water"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_WATERDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("flying"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_FLYINGDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("poison"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_POISONDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("electric"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_ELECTRICDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("ground"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_GROUNDDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("rock"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_ROCKDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("bug"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_BUGDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("dragon"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_DRAGONDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("ghost"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_GHOSTDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("dark"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_DARKDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("steel"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_STEELDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("fairy"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_FAIRYDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("fighting"))) { //pota
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_FIGHTINGDAMAGE;
				}
			} else if ((attr = immunityNode.attribute("lifedrain"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_LIFEDRAIN;
				}
			} else if ((attr = immunityNode.attribute("manadrain"))) {
				if (attr.as_bool()) {
					mType->info.damageImmunities |= COMBAT_MANADRAIN;
				}
			} else if ((attr = immunityNode.attribute("paralyze"))) {
				if (attr.as_bool()) {
					mType->info.conditionImmunities |= CONDITION_PARALYZE;
				}
			} else if ((attr = immunityNode.attribute("sleep"))) { //pota
				if (attr.as_bool()) {
					mType->info.conditionImmunities |= CONDITION_SLEEP;
				}
			} else if ((attr = immunityNode.attribute("silence"))) { //helena
				if (attr.as_bool()) {
					mType->info.conditionImmunities |= CONDITION_SILENCE;
				}
				
			} else if ((attr = immunityNode.attribute("outfit"))) {
				if (attr.as_bool()) {
					mType->info.conditionImmunities |= CONDITION_OUTFIT;
				}
			} else if ((attr = immunityNode.attribute("bleed"))) {
				if (attr.as_bool()) {
					mType->info.conditionImmunities |= CONDITION_BLEEDING;
				}
			} else if ((attr = immunityNode.attribute("drunk"))) {
				if (attr.as_bool()) {
					mType->info.conditionImmunities |= CONDITION_DRUNK;
				}
			} else if ((attr = immunityNode.attribute("invisible")) || (attr = immunityNode.attribute("invisibility"))) {
				if (attr.as_bool()) {
					mType->info.conditionImmunities |= CONDITION_INVISIBLE;
				}
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Unknown immunity. " << file << std::endl;
			}
		}
	}

	if ((node = monsterNode.child("voices"))) {
		if ((attr = node.attribute("speed")) || (attr = node.attribute("interval"))) {
			mType->info.yellSpeedTicks = pugi::cast<uint32_t>(attr.value());
		} else {
			std::cout << "[Warning - Monsters::loadMonster] Missing voices speed. " << file << std::endl;
		}

		if ((attr = node.attribute("chance"))) {
			mType->info.yellChance = pugi::cast<uint32_t>(attr.value());
		} else {
			std::cout << "[Warning - Monsters::loadMonster] Missing voices chance. " << file << std::endl;
		}

		for (auto voiceNode : node.children()) {
			voiceBlock_t vb;
			if ((attr = voiceNode.attribute("sentence"))) {
				vb.text = attr.as_string();
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Missing voice sentence. " << file << std::endl;
			}

			if ((attr = voiceNode.attribute("yell"))) {
				vb.yellText = attr.as_bool();
			} else {
				vb.yellText = false;
			}
			mType->info.voiceVector.emplace_back(vb);
		}
	}

	if ((node = monsterNode.child("loot"))) {
		for (auto lootNode : node.children()) {
			LootBlock lootBlock;
			if (loadLootItem(lootNode, lootBlock)) {
				mType->info.lootItems.emplace_back(std::move(lootBlock));
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Cant load loot. " << file << std::endl;
			}
		}
	}

	if ((node = monsterNode.child("elements"))) {
		for (auto elementNode : node.children()) {
			if ((attr = elementNode.attribute("physicalPercent"))) {
				mType->info.elementMap[COMBAT_PHYSICALDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("icePercent"))) {
				mType->info.elementMap[COMBAT_ICEDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("poisonPercent")) || (attr = elementNode.attribute("poisonPercent"))) {
				mType->info.elementMap[COMBAT_POISONDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("firePercent"))) {
				mType->info.elementMap[COMBAT_FIREDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("energyPercent"))) {
				mType->info.elementMap[COMBAT_ENERGYDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("holyPercent"))) {
				mType->info.elementMap[COMBAT_HOLYDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("deathPercent"))) {
				mType->info.elementMap[COMBAT_DEATHDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("psychicPercent"))) { //pota
				mType->info.elementMap[COMBAT_PSYCHICDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("grassPercent"))) { //pota
				mType->info.elementMap[COMBAT_GRASSDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("normalPercent"))) { //pota
				mType->info.elementMap[COMBAT_NORMALDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("waterPercent"))) { //pota
				mType->info.elementMap[COMBAT_WATERDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("flyingPercent"))) { //pota
				mType->info.elementMap[COMBAT_FLYINGDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("poisonPercent"))) { //pota
				mType->info.elementMap[COMBAT_POISONDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("electricPercent"))) { //pota
				mType->info.elementMap[COMBAT_ELECTRICDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("groundPercent"))) { //pota
				mType->info.elementMap[COMBAT_GROUNDDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("rockPercent"))) { //pota
				mType->info.elementMap[COMBAT_ROCKDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("bugPercent"))) { //pota
				mType->info.elementMap[COMBAT_BUGDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("dragonPercent"))) { //pota
				mType->info.elementMap[COMBAT_DRAGONDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("ghostPercent"))) { //pota
				mType->info.elementMap[COMBAT_GHOSTDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("darkPercent"))) { //pota
				mType->info.elementMap[COMBAT_DARKDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("steelPercent"))) { //pota
				mType->info.elementMap[COMBAT_STEELDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("fairyPercent"))) { //pota
				mType->info.elementMap[COMBAT_FAIRYDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("fightingPercent"))) { //pota
				mType->info.elementMap[COMBAT_FIGHTINGDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("drownPercent"))) {
				mType->info.elementMap[COMBAT_DROWNDAMAGE] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("lifedrainPercent"))) {
				mType->info.elementMap[COMBAT_LIFEDRAIN] = pugi::cast<int32_t>(attr.value());
			} else if ((attr = elementNode.attribute("manadrainPercent"))) {
				mType->info.elementMap[COMBAT_MANADRAIN] = pugi::cast<int32_t>(attr.value());
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Unknown element percent. " << file << std::endl;
			}
		}
	}

	if ((node = monsterNode.child("summons"))) {
		if ((attr = node.attribute("maxSummons"))) {
			mType->info.maxSummons = std::min<uint32_t>(pugi::cast<uint32_t>(attr.value()), 100);
		} else {
			std::cout << "[Warning - Monsters::loadMonster] Missing summons maxSummons. " << file << std::endl;
		}

		for (auto summonNode : node.children()) {
			int32_t chance = 100;
			int32_t speed = 1000;
			int32_t max = mType->info.maxSummons;
			bool force = false;

			if ((attr = summonNode.attribute("speed")) || (attr = summonNode.attribute("interval"))) {
				speed = std::max<int32_t>(1, pugi::cast<int32_t>(attr.value()));
			}

			if ((attr = summonNode.attribute("chance"))) {
				chance = pugi::cast<int32_t>(attr.value());
			}

			if ((attr = summonNode.attribute("max"))) {
				max = pugi::cast<uint32_t>(attr.value());
			}

			if ((attr = summonNode.attribute("force"))) {
				force = attr.as_bool();
			}

			if ((attr = summonNode.attribute("name"))) {
				summonBlock_t sb;
				sb.name = attr.as_string();
				sb.speed = speed;
				sb.chance = chance;
				sb.max = max;
				sb.force = force;
				mType->info.summons.emplace_back(sb);
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Missing summon name. " << file << std::endl;
			}
		}
	}

	if ((node = monsterNode.child("script"))) {
		for (auto eventNode : node.children()) {
			if ((attr = eventNode.attribute("name"))) {
				mType->info.scripts.emplace_back(attr.as_string());
			} else {
				std::cout << "[Warning - Monsters::loadMonster] Missing name for script event. " << file << std::endl;
			}
		}
	}

	mType->info.summons.shrink_to_fit();
	mType->info.lootItems.shrink_to_fit();
	mType->info.attackSpells.shrink_to_fit();
	mType->info.defenseSpells.shrink_to_fit();
	mType->info.voiceVector.shrink_to_fit();
	mType->info.scripts.shrink_to_fit();

	mType->info.moves.shrink_to_fit(); //pota
	mType->info.evolutions.shrink_to_fit(); //pota

	return true;
}

