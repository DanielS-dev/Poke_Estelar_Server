local racesStrength = 
	{
		["none"] = {strong = {}, weak = {}},
		["blood"] = {strong = {}, weak = {}},
		["physical"] = {strong = {}, weak = {}},
		["healing"] = {strong = {}, weak = {}},
		["fire"] = {strong = {"fairy", "fire", "bug", "steel", "grass", "ice"}, weak = {"ground", "rock", "water"}},
		["grass"] = {strong = {"ground", "water", "grass", "electric"}, weak = {"flying", "poison", "bug", "fire", "ice"}},
		["normal"] = {strong = {}, weak = {"fighting"}, imune = {"ghost"}},
		["water"] = {strong = {"steel", "fire", "water", "ice"}, weak = {"electric", "grass"}},
		["flying"] = {strong = {"fighting", "bug", "grass"}, weak = {"rock", "electric", "ice"}, imune = {"ground"}},
		["poison"] = {strong = {"fighting", "poison", "bug", "grass", "fairy"}, weak = {"ground", "psychic"}},
		["electric"] = {strong = {"flying", "steel", "electric"}, weak = {"ground"}},
		["ground"] = {strong = {"poison", "rock"}, weak = {"water", "grass", "ice"}, imune = {"electric"}},
		["psychic"] = {strong = {"fighting", "psychic"}, weak = {"bug", "ghost", "dark"}},
		["rock"] = {strong = {"normal", "physical", "flying", "poison", "fire"}, weak = {"fighting", "ground", "steel", "water", "grass"}},
		["ice"] = {strong = {"ice"}, weak = {"fighting", "rock", "steel", "fire"}},
		["bug"] = {strong = {"fighting", "ground", "grass"}, weak = {"flying", "rock", "fire"}},
		["dragon"] = {strong = {"fire", "water", "grass", "electric"}, weak = {"ice", "dragon", "fairy"}},
		["ghost"] = {strong = {"poison", "bug"}, weak = {"ghost", "dark"}, imune = {"normal", "fighting", "physical"}},
		["dark"] = {strong = {"ghost", "dark"}, weak = {"fighting", "bug", "fairy"}, imune = {"psychic"}},
		["steel"] = {strong = {"normal", "physical", "flying", "rock", "bug", "steel", "grass", "psychic", "ice", "dragon", "fairy"}, weak = {"fighting", "ground", "fire"}, imune = {"poison"}},
		["fairy"] = {strong = {"fighting", "bug", "dark"}, weak = {"poison", "steel"}, imune = {"dragon"}},
		["fighting"] = {strong = {"rock", "bug", "dark"}, weak = {"flying", "psychic", "fairy"}}
	}

local typetonumber = {
	["fire"] = 8,
	["ice"] = 512,
	["psychic"] = 4096,
	["grass"] = 8192,
	["normal"] = 16384,
	["water"] = 32768,
	["flying"] = 65536,
	["poison"] = 131072,
	["electric"] = 262144,
	["ground"] = 524288,
	["rock"] = 1048576,
	["bug"] = 2097152,
	["dragon"] = 4194304,
	["ghost"] = 8388608,
	["dark"] = 16777216,
	["steel"] = 33554432,
	["fairy"] = 67108864,
	["fighting"] = 134217728,
}

local function isStrongAgainst(attackerRace, defenderRace)
	if isInArray(racesStrength[defenderRace].strong, attackerRace) then
		return true
	end
	return false
end

local function isWeakAgainst(attackerRace, defenderRace)
	if isInArray(racesStrength[defenderRace].weak, attackerRace) then
		return true
	end
	return false
end

local function isSuperWeakAgainst(attackerRace, defenderRace)
	if isInArray(racesStrength[defenderRace].weak, attackerRace) then
		return true
	end
	return false
end

local function isImune(attackerRace, defenderRace, defenderRace2)
	if isInArray(racesStrength[defenderRace].imune, attackerRace) or isInArray(racesStrength[defenderRace2].imune, attackerRace) then
		return true
	end
	return false
end

local function isImmuneAbility(attackerRace, name, defender, primaryDamage)
	local abilities = {hiddenabilities.flashfire, hiddenabilities.waterabsorb, hiddenabilities.stormdrain, hiddenabilities.levitate, hiddenabilities.lightningrod, hiddenabilities.voltabsorb}
	local immunities = {{dmg = "fire", buff = "attackup"}, {dmg = "water", buff = "life"}, {dmg = "water", buff = "attackup"}, {dmg = "ground", buff = "none"}, {dmg = "electric", buff = "attackup"}, {dmg = "electric", buff = "life"}}
	for i = 1, #abilities do
		if isInArray(abilities[i], Creature(defender):getName()) then
			if attackerRace == immunities[i].dmg then
				if name ~= nil and isInArray(hiddenabilities.moldbreaker, name) then return false end
				if name ~= nil and isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turret", "porygon turret"}, name) then return false end
				if immunities[i].buff == "attackup" then
					defender = Creature(defender)
					local condition = Condition(CONDITION_ATTACKPLUS)
					condition:setParameter(CONDITION_PARAM_TICKS, 5000)
					defender:addCondition(condition)
					return true
				elseif immunities[i].buff == "life" then
					defender = Creature(defender)
					defender:addHealth(primaryDamage)
					return true
				end
				return true
			end
		end
	end
	return false
end

function onHealthChange(creature, attacker, primaryDamage, primaryType, secondaryDamage, secondaryType, origin)
	if getCombatName(primaryType) == "healing" then
		if creature:isPokemon() and creature:getMaster():isPlayer() then
			local talisman = creature:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
			if talismanTable[talisman] and talismanTable[talisman].buff == 'healing' then
				primaryDamage = primaryDamage * talismanTable[talisman].amount
			end
		end
		return primaryDamage, primaryType, secondaryDamage, secondaryType
	end
	
	if not attacker or attacker:isPlayer() then
		return primaryDamage, primaryType, secondaryDamage, secondaryType
	end
	
	-- Normal damage, pokémon vs pokémon.
	
	if attacker and not creature:isPlayer() then
		local returndmg = primaryDamage
		local critical = 1
		local stab = 1
		local typeeffectiveness = 1
		local primaryTypeName = getCombatName(primaryType)
		local secondaryTypeName = getCombatName(secondaryType)
		local defenderMonsterType = MonsterType(creature:getName())
		local defenderRace = defenderMonsterType:getRaceName()
		local defenderRace2 = defenderMonsterType:getRace2Name()
		local attackerMonsterType = MonsterType(attacker:getName())
		local attackerRace = attackerMonsterType:getRaceName()
		local attackerRace2 = attackerMonsterType:getRace2Name()
		local evatk1 = 0
		local evdef1 = 0
		local evatk2 = 0
		local evdef2 = 0
		if attacker:getMaster() and attacker:getMaster():isPlayer() then
			evatk1 = attacker:getMaster():getUsingBall():getSpecialAttribute("evatk") or 0
			evdef1 = attacker:getMaster():getUsingBall():getSpecialAttribute("evdef") or 0
		end
		if creature:getMaster() and creature:getMaster():isPlayer() then
			evatk2 = creature:getMaster():getUsingBall():getSpecialAttribute("evatk") or 0
			evdef2 = creature:getMaster():getUsingBall():getSpecialAttribute("evdef") or 0
		end
		
		-- Form Change System
		
		if attacker:getName() == "Castform" and primaryTypeName ~= "physical" then
			if attacker:getOutfit().lookType == 3436 then -- fire
				attackerRace = "fire"
			elseif attacker:getOutfit().lookType == 3437 then -- water
				attackerRace = "water"
			elseif attacker:getOutfit().lookType == 3438 then -- ice
				attackerRace = "ice"
			end
		elseif creature:getName() == "Castform" then
			if creature:getOutfit().lookType == 3436 then -- fire
				defenderRace = "fire"
			elseif creature:getOutfit().lookType == 3437 then -- water
				defenderRace = "water"
			elseif creature:getOutfit().lookType == 3438 then -- ice
				defenderRace = "ice"
			end
		elseif creature:getName() == "Wormadam" then
			if creature:getOutfit().lookType == 3487 then -- steel
				defenderRace2 = "steel"
			elseif creature:getOutfit().lookType == 3488 then -- ground
				defenderRace2 = "ground"
			elseif creature:getOutfit().lookType == 3489 then -- grass
				defenderRace2 = "grass"
			end
		elseif attacker:getName() == "Wormadam" and primaryTypeName ~= "physical" then
			if attacker:getOutfit().lookType == 3487 then -- steel
				attackerRace2 = "steel"
			elseif attacker:getOutfit().lookType == 3488 then -- ground
				attackerRace2 = "ground"
			elseif attacker:getOutfit().lookType == 3489 then -- grass
				attackerRace2 = "grass"
			end
		elseif creature:getName() == "Shaymin" then
			if creature:getOutfit().lookType == 3492 then -- flying
				defenderRace2 = "flying"
			end
		elseif attacker:getName() == "Shaymin" and primaryTypeName ~= "physical" then
			if attacker:getOutfit().lookType == 3492 then -- flying
				attackerRace2 = "flying"
			end
		elseif creature:getName() == "Meloetta" then
			if creature:getOutfit().lookType == 3446 then -- flying
				defenderRace2 = "fighting"
			end
		elseif attacker:getName() == "Meloetta" and primaryTypeName ~= "physical" then
			if attacker:getOutfit().lookType == 3446 then -- flying
				attackerRace2 = "fighting"
			end
		elseif creature:getName() == "Rotom" then
			if creature:getOutfit().lookType == 3450 then -- steel
				defenderRace2 = "ice"
			elseif creature:getOutfit().lookType == 3452 then -- ground
				defenderRace2 = "grass"
			elseif creature:getOutfit().lookType == 3454 then -- grass
				defenderRace2 = "ghost"
			elseif creature:getOutfit().lookType == 3456 then -- grass
				defenderRace2 = "flying"
			elseif creature:getOutfit().lookType == 3458 then -- grass
				defenderRace2 = "fire"
			elseif creature:getOutfit().lookType == 3460 then -- grass
				defenderRace2 = "water"
			end
		elseif attacker:getName() == "Rotom" and primaryTypeName ~= "physical" then
			if attacker:getOutfit().lookType == 3450 then -- steel
				attackerRace2 = "ice"
			elseif attacker:getOutfit().lookType == 3452 then -- ground
				attackerRace2 = "grass"
			elseif attacker:getOutfit().lookType == 3454 then -- grass
				attackerRace2 = "ghost"
			elseif attacker:getOutfit().lookType == 3456 then -- grass
				attackerRace2 = "flying"
			elseif attacker:getOutfit().lookType == 3458 then -- grass
				attackerRace2 = "fire"
			elseif attacker:getOutfit().lookType == 3460 then -- grass
				attackerRace2 = "water"
			end
		elseif attacker:getName() == "Hoopa" and primaryTypeName ~= "physical" then
			if attacker:getOutfit().lookType == 4026 then
				attackerRace2 = "dark"
			elseif attacker:getOutfit().lookType == 4027 then 
				attackerRace2 = "ghost"
			end
		elseif creature:getName() == "Rotom" then
			if creature:getOutfit().lookType == 4026 then -- steel
				defenderRace2 = "dark"
			elseif creature:getOutfit().lookType == 4027 then -- ground
				defenderRace2 = "ghost"
			end
		end
		
		if creature:getSkull() >= 11 and creature:getSkull() <= 28 then
			defenderRace = skullToTera[creature:getSkull()]
			defenderRace2 = "none"
		elseif creature:getSkull() >= 11 and creature:getSkull() <= 28 then
			attackerRace = skullToTera[creature:getSkull()]
			attackerRace2 = "none"
		end
		
		-- Kecleon System
		
		if attacker:getName() == "Kecleon" and primaryTypeName ~= "physical" then
			attackerRace = primaryTypeName
		end
		if creature:getName() == "Kecleon" and primaryTypeName ~= "physical" then
			defenderRace = primaryTypeName
		end
		if (isStrongAgainst(primaryTypeName, defenderRace) and isWeakAgainst(primaryTypeName, defenderRace2)) or (isStrongAgainst(primaryTypeName, defenderRace2) and isWeakAgainst(primaryTypeName, defenderRace)) then
			typeeffectiveness = 1
		elseif isStrongAgainst(primaryTypeName, defenderRace) and isStrongAgainst(primaryTypeName, defenderRace2) then
			typeeffectiveness = 0.25
		elseif isStrongAgainst(primaryTypeName, defenderRace) or isStrongAgainst(primaryTypeName, defenderRace2) then
			typeeffectiveness = 0.5
		elseif isWeakAgainst(primaryTypeName, defenderRace) and isWeakAgainst(primaryTypeName, defenderRace2) then
			typeeffectiveness = 4
		elseif isWeakAgainst(primaryTypeName, defenderRace) or isWeakAgainst(primaryTypeName, defenderRace2) then
			typeeffectiveness = 2
		end
		if creature:getName() == "Shedinja" and typeeffectiveness < 2 then
			typeeffectiveness = 0
		end
		if math.random(1, 24) <= 1 then
			critical = 1.5
			if attacker:isPokemon() and attacker:getMaster():isPlayer() then
				local talisman = attacker:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
				if talismanTable[talisman] and talismanTable[talisman].buff == 'crit' then
					critical = talismanTable[talisman].amount
				end
			end
			Game.sendAnimatedText(attacker:getPosition(), "CRITICAL", TEXTCOLOR_RED)
		end
		
		if primaryTypeName == attackerRace or primaryTypeName == attackerRace2 then
			if isInArray(hiddenabilities.adaptability, attacker:getName()) and creature:getSkull() >= 11 and creature:getSkull() <= 28 then
				stab = 2.25
			elseif isInArray(hiddenabilities.adaptability, attacker:getName()) or (creature:getSkull() >= 11 and creature:getSkull() <= 28) then
				stab = 2.0
			else
				stab = 1.5
			end
			if primaryDamage < 60 then primaryDamage = 60 end
		end
		
		if attacker:getName() == "Arceus" and primaryTypeName ~= "physical" then
			stab = 1.5
		end
		if creature:getName() == "Arceus" and primaryTypeName ~= "physical" then
			typeeffectiveness = 0.5
		end
		
		local formula = ((2 * attacker:getLevel()) / 5) + 2
		formula = formula * primaryDamage
		if secondaryTypeName == "physical" then
			if attacker:getName() == "Shuckle" and math.random(1, 100) <= 33 then
				formula = (formula * (attacker:getTotalDefense() + evdef1)) / ((creature:getTotalDefense() / 2) + evdef2)
			else
				formula = (formula * (attacker:getTotalMeleeAttack() + evatk1)) / ((creature:getTotalDefense() / 2) + evdef2)
			end
			if attacker:getCondition(CONDITION_FIRE) ~= nil then
				formula = formula * 0.5
			end
		else
			if primaryTypeName ~= "physical" then
				formula = (formula * (attacker:getTotalMagicAttack() + evatk1)) / ((creature:getTotalMagicDefense() / 2) + evdef2)
			end
		end
		formula = ((formula / 25) + 2) * critical * (math.random(85, 100) / 100) * stab * typeeffectiveness
		
		if attacker:isPokemon() and not creature:isPokemon() and isInArray(legendaryPokemons, creature:getName()) then
			formula = formula / 100
		end
		
		if attacker:getMaster() and attacker:getMaster():isNpc() then
			local gymleaders = {"Brock", "Misty", "Lt. Surge", "Erika", "Sabrina", "Koga", "Blaine", "Giovanni"}
			if isInArray(gymleaders, attacker:getMaster():getName()) then
				formula = formula * 10
			else
				formula = formula * 5
			end
		end
		
		--- Focus
	
		if attacker:getCondition(CONDITION_FOCUS) ~= nil then
			formula = formula * 1.5
		end
		
		-- Defense
		
		if creature:getCondition(CONDITION_DEFENSEPLUS) ~= nil then
			formula = formula * 0.9
		end
		
		if creature:getCondition(CONDITION_DEFENSEMINUS) ~= nil then
			formula = formula * 1.1
		end
		
		-- Attack
		
		if attacker:getCondition(CONDITION_ATTACKPLUS) ~= nil then
			formula = formula * 1.1
		end
		
		if attacker:getCondition(CONDITION_ATTACKMINUS) ~= nil then
			formula = formula * 0.9
		end
		
		-- Held Bonuses
		
		if attacker:isPokemon() then
			if not attacker:getMaster():isPlayer() then return false end
			if attacker:getMaster():getUsingBall():getSpecialAttribute("held") and attacker:getMaster():getUsingBall():getSpecialAttribute("held") == 'held attack'  then
				formula = formula * 1.15
			end
		end
		
		if creature:isPokemon() then
			if not creature:getMaster():isPlayer() then return false end
			if creature:getMaster():getUsingBall():getSpecialAttribute("held") and creature:getMaster():getUsingBall():getSpecialAttribute("held") == 'held defense' then
				formula = formula * 0.9
			end
		end
		
		-- Talisman Buffs
		
		if attacker:isPokemon() and attacker:getMaster():isPlayer() then
			local talisman = attacker:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
			if talismanTable[talisman] and talismanTable[talisman].buff == primaryTypeName then
				formula = formula * talismanTable[talisman].amount
			end
		end
	
		-- Form Buffs
		
		if attacker:getName() == "Deoxys" and primaryTypeName ~= "physical" then
			if attacker:getOutfit().lookType == 3444 then
				formula = formula * 1.5
			elseif attacker:getOutfit().lookType == 3445 then
				formula = formula * 0.75
			elseif creature:getOutfit().lookType == 3439 then
				formula = formula * 0.5
			end
		elseif creature:getName() == "Deoxys" and primaryTypeName ~= "physical" then
			if creature:getOutfit().lookType == 3444 then
				formula = formula * 1.5
			elseif creature:getOutfit().lookType == 3445 then
				formula = formula * 0.75
			elseif creature:getOutfit().lookType == 3439 then
				formula = formula * 2
				if math.random(1, 10) <= 40 then
					formula = 0
				end
				creature:changeSpeed((-creature:getSpeed() + creature:getTotalSpeed())+150)
			end
		elseif attacker:getName() == "Hoopa" and primaryTypeName ~= "physical" then
			if attacker:getOutfit().lookType == 4026 then
				formula = formula * 1.5
			end
		end
		
		-- Changing Type Ability
		
		if isInArray(hiddenabilities.pixilate, attacker:getName()) and primaryTypeName == "normal" then
			primaryType = typetonumber["fairy"]
			primaryTypeName = "fairy"
			formula = formula * 1.30
		elseif isInArray(hiddenabilities.normalize, attacker:getName()) and primaryTypeName ~= "physical" then
			primaryType = typetonumber["normal"]
			primaryTypeName = "normal"
			formula = formula * 1.20
		elseif isInArray(hiddenabilities.aerilate, attacker:getName()) and primaryTypeName == "normal" then
			primaryType = typetonumber["flying"]
			primaryTypeName = "flying"
			formula = formula * 1.30
		elseif isInArray(hiddenabilities.refrigerate, attacker:getName()) and primaryTypeName == "normal" then
			primaryType = typetonumber["ice"]
			primaryTypeName = "ice"
			formula = formula * 1.30
		elseif isInArray(hiddenabilities.galvanize, attacker:getName()) and primaryTypeName == "normal" then
			primaryType = typetonumber["electric"]
			primaryTypeName = "electric"
			formula = formula * 1.20
		end
		
		-- Water Bubble
		
		if attacker:getName() == "Araquanid" and primaryTypeName == "water" then
			formula = formula * 2
		end
		if creature:getName() == "Araquanid" and primaryTypeName == "fire" then
			formula = formula * 0.5
		end
		
		-- Immune
		
		if isImune(primaryTypeName, defenderRace, defenderRace2) and not isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turret", "porygon turret"}, attacker:getName()) then
			if isInArray(hiddenabilities.scrappy, attacker:getName()) and (defenderRace == 'ghost' or defenderRace2 == 'ghost') then
				formula = formula
			elseif attacker:getName() == "Salazzle" and (defenderRace == 'steel' or defenderRace2 == 'steel') then
				formula = formula
			elseif attacker:isPokemon() and attacker:getMaster() and attacker:getMaster():getUsingBall() and attacker:getMaster():getUsingBall():getSpecialAttribute("talisman") and attacker:getMaster():getUsingBall():getSpecialAttribute("talisman") == "ignore" then
				formula = formula
			else
				formula = 0
			end
		elseif isImmuneAbility(primaryTypeName, attacker:getName(), creature.uid, primaryDamage) then
			formula = 0
		elseif creature:getCondition(CONDITION_IMMUNE) ~= nil then
			formula = 0
		end
		
		-- Confusion
		
		if attacker:getCondition(CONDITION_DRUNK) ~= nil then
			if math.random(1, 100) <= 10 then
				doTargetCombatHealth(creature.uid, attacker.uid, primaryType, primaryDamage*0.10, primaryDamage*0.10, 0)
				attacker:getPosition():sendMagicEffect(598)
				formula = 0
			end
		end
		
		-- Talisman Reflect
		
		if creature:isPokemon() and creature:getMaster():isPlayer() then
			local talisman = creature:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
			if talismanTable[talisman] and talismanTable[talisman].buff == 'return' then
				doTargetCombatHealth(creature.uid, attacker.uid, primaryType, returndmg * 1.05, returndmg * 1.05, 0)
			end
		elseif creature:getCondition(CONDITION_REFLECT) ~= nil and not isInArray(hiddenabilities.infiltrator, attacker:getName()) and secondaryTypeName == "physical" then
			doTargetCombatHealth(creature.uid, attacker.uid, primaryType, MonsterType(creature:getName()):getDefense() * 2, MonsterType(creature:getName()):getDefense() * 2, 0)
			creature:getPosition():sendMagicEffect(255)
			formula = 0
			creature:removeCondition(CONDITION_REFLECT)
		elseif isInArray({"Wobbuffet"}, creature:getName()) and math.random(1, 100) <= 33 and not isInArray(hiddenabilities.infiltrator, attacker:getName()) then
			creature:getPosition():sendMagicEffect(255)
			doTargetCombatHealth(creature.uid, attacker.uid, primaryType, returndmg*2, returndmg*2, 0)
			formula = 0
		elseif isInArray({"Lucario", "Mega Lucario", "Lopunny", "Mega Lopunny", "Medicham", "Mega Medicham", "Electabuzz", "Electivire", "Lycanroc", "Annihilape"}, creature:getName()) and math.random(1, 100) <= 10 and not isInArray(hiddenabilities.infiltrator, attacker:getName()) then
			creature:getPosition():sendMagicEffect(255)
			doTargetCombatHealth(creature.uid, attacker.uid, primaryType, returndmg, returndmg, 0)
			formula = 0
		elseif isInArray({"Mimikyu"}, creature:getName()) and math.random(1, 100) <= 15 then
			creature:getPosition():sendMagicEffect(3)
			formula = 0
		elseif isInArray({"Ferrothorn"}, creature:getName()) and primaryTypeName == "physical" then
			doTargetCombatHealth(creature.uid, attacker.uid, primaryType, returndmg/8, returndmg/8, 0)
			formula = 0
		end
		
		-- Evasion
		
		if creature:getMaster() and creature:getMaster():isPlayer() then
			local evasiontalisman = creature:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
			if talismanTable[evasiontalisman] and talismanTable[evasiontalisman].buff == 'evade' then
				if math.random(1, 100) <= talismanTable[evasiontalisman].amount then
					formula = 0
				end
			end
		end
		
		if creature:getCondition(CONDITION_EVASION) ~= nil then
			if math.random(1, 100) <= 10 then
				formula = 0
			end
		end
		
		-- Damage to PVP Pokemon
	
		if attacker:isPokemon() and creature:isPokemon() then
			if not attacker:getMaster() then return false end
			if not creature:getMaster() then return false end
			if attacker:getMaster():isNpc() then return false end
			if isInArray(getPartyMembers(attacker:getMaster()), getPlayerByName(creature:getMaster():getName())) then 
				formula = 0
			else
				formula = formula * 0.25
			end
		elseif attacker:isPokemon() and creature:isPlayer() then
			if not attacker:getMaster() then return false end
			if not creature:getMaster() then return false end
			if attacker:getMaster():isNpc() then return false end
			if isInArray(getPartyMembers(attacker:getMaster()), getPlayerByName(creature:getName())) then 
				formula = 0
			end
		end
		
		-- Melee balancing
		
		if primaryTypeName == "physical" then
			formula = formula * 0.5
		end
		
		-- Level difference balancing.
		
		if primaryTypeName ~= "physical" and attacker:isPokemon() then
			local extra = attacker:getLevel() - creature:getLevel()
			if extra < 10 then
				extra = (extra / 100) + 1
			elseif extra >= 10 and extra < 20 then
				extra = (extra / 100) + 1.2
				formula = formula * extra
			elseif extra >= 20 and extra < 30 then
				extra = (extra / 100) + 1.4
				formula = formula * extra
			elseif extra >= 30 and extra < 40 then
				extra = (extra / 100) + 1.6
				formula = formula * extra
			elseif extra >= 40 and extra < 50 then
				extra = (extra / 100) + 1.8
				formula = formula * extra
			elseif extra >= 50 and extra < 60 then
				extra = (extra / 100) + 2
				formula = formula * extra
			elseif extra >= 60 and extra < 70 then
				extra = (extra / 100) + 2.2
				formula = formula * extra
			elseif extra >= 70 and extra < 80 then
				extra = (extra / 100) + 2.4
				formula = formula * extra
			elseif extra >= 80 and extra < 90 then
				extra = (extra / 100) + 2.6
				formula = formula * extra
			elseif extra >= 90 and extra < 100 then
				extra = (extra / 100) + 3
				formula = formula * extra
			end
		end
		
		-- Passives
		
		if secondaryTypeName == "physical"  and isInArray(hiddenabilities.flamebody, creature:getName()) then
			if math.random(1, 100) <= 30 then
				setConditionOn(creature.uid, attacker.uid, 'burn')
			end
		elseif isInArray(hiddenabilities.cursedbody, creature:getName()) and secondaryTypeName == "physical" then
			if math.random(1, 100) <= 10 then
				setConditionOn(creature.uid, attacker.uid, 'silence')
			end
		elseif (secondaryTypeName == "physical"  and isInArray(hiddenabilities.poisonpoint, creature:getName())) or (secondaryTypeName == "physical"  and isInArray(hiddenabilities.poisontouch, creature:getName())) then
			if math.random(1, 100) <= 30 then
				setConditionOn(creature.uid, attacker.uid, 'poison')
			end
		elseif secondaryTypeName == "physical" and isInArray(hiddenabilities.effectspore, creature:getName()) then
			local condis = {'sleep', 'paralyze'}
			if math.random(1, 100) <= 30 then
				setConditionOn(creature.uid, attacker.uid, condis[math.random(1, 2)])
				setConditionOn(creature.uid, attacker.uid, 'poison')
			end
		elseif secondaryTypeName == "physical"  and isInArray(hiddenabilities.static, creature:getName()) then
			if math.random(1, 100) <= 30 then
				setConditionOn(creature.uid, attacker.uid, 'paralyze')
			end
		end
		
		-- Talisman Defender
		
		if creature:isPokemon() and creature:getMaster():isPlayer() then
			local talisman = creature:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
			if talismanTable[talisman] and talismanTable[talisman].buff and talismanTable[talisman].buff:split("_") and talismanTable[talisman].buff:split("_") ~= 0 and talismanTable[talisman].buff:split("_")[1] == 'ret' and math.random(1, 100) <= talismanTable[talisman].amount then
				setConditionOn(creature.uid, attacker.uid, talismanTable[talisman].buff:split("_")[2])
			elseif talismanTable[talisman] and talismanTable[talisman].buff and talismanTable[talisman].buff:split("_") and talismanTable[talisman].buff:split("_") ~= 0 and talismanTable[talisman].buff:split("_")[1] == 'spell' and math.random(1, 100) <= talismanTable[talisman].amount then
				doCreatureCastSpell(creature.uid, talismanTable[talisman].buff:split("_")[2])
			elseif talismanTable[talisman] and talismanTable[talisman].buff == 'immunity' and talismanTable[talisman].amount == getCombatName(primaryType) then
				formula = 0
			elseif talismanTable[talisman] and talismanTable[talisman].buff and talismanTable[talisman].buff:split("_") and talismanTable[talisman].buff:split("_") ~= 0 and talismanTable[talisman].buff:split("_")[1] == 'res' and (attackerRace == talismanTable[talisman].buff:split("_")[2] or attackerRace2 == talismanTable[talisman].buff:split("_")[2]) then
				formula = formula * talismanTable[talisman].amount
			end
		end
		
		-- Talisman Attacker
		
		if attacker:isPokemon() and attacker:getMaster():isPlayer() then
			local talisman = attacker:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
			if talismanTable[talisman] and talismanTable[talisman].buff == 'lifesteal' then
				doTargetCombatHealth(0, attacker.uid, COMBAT_HEALING, formula * talismanTable[talisman].amount, formula * talismanTable[talisman].amount, 0)
			elseif talismanTable[talisman] and talismanTable[talisman].buff == 'money' then
				attacker:getMaster():setBankBalance(attacker:getMaster():getBankBalance() + (formula * (talismanTable[talisman].amount - 1)))
				formula = formula * (2 - talismanTable[talisman].amount)
			elseif talismanTable[talisman] and talismanTable[talisman].buff and talismanTable[talisman].buff:split("_") and talismanTable[talisman].buff:split("_") ~= 0 and talismanTable[talisman].buff:split("_")[1] == 'eff' and (defenderRace == talismanTable[talisman].buff:split("_")[2] or defenderRace2 == talismanTable[talisman].buff:split("_")[2]) then
				formula = formula * talismanTable[talisman].amount
			end
		end
		
		-- Sturdy
		
		if isInArray(hiddenabilities.sturdy, creature:getName()) then
			if formula >= creature:getHealth() and creature:getCondition(CONDITION_MANASHIELD) == nil then
				local sturdy = Condition(CONDITION_STURDY)
				sturdy:setTicks(5000)
				local exhaust = Condition(CONDITION_MANASHIELD)
				exhaust:setTicks(60000)
				creature:addCondition(sturdy)
				creature:addCondition(exhaust)
				creature:setHealth(1)
			end
		end
		
		if creature:getCondition(CONDITION_STURDY) ~= nil and not isInArray(hiddenabilities.moldbreaker, attacker:getName()) then
			formula = 0
		end
		
		formula = math.ceil(formula)
		return formula, primaryType, secondaryDamage, secondaryType
	end
	
	if attacker and creature:isPlayer() then
		local formula = ((2 * attacker:getLevel()) / 5) + 2
		formula = formula * primaryDamage
		if secondaryTypeName == "physical" then
			formula = (formula * attacker:getTotalMeleeAttack()) / 10
		else
			if primaryTypeName ~= "physical" then
				formula = (formula * attacker:getTotalMagicAttack()) / 10
			end
		end
		formula = ((formula / 50) + 2) * 1 * (math.random(85, 100) / 100) * 1 * 1
		formula = math.ceil(formula)
		
		return formula, primaryType, secondaryDamage, secondaryType
	end
end
