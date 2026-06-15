local criticalProbability = 1
local blockedProbability = 1
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
		["dark"] = {strong = {"ghost", "dark"}, weak = {"fighting", "bug", "fairy"}},
		["steel"] = {strong = {"normal", "physical", "flying", "rock", "bug", "steel", "grass", "psychic", "ice", "dragon", "fairy"}, weak = {"fighting", "ground", "fire"}, imune = {"poison"}},
		["fairy"] = {strong = {"fighting", "bug", "dark"}, weak = {"poison", "steel"}, imune = {"dragon"}},
		["fighting"] = {strong = {"rock", "bug", "dark"}, weak = {"flying", "psychic", "fairy"}}
	}
	
--strong = 0.5
--weak = 2
--imune = 0
-- dano que recebe
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
		if isInArray(abilities[i], name) then
			if attackerRace == immunities[i].dmg then
				if immunities[i].buff == "attackup" then
					defender = Creature(defender)
					local condition = Condition(CONDITION_ATTACKPLUS)
					condition:setParameter(CONDITION_PARAM_TICKS, 5000)
					defender:addCondition(condition)
					defender:getPosition():sendMagicEffect(55)
					return true
				elseif immunities[attackerRace].buff == "life" then
					defender = Creature(defender)
					defender:addLife(primaryDamage)
					return true
				end
				return true
			end
		end
	end
	return false
end

function onHealthChange(creature, attacker, primaryDamage, primaryType, secondaryDamage, secondaryType, origin)
	
	local localDamageMultiplier = 1.0
	if not attacker then
		local defenderMonsterType = MonsterType(creature:getName())
		local defenderRace = defenderMonsterType:getRaceName()
		local defenderRace2 = defenderMonsterType:getRace2Name()
		if primaryDamage then
			local primaryTypeName = getCombatName(primaryType)
			if isImune(primaryTypeName, defenderRace, defenderRace2) then
				return 0, primaryType, secondaryDamage, secondaryType
			end
			if (isStrongAgainst(primaryTypeName, defenderRace) and isWeakAgainst(primaryTypeName, defenderRace2)) or (isStrongAgainst(primaryTypeName, defenderRace2) and isWeakAgainst(primaryTypeName, defenderRace)) then
				return primaryDamage, primaryType, secondaryDamage, secondaryType
			elseif isStrongAgainst(primaryTypeName, defenderRace) and isStrongAgainst(primaryTypeName, defenderRace2) then
				return primaryDamage * 0.25, primaryType, secondaryDamage, secondaryType
			elseif isStrongAgainst(primaryTypeName, defenderRace) or isStrongAgainst(primaryTypeName, defenderRace2) then
				return primaryDamage * 0.5, primaryType, secondaryDamage, secondaryType
			elseif isWeakAgainst(primaryTypeName, defenderRace) and isWeakAgainst(primaryTypeName, defenderRace2) then
				return primaryDamage * 4, primaryType, secondaryDamage, secondaryType
			elseif isWeakAgainst(primaryTypeName, defenderRace) or isWeakAgainst(primaryTypeName, defenderRace2) then
				return primaryDamage * 2, primaryType, secondaryDamage, secondaryType
			end
			if isImmuneAbility(primaryTypeName, creature:getName(), creature.uid, primaryDamage) then
				return 0, primaryType, secondaryDamage, secondaryType
			end
		elseif secondaryDamage then
			local secondaryTypeName = getCombatName(secondaryType)
			if isImune(primaryTypeName, defenderRace, defenderRace2) then
				return primaryDamage, primaryType, 0, secondaryType
			end
			if (isStrongAgainst(secondaryTypeName, defenderRace) and isWeakAgainst(secondaryTypeName, defenderRace2)) or (isStrongAgainst(secondaryTypeName, defenderRace2) and isWeakAgainst(secondaryTypeName, defenderRace)) then
				return primaryDamage, primaryType, secondaryDamage, secondaryType
			elseif isStrongAgainst(secondaryTypeName, defenderRace) and isStrongAgainst(secondaryTypeName, defenderRace2) then
				return primaryDamage, primaryType, secondaryDamage * 0.25, secondaryType
			elseif isStrongAgainst(secondaryTypeName, defenderRace) or isStrongAgainst(secondaryTypeName, defenderRace2) then
				return primaryDamage, primaryType, secondaryDamage * 0.5, secondaryType
			elseif isWeakAgainst(secondaryTypeName, defenderRace) and isWeakAgainst(secondaryTypeName, defenderRace2) then
				return primaryDamage, primaryType, secondaryDamage * 4, secondaryType
			elseif isWeakAgainst(secondaryTypeName, defenderRace) or isWeakAgainst(secondaryTypeName, defenderRace2) then
				return primaryDamage, primaryType, secondaryDamage * 2, secondaryType
			end
			if isImmuneAbility(primaryTypeName, creature:getName(), creature.uid, secondaryDamage) then
				return primaryDamage, primaryType, 0, secondaryType
			end
		end
	end
	
	
	
	if attacker then
		
		-- Immunity
		if primaryDamage then
		attacker:getMaster():sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, primaryDamage)
		end
		if secondaryDamage then
		attacker:getMaster():sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, secondaryDamage)
		end
		if creature:getCondition(CONDITION_IMMUNE) ~= nil then
			localDamageMultiplier = 0
			secondaryDamage = 0
			primaryDamage = 0
			creature:getMaster():sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu pokemon precisa estar pra fora da pokebola.")
		end
		
		-- Confusion
		
		if attacker:getCondition(CONDITION_DRUNK) ~= nil then
			if math.random(1, 100) <= 33 then
				local shield = math.floor(primaryDamage * localDamageMultiplier)
				local shield2 = math.floor(secondaryDamage * localDamageMultiplier)
				if primaryDamage then
					primaryDamage = 0
					attacker:addHealth(-shield)
					attacker:getPosition():sendMagicEffect(598)
				end
				if secondaryDamage then
					secondaryDamage = 0
					attacker:addHealth(-shield2)
					attacker:getPosition():sendMagicEffect(598)
				end
			end
		end
		
		-- Reflect 
		
		if creature:getCondition(CONDITION_REFLECT) ~= nil then
			local shield = math.floor(primaryDamage * localDamageMultiplier)
			local shield2 = math.floor(secondaryDamage * localDamageMultiplier)
			if primaryDamage and shield >= 50 then
				primaryDamage = 0
				attacker:addHealth(-shield)
				creature:removeCondition(CONDITION_REFLECT)
			end
			if secondaryDamage and shield2 >= 50 then
				secondaryDamage = 0
				attacker:addHealth(-shield2)
				creature:removeCondition(CONDITION_REFLECT)
			end
		end
		
		-- Evasion
		
		if creature:getCondition(CONDITION_EVASION) ~= nil then
			if math.random(1, 100) <= 10 then
				if primaryDamage then
					primaryDamage = 0
				end
				if secondaryDamage then
					secondaryDamage = 0
				end
			end
		end
	
	end
	
	if not attacker then
		return primaryDamage, primaryType, secondaryDamage, secondaryType
	end
	if creature:isPlayer() or attacker:isPlayer() then
		if primaryDamage then primaryDamage = math.floor(primaryDamage * 0.08) end
		return primaryDamage, primaryType, secondaryDamage, secondaryType
	end

	local primaryTypeName = getCombatName(primaryType)
	local secondaryTypeName = getCombatName(secondaryType)

	local masterLevel
	local summonLevel
	local summonBoost
	local summonLove

	if attacker:getMaster() and attacker:getMaster():isNpc() then
		masterLevel = 100
		summonLevel = attacker:getLevel()
		summonBoost = 0
		summonLove = 0
	else
		masterLevel = attacker:getMasterLevel()
		summonLevel = attacker:getLevel()
		summonBoost = attacker:getBoost()
		summonLove = attacker:getLove()
	end
	
	if secondaryTypeName == "physical" then
		local defenseDamping = (1-creature:getTotalDefense()/600)
		if defenseDamping <= 0.5 then 
			defenseDamping = 0.5
		elseif defenseDamping >= 1 then
			defenseDamping = 1
		end
		localDamageMultiplier = localDamageMultiplier * defenseDamping
	else
		if primaryTypeName ~= "physical" and creature:getTotalMagicDefense() > 0 then	
			local defenseDamping = (1-creature:getTotalMagicDefense()/600)
			if defenseDamping <= 0.5 then 
				defenseDamping = 0.5
			elseif defenseDamping >= 1 then
				defenseDamping = 1
			end
			localDamageMultiplier = localDamageMultiplier * defenseDamping
		end
	end

	local defenderMonsterType = MonsterType(creature:getName())
	local defenderRace = defenderMonsterType:getRaceName()
	local defenderRace2 = defenderMonsterType:getRace2Name()
	local sms = 0
	local smscolor = 0
	local typedmg = 0
	local stabdmg = 0
	local critdmg = 0
	
	if (isStrongAgainst(primaryTypeName, defenderRace) and isWeakAgainst(primaryTypeName, defenderRace2)) or (isStrongAgainst(primaryTypeName, defenderRace2) and isWeakAgainst(primaryTypeName, defenderRace)) then
		typedmg = 1
	elseif isStrongAgainst(primaryTypeName, defenderRace) and isStrongAgainst(primaryTypeName, defenderRace2) then
		typedmg = 0.25
		sms = "Super Inefetivo"
		smscolor = TEXTCOLOR_RED
	elseif isStrongAgainst(primaryTypeName, defenderRace) or isStrongAgainst(primaryTypeName, defenderRace2) then
		typedmg = 0.5
		sms = "Inefetivo"
		smscolor = TEXTCOLOR_RED
	elseif isWeakAgainst(primaryTypeName, defenderRace) and isWeakAgainst(primaryTypeName, defenderRace2) then
		typedmg = 4
		sms = "Super Efetivo"
		smscolor = TEXTCOLOR_BLUE
	elseif isWeakAgainst(primaryTypeName, defenderRace) or isWeakAgainst(primaryTypeName, defenderRace2) then
		typedmg = 2
		sms = "Efetivo"
		smscolor = TEXTCOLOR_BLUE
	end
	
	if primaryTypeName == MonsterType(attacker:getName()):getRaceName() or primaryTypeName == MonsterType(attacker:getName()):getRace2Name() then
		stabdmg = 1.5
	end
	
	if isImune(primaryTypeName, defenderRace, defenderRace2) then
		localDamageMultiplier = 0
		sms = "Imune"
		smscolor = TEXTCOLOR_LIGHTGREY
	end
	
	if isImmuneAbility(primaryTypeName, creature:getName(), creature.uid, primaryDamage) then
		localDamageMultiplier = 0
		sms = "Imune"
		smscolor = TEXTCOLOR_LIGHTGREY
	end
	
	if sms ~= 0 then
		if sms == "Imune" then
			Game.sendAnimatedText(creature:getPosition(), sms, smscolor)
		else
			Game.sendAnimatedText(attacker:getPosition(), sms, smscolor)
		end
	end

	if math.random(1, 48) <= criticalProbability then
		critdmg = 1.5
		Game.sendAnimatedText(creature:getPosition(), "CRITICAL", TEXTCOLOR_RED)
	end
	
	if attacker:isPokemon() and creature:isPokemon() then --duel between players
		localDamageMultiplier = localDamageMultiplier / 7.0
	end

	if not attacker:isPokemon() and creature:isPokemon() then --wild pokemon damage
		localDamageMultiplier = localDamageMultiplier / 3.0
	end
	
	--- Focus
	
	if attacker:getCondition(CONDITION_FOCUS) ~= nil then
		if primaryDamage then
			localDamageMultiplier = localDamageMultiplier * 1.25
			attacker:removeCondition(CONDITION_FOCUS)
		end
		if secondaryDamage then
			localDamageMultiplier = localDamageMultiplier * 1.25
			attacker:removeCondition(CONDITION_FOCUS)
		end
	end
	
	-- Defense
	
	if creature:getCondition(CONDITION_DEFENSEPLUS) ~= nil then
		localDamageMultiplier = localDamageMultiplier * 0.9
	end
	
	if creature:getCondition(CONDITION_DEFENSEMINUS) ~= nil then
		localDamageMultiplier = localDamageMultiplier * 1.1
	end
	
	-- Attack
	
	if attacker:getCondition(CONDITION_ATTACKPLUS) ~= nil then
		localDamageMultiplier = localDamageMultiplier * 1.1
	end
	
	if attacker:getCondition(CONDITION_ATTACKMINUS) ~= nil then
		localDamageMultiplier = localDamageMultiplier * 0.9
	end
	
	
	
	localDamageMultiplier = localDamageMultiplier * (0.3 + math.random(1, 20) * 0.01)
	
	
	
	
	if primaryDamage then primaryDamage = math.floor(primaryDamage * localDamageMultiplier) end
	if secundaryDamage then secondaryDamage = math.floor(secondaryDamage * localDamageMultiplier) end
	
	if attacker:isPokemon() then
		
		local heldx = attacker:getMaster():getUsingBall():getSpecialAttribute("heldx") or 0
		if heldx ~= 0 then
			if firstToUpper(heldx:split("|")[1]) == "Attack"  and primaryDamage then primaryDamage = primaryDamage * 1.5 end
			if firstToUpper(heldx:split("|")[1]) == "Attack"  and secundaryDamage then secundaryDamage = secundaryDamage * 1.5 end
		end
		
	end
	
	return primaryDamage, primaryType, secondaryDamage, secondaryType
end
