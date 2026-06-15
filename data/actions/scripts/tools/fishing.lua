local useWorms = false
local maxSkill = 105

local rods = {
	[26820] = {common = {"Magikarp"}, uncommon = {"Magikarp"}, rare = {"Magikarp"}, epic = {"Magikarp"}, mythic = {"Magikarp"}},
	[38897] = {common = {"Poliwag", "Shellder", "Krabby", "Horsea"}, uncommon = {"Totodile", "Squirtle", "Oshawott", "Goldeen", "Seel"}, rare = {"Psyduck", "Piplup", "Tentacool"}, epic = {"Mudkip", "Qwilfish", "Slowpoke", "Staryu"}, mythic = {"Froakie", "Popplio", "Bibarel", "Lumineon", "Luvdisc"}},
	[38898] = {common = {"Poliwhirl", "Kingler", "Seadra", "Cloyster"}, uncommon = {"Wartortle", "Croconaw", "Dewott", "Seaking", "Dewgong"}, rare = {"Prinplup", "Tentacruel", "Quagsire", "Corsola"}, epic = {"Marshtomp", "Lanturn", "Omanyte", "Kabuto"}, mythic = {"Frogadier", "Brionne", "Gastrodon", "Gorebyss", "Huntail", "Floatzel"}},
	[38899] = {common = {"Poliwrath", "Politoed", "Kingdra"}, uncommon = {"Blastoise", "Feraligatr", "Samurott", "Octillery"}, rare = {"Empoleon", "Golduck", "Slowbro", "Starmie"}, epic = {"Swampert", "Omastar", "Kabutops", "Vaporeon", "Slowking", "Lapras", "Gyarados", "Mantine"}, mythic = {"Greninja", "Primarina", "Crawdaunt", "Sharpedo", "Whiscash", "Relicanth", "Walrein"}}
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local targetId = target.itemid
	
	if not isInArray(waterIds, target.itemid) then
		return false
	end
	local exhaust = Condition(CONDITION_EXHAUST_WEAPON)
	exhaust:setParameter(CONDITION_PARAM_TICKS, 3000)
	toPosition:sendMagicEffect(CONST_ME_LOSEENERGY)
	
	if player:getCondition(CONDITION_EXHAUST_WEAPON) then
		player:sendCancelMessage("Voce nao pescou nada.")
		return true
	end
	
	if player:getCondition(CONDITION_SAFFARI) ~= nil or player:getCondition(CONDITION_PARK) ~= nil then
		player:sendCancelMessage("You cant fish here.")
		return true 
	elseif isInRange(player:getPosition(), Position(2411, 0, 0), Position(2733, 351, 7)) then
		player:sendCancelMessage("Voce nao pode pescar na zona de distorcao.")
		return true 
	elseif isInRange(player:getPosition(), Position(664, 759, 7), Position(767, 810, 7)) then
		player:sendCancelMessage("Voce nao pode pescar na cidade.")
		return true 
	elseif isInRange(player:getPosition(), Position(625, 807, 7), Position(740, 900, 7)) then
		player:sendCancelMessage("Voce nao pode pescar na cidade.")
		return true 
	end
	
	local summons = player:getSummons()
	if #summons <= 0 then
		player:sendCancelMessage("Sorry, not possible. You need a Pokemon to be able to fish.")
		return true 
	end

	local summonTile = summons[1]:getTile()
	if summonTile:getHouse() or summonTile:hasFlag(TILESTATE_PROTECTIONZONE) then
		player:sendCancelMessage("Sorry, not possible. Your summon must be outside a protection zone.")
		return true 
	end

	if player:getEffectiveSkillLevel(SKILL_FISHING) <= maxSkill then
		if player:getSkillLevel(SKILL_FISHING) >= 100 then
			player:addSkillTries(SKILL_FISHING, (player:getSkillLevel(SKILL_FISHING)/5))
		elseif player:getSkillLevel(SKILL_FISHING) >= 99 then
			player:addSkillTries(SKILL_FISHING, (player:getSkillLevel(SKILL_FISHING)/2))
		else
			player:addSkillTries(SKILL_FISHING, player:getSkillLevel(SKILL_FISHING))
		end
	end
	
	local formulafish = math.random(1, player:getSkillLevel(SKILL_FISHING))
	
	if formulafish < 25 then
		name = rods[item:getId()].common[math.random(1, #rods[item:getId()].common)]
	elseif formulafish >= 25 and formulafish < 50 then
		name = rods[item:getId()].uncommon[math.random(1, #rods[item:getId()].uncommon)]
	elseif formulafish >= 50 and formulafish < 75 then
		name = rods[item:getId()].rare[math.random(1, #rods[item:getId()].rare)]
	elseif formulafish >= 75 and formulafish < 100 then
		name = rods[item:getId()].epic[math.random(1, #rods[item:getId()].epic)]
	elseif formulafish >= 100 then
		name = rods[item:getId()].mythic[math.random(1, #rods[item:getId()].mythic)]
		if isInArray({"Uxie", "Azelf", "Mesprit", "Kyogre"}, name) and player:getStorageValue(846514) == 1 then name = "Magikarp" end
	end	
	
	if MonsterType(name):hasMega() > 0 then
		if math.random(1, 100) <= 1 * megaVar then
			name = "Mega " .. name
		end
	end
	local spawnpos = player:getClosestFreePosition(player:getPosition())
	local monstro = Game.createMonster(name, spawnpos)
	
	if not string.find(name, "Mega ") and not isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turret", "porygon turret"}, name) then
		if math.random(1, 1000) <= 3 * teraVar then
			monstro:setSkull(math.random(11, 28))
		end
	end
	player:addCondition(exhaust)
	return true
end
