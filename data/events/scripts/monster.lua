local megaChance = 1

function Monster:onSpawn(position, startup, artificial) -- Life Formula
	local hp = self:getMaxHealth()
	local lv = self:getLevel()
	local formula = ((lv * 20) + (hp * 0.10)) + hp
	self:setMaxHealth(formula)
	self:setHealth(formula)
	if isInRange(position, Position(2411, 0, 0), Position(2733, 351, 7)) and not artificial then
		self:setMaxHealth(formula * 10)
		self:setHealth(formula * 10)
	end
	if string.find(self:getName(), "Mega ") and not Creature(self):isPokemon() then
		self:setMaxHealth(formula * 10)
		self:setHealth(formula * 10)
	end
	if isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turret", "porygon turret"}, self:getName():lower()) and not artificial then
		self:setHiddenHealth(true)
	end
	if self:getName() == "Unown" and not artificial then
		local types = {3468, 3469, 3470, 3471, 3472, 3473, 3474, 3475, 3476, 3477, 3478, 3479, 3480, 3481, 3482, 3483, 3484, 3485, 3486, 3461, 3462, 3463, 3464, 3465, 3466, 3467}
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = types[math.random(1, 26)]})
		self:addCondition(condition)
	end
	if self:getName() == "Wormadam" and not artificial then
		local types = {3487, 3488, 3489}
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = types[math.random(1, 3)]})
		self:addCondition(condition)
	end
	if not string.find(self:getName(), "Mega ") and not artificial and not isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turret", "porygon turret", "arceus", "kecleon"}, self:getName():lower()) and not startup then
		local chance = 3 * teraVar
		local rand = math.random(1, 1000)
		if isInRange(self:getPosition(), Position(1105, 1607, 15), Position(1313, 1720, 15)) then
			chance = 12 * teraVar
		end
		if rand <= chance then
			self:setSkull(math.random(11, 28))
		end
	end
	if MonsterType(self:getName()):hasMega() > 0 and not artificial and not startup then
		local chance = 1 * megaVar
		local rand = math.random(1, 100)
		if isInRange(self:getPosition(), Position(1105, 1607, 15), Position(1313, 1720, 15)) then
			chance = 4 * megaVar
		end		
		if rand <= chance then
			local megaName = "Mega " .. self:getName()
			if megaName == "Mega Charizard" then if math.random(1, 2) == 1 then megaName = megaName.." X" else megaName = megaName.." Y" end end
			local megaMonsterType = MonsterType(self:getName())
			if not megaMonsterType then
				print("WARNING! " .. megaName .. " not found for respawn.")
			else
				Game.createMonster(megaName, position, false, true, 0, 0)
				return false
			end
		end
	end
	
	if math.random(1, 1000) <= 1 * lendaVar and MonsterType(self:getName()):getNumber() <= 151 and self:getLevel() > 60 and not artificial and not startup then -- birds
		local pokes = {"Articuno", "Moltres", "Zapdos"}
		local monstro = Game.createMonster(pokes[math.random(1, #pokes)], position)
		addEvent(doRemoveCreature, 10*60*1000, monstro.uid)	
		position:sendMagicEffect(331)
	elseif math.random(1, 1000) <= 1 * lendaVar and ((MonsterType(self:getName()):getNumber() > 151 and MonsterType(self:getName()):getNumber() < 243) or MonsterType(self:getName()):getNumber() == 248) and self:getLevel() > 60 and not artificial and not startup then -- Dogs
		local dogs = {"Entei", "Suicune", "Raikou"}
		local monstro = Game.createMonster(dogs[math.random(1, #dogs)], position)
		addEvent(doRemoveCreature, 10*60*1000, monstro.uid)	
		position:sendMagicEffect(331)
	elseif math.random(1, 1000) <= 1 * lendaVar and MonsterType(self:getName()):getNumber() > 251 and MonsterType(self:getName()):getNumber() < 377 and self:getLevel() > 60 and not artificial and not startup then -- Latios/Latias
		local pokes = {"Latios", "Latias", "Regice", "Registeel", "Regirock"}
		local monstro = Game.createMonster(pokes[math.random(1, #pokes)], position)
		addEvent(doRemoveCreature, 10*60*1000, monstro.uid)	
		position:sendMagicEffect(331)
	elseif math.random(1, 1000) <= 1 * lendaVar and MonsterType(self:getName()):getNumber() > 386 and MonsterType(self:getName()):getNumber() < 480 and self:getLevel() > 60 and not artificial and not startup then -- Cresselia
		local pokes = {"Cresselia"}
		local monstro = Game.createMonster(pokes[math.random(1, #pokes)], position)
		addEvent(doRemoveCreature, 10*60*1000, monstro.uid)	
		position:sendMagicEffect(331)
	elseif math.random(1, 100) <= 5 and MonsterType(self:getName()):getCorpseId() == 39260 and not isInArray({"Arceus", "Kleavor", "Wyrdeer", "Ursaluna", "Basculegion", "Sneasler", "Overqwil", "Toedscruel", "Wugtrio", "Annihilape", "Clodsire", "Farigiraf", "Dudunsparce", "Iron Bundle"}, self:getName()) and not artificial and not startup then
		local boss = {"Kleavor", "Wyrdeer", "Ursaluna", "Basculegion", "Sneasler", "Overqwil", "Toedscruel", "Wugtrio", "Annihilape", "Clodsire", "Farigiraf", "Dudunsparce", "Iron Bundle"}
		local monstro = Game.createMonster(boss[math.random(1, #boss)], position)
		addEvent(doRemoveCreature, 5*60*1000, monstro.uid)
		monstro:setMaxHealth(monstro:getHealth() * 25)
		monstro:setHealth(monstro:getMaxHealth())
	elseif math.random(1, 1000) <= 1 * lendaVar and (MonsterType(self:getName()):getRaceName() == "water" or MonsterType(self:getName()):getRace2Name() == "water") and self:getLevel() > 60 and not artificial and not startup then
		local pokes = {"Kyogre", "Uxie", "Azelf", "Mesprit"}
		local monstro = Game.createMonster(pokes[math.random(1, #pokes)], position)
		addEvent(doRemoveCreature, 10*60*1000, monstro.uid)	
		position:sendMagicEffect(331)
	elseif math.random(1, 1000) <= 1 * lendaVar and (MonsterType(self:getName()):getRaceName() == "fire" or MonsterType(self:getName()):getRace2Name() == "fire") and self:getLevel() > 60 and not artificial and not startup then
		local pokes = {"Groudon"}
		local monstro = Game.createMonster(pokes[math.random(1, #pokes)], position)
		addEvent(doRemoveCreature, 10*60*1000, monstro.uid)	
		position:sendMagicEffect(331)
	end
	
	return true
end
