local initialLevel = 1
local initialBoost = 0
local multiplierExpFirstNormal = 100
local multiplierExpNormal = 5
local multiplierExpFirstShiny = 3000
local multiplierExpShiny = 1000

local function doPlayerSendEffect(cid, effect)
	local player = Player(cid)
	if player then
		player:getPosition():sendMagicEffect(effect)
	end
	return true
end

local function doPlayerAddExperience(cid, exp)
	local player = Player(cid)
	if player then
		player:addExperience(exp, true)
	end
	return true
end

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local tile = Tile(toPosition)
	if not tile or not tile:getTopDownItem() or not ItemType(tile:getTopDownItem():getId()):isCorpse() then
		return false
	end
	if Tile(player:getPosition()):getGround():getId() == 10769 then
		player:sendCancelMessage("Nao e possivel capturar pokemons em um trial.")
		return true
	end
	local targetCorpse = tile:getTopDownItem()

	local owner = targetCorpse:getAttribute(ITEM_ATTRIBUTE_CORPSEOWNER)
	if player:getParty() and not isInArray(getPartyMembers(player), owner) then
		player:sendCancelMessage(tostring(owner))
		return true
	end
	if owner ~= 0 and owner ~= player:getId() and not player:getParty() then
		player:sendCancelMessage("Sorry, not possible. You are not the owner.")
		return true
	end
	local ballKey = getBallKey(item:getId())
	local playerPos = getPlayerPosition(player)
	local d = getDistanceBetween(playerPos, toPosition)
	local delay = d * 80
	local delayMessage = delay + 2800
	local name = targetCorpse:getName()
	if name == "dead human" then		
		playerPos:sendMagicEffect(CONST_ME_POFF)
		return false
	end
	if name == "dead enlightened of the cult" then
		name = "enlightened of the cult"
	elseif name == "slain undead dragon" then
		name = "undead dragon"
	else
		name = string.gsub(name, "the ", "")
		name = string.gsub(name, "remains of ferumbras", "Ferumbras")
		name = string.gsub(name, "remains of", "")
		name = string.gsub(name, " a ", "")
		name = string.gsub(name, " an ", "")
		name = string.gsub(name, "slain ", "")
		name = string.gsub(name, "fainted ", "")
		name = string.gsub(name, "defeated ", "")
--		name = string.gsub(name, "dead ", "")
	end
	
	local monsterType = MonsterType(name)
	if not monsterType then
		print("WARNING! Monster " .. name .. " with bug on catch!")
		player:sendCancelMessage("Sorry, not possible. This problem was reported.")
		return true
	end
	local monsterNumber = monsterType:getNumber()
	local storageCatch = baseStorageCatches + monsterNumber
	local storageTry = baseStorageTries + monsterNumber
	local level = targetCorpse:getSpecialAttribute("corpseLevel") or initialLevel
	local teraType = targetCorpse:getSpecialAttribute("teraType") or 0
	local chance
	if level < 10 and not isInArray(legendaryPokemons, firstToUpper(name)) and name:lower() ~= "ditto" then
		chance = (100 - level + monsterType:catchChance()) * balls[ballKey].chanceMultiplier
	elseif isInArray(legendaryPokemons, firstToUpper(name)) then
		chance = 5 * balls[ballKey].chanceMultiplier
	else
		chance = (math.random(1, math.ceil(math.random((monsterType:catchChance() / 20), (monsterType:catchChance() / 10)))) + (100 - level)) * balls[ballKey].chanceMultiplier
		chance = math.random(1, math.ceil(chance))
	end
	-- print('Chance de catch do pokemon: '..name..' = '..chance)
	-- Unown System
	
	if name == "unown" then
		name = "unown|"..targetCorpse:getSpecialAttribute("unown")
	end
	if name == "wormadam" then
		name = "Wormadam|"..targetCorpse:getSpecialAttribute("wormadam")
	end
	
	-- New Balls
	
	if ballKey == "fastball" and monsterType:getBaseSpeed() < 200 then
		doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Nao funciona neste pokemon.")
		return true
	elseif ballKey == "saffariball" and player:getCondition(CONDITION_SAFFARI) == nil then
		doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Nao funciona fora do saffari.")
		return true
	elseif ballKey == "parkball" and player:getCondition(CONDITION_PARK) == nil then
		doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Nao funciona fora do pokepark.")
		return true
	elseif ballKey == "netball" then
		if not isInArray({"water", "bug"}, monsterType:getRaceName()) and not isInArray({"water", "bug"}, monsterType:getRace2Name()) then
			doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Nao funciona neste pokemon.")
			return true
		end
	elseif ballKey == "loveball" then
		if name ~= player:getUsingBall():getSpecialAttribute("pokeName"):lower() then
			doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Nao funciona neste pokemon.")
			return true
		end
	elseif ballKey == "duskball" then
		local worldTime = getWorldTime()
		local hours = math.floor(worldTime / 60)
		if hours > 4 and hours < 18 then
			doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Esta pokebola so funciona a noite. Hora agora: "..getFormattedWorldTime().."")
			return true
		end
	elseif ballKey == "heavyball" then
		if isInArray(weight.superheavy, monsterType:getName()) then
			chance = chance + 100
		elseif isInArray(weight.heavy, monsterType:getName()) then
			chance = chance + 50
		elseif isInArray(weight.normal, monsterType:getName()) then
			chance = chance + 25
		else
			doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Nao funciona neste pokemon.")
			return true
		end
	end
	
	if ballKey ~= "parkball" and player:getCondition(CONDITION_PARK) ~= nil then
		doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Voce so pode usar a Park Ball aqui.")
		return true
	end
	
	if ballKey ~= "saffariball" and player:getCondition(CONDITION_SAFFARI) ~= nil then
		doPlayerSendTextMessage(player:getId(), MESSAGE_EVENT_ADVANCE, "Voce so pode usar a Saffari Ball aqui.")
		return true
	end
	
	if player:getVocation():getName() == "Catcher" then
		chance = chance * catcherCatchBuff
	end
	if chance == 0 then
		playerPos:sendMagicEffect(CONST_ME_POFF)
		player:sendCancelMessage("Sorry, it is impossible to catch this monster.")
		return true
	end
	
	doSendDistanceShoot(playerPos, toPosition, balls[ballKey].missile)
	item:remove(1)
	targetCorpse:remove()
	if player:getStorageValue(storageTry) < 0 then
		player:setStorageValue(storageTry, 1)
	else
		player:setStorageValue(storageTry, player:getStorageValue(storageTry) + 1)
	end
	if ballKey == "saffariball" and player:getCondition(CONDITION_SAFFARI) ~= nil then
		if player:getItemCount(26685) <= 0 then
			player:removeCondition(CONDITION_SAFFARI) 
			player:teleportTo(Position(1227, 1681, 7))
		end
	end
	if ballKey == "parkball" and player:getCondition(CONDITION_PARK) ~= nil then
		if player:getItemCount(39132) <= 0 then
			player:removeCondition(CONDITION_PARK)
			player:teleportTo(Position(1180, 1658, 7))
		end
	end
	
	chance = chance * catchVar
	
	if math.random(1, 1000) <= chance or ballKey == "masterball" then
		if player:getSlotItem(CONST_SLOT_BACKPACK) and player:getSlotItem(CONST_SLOT_BACKPACK):getEmptySlots() >= 1 and player:getFreeCapacity() >= 1 then -- add to backpack
			addEvent(doAddPokeball, delayMessage, player:getId(), name, level, initialBoost, ballKey, false, delayMessage, teraType)
		else -- send to cp
			local addPokeball = doAddPokeball(player:getId(), name, level, initialBoost, ballKey, true, delayMessage + 4000, teraType)
			if not addPokeball then
				print("ERROR! Player " .. player:getName() .. " lost pokemon " .. name .. "! addPokeball false")
			end
			addEvent(doPlayerSendTextMessage, delayMessage + 2000, player:getId(), MESSAGE_EVENT_ADVANCE, "Since you are at maximum capacity, your ball was sent to CP.")
		end
		
		local playerLevel = player:getLevel()
		local maxExp = getNeededExp(playerLevel + 2) - getNeededExp(playerLevel)
		local maxExpShiny = getNeededExp(playerLevel + 5) - getNeededExp(playerLevel)

		local givenExp = monsterType:getExperience() * configManager.getNumber(configKeys.RATE_EXPERIENCE)
		if not msgcontains(name, 'Shiny') and player:getStorageValue(storageCatch) == -1 then
			givenExp = givenExp * multiplierExpFirstNormal
			if givenExp > maxExp then
				givenExp = maxExp
			end
			addEvent(doPlayerSendTextMessage, delayMessage + 1000, player:getId(), MESSAGE_EVENT_ADVANCE, "You got a bonus exp for your first catch of " .. name .. "!")
		else
			givenExp = givenExp * multiplierExpNormal
			if givenExp > maxExp then
				givenExp = maxExp
			end

		end

		if player:getStorageValue(storageCatch) == -1 then
			player:setStorageValue(storageCatch, 1)
		else
			player:setStorageValue(storageCatch, player:getStorageValue(storageCatch) + 1)
		end

		addEvent(doPlayerAddExperience, delayMessage, player:getId(), givenExp)
		addEvent(doSendMagicEffect, delay, toPosition, balls[ballKey].effectSucceed)
		addEvent(doPlayerSendTextMessage, delayMessage, player:getId(), MESSAGE_EVENT_ADVANCE, "Congratulations! You have caught a " .. name .. "!")
		addEvent(doPlayerSendEffect, delayMessage, player:getId(), 297)
	else -- missed		
		addEvent(doSendMagicEffect, delay, toPosition, balls[ballKey].effectFail)
		addEvent(doPlayerSendEffect, delayMessage, player:getId(), 286)
		return true
	end	

	return true
end
