local outfit = {lookType = 267, lookHead = 0, lookBody = 0, lookLegs = 0, lookFeet = 0, lookTypeEx = 0, lookAddons = 0}
local rocks = {1285, 3609}
local bushes = {2767}
local holes = {468, 481, 483, 7932}

local function walkToPosition(cid, path, count, extra)
	local creature = Creature(cid)
	if not creature then return true end
	if creature:getCondition(CONDITION_MOVING) == nil then return true end
	if count > #path then
		if extra then
			if extra.action == "destroy" then
				local item = extra.tile:getTopTopItem()
				if item and (isInArray(rocks, item:getId()) or isInArray(bushes, item:getId())) then
					extra.position:sendMagicEffect(extra.effect)
					item:transform(extra.newItem)
					item:decay()
					if math.random(1, 1000) <= 1 and creature:getLevel() >= 75 then
						Game.createMonster("Shaymin", creature:getClosestFreePosition(creature:getPosition()))
					end
				end
			elseif extra.action == "changeGround" then
				local ground = extra.tile:getGround()
				if ground and (isInArray(holes, ground:getId())) then
					extra.position:sendMagicEffect(extra.effect)
					ground:transform(extra.newGround)
					ground:decay()
				end
			elseif extra.action == "mount" then
				local player = Player(extra.playerId)
				if player then
					player:setStorageValue(extra.storage, 1)
					doRemoveSummon(extra.playerId, false)
					doChangeOutfit(extra.playerId, extra.outfit)
					player:changeSpeed(extra.speed)
				end
			end
		end
		return true
	end

	local dir = path[count]
	creature:move(dir)
	count = count + 1
	addEvent(walkToPosition, creature:getWalkDelay(dir), cid, path, count, extra)
end

local function setCreatureIdle(cid, time)
	local creature = Creature(cid)
	if not creature then return true end
	local condition = Condition(CONDITION_MOVING)
	condition:setParameter(CONDITION_PARAM_TICKS, time)
	creature:addCondition(condition)
end

function Creature.walk(self, position, maxDistance, extra)
	local path = self:getPathTo(position, 0, maxDistance, true, false, 14)
	if not path then return false end

	setCreatureIdle(self.uid, #path * 500 + 10000)
	walkToPosition(self.uid, path, 1, extra)

	return true
end

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if not target then
		return true
	end

	if type(target) ~= "userdata" then
		return true
	end

	if target:isItem() or target == player then
		local tileUnder = Tile(player:getPosition())
		if not tileUnder then
			player:sendCancelMessage("WARNING! Tile not found pos " .. player:getPosition().x .. " " .. player:getPosition().y .. " " .. player:getPosition().z .. ".")
			return true
		end
		local groundUnder = tileUnder:getGround()
		if not groundUnder then
			player:sendCancelMessage("WARNING! Ground not found pos " .. player:getPosition().x .. " " .. player:getPosition().y .. " " .. player:getPosition().z .. ".")
			return true
		end		
		if groundUnder:getId() == flyFloor then
			player:sendCancelMessage("Sorry, not possible. First go downstairs.")
			return true
		end
		if (player:getStorageValue(storageRide) == 1 or player:getStorageValue(storageFly) == 1) then
			local summonName = player:getSummonNameFromBall()
			local actualSpeed = player:getSpeed()
			player:say("Thanks, " .. summonName .. "!", TALKTYPE_SAY)
			player:removeCondition(CONDITION_OUTFIT)
			player:changeSpeed(-actualSpeed+player:getBaseSpeed())
			player:setStorageValue(storageRide, -1)
			player:setStorageValue(storageFly, -1)
			doReleaseSummon(player:getId(), player:getPosition(), false)
			return true
		end
	end

	if not hasSummons(player) then
		player:sendCancelMessage("Sorry, not possible. You need a summon to order.")
		return true
	end

	local summon = player:getSummon()
	local summonName = summon:getName()
	local summonPos = summon:getPosition()
	local playerPos = player:getPosition()

	if summon:getCondition(CONDITION_PARALYZE) or summon:getCondition(CONDITION_SLEEP) then
		player:sendCancelMessage("Sorry, not possible. Your Pokemon is either paralyzed or sleeping.")
		return true
	end

	if target:isCreature() then
		if target ~= player and target:isMonster() then
			local name = player:getSummonNameFromBall():lower()
			if name == "ditto" then
				if target == player:getSummon() then
					local ball = player:getUsingBall()
					ball:setSpecialAttribute("dittoTransform", player:getUsingBall():getSpecialAttribute('pokeName'))
					doRemoveSummon(player:getId(), false, false, false)
					ball:setBeingUsed()
					doReleaseSummon(player:getId(), summonPos, false, false)
					summonPos:sendMagicEffect(304)
					return true
				end
				local ball = player:getUsingBall()
				if isInArray({"ditto", "smeargle", "missingno", "kleavor", "wyrdeer", "ursaluna", "basculegion", "sneasler", "overqwil", "toedscruel", "wugtrio", "annihilape", "clodsire", "farigiraf", "dudunsparce", "iron bundle", "gholdengo"}, target:getName():lower()) then return true end
				if isInArray(legendaryPokemons, target:getName()) then return true end
				if string.find(target:getName(), "Mega ") then return true end
				local targetName = target:getName()

				local ballKey = getBallKey(ball:getId())
				ball:setSpecialAttribute("dittoTransform", targetName)
				doRemoveSummon(player:getId(), false, false, false)
				ball:setBeingUsed()
				doReleaseSummon(player:getId(), summonPos, false, false)
				player:say(name .. ", transform into a " .. targetName .. "!", TALKTYPE_SAY)
				return true
			elseif name == "smeargle" or name == "shiny smeargle" then
				if target == player:getSummon() then
					local condition = Condition(CONDITION_MANASHIELD)
					condition:setTicks(5000)
					player:getSummon():addCondition(condition)
					player:getSummon():getPosition():sendMagicEffect(448)
					return true
				end
			else
				player:sendCancelMessage("Sorry, not possible. You can only use order on the ground or in yourself.")
				return true
			end
		end
	end

	if target:isItem() then
		local tile = Tile(toPosition)
		if not tile then
			return false
		end
		local ground = tile:getGround()
		if not ground then
			return false
		end

		local destTile = getTileInfo(toPosition)
		if not destTile or destTile.house or destTile.protection then
			return false
		end

		local item = tile:getTopTopItem()
		if item and isInArray(rocks, item:getId()) then
			local race = MonsterType(summonName):getRaceName()
			local race2 = MonsterType(summonName):getRace2Name()
			if race == "rock" or race2 == "rock" or race == "fighting" or race2 == "fighting" then
				summon:walk(toPosition, 1, {action = "destroy", effect = CONST_ME_GROUNDSHAKER, position = toPosition, tile = tile, newItem = 1336})
				player:say(summonName .. ", destroy it!", TALKTYPE_SAY)
			else
				player:sendCancelMessage("Sorry, not possible. You need a rock type pokemon for rock smash.")
			end
			return true
		end
		if item and isInArray(bushes, item:getId()) then
			local race = MonsterType(summonName):getRaceName()
			local race2 = MonsterType(summonName):getRace2Name()
			if race == "grass" or race2 == "grass" then
				summon:walk(toPosition, 1, {action = "destroy", effect = CONST_ME_GROUNDSHAKER, position = toPosition, tile = tile, newItem = 6216})
				player:say(summonName .. ", cut it!", TALKTYPE_SAY)
			else
				player:sendCancelMessage("Sorry, not possible. You need a grass type pokemon for cut.")
			end
			return true
		end
		local groundId = ground:getId()
		if isInArray(holes, groundId) then
			local race = MonsterType(summonName):getRaceName()
			local race2 = MonsterType(summonName):getRace2Name()
			if race == "ground" or race2 == "ground" then
				summon:walk(toPosition, 1, {action = "changeGround", effect = CONST_ME_GROUNDSHAKER, position = toPosition, tile = tile, newGround = groundId + 1})
				player:say(summonName .. ", use dig!", TALKTYPE_SAY)
			else
				player:sendCancelMessage("Sorry, not possible. You need a ground type pokemon for dig.")
			end
			return true
		end

		if Tile(toPosition):hasProperty(CONST_PROP_BLOCKSOLID) or Tile(toPosition):hasProperty(CONST_PROP_BLOCKPATH) then
			return false
		end

		if not summon:getCondition(CONDITION_MOVING) then
			if summon:walk(toPosition, 0) then
				player:say(summonName .. ", move there!", TALKTYPE_SAY)
			else
				player:sendCancelMessage("Sorry, not possible. Too far way.")
			end
		else
			summon:removeCondition(CONDITION_MOVING)
			player:sendCancelMessage("Sorry, not possible. Your pokemon was already moving.")
		end
		return true
	end

	if target:isCreature() then
		if target == player then -- order ride or fly
			if player:isOnBike() then
				player:sendCancelMessage("Sorry, not possible while on bike.")
				return true
			end
			local msg = summonName
			local monsterType = MonsterType(summonName)
			local flyOutfit = monsterType:isFlyable()
			local rideOutfit = monsterType:isRideable()	
			local summonSpeed = summon:getTotalSpeed() + player:getSpeed()
			local storage = 0
			if rideOutfit > 0 and flyOutfit == 0 then -- ride
				if rideOutfit > 1 then outfit.lookType = rideOutfit end
				msg = msg .. ", give me a ride!"
				storage = storageRide
				if rideOutfit == 1 then
					if string.find(player:getSummon():getName() , "Mega ") then
						outfit.lookType = MonsterType(creature:getName()):getOutfit().lookType
					else
						outfit.lookType = monsterType:getOutfit().lookType
					end
				else
					if player:getUsingBall():getSpecialAttribute("usingaddon") and player:getUsingBall():getSpecialAttribute("usingaddon") ~= monsterType:getOutfit().lookType then
						if string.find(player:getSummon():getName() , "Mega ") then
							outfit.lookType = addonnumber[addonmega[player:getUsingBall():getSpecialAttribute("usingaddon")]].hab
						else
							outfit.lookType = addonnumber[player:getUsingBall():getSpecialAttribute("usingaddon")].hab
						end
					else
						outfit.lookType = rideOutfit
					end
				end
			elseif rideOutfit == 0 and flyOutfit > 0 then -- fly
				local pos = player:getPosition()
				if isInArray({0, 1, 8, 9, 10, 11, 12, 13, 14, 15}, pos.z) then player:sendCancelMessage("Sorry, not possible. you cant fly on floors 0 and 1.") return true end
				if isInRange(pos, Position(2411, 0, 0), Position(2733, 351, 7)) and not player:isPremium() then
					player:sendCancelMessage("Desculpe, voce precisa de premium para voar aqui.")
					return false
				end
				if flyOutfit > 1 then outfit.lookType = flyOutfit end
				msg = msg .. ", let me fly on you!"
				storage = storageFly
				if player:getUsingBall():getSpecialAttribute("held") and player:getUsingBall():getSpecialAttribute("held") == 'held wing' then
					summonSpeed = summonSpeed + 500
				end
				local talisman = player:getUsingBall():getSpecialAttribute('talisman') or 0
				if talismanTable[talisman] and talismanTable[talisman].buff == 'fly' then
					summonSpeed = summonSpeed + talismanTable[talisman].amount
				end
				if flyOutfit == 1 then
					if string.find(player:getSummon():getName() , "Mega ") then
						outfit.lookType = MonsterType(creature:getName()):getOutfit().lookType
					else
						outfit.lookType = monsterType:getOutfit().lookType
					end
				else
					if player:getUsingBall():getSpecialAttribute("usingaddon") and player:getUsingBall():getSpecialAttribute("usingaddon") ~= monsterType:getOutfit().lookType then
						if string.find(player:getSummon():getName() , "Mega ") then
							outfit.lookType = addonnumber[addonmega[player:getUsingBall():getSpecialAttribute("usingaddon")]].hab
						else
							outfit.lookType = addonnumber[player:getUsingBall():getSpecialAttribute("usingaddon")].hab
						end
					else
						outfit.lookType = flyOutfit
					end
				end		
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Use as teclas 'PgUP' e 'PgDOWN' no seu teclado ou !up e !down para mudar o andar do fly.")		
			elseif rideOutfit > 0 and flyOutfit > 0 then -- fly
				local pos = player:getPosition()
				if isInArray({0, 1, 8, 9, 10, 11, 12, 13, 14, 15}, pos.z) then player:sendCancelMessage("Sorry, not possible. you cant fly on floors 0 and 1.") return true end
				if flyOutfit > 1 then outfit.lookType = flyOutfit end
				msg = msg .. ", let me fly on you!"
				storage = storageFly
				if player:getUsingBall():getSpecialAttribute("held") and player:getUsingBall():getSpecialAttribute("held") == 'held wing' then
					summonSpeed = summonSpeed + 500
				end
				local talisman = player:getUsingBall():getSpecialAttribute('talisman') or 0
				if talismanTable[talisman] and talismanTable[talisman].buff == 'fly' then
					summonSpeed = summonSpeed + talismanTable[talisman].amount
				end
				if flyOutfit == 1 then
					if string.find(player:getSummon():getName() , "Mega ") then
						outfit.lookType = MonsterType(creature:getName()):getOutfit().lookType
					else
						outfit.lookType = monsterType:getOutfit().lookType
					end
				else
					if player:getUsingBall():getSpecialAttribute("usingaddon") and player:getUsingBall():getSpecialAttribute("usingaddon") ~= monsterType:getOutfit().lookType then
						if string.find(player:getSummon():getName() , "Mega ") then
							outfit.lookType = addonnumber[addonmega[player:getUsingBall():getSpecialAttribute("usingaddon")]].hab
						else
							outfit.lookType = addonnumber[player:getUsingBall():getSpecialAttribute("usingaddon")].hab
						end
					else
						outfit.lookType = flyOutfit
					end
				end
			else -- none
				player:sendCancelMessage("Sorry, not possible. You can not get ride or fly in your summon.")
				return true
			end

			summon:walk(toPosition, 1, {action = "mount", playerId = player:getId(), outfit = outfit, speed = summonSpeed, storage = storage})
			player:say(msg, TALKTYPE_SAY)
		end
	end
	return true
end
