-- function Player:onBrowseField(position)
	-- return false
-- end

function Player:onLook(thing, position, distance)
	local description = "You see " .. thing:getDescription(distance)
	if not thing:isItem() and isSummon(thing) then
		local master = thing:getMaster()
		if master:isPlayer() then
			local item = master:getUsingBall()
			local pokeName = item:getSpecialAttribute("pokeName")
			local pokeLevel = item:getSpecialAttribute("pokeLevel")
			local pokeBoost = item:getSpecialAttribute("pokeBoost") or 0
			local evhp = item:getSpecialAttribute("evhp") or 0
			local evatk = item:getSpecialAttribute("evatk") or 0
			local evdef = item:getSpecialAttribute("evdef") or 0
			local evpoints = item:getSpecialAttribute("evpoints") or 0
			local pokeLove = item:getSpecialAttribute("pokeLove") or 0
			local held = item:getSpecialAttribute("held") or 0
			local expshare = item:getSpecialAttribute("expShare") or 0
			local talisman = item:getSpecialAttribute("talisman") or 0
			local letter = item:getSpecialAttribute("unown") or 0
			local teraType = item:getSpecialAttribute("teraType") or 0
			local nature = item:getSpecialAttribute("nature") or 0
			local pokexp = item:getSpecialAttribute("pokeExperience") or 0
			if pokeName ~= nil and pokeLevel ~= nil then	
				description = string.format("%s\nIt belongs to %s. Level: %s. Health: %s. Attack: %s. Special Attack: %s. Defense: %s. Special Defense: %s. Speed: %s.\n Love: %s.", description, master:getName(), pokeLevel, (thing:getTotalHealth() + (evhp * 10)), (thing:getTotalMeleeAttack() + evatk), (thing:getTotalMagicAttack() + evatk), (thing:getTotalDefense() + evdef), (thing:getTotalMagicDefense()+evdef), thing:getTotalSpeed(), pokeLove)
				description = string.format("%s\nHP EV: %s. ATK EV: %s. DEF EV: %s.\nEV Points: %s.", description, evhp, evatk, evdef, evpoints)
				if teraType ~= 0 then
					description = string.format("%s\nTera Type: %s", description, firstToUpper(skullToTera[teraType]))
				end
				if nature ~= 0 then
					description = string.format("%s\nNature: %s", description, nature .." ["..naturedesc[nature].."]")
				end
				if held ~= 0 then
					description = string.format("%s\nHolding: %s.", description, firstToUpper(held))
				end
				if expshare ~= 0 then
					description = string.format("%s\nHolding: Exp Share.", description)
				end
				if talisman ~= 0 then
					description = string.format("%s\nTalisman imprint: %s\n[%s]", description, firstToUpper(talisman),  talismanTable[talisman].desc)
				end
				if letter ~= 0 then
					description = string.format("%s\nLetter: %s.", description, firstToUpper(letter))
				end
				if pokexp ~= 0 then
					description = string.format("%s\nExp: %s for next level.", description, getNeededExp(pokeLevel+1) - pokexp)
				end
			end
		end
	end
	if thing:isItem() and thing:getSpecialAttribute("steps") and thing:getSpecialAttribute("steps") >= 0 then
		description = string.format("%s\nPassos: %s.", description, thing:getSpecialAttribute("steps"))
	end
	if thing:isItem() and thing:getSpecialAttribute("unown") then
		description = string.format("%s\nLetter: %s.", description, thing:getSpecialAttribute("unown"))
	end
	if thing:isItem() and thing:getSpecialAttribute("talisman") and not thing:isPokeball() then
		description = string.format("%s\nImprint: %s\n[%s].", description, firstToUpper(thing:getSpecialAttribute("talisman")), talismanTable[thing:getSpecialAttribute("talisman")].desc)
	end
	if thing:isItem() and thing:getSpecialAttribute("addon") then
		description = string.format("%s\nAddon: %s.", description, addonnumber[tonumber(thing:getSpecialAttribute("addon"))].name)
	end
	if thing:isItem() and thing:getSpecialAttribute("addon") then
		description = string.format("%s\nAddon: %s.", description, addonnumber[tonumber(thing:getSpecialAttribute("addon"))].name)
	end
	if thing:isItem() and thing:isPokeball() then
		local pokeName = thing:getSpecialAttribute("pokeName")
		local pokeLevel = thing:getSpecialAttribute("pokeLevel")
		local evhp = thing:getSpecialAttribute("evhp") or 0
		local evatk = thing:getSpecialAttribute("evatk") or 0
		local evdef = thing:getSpecialAttribute("evdef") or 0
		local evpoints = thing:getSpecialAttribute("evpoints") or 0
		local pokeBoost = thing:getSpecialAttribute("pokeBoost") or 0
		local pokeLove = thing:getSpecialAttribute("pokeLove") or 0
		local ownerName = thing:getSpecialAttribute("owner")
		local pokeHealth = tonumber(thing:getSpecialAttribute("pokeHealth")) or 0
		local held = thing:getSpecialAttribute("held") or 0
		local expshare = thing:getSpecialAttribute("expShare") or 0
		local talisman = thing:getSpecialAttribute("talisman") or 0
		local letter = thing:getSpecialAttribute("letter") or 0
		local teraType = thing:getSpecialAttribute("teraType") or 0
		local nature = thing:getSpecialAttribute("nature") or 0
		local pokexp = thing:getSpecialAttribute("pokeExperience") or 0
		local healthStr = ""
		if ownerName then
			healthStr = "It belongs to " .. ownerName .. "."
		end
		if pokeHealth <= 0 then
			healthStr = "It is fainted."
		end
		if pokeName ~= nil and pokeLevel ~= nil and healthStr ~= nil then			
			description = string.format("%s\nIt contains a %s. Level: %s. %s", description, pokeName, pokeLevel, healthStr)
			description = string.format("%s\nHP EV: %s. ATK EV: %s. DEF EV: %s.\nEV Points: %s.", description, evhp, evatk, evdef, evpoints)
		end
		if teraType ~= 0 then
			description = string.format("%s\n Tera Type: %s", description, firstToUpper(skullToTera[teraType]))
		end
		if nature ~= 0 then
			description = string.format("%s\n Nature: %s", description, nature .." ["..naturedesc[nature].."]")
		end
		if held ~= 0 then
			description = string.format("%s\n Holding: %s.", description, firstToUpper(held))
		end
		if expshare ~= 0 then
			description = string.format("%s\n Holding: Exp Share.", description)
		end
		if talisman ~= 0 then
			description = string.format("%s\n Talisman imprint: %s\n[%s]", description, firstToUpper(talisman),  talismanTable[talisman].desc)
		end
		if letter ~= 0 then
			description = string.format("%s\n Letter: %s.", description, firstToUpper(letter))
		end
		if pokexp ~= 0 then
			description = string.format("%s\nExp: %s for next level.", description, getNeededExp(pokeLevel+1) - pokexp)
		end
	end
	if thing:isPlayer() and thing ~= self then
		if thing:getAccountType() == ACCOUNT_TYPE_TUTOR then
			if thing:getSex() == PLAYERSEX_MALE then
				description = string.format("%s He is a Tutor.", description)
			else
				description = string.format("%s She is a Tutor.", description)
			end
		end
	end
	if thing:isPlayer() and thing == self then
		if thing:getAccountType() == ACCOUNT_TYPE_TUTOR then
			description = string.format("%s You are a Tutor.", description)
		end
	end
	if self:getGroup():getAccess() then
		if thing:isItem() then
			description = string.format("%s\nItem ID: %d", description, thing:getId())

			local actionId = thing:getActionId()
			if actionId ~= 0 then
				description = string.format("%s, Action ID: %d", description, actionId)
			end

			local uniqueId = thing:getAttribute(ITEM_ATTRIBUTE_UNIQUEID)
			if uniqueId > 0 and uniqueId < 65536 then
				description = string.format("%s, Unique ID: %d", description, uniqueId)
			end

			local itemType = thing:getType()
			local transformEquipId = itemType:getTransformEquipId()
			local transformDeEquipId = itemType:getTransformDeEquipId()
			if transformEquipId ~= 0 then
				description = string.format("%s\nTransforms to: %d (onEquip)", description, transformEquipId)
			elseif transformDeEquipId ~= 0 then
				description = string.format("%s\nTransforms to: %d (onDeEquip)", description, transformDeEquipId)
			end

			local decayId = itemType:getDecayId()
			if decayId ~= -1 then
				description = string.format("%s\nDecays to: %d", description, decayId)
			end
		elseif thing:isCreature() then
			local str = "%s\nHealth: %d / %d"
			if thing:getMaxMana() > 0 then
				str = string.format("%s, Mana: %d / %d", str, thing:getMana(), thing:getMaxMana())
			end
			description = string.format(str, description, thing:getHealth(), thing:getMaxHealth()) .. "."
		end

		if thing:isCreature() then
			if thing:isPlayer() then
				description = string.format("%s\nIP: %s.", description, Game.convertIpToString(thing:getIp()))
			end
		end
	end
	if self:getAccountType() >= ACCOUNT_TYPE_TUTOR then
		local position = thing:getPosition()
		description = string.format(
			"%s\nPosition: %d, %d, %d",
			description, position.x, position.y, position.z
		)
	end
	self:sendTextMessage(MESSAGE_INFO_DESCR, description)
end

function Player:onLookInBattleList(creature, distance)
	local description = "You see " .. creature:getDescription(distance)
	if isSummon(creature) then
		local master = creature:getMaster()
--		local item = master:getSlotItem(CONST_SLOT_AMMO)
--		local pokeName = item:getSpecialAttribute("pokeName")
--		local pokeLevel = item:getSpecialAttribute("pokeLevel")
		local pokeName = master:getName()
		local pokeLevel = creature:getLevel()
		if pokeName ~= nil and pokeLevel ~= nil then			
			description = string.format("%s\nIt belongs to %s. Level: %s.", description, master:getName(), pokeLevel)
		end
	end
	if self:getGroup():getAccess() then
		local str = "%s\nHealth: %d / %d"
		if creature:getMaxMana() > 0 then
			str = string.format("%s, Mana: %d / %d", str, creature:getMana(), creature:getMaxMana())
		end
		description = string.format(str, description, creature:getHealth(), creature:getMaxHealth()) .. "."

		local position = creature:getPosition()
		description = string.format(
			"%s\nPosition: %d, %d, %d",
			description, position.x, position.y, position.z
		)

		if creature:isPlayer() then
			description = string.format("%s\nIP: %s", description, Game.convertIpToString(creature:getIp()))
		end
	end
	self:sendTextMessage(MESSAGE_INFO_DESCR, description)
end

function Player:onLookInTrade(partner, item, distance)
	local description = "You see " .. item:getDescription(distance)
	if item:isPokeball() then
		local pokeName = item:getSpecialAttribute("pokeName")
		local pokeLevel = item:getSpecialAttribute("pokeLevel")
		local pokeBoost = item:getSpecialAttribute("pokeBoost") or 0
		local pokeLove = item:getSpecialAttribute("pokeLove") or 0
		local evhp = item:getSpecialAttribute("evhp") or 0
		local evatk = item:getSpecialAttribute("evatk") or 0
		local evdef = item:getSpecialAttribute("evdef") or 0
		local evpoints = item:getSpecialAttribute("evpoints") or 0
		local pokeHealth = tonumber(item:getSpecialAttribute("pokeHealth"))
		local healthStr = ""
		local held = item:getSpecialAttribute("held") or 0
		local expshare = item:getSpecialAttribute("expShare") or 0
		local letter = item:getSpecialAttribute("letter") or 0
		local teraType = item:getSpecialAttribute("teraType") or 0
		local nature = item:getSpecialAttribute("nature") or 0
		local talisman = item:getSpecialAttribute("talisman") or 0
		
		if pokeHealth <= 0 then
			healthStr = "It is fainted."
		end
		if pokeName ~= nil and pokeLevel ~= nil and healthStr ~= nil then			
			description = string.format("%s\nIt contains a %s. Level: %s. Boost: +%s. Love: +%s. %s", description, pokeName, pokeLevel, pokeBoost, pokeLove, healthStr)
			description = string.format("%s\nHP EV: %s. ATK EV: %s. DEF EV: %s.\nEV Points: %s.", description, evhp, evatk, evdef, evpoints)
		end
		if held ~= 0 then
			description = string.format("%s\n Holding: %s.", description, firstToUpper(held))
		end
		if expshare ~= 0 then
			description = string.format("%s\n Holding: Exp Share.", description)
		end
		if letter ~= 0 then
			description = string.format("%s\n Letter: %s.", description, firstToUpper(letter))
		end
		if teraType ~= 0 then
			description = string.format("%s\n Tera Type: %s", description, firstToUpper(skullToTera[teraType]))
		end
		if nature ~= 0 then
			description = string.format("%s\n Nature: %s", description, nature .." ["..naturedesc[nature].."]")
		end
		if talisman ~= 0 then
			description = string.format("%s\n Talisman imprint: %s\n[%s]", description, firstToUpper(talisman),  talismanTable[talisman].desc)
		end
		if item:getId() == 39319 and not talisman ~= 0 then
			description = string.format("%sTALISMAN BUGADO NAO COMPRE.", description)
		end
	end
	self:sendTextMessage(MESSAGE_INFO_DESCR, description)
end

function Player:onLookInShop(itemType, count)
	return true
end

function Player:onMoveItem(item, count, fromPosition, toPosition, fromCylinder, toCylinder)
	if item:getId() == 2270 or item:getId() == 2263 or item:getId() == 8922 then self:sendCancelMessage("Sorry, not possible.") return false end
	if isInArray({27634, 39232, 39233, 39234, 39235, 39236, 39237, 39318, 39306, 39334}, item:getId()) and toPosition.x ~= 65535 and self:getStorageValue(storageBike) > 0 then self:sendCancelMessage("Sorry, not possible.") return false end
	if item:isContainer() then
		print(">>> WARNING! Player " .. self:getName() .. " moving backpack!")
	elseif item:getId() == 36318 then
		print(">>> WARNING! Player " .. self:getName() .. " movendo vale token!")
	end
	if fromPosition.x == 65535 and toPosition.x ~= 65535 then self:save() end
	if self:getCondition(CONDITION_SAFFARI) ~= nil then
		if item:getId() == 26685 and toPosition.x ~= 65535 then return false end
	end
	if item:getSpecialAttribute('unique')  and toPosition.x ~= 65535 then self:sendCancelMessage("You cant throw away an unique item.") return false end
	if fromPosition.x == 65535 and fromPosition.y == 10 or (toPosition.x == 65535 and toPosition.y == 10) and item:isPokeball() then 
		if self:getStorageValue(storageFly) == 1 then
			self:sendCancelMessage("Sorry, not possible while on fly.")
			return false
		end
		if self:getStorageValue(storageSurf) > 0 then
			self:sendCancelMessage("Sorry, not possible while on surf.")
			return false
		end
		if self:getStorageValue(storageRide) > 0 then
			self:sendCancelMessage("Sorry, not possible while on ride.")
			return false
		end
		local summon = self:getSummon()
		if summon and summon:isEvolving() then
			self:sendCancelMessage("Sorry, not possible. Your summon is evolving.")
			return false
		end
	end
	if fromPosition.x == 65535 and fromPosition.y == 10 and item:isPokeball() then
		local pokeName = item:getSpecialAttribute("pokeName")
		local monsterType = MonsterType(pokeName)
		local portraitId = monsterType:portraitId()
		if portraitId == 0 then return true end
		local putPortrait = self:removeItem(portraitId)
		if not putPortrait then
			print("WARNING! Problem on remove portrait player events " .. pokeName .. " player " .. self:getName())
		end	
	end

	if self:isDuelingWithNpc() and item:isPokeball() and toPosition.x == 65535 and fromPosition.x ~= 65535 then
		self:sendCancelMessage("Sorry, not possible while in duel.")
		return false
	end

--	if toPosition.x ~= 65535 or (toPosition.x == 65535 and toPosition.y ~= 64 and toPosition.y ~= 3 and toPosition.y ~= 10) then
		if item:isPokeball() then
			local isBallBeingUsed = item:getSpecialAttribute("isBeingUsed")
			if isBallBeingUsed and isBallBeingUsed == 1 then
				self:sendCancelMessage("Sorry, not possible while using Pokemon.")
				return false
			end
		elseif item:isContainer() then
			local balls = item:getPokeballs()
			for i = 1, #balls do
				local isBallBeingUsed = balls[i]:getSpecialAttribute("isBeingUsed")
				if isBallBeingUsed and isBallBeingUsed == 1 then
					self:sendCancelMessage("Sorry, not possible while using Pokemon.")
					return false
				end
			end
		end
--	end

	return true
end

function Player:onItemMoved(item, count, fromPosition, toPosition, fromCylinder, toCylinder)
	if item:isPokeball() or item:isContainer() then
		self:refreshPokemonBar({}, {})
	end
end

function Player:onMoveCreature(creature, fromPosition, toPosition)
	return true
end

function Player:onTurn(direction)
	if hasSummons(self) then
		local summon = self:getSummons()[1]
		local summonDirection = summon:getDirection()
		if summonDirection == direction then return true end
--		local msg = summon:getName() .. "! Turn to "
--		if direction == 0 then msg = msg .. "north." end
--		if direction == 1 then msg = msg .. "east." end
--		if direction == 2 then msg = msg .. "south." end
--		if direction == 3 then msg = msg .. "west." end
		summon:setDirection(direction)
		summon:setIdle(6000)
--		self:say(msg, TALKTYPE_SAY)
	end
	return true
end

function Player:onTradeRequest(target, item)
	if self:isDuelingWithNpc() and item:isPokeball() then
		self:sendCancelMessage("Sorry, not possible while in duel.")
		return false
	end
	if item:isPokeball() then
		if item:isBeingUsed() then
			self:sendCancelMessage("Sorry, not possible while using pokeball.")
			return false
		end
	end
	if item:isContainer() then
		local pokeballs = item:getPokeballs()
		for i = 1, #pokeballs do
			if pokeballs[i]:isBeingUsed() then
				self:sendCancelMessage("Sorry, not possible while using pokeball.")
				return false
			end
		end
	end
	return true
end

function Player:onTradeAccept(target, item, targetItem)
	self:save()
	target:save()
	print(">>> Player "..self:getName().." trading with "..target:getName()..".")
	return true
end

local soulCondition = Condition(CONDITION_SOUL, CONDITIONID_DEFAULT)
soulCondition:setTicks(4 * 60 * 1000)
soulCondition:setParameter(CONDITION_PARAM_SOULGAIN, 1)

local function useStamina(player)
	local staminaMinutes = player:getStamina()
	if staminaMinutes == 0 then
		return
	end

	local playerId = player:getId()
	local currentTime = os.time()
	if nextUseStaminaTime[playerId] == nil then
		return
	end
	local timePassed = currentTime - nextUseStaminaTime[playerId]
	if timePassed <= 0 then
		return
	end

	if timePassed > 60 then
		if staminaMinutes > 2 then
			staminaMinutes = staminaMinutes - 2
		else
			staminaMinutes = 0
		end
		nextUseStaminaTime[playerId] = currentTime + 120
	else
		staminaMinutes = staminaMinutes - 1
		nextUseStaminaTime[playerId] = currentTime + 60
	end
	player:setStamina(2520)
end

function Player:onGainExperience(source, exp, rawExp)
	local multiplier = 1 -- how many times more exp than players a monster will get
	if not source then
		return exp
	end
	if self:getItemCount(39321) >= 1 then
		exp = exp * 2
	end
	if source:getCondition(CONDITION_FISHING) ~= nil then
		exp = exp * 0.25
	end
	
	if self:getUsingBall() and self:getUsingBall():getSpecialAttribute("held") and self:getUsingBall():getSpecialAttribute("held") == 'held experience' then
		exp = exp * 1.25
	end
	local talisman = 0
	if self:getUsingBall() and self:getUsingBall():getSpecialAttribute("talisman") then
		talisman = self:getUsingBall():getSpecialAttribute('talisman') or 0
		if talismanTable[talisman] and talismanTable[talisman].buff == 'exp' then
			exp = exp * talismanTable[talisman].amount
		end
	end
	
	local baseexp = exp * expVar * 5
	exp = exp * expVar * 5
	-- Soul regeneration
	local vocation = self:getVocation()
	if self:getSoul() < vocation:getMaxSoul() and exp >= self:getLevel() then
		soulCondition:setParameter(CONDITION_PARAM_SOULTICKS, vocation:getSoulGainTicks() * 1000)
		self:addCondition(soulCondition)
	end
	
	if self:isPremium() then
		exp = exp * 1.25
	end
	
	-- Update questlog
	if exp + self:getExperience() >= getNeededExp(self:getLevel() + 1) then
		self:updateQuestLog()
	end

	-- Vocation buff
	if vocation:getName() == "Explorer" then
		exp = exp * explorerExperienceBuff
	end

	if hasSummons(self) then
		local balls = self:getPokeballs()
		for i = 1, #balls do
			local item = balls[i]
			if item and item:isPokeball() then
				if self:getUsingBall() ~= item then
					if item:getSpecialAttribute("expShare") and item:getSpecialAttribute("expShare") == 1 then
						local level = item:getSpecialAttribute("pokeLevel") or 1
						if level >= summonMaxLevel then
							return baseexp
						end
						if level > 90 then
							exp = exp * 0.1 / 2
						elseif level > 80 and level <= 90 then
							exp = exp * 0.20 / 2
						elseif level > 70 and level <= 80 then
							exp = exp * 0.25 / 2
						elseif level > 60 and level <= 70 then
							exp = exp * 0.50 / 2
						elseif level > 50 and level <= 60 then
							exp = exp * 0.75 / 2
						elseif level > 40 and level <= 50 then
							exp = exp * 1.0 / 2
						elseif level > 30 and level <= 40 then
							exp = exp * 1.25 / 2
						elseif level > 20 and level <= 30 then
							exp = exp * 1.50 / 2
						elseif level > 10 and level <= 20 then
							exp = exp * 1.75 / 2
						elseif level > 0 and level <= 10 then
							exp = exp * 2 / 2
						end
						local givenExp = (exp * multiplier) / 2
						if vocation:getName() == "Explorer" then
							givenExp = math.floor(givenExp / explorerExperienceBuff)
						end
						
						local pokeExp = item:getSpecialAttribute("pokeExperience") or 0
						local nextLevel = level + 1
						local newExp = pokeExp + givenExp
						item:setSpecialAttribute("pokeExperience", newExp)
						if newExp > getNeededExp(nextLevel)  then				
							item:setSpecialAttribute("pokeLevel", nextLevel)
							local love = item:getSpecialAttribute("pokeLove") or 0
							local talismanlove = 1
							if talismanTable[talisman] and talismanTable[talisman].buff == 'love' then
								talismanlove = 2
							end
							if MonsterType(source:getName()):isLegendary() then 
								love = love + (3 * talismanlove)
							elseif level < source:getLevel() then
								love = love + (2 * talismanlove)				
							else
								love = love + (1 * talismanlove)
							end
							item:setSpecialAttribute("pokeLove", love)
							self:save()
						end
					end
				end
			end
		end
		-- end
		local creature = self:getSummon()
		--local item = self:getSlotItem(CONST_SLOT_AMMO)
		local item = self:getUsingBall()
		if item and item:isPokeball() then
			local kills = item:getSpecialAttribute("evkills") or 0
			local points = item:getSpecialAttribute("evpoints") or 0
			local evhp = item:getSpecialAttribute("evhp") or 0
			local evatk = item:getSpecialAttribute("evatk") or 0
			local evdef = item:getSpecialAttribute("evdef") or 0
			if kills >= 0 and points + evhp + evatk + evdef < 300 then
				kills = kills + 1
				item:setSpecialAttribute("evkills", kills) 
				if kills >= 10 then
					if talismanTable[talisman] and talismanTable[talisman].buff == 'ev' then
						item:setSpecialAttribute("evpoints", points + 2) 
						item:setSpecialAttribute("evkills", 0) 
						creature:getPosition():sendMagicEffect(30)
					else
						item:setSpecialAttribute("evpoints", points + 1) 
						item:setSpecialAttribute("evkills", 0) 
						creature:getPosition():sendMagicEffect(30)
					end
				end
			end
			local level = item:getSpecialAttribute("pokeLevel") or 1
			if level >= summonMaxLevel then
				return baseexp
			end
			if level > 90 then
				exp = exp * 0.1
			elseif level > 80 and level <= 90 then
				exp = exp * 0.20
			elseif level > 70 and level <= 80 then
				exp = exp * 0.25
			elseif level > 60 and level <= 70 then
				exp = exp * 0.50
			elseif level > 50 and level <= 60 then
				exp = exp * 0.75
			elseif level > 40 and level <= 50 then
				exp = exp * 1.0
			elseif level > 30 and level <= 40 then
				exp = exp * 1.25
			elseif level > 20 and level <= 30 then
				exp = exp * 1.50
			elseif level > 10 and level <= 20 then
				exp = exp * 1.75
			elseif level > 0 and level <= 10 then
				exp = exp * 2
			end
			local givenExp = exp * multiplier
			if vocation:getName() == "Explorer" then
				givenExp = math.floor(givenExp / explorerExperienceBuff)
			end
			local summonPos = creature:getPosition()
			local pokeExp = item:getSpecialAttribute("pokeExperience") or 0
			local nextLevel = level + 1
			local newExp = pokeExp + givenExp
			item:setSpecialAttribute("pokeExperience", newExp)
			if givenExp > 0 then 
				summonPos:sendAnimatedNumber(MESSAGE_EXPERIENCE_OTHERS, "Your " .. creature:getName() .. " gained " .. givenExp .. " experience points.", givenExp, TEXTCOLOR_WHITE_EXP)
			end
			
			-- adicionar lucky egg aqui
			
			if newExp > getNeededExp(nextLevel)  then				
				item:setSpecialAttribute("pokeLevel", nextLevel)
				local love = item:getSpecialAttribute("pokeLove") or 0
				local newMaxHealth = creature:getTotalHealth()
				creature:setMaxHealth(newMaxHealth)
				creature:changeSpeed(-creature:getSpeed() + creature:getTotalSpeed())			
				creature:setHealth(newMaxHealth)
				summonPos:sendMagicEffect(CONST_ME_HEARTS)
				local talismanlove = 1
				if talismanTable[talisman] and talismanTable[talisman].buff == 'love' then
					talismanlove = 2
				end
				if MonsterType(source:getName()):isLegendary() then 
					love = love + (3 * talismanlove)
				elseif level < source:getLevel() then
					love = love + (2 * talismanlove)
				else
					love = love + (1 * talismanlove)
				end
				self:save()
				item:setSpecialAttribute("pokeLove", love)
				doRemoveSummon(self:getId(), false, nil, false)
				item:setSpecialAttribute("isBeingUsed", 1)
				local cid = doReleaseSummon(self:getId(), summonPos, false, false)
				if not cid then
					print("WARNING! Creature " .. creature:getName() .. ", level " .. nextLevel .. " from player " .. self:getName() .. " with problems on change level.")
				end
			end
		end
	end
	self:save()
	return baseexp
end

function Player:onLoseExperience(exp)
	exp = exp / 2
	if self:isPremium() then
		exp = exp * 0.70
	end
	if self:hasBlessing(7) then
		exp = 0
	end
	return exp
end

function Player:onGainSkillTries(skill, tries)
	if APPLY_SKILL_MULTIPLIER == false then
		return tries
	end

	if skill == SKILL_MAGLEVEL then
		return tries * configManager.getNumber(configKeys.RATE_MAGIC)
	end
	return tries * configManager.getNumber(configKeys.RATE_SKILL)
end
