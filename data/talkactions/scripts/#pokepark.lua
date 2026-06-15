function onSay(player, words, param)
	if not param:split("|") then return false end
	local poke = param:split("|")[1]	
	local level = tonumber(param:split("|")[2])
	local price = tonumber(param:split("|")[5])
	local monsterType = MonsterType(poke)
	local baseHealth = monsterType:getMaxHealth()
	local maxHealth = math.floor(20 + (baseHealth * 0.10) + baseHealth)
	local backpack = player:getSlotItem(CONST_SLOT_BACKPACK)
	local addPokeball
	if player:getStorageValue(1905002) >= price then
		player:setStorageValue(1905002, player:getStorageValue(1905002) - price)
		if player:getSlotItem(CONST_SLOT_BACKPACK) and player:getSlotItem(CONST_SLOT_BACKPACK):getEmptySlots() >= 1 and player:getFreeCapacity() >= 1 then
			addPokeball = backpack:addItem(39133, 1)
		else
			addPokeball = player:getInbox():addItem(39133, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
		end
		if addPokeball then
			addPokeball:setSpecialAttribute("pokeName", poke)
			addPokeball:setSpecialAttribute("pokeLevel", level)
			addPokeball:setSpecialAttribute("pokeExperience", 0)
			addPokeball:setSpecialAttribute("pokeBoost", 0)
			addPokeball:setSpecialAttribute("pokeMaxHealth", maxHealth)
			addPokeball:setSpecialAttribute("pokeHealth", maxHealth)
			addPokeball:setSpecialAttribute("pokeLove", 0)
			addPokeball:setSpecialAttribute("evhp", 0)
			addPokeball:setSpecialAttribute("evatk", 0)
			addPokeball:setSpecialAttribute("evdef", 0)
			addPokeball:setSpecialAttribute("evpoints", 0)
			addPokeball:setSpecialAttribute("evkills", 0)
			if tonumber(param:split("|")[3]) ~= 0 then 
				addPokeball:setSpecialAttribute("teraType", math.random(11, 28))
			end
			if tonumber(param:split("|")[4]) ~= 0 then 
				if poke == "Lopunny" then
					addPokeball:setSpecialAttribute("held", "lopunnite")
				elseif poke == "Garchomp" then
					addPokeball:setSpecialAttribute("held", "garchompite")
				end
			end
		else
			print("WARNING! Player " .. player:getName() .. " without Park POKE: "..poke..".")
		end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tem pontos os suficiente.")
	end
	return false
end