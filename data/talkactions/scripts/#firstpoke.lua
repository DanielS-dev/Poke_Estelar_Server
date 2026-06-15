function onSay(player, words, param)
	local firstItems = {8922, 1988}
	local minInitialCapacity = 40000
	local pokemonName = param and param:match("^%s*(.-)%s*$") or ""
	
	if player:getStorageValue(63001) == 1 then
		player:sendCancelMessage("Voce ja recebeu seu Pokemon inicial.")
		return false
	end

	if pokemonName == "" then
		player:sendCancelMessage("Escolha um Pokemon inicial valido.")
		return false
	end

	local monsterType = MonsterType(pokemonName)
	if not monsterType then
		player:sendCancelMessage("Pokemon inicial invalido: " .. pokemonName)
		print("WARNING! Invalid initial pokemon '" .. pokemonName .. "' for player " .. player:getName() .. ".")
		return false
	end

	player:setCapacity(minInitialCapacity)

	for i = 1, #firstItems do
		if not player:getItemById(firstItems[i]) then
			player:addItem(firstItems[i], 1)
		end
	end
	player:addSlotItems()

	local backpack = player:getSlotItem(CONST_SLOT_BACKPACK)
	if not backpack then
		backpack = player:addItem(1988, 1, false, CONST_SLOT_BACKPACK)
	end

	if not backpack then
		player:sendCancelMessage("Nao foi possivel criar sua backpack inicial.")
		print("WARNING! Player " .. player:getName() .. " without initial backpack.")
		return false
	end

	local baseHealth = monsterType:getMaxHealth()
	local maxHealth = math.floor(20 + (baseHealth * 0.10) + baseHealth)
	local addPokeball
	local sentToInbox = false

	if backpack:getEmptySlots() >= 1 and player:getFreeCapacity() >= 1 then
		addPokeball = backpack:addItem(26661, 1)
	end

	if not addPokeball then
		addPokeball = player:getInbox():addItem(26661, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
		sentToInbox = addPokeball ~= nil
	end

	if not addPokeball then
		player:sendCancelMessage("Nao foi possivel criar sua pokeball inicial.")
		print("WARNING! Player " .. player:getName() .. " without initial pokeball in backpack and inbox.")
		return false
	end

	addPokeball:setSpecialAttribute("pokeName", pokemonName)
	addPokeball:setSpecialAttribute("pokeLevel", 5)
	addPokeball:setSpecialAttribute("pokeExperience", 0)
	addPokeball:setSpecialAttribute("pokeBoost", 0)
	addPokeball:setSpecialAttribute("pokeMaxHealth", maxHealth)
	addPokeball:setSpecialAttribute("pokeHealth", maxHealth)
	addPokeball:setSpecialAttribute("pokeLove", 0)
	addPokeball:setSpecialAttribute("evhp", 0)
	addPokeball:setSpecialAttribute("evatk", 0)
	addPokeball:setSpecialAttribute("evdef", 0)
	addPokeball:setSpecialAttribute("evpoints", 300)
	addPokeball:setSpecialAttribute("evkills", 0)
	addPokeball:setSpecialAttribute("unique", 1)
	player:refreshPokemonBar({}, {})
	if sentToInbox then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Sua pokeball inicial foi enviada para o CP.")
	end
	player:addItem(27642, 100)
	player:addItem(26662, 100)
	player:addItem(27645, 10)
	player:setStorageValue(63001, 1)
	player:teleportTo(Position(42, 129, 15))
	return false
end
