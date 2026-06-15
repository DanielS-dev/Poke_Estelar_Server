function onSay(player, words, param)
	local prizes = {"mewtwo", "rayquaza", "giratina", "empty masterball"}
	if not isInArray(prizes, param:lower()) then
		local txt = ""
		for i = 1, #prizes do
			txt = txt .. firstToUpper(prizes[i]) .. ", "
		end
		print('x')
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Escolha um dos premios a seguir e digite !johto xxxxxx.")
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, txt)
	elseif isInArray(prizes, param:lower()) then
		if param:lower() == "empty masterball" then
			if player:removeItem(26194, 1) then
				player:addItem(param, 1)
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce resgatou um "..param..".")
				return false
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao possui um johto prize shell.")
				return false
			end
		else
			if player:removeItem(26194, 1) then
				local addPokeball = player:getInbox():addItem(26661, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
				addPokeball:setSpecialAttribute("pokeName", firstToUpper(param))
				addPokeball:setSpecialAttribute("pokeLevel", 1)
				addPokeball:setSpecialAttribute("pokeExperience", 0)
				addPokeball:setSpecialAttribute("pokeBoost", 0)
				addPokeball:setSpecialAttribute("pokeMaxHealth", MonsterType(item:getSpecialAttribute("eggname")):getMaxHealth())
				addPokeball:setSpecialAttribute("pokeHealth", MonsterType(item:getSpecialAttribute("eggname")):getMaxHealth())
				addPokeball:setSpecialAttribute("pokeLove", 100)
				addPokeball:setSpecialAttribute("evhp", 0)
				addPokeball:setSpecialAttribute("evatk", 0)
				addPokeball:setSpecialAttribute("evdef", 0)
				addPokeball:setSpecialAttribute("evpoints", 300)
				addPokeball:setSpecialAttribute("evkills", 0)
				if math.random(1, 1000) <= 50 * teraVar and item:getSpecialAttribute("eggname") ~= "Arceus" then
					addPokeball:setSpecialAttribute("teraType", math.random(11, 28))
				end
				addPokeball:setSpecialAttribute("nature", 'Modest')
				if param == "giratina" then
					player:addItem("Griseous Orb", 1)
				end
				player:refreshPokemonBar({}, {})
				player:save()
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce resgatou um "..param..".")
				return false
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao possui um johto prize shell.")
				return false
			end
		end
	end
	return false
end
	