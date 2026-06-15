function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if hasSummons(player) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon precisa estar para dentro para evoluir.")
		return false
	end
	
	if not target:isPokeball() then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce so pode usar isso em uma pokebola.")
		return false
	end
	
	if not isInArray(player:getPokeballs(), target) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce so pode usar isso em uma pokebola que seja sua.")
		return false
	end
	
	if target:isPokeball() then
		if target:getSpecialAttribute("pokeLevel") == 100 then
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Este pokemon ja esta no nivel maximo.")
			return false
		end
		if item:remove(1) then
			item:setSpecialAttribute("pokeExperience", getNeededExp(target:getSpecialAttribute("pokeLevel") + 1))
			target:setSpecialAttribute("pokeLevel", target:getSpecialAttribute("pokeLevel") + 1)
		end
	end
	return true
end
