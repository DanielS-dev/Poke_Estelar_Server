function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if hasSummons(player) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon precisa estar para dentro para aplicar um talisman.")
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
	
	if not item:getSpecialAttribute('talisman') then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu talisman nao possui um imprint.")
		return false
	end

	if target:isPokeball() then
		if talismanTable[item:getSpecialAttribute('talisman')] then
			if target:getSpecialAttribute("talisman") and target:getSpecialAttribute("talisman") ~= 0 then
				player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon ja possui um talisman, por favor, remova o talisman em um celular.")
				return false
			end
			if target:setSpecialAttribute("talisman", item:getSpecialAttribute('talisman')) then
				item:remove()
			end
		else
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Talisman nao habilitado no momento.")
			return false
		end
	end
	return true
end
