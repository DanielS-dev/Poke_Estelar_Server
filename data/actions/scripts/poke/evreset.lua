function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if hasSummons(player) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon precisa estar dentro da pokebola.")
		return false
	end
	
	if not target:isPokeball() then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce so pode usar isso em uma pokebola.")
		return false
	end

	if not target:isCreature() then
		if target:isPokeball() then
			local evhp = target:getSpecialAttribute("evhp") or 0
			local evatk = target:getSpecialAttribute("evatk") or 0
			local evdef = target:getSpecialAttribute("evdef") or 0
			local evpoints = target:getSpecialAttribute("evpoints") or 0
			target:setSpecialAttribute("evhp", 0)
			target:setSpecialAttribute("evatk", 0)
			target:setSpecialAttribute("evdef", 0)
			target:setSpecialAttribute("evpoints", evhp + evatk + evdef + evpoints)
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce resetou os evs do seu pokemon.")
			item:remove(1)
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o ev reset em uma pokebola.")
		end
	else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o ev reset em uma pokebola.")
	end
	return true
end
