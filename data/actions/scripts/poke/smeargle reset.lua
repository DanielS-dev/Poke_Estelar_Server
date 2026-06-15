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
			for i = 1, 8 do
				target:setSpecialAttribute("sketch"..i, 0)
			end
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce resetou os moves do seu Smeargle.")
			item:remove(1)
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o smeargle reset em uma pokebola.")
		end
	else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o smeargle reset em uma pokebola.")
	end
	return true
end
