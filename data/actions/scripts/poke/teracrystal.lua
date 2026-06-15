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
			if target:getSpecialAttribute("teraType") and target:getSpecialAttribute("teraType") ~= 0 then
				target:setSpecialAttribute("teraType", math.random(11, 28))
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce mudou o tera type do seu pokemon.")
				item:remove(1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Este pokemon nao possui um Tera Type.")
			end
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o ev reset em uma pokebola.")
		end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o ev reset em uma pokebola.")
	end
	return true
end
