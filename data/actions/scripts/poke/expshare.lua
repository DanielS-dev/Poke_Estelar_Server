function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if not target:isCreature() then
		if target:isPokeball() then
			if target:getSpecialAttribute("expShare") ~= 1 then
				if item:remove(1) then
					target:setSpecialAttribute("expShare", 1)
					player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu ".. target:getSpecialAttribute("pokeName") .." agora esta segurando um exp share. Para remover um exp share utilize um celular.")
					return true
				else
					player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu jogo bugou, entre em contato com um admistrador.")
				end
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu pokemon ja tem exp share. Para remover um exp share utilize um celular.")
			end
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o exp share em uma pokebola.")
		end
	else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o exp share em uma pokebola.")
	end
	return true
end