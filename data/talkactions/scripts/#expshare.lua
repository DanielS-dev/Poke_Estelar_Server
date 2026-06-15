function onSay(player, words, param)
	local ball = player:getUsingBall() or 0
	if ball ~= 0 then
		if ball:getSpecialAttribute("expShare") == 1 then
			ball:setSpecialAttribute("expShare", 0)
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce removeu o exp share do seu pokemon, o item foi adicionado no seu inventario.")
			player:addItem(38895, 1)
			return false
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu pokemon nao possui exp share.")
			return false
		end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Solte o pokemon com o exp share para poder remover.")
		return false
	end
	return false
end
	