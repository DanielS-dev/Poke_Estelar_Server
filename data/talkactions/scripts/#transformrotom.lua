function onSay(player, words, param)
	local ball = player:getUsingBall() or 0
	local form = param
	if ball:getSpecialAttribute("pokeName") ~= "Rotom" then player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode mudar a forma de um Rotom.") return false end
	if ball ~= 0 then
		if ball:setSpecialAttribute("form", form) then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce mudou a forma do seu Deoxys, por favor solte ele novamente.")
			return false
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Nao foi possivel mudar a forma do seu Deoxys.")
			return false
		end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Solte o Deoxys para poder mudar a forma dele.")
		return false
	end
	return false
end
	