function onSay(player, words, param)
	
	if player:getStorageValue(846514) == 1 then
		player:setStorageValue(846514, 0)
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce ativou o spawn de lenda na pesca.")
	else
		player:setStorageValue(846514, 1)
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce desativou o spawn de lenda na pesca.")
	end
	return false
end
	