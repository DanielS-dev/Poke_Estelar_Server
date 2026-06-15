function onSay(player, words, param)
	
	player:setStamina(2400)
	player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce tem: "..math.floor(player:getStamina()/60)..":"..math.fmod(player:getStamina(), 60).." de stamina.")
	return false
end
