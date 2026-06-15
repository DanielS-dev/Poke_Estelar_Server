function onSay(player, words, param)
	local senha = tonumber(param) or 0
	if senha == player:getStorageValue(564561) then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Senha correta, nos vemos em breve.")
		if player:getCondition(CONDITION_MANASHIELD) ~= nil then player:removeCondition(CONDITION_MANASHIELD) end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Senha incorreta, a senha e: !antibot "..player:getStorageValue(564561).."")
	end
	return false
end
	