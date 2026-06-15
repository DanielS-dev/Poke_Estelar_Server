function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if item:remove(100) then
		local tokens = math.random(250, 500)
		player:addTokens(tokens)
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce recebeu ".. tokens .." tokens. Troque com o NPC Token Collector no TC.")
 	elseif item:remove(1) then
		local tokens = math.random(1, 5)
		player:addTokens(tokens)
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce recebeu ".. tokens .." tokens. Troque com o NPC Token Collector no TC.")
	end
	return true
end