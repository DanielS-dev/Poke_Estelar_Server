function onSay(player, words, param)
	if not player:getSummon() then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce precisa ter um pokemon pra fora.")
		return false
	end
	for i = 1, 12 do
		if player:getUsingBall() and player:getUsingBall():getSpecialAttribute("plate"..i) then
			player:getUsingBall():setSpecialAttribute("plate"..i, 0)
		end
	end
	return false
end
	