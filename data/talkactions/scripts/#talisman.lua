function onSay(player, words, param)
	if player:getUsingBall() and player:getUsingBall():getSpecialAttribute('talisman') and player:getUsingBall():getSpecialAttribute('talisman') ~= 0 then
		local imprint = player:getUsingBall():getSpecialAttribute('talisman')
		if player:getUsingBall():setSpecialAttribute("talisman", 0) then
			local item = player:addItem(39319, 1)
			item:setSpecialAttribute("talisman", imprint)
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce removeu o talisman de seu pokemon.")
		end
	end
	return false
end