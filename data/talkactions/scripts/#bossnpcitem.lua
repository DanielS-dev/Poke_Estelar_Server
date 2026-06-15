function onSay(player, words, param)
	local item = param:split('|')[1] or 0
	local qt = 100
	if not item or not qt then return false end
	local currency = 34765
	if item:lower() == "gholdengo" then currency = 2160 qt = 9999 end
	if player:removeItem(currency, qt) then
		local egg = player:getInbox():addItem(36570, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
		egg:setSpecialAttribute("eggname", item)
		egg:setSpecialAttribute("steps", 0)
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Um pokemon egg foi enviado para sua catch box.")
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tem os itens necessarios.")
		return false
	end
	return false
end
	