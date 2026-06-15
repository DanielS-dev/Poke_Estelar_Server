function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	player:addItem(39315, 5)
	player:addItem(39316, 1)
	player:addItem(39317, 1)
	if player:getSex() == PLAYERSEX_MALE then
		player:addOutfit(4019)
	else
		player:addOutfit(4018)
	end
	player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Obrigado por ajudar o servidor, voce recebeu: 5 Tapetes, 1 Ursinho, 1 Bag e 1 Outfit.")
	player:getPosition():sendMagicEffect(CONST_ME_MAGIC_GREEN)
	item:remove(1)
	return true
end