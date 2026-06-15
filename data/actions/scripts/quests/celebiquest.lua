function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if player:hasKilledLegendaryPokemon() then
		player:giveQuestPrize(item.uid)
	else
		self:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce precisa contribuir com o abate do pokemon para abrir o bau.")
	end
	return true
end
