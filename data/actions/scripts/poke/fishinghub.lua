function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if player:isDuelingWithNpc() then
		player:unsetDuelWithNpc()
	end
	if player:getCondition(CONDITION_SAFFARI) ~= nil then
		player:removeCondition(CONDITION_SAFFARI)
		if player:getItemCount(26685) >= 1 then
			player:removeItem(26685, player:getItemCount(26685))
		end
	end
	if player:getCondition(CONDITION_PARK) ~= nil then
		player:removeCondition(CONDITION_PARK)
		if player:getItemCount(39132) >= 1 then
			player:removeItem(39132, player:getItemCount(39132))
		end
	end
	player:teleportTo(Position(774, 828, 14))
	return true
end