function onSay(player, words, param)
	if param == "reset" then
		for i = 1, 10 do
			player:setStorageValue(900001 + (i * 10), 0)
			player:setStorageValue(900001 + 1 + (i * 10), 0)
			player:setStorageValue(900001 + 2 + (i * 10), 0)
		end
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce resetou todos os checkpoints")
		return false
	end
	local slot = tonumber(param)
	if player:getStorageValue(900001 + (slot * 10)) ~= 0 or player:getStorageValue(900001 + (slot * 10)) ~= -1 then
		local x = player:getStorageValue(900001 + (slot * 10))
		local y = player:getStorageValue(900001 + 1 + (slot * 10))
		local z = player:getStorageValue(900001 + 2 + (slot * 10))
		player:teleportTo(Position(x, y, z))
	else
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao tem um checkpoint salvo nesse slot.")
		return false
	end
	return false
end
	