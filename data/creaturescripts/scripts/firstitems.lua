function onLogin(player)
	if player:getLastLoginSaved() == 0 or player:getStorageValue(63001) ~= 1 then
		player:teleportTo(Position(45, 56, 15))
	end
	return true
end