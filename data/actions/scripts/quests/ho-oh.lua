function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if player:getStorageValue(65027) >= 1 then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce ja derrotou o Ho-oh, o que deseja aqui?")
		return true
	end
	if not areaHasPlayer(Position(51, 448, 1), 2, 5) and not areaHasPlayer(Position(51, 448, 0), 2, 5) then
		cleanArea(Position(51, 448, 1), 2, 5)
		cleanArea(Position(51, 448, 0), 2, 5)
		player:teleportTo(Position(51, 453, 0))
		Game.createNpc("Ho-oh", Position(51, 445, 0))
		return true
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Alguem esta tentando a Burning Tower agora, aguarde um pouco.")
		return true
	end
	return true
end
