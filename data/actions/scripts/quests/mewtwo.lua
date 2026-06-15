local featherPos = {Position(642, 409, 6), Position(644, 409, 6), Position(646, 409, 6)}
local feathers = {27654, 27655, 27653}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local todelete = {}
	if player:getStorageValue(65026) >= 1 then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce ja derrotou o nosso mestre, o que deseja aqui?")
		return true
	end
	for i = 1, 3 do
		if Tile(featherPos[i]) then
			if Tile(featherPos[i]):getItemById(feathers[i]) then
				table.insert(todelete, Tile(featherPos[i]):getItemById(feathers[i]))
			end
		end
	end
	if #todelete == 3 then
		if not areaHasPlayer(Position(648, 413, 7), 4, 4) and not areaHasPlayer(Position(648, 413, 8), 4, 4) and not areaHasPlayer(Position(648, 395, 8), 1, 1) then
			for i = 1, 3 do
				todelete[i]:remove()
			end
			cleanArea(Position(648, 413, 7), 4, 4)
			cleanArea(Position(648, 413, 8), 4, 4)
			player:teleportTo(Position(646, 413, 7))
			Game.createNpc("Mewtwo", Position(651, 413, 7))
			return true
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Alguem esta enfrentando o mestre agora, aguarde esta pessoa falhar miseravelmente.")
			return true
		end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce precisa provar que eis digno.")
		return true
	end
	return true
end
