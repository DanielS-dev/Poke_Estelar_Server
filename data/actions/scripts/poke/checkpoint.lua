function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if isInRange(toPosition, Position(2411, 0, 0), Position(2733, 351, 7)) then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao pode salvar esta posicao.")
		return false
	elseif isInRange(toPosition, Position(799, 1510, 11), Position(1334, 1736, 15)) then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao pode salvar esta posicao.")
		return false
	elseif isInRange(toPosition, Position(281, 868, 0), Position(284, 872, 5)) then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao pode salvar esta posicao.")
		return false
	elseif toPosition.z == 14 or toPosition.z == 15 then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao pode salvar esta posicao.")
		return false
	elseif toPosition.z ~= player:getPosition().z then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao pode salvar esta posicao.")
		return false
	elseif Tile(toPosition):getHouse() then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao pode salvar uma casa.")
		return false
	end
	if Tile(toPosition) and not Tile(toPosition):hasFlag(TILESTATE_BLOCKPATH) and not Tile(toPosition):hasFlag(TILESTATE_BLOCKSOLID) then
		for i = 1, 10 do
			if player:getItemCount(39262) < 1 then
				player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao tem checkpoint register para salvar novos checkpoints.")
				return false
			end
			if player:getStorageValue(900001 + (i * 10)) == 0 or player:getStorageValue(900001 + (i * 10)) == -1 then
				player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce salvou esta posicao no Checkpoint #"..i)
				player:setStorageValue(900001 + (i * 10), toPosition.x)
				player:setStorageValue(900001 + 1 + (i * 10), toPosition.y)
				player:setStorageValue(900001 + 2 + (i * 10), toPosition.z)
				item:remove(1)
				return false
			end
			player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao tem slots de checkpoint disponiveis. Por favor resete os checkpoints para adicionar outros.")
		end
	else
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce nao pode salvar esta posicao.")
		return false
	end
	return false
end
