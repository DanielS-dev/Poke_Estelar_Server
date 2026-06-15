local OPCODE_LANGUAGE = 1
local OPCODE_SKILLBAR = 52

function onExtendedOpcode(player, opcode, buffer)
	if opcode == OPCODE_LANGUAGE then
		-- otclient language
		if buffer == 'en' or buffer == 'pt' then
			-- example, setting player language, because otclient is multi-language...
			-- player:setStorageValue(SOME_STORAGE_ID, SOME_VALUE)
		end
	elseif opcode == OPCODE_SKILLBAR then
	elseif opcode == 54 then
		local tibiaCoins = getPlayerStorageValue(player, 18051)
		player:sendExtendedOpcode(54, tibiaCoins)
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, tibiaCoins)
	end
end
