function onSay(player, words, param)
	if param == "1" then
		local ball = player:getUsingBall() or 0
		if ball ~= 0 then
			local getaddons = ball:getSpecialAttribute("addons") or 0
			if getaddons ~= 0 then
				player:sendExtendedOpcode(63, ","..MonsterType(player:getSummon():getName()):getOutfit().lookType.. "" ..getaddons)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Este pokemon nao tem addons.")
				return false
			end
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu pokemon precisa estar pra fora da pokebola.")
			return false
		end
	else
		local addon = Condition(CONDITION_OUTFIT)
		addon:setTicks(-1)
		if string.find(player:getSummon():getName(), "Mega ") and isInArray({3960, 3967, 3968, 3972, 3988, 3992, 3735, 3740, 3742, 3749, 3758}, tonumber(param)) then
			addon:setOutfit({lookType = addonmega[tonumber(param)]})
		else
			addon:setOutfit({lookType = tonumber(param)})
		end
		player:getSummon():addCondition(addon)
		player:getUsingBall():setSpecialAttribute('usingaddon', tonumber(param))
	end
	return false
end
