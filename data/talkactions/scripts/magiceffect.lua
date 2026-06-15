function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end
	if player:getSummon() then
		if param:split(",")[2] and param:split(",")[3] then
			local pos = player:getSummon():getPosition()
			pos.x = pos.x + tonumber(param:split(",")[2])
			pos.y = pos.y + tonumber(param:split(",")[3])
			pos:sendMagicEffect(tonumber(param:split(",")[1]))
		else
			player:getSummon():getPosition():sendMagicEffect(tonumber(param))
		end
	else
		if param:split(",")[2] and param:split(",")[3] then
			local pos = player:getPosition()
			pos.x = pos.x + tonumber(param:split(",")[2])
			pos.y = pos.y + tonumber(param:split(",")[3])
			pos:sendMagicEffect(tonumber(param:split(",")[1]))
		else
			player:getPosition():sendMagicEffect(tonumber(param))
		end
	end
	return false
end
