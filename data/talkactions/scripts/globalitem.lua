function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end

	if player:getAccountType() < ACCOUNT_TYPE_GOD then
		return false
	end
	
	local t = param:split(',')
	if t[1] ~= nil and t[2] ~= nil then
	local list = getOnlinePlayers()

	for i = 1, #list do
		Player(getPlayerByName(list[i])):addItem(t[1],t[2])
	end
	
	broadcastMessage(player:getName() .. "  Presenteou: " .. t[2] .." ".. t[1] .. " para todos os players online!")

	else
		doPlayerPopupFYI(cid, "No parm...\nSend:\n /itemadd itemid,how_much_items\nexample:\n /itemadd 2160,10")
	end

return true
end