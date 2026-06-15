function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end

	if player:getAccountType() < ACCOUNT_TYPE_GOD then
		return true
	end
	local item = player:addItem(39319, 1)
	item:setSpecialAttribute("talisman", param)
	return false
end
