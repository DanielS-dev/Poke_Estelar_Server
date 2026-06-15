function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end

	if player:getAccountType() < ACCOUNT_TYPE_GOD then
		return true
	end
	local target = Player('Bene')

	target:addOutfit(4019)
	return false
end
