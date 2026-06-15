function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end

	if player:getAccountType() < ACCOUNT_TYPE_GOD then
		return true
	end

	local split = param:split(",")
	local targetName = split[1]

	local target = Player(targetName)
	if target == nil then
		player:sendCancelMessage("A player with that name is not online.")
		return false
	end

	local qt = split[2]
	if qt == nil then
		qt = 0
	end
	
	target:getInbox():addItem(38942, qt, INDEX_WHEREEVER, FLAG_NOLIMIT)

	target:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce recebeu " .. qt .. " packs de pe, retire-os em sua catch box no depot.")
	player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce entregou "..qt.." packs de pe ao jogador: "..targetName..".")
	return false
end
