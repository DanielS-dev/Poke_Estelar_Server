function onSay(player, words, param)
	local rod = player:getSlotItem(CONST_SLOT_NECKLACE)	
	local rod1 = player:getStorageValue(64001)
	local rod2 = player:getStorageValue(64002)
	local rod3 = player:getStorageValue(64003)
	if player:getSlotItem(CONST_SLOT_NECKLACE):getId() == 26820 and rod1 >= 1 then
		player:getSlotItem(CONST_SLOT_NECKLACE):transform(38897)
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce trocou para a great rod")
		return false
	elseif player:getSlotItem(CONST_SLOT_NECKLACE):getId() == 38897 and rod2 >= 1 then
		player:getSlotItem(CONST_SLOT_NECKLACE):transform(38898)
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce trocou para a super rod")
		return false
	elseif player:getSlotItem(CONST_SLOT_NECKLACE):getId() == 38898 and rod3 >= 1 then
		player:getSlotItem(CONST_SLOT_NECKLACE):transform(38899)
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce trocou para a ultra rod")
		return false
	elseif player:getSlotItem(CONST_SLOT_NECKLACE):getId() == 38899 then
		player:getSlotItem(CONST_SLOT_NECKLACE):transform(26820)
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce trocou para a old rod")
		return false
	elseif player:getSlotItem(CONST_SLOT_NECKLACE):getId() ~= 26820 then
		player:getSlotItem(CONST_SLOT_NECKLACE):transform(26820)
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce trocou para a old rod")
		return false
	end
	return false
end
