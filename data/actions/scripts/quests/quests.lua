function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	-- if item.uid <= 1250 or item.uid >= 30000 then
		-- return false
	-- end
	if item.uid == 65000 then
		player:giveQuestPrize(storageLeagueDone)
	else
		player:giveQuestPrize(item.uid)
	end
	return true
end
