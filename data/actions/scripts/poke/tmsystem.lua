function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local number = 3
	local rotom = MonsterType("rotom")
	if player:getStorageValue(baseStorageCatches + rotom:getNumber()) and player:getStorageValue(baseStorageCatches + rotom:getNumber()) >= 1 then number = number + 1 end
	local deoxys = MonsterType("deoxys")
	if player:getStorageValue(baseStorageCatches + deoxys:getNumber()) and player:getStorageValue(baseStorageCatches + deoxys:getNumber()) >= 1 then number = number + 1 end
	player:sendExtendedOpcode(17, number)
end