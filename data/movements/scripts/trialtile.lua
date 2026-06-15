function onStepIn(creature, item, position, fromPosition)
	if not creature:isPlayer() then return false end
	if creature:getStorageValue(storageBike) > 0 then
		creature:removeCondition(CONDITION_OUTFIT)
		creature:changeSpeed(creature:getBaseSpeed()-creature:getSpeed())
		creature:setStorageValue(storageBike, -1)
	end
	return true
end