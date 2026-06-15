function onStepIn(creature, item, position, fromPosition)
	if not creature:isPlayer() then
		return false
	end
	local tile = Tile(creature:getPosition())

	if not tile or not tile:getGround() then
		return false
	end

	local tileId = tile:getGround():getId()
	if creature:getStorageValue(storageSurf) > 0 then
		creature:changeSpeed(creature:getBaseSpeed()-creature:getSpeed())
		creature:setStorageValue(storageSurf, -1)
		doReleaseSummon(creature:getId(), creature:getPosition(), false, false)
		creature:say("Thanks!", TALKTYPE_SAY)
	end

	if not (creature:getStorageValue(storageRide) > 0 or creature:getStorageValue(storageFly) > 0 or creature:getStorageValue(storageBike) > 0 or creature:getStorageValue(storageSurf) > 0) then
		creature:removeCondition(CONDITION_OUTFIT)
	end
	return true
end
