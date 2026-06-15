function onMove(creature, toPosition, fromPosition)
	local player = Player(creature:getId())
    if player and player:isOnFly() then
		if isInRange(toPosition, Position(0, 0, 0), Position(3, 2058, 7)) then return false end
		if isInRange(toPosition, Position(0, 2056, 0), Position(2402, 2058, 7)) then return false end
		if isInRange(toPosition, Position(2400, 0, 0), Position(2402, 2058, 7)) then return false end
		if isInRange(toPosition, Position(0, 0, 0), Position(2402, 2, 7)) then return false end
		if isInArray({0, 1, 8, 9, 10, 11, 12, 13, 14, 15}, fromPosition.z) then
			local summonName = player:getSummonNameFromBall()
			local actualSpeed = player:getSpeed()
			player:say("Thanks, " .. summonName .. "!", TALKTYPE_SAY)
			player:removeCondition(CONDITION_OUTFIT)
			player:changeSpeed(-actualSpeed+player:getBaseSpeed())
			player:setStorageValue(storageRide, -1)
			player:setStorageValue(storageFly, -1)
			doReleaseSummon(player:getId(), player:getPosition(), false)
			return true
		end
        toPosition:createFlyFloor()
		local dir = player:getDirection()
		toPosition:getNextPosition(dir)
		toPosition:createFlyFloor()
    end
    return true
end
