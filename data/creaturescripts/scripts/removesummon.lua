function onMove(creature, toPosition, fromPosition)
	local player = Player(creature:getId())
	if not hasSummons(player) then
		return true
	end
	local summon = player:getSummon()
	if summon:getSpeed() == 0 then
		summon:changeSpeed(summon:getTotalSpeed())
	end

        local toTile = Tile(toPosition)

	if toTile and (toTile:getHouse() or toTile:hasFlag(TILESTATE_PROTECTIONZONE)) then 
		if hasSummons(player) then
			local ball = player:getUsingBall()
			local ballId = ball:getId()
			local ballKey = getBallKey(ballId)
			ball:transform(balls[ballKey].usedOn)
			doRemoveSummon(player:getId(), balls[ballKey].effectRelease, false, true, balls[ballKey].missile)
		end		
	end

	return true
end
