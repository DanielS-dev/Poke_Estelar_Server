local delay = 12*60*60

function onSay(player, words, param)
	
	if player:isOnDive() then
		player:setStorageValue(storageDive, -1)
		player:removeCondition(CONDITION_OUTFIT)
	end

	if player:isDuelingWithNpc() then
		player:unsetDuelWithNpc()
	end
	
	if player:getCondition(CONDITION_SAFFARI) ~= nil then
		player:removeCondition(CONDITION_SAFFARI)
		if player:getItemCount(26685) >= 1 then
			player:removeItem(26685, player:getItemCount(26685))
		end
	end
	if player:getCondition(CONDITION_PARK) ~= nil then
		player:removeCondition(CONDITION_PARK)
		if player:getItemCount(39132) >= 1 then
			player:removeItem(39132, player:getItemCount(39132))
		end
	end
	
	if player:isOnSurf() then -- Check surf
		local totalSpeed = player:getStorageValue(storageLogoutSpeed) or 50
		if totalSpeed < 50 then totalSpeed = 50 end
		player:changeSpeed(-player:getSpeed() + totalSpeed)
	elseif player:isOnRide() then -- Check ride
		local summonName = player:getSummonNameFromBall()
		local monsterType = MonsterType(summonName)
		if monsterType and monsterType:isRideable() > 0 then
			local totalSpeed = player:getStorageValue(storageLogoutSpeed) or 50
			if totalSpeed < 50 then totalSpeed = 50 end
			player:changeSpeed(-player:getSpeed() + totalSpeed)
			doChangeOutfit(player:getId(), {lookType = monsterType:isRideable()})
		else
			print("WARNING! Player " .. player:getName() .. " summonName not found onLogin for ride!")
			player:setStorageValue(storageRide, -1)
			player:teleportTo(player:getTown():getTemplePosition())
		end		
	elseif player:isOnFly() then -- Check fly
		local summonName = player:getSummonNameFromBall()
		local monsterType = MonsterType(summonName)
		if monsterType and monsterType:isFlyable() > 0 then
			local totalSpeed = player:getStorageValue(storageLogoutSpeed) or 50
			if totalSpeed < 50 then totalSpeed = 50 end
			player:changeSpeed(-player:getSpeed() + totalSpeed)
			doChangeOutfit(player:getId(), {lookType = monsterType:isFlyable()})
			player:activateFly()
		else
			print("WARNING! Player " .. player:getName() .. " summonName not found onLogin for fly!")
			player:setStorageValue(storageFly, -1)
			player:teleportTo(player:getTown():getTemplePosition())
		end
	elseif player:isOnDive() then -- Check dive
		doChangeOutfit(player:getId(), {lookType = 267})
	end

	player:teleportTo(player:getTown():getTemplePosition())
	return false
end
