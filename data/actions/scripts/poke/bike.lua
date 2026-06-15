local delay = 0.1
local bonusSpeed = 3
local outfitMale = 1315
local outfitFemale = 1316
local condition = Condition(CONDITION_OUTFIT)
condition:setTicks(-1)

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if os.time() > player:getStorageValue(storageDelay) then
	       	player:setStorageValue(storageDelay, os.time() + delay)
	else
		player:sendCancelMessage(RETURNVALUE_YOUAREEXHAUSTED)
		return true
	end
	if item:getId() == 39232 then -- yellow
		outfitMale = 2801
		outfitFemale = 2795
	elseif item:getId() == 39233 then -- red
		outfitMale = 2800
		outfitFemale = 2793
	elseif item:getId() == 39234 then -- pink
		outfitMale = 2798
		outfitFemale = 2792
	elseif item:getId() == 39235 then -- green
		outfitMale = 2799
		outfitFemale = 2791
	elseif item:getId() == 39236 then -- blue
		outfitMale = 2790
		outfitFemale = 2789
	elseif item:getId() == 39237 then -- black
		outfitMale = 2802
		outfitFemale = 2794
	elseif item:getId() == 39306 then -- mario
		outfitMale = 4056
		outfitFemale = 4057
	elseif item:getId() == 39334 then -- mario
		outfitMale = 4081
		outfitFemale = 4082
	end

	if fromPosition.x ~= 65535 then
		player:sendCancelMessage("First pick up the bike.")
		return true
	end

	if player:getStorageValue(storageRide) == 1 then
		player:sendCancelMessage("Sorry, not possible while on ride.")
		return true
	end

	if player:getStorageValue(storageFly) == 1 then
		player:sendCancelMessage("Sorry, not possible while on fly.")
		return true
	end

	if player:getStorageValue(storageSurf) > 0 then
		player:sendCancelMessage("Sorry, not possible while on surf.")
		return true
	end

	if player:getStorageValue(storageDive) > 0 then
		player:sendCancelMessage("Sorry, not possible while on dive.")
		return true
	end

	if player:getStorageValue(storageEvent) > 0 then
		player:sendCancelMessage("Sorry, not possible while on event.")
		return true
	end

	if player:getStorageValue(storageBike) > 0 then
		player:removeCondition(CONDITION_OUTFIT)
		player:changeSpeed(player:getBaseSpeed()-player:getSpeed())
		player:setStorageValue(storageBike, -1)
	else
		local delta = player:getSpeed() * bonusSpeed
		if player:getSex() == PLAYERSEX_MALE then outfit = outfitMale else outfit = outfitFemale end
		condition:setOutfit({lookType = outfit, lookHead = player:getOutfit().lookHead, lookBody = player:getOutfit().lookBody, lookLegs = player:getOutfit().lookLegs, lookFeet = player:getOutfit().lookFeet})
		if item:getId() ~= 39318 then
			player:addCondition(condition)
		end
		player:setStorageValue(storageBike, 1)
		player:changeSpeed(delta)
	end

	return true
end






