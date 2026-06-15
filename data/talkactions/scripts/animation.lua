function onSay(player, words, param)
	local outfit = player:getOutfit().lookType
	local condition = Condition(CONDITION_OUTFIT)
	condition:setTicks(-1)
	if outfit == 3793 then -- majin boo
		condition:setOutfit({lookType = 3794})
	elseif outfit == 3791 then -- goku
		condition:setOutfit({lookType = 3792})
	elseif outfit == 2914 then -- psychic trainer female
		condition:setOutfit({lookType = 2912, lookHead = player:getOutfit().lookHead, lookBody = player:getOutfit().lookBody, lookLegs = player:getOutfit().lookLegs, lookFeet = player:getOutfit().lookFeet})
	elseif outfit == 2913 then-- psychic trainer male
		condition:setOutfit({lookType = 2911, lookHead = player:getOutfit().lookHead, lookBody = player:getOutfit().lookBody, lookLegs = player:getOutfit().lookLegs, lookFeet = player:getOutfit().lookFeet})
	elseif outfit == 3794 then -- majin boo
		condition:setOutfit({lookType = 3793})
	elseif outfit == 3792 then -- goku
		condition:setOutfit({lookType = 3791})
	elseif outfit == 2912 then -- psychic trainer female
		condition:setOutfit({lookType = 2914, lookHead = player:getOutfit().lookHead, lookBody = player:getOutfit().lookBody, lookLegs = player:getOutfit().lookLegs, lookFeet = player:getOutfit().lookFeet})
	elseif outfit == 2911 then-- psychic trainer male
		condition:setOutfit({lookType = 2913, lookHead = player:getOutfit().lookHead, lookBody = player:getOutfit().lookBody, lookLegs = player:getOutfit().lookLegs, lookFeet = player:getOutfit().lookFeet})
	end
	player:addCondition(condition)
	return false
end
