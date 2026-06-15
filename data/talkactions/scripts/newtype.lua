function onSay(player, words, param)
	if isInArray({"Zay"}, player:getName()) then
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = tonumber(param)})
		player:addCondition(condition)
	end
	return false
end