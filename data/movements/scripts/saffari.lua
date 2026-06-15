function onStepIn(creature, item, position, fromPosition)
	if not creature:isPlayer() then return false end
	if item.actionid == 6699 then
		if creature:getPosition().z == 14 then
			creature:teleportTo(Position(1227, 1681, 7))
			if creature:getCondition(CONDITION_SAFFARI) ~= nil then creature:removeCondition(CONDITION_SAFFARI) end
			if creature:getItemCount(26685) >= 1 then creature:removeItem(26685, creature:getItemCount(26685)) end
		elseif creature:getPosition().z == 10 then
			return false
		else
			local pos = creature:getPosition()
			pos.y = pos.y + 1
			pos.z = pos.z - 1
			creature:teleportTo(pos)
		end
	elseif item.actionid == 6698 then
		if creature:getPosition().z == 14 then
			return false
		else
			local pos = creature:getPosition()
			pos.y = pos.y + 1
			pos.z = pos.z + 1
			creature:teleportTo(pos)
		end
	end
	return true
end

