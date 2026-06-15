function onPrepareDeath(creature, killer)
	-- if creature:getCondition(CONDITION_SAFFARI) ~= nil then
		-- creature:addHealth(creature:getMaxHealth() - creature:getHealth())
		-- creature:removeCondition(CONDITION_SAFFARI)
		-- local town = creature:getTown()
		-- creature:teleportTo(town:getTemplePosition())
		-- return false
	-- elseif creature:getCondition(CONDITION_PARK) ~= nil then
		-- creature:addHealth(creature:getMaxHealth() - creature:getHealth())
		-- creature:removeCondition(CONDITION_PARK)
		-- local town = creature:getTown()
		-- creature:teleportTo(town:getTemplePosition())
		-- return false
	-- end
	return true
end
