function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:sendMagicEffect(828)
	if creature:getName() == "Castform" then
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = 3436})
		creature:addCondition(condition)
	elseif creature:getName() == "Cherrim" then
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = 3491})
		creature:addCondition(condition)
	end
	if isInArray(hiddenabilities.chlorophyll, creature:getName()) then
		local speed = Condition(CONDITION_HASTE)
		speed:setParameter(CONDITION_PARAM_TICKS, 5000)
		speed:setFormula(0, creature:getTotalSpeed(), 0, creature:getTotalSpeed())
		creature:addCondition(speed)
		Game.sendAnimatedText(creature:getPosition(), "SPEED UP", TEXTCOLOR_WHITE)
	end
	if MonsterType(creature:getName()):getRaceName() == "fire" or MonsterType(creature:getName()):getRace2Name() == "fire" then
		local condition = Condition(CONDITION_FOCUS)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addCondition(condition)
		Game.sendAnimatedText(creature:getPosition(), "FOCUS", TEXTCOLOR_WHITE)
	end
	return true
end