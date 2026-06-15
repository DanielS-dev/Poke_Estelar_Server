function onCastSpell(creature, variant)
	creature:getPosition():sendMagicEffect(431)
	if creature:getName() == "Castform" then
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = 3438})
		creature:addCondition(condition)
	end
	if creature:getName() == "Castform" then
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = 3438})
		creature:addCondition(condition)
	end
	if isInArray(hiddenabilities.snowcloak, creature:getName()) then
		local condition = Condition(CONDITION_EVASION)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addCondition(condition)
		Game.sendAnimatedText(creature:getPosition(), "EVASION UP", TEXTCOLOR_WHITE)
	end
	if isInArray(hiddenabilities.icebody, creature:getName()) then
		local condition = Condition(CONDITION_FOCUS)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addCondition(condition)
		Game.sendAnimatedText(creature:getPosition(), "FOCUS", TEXTCOLOR_WHITE)
	end
	return true
end