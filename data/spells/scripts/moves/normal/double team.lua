function onCastSpell(creature, variant)
	local condition = Condition(CONDITION_EVASION)
	condition:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(condition)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(941)
	return true
end
