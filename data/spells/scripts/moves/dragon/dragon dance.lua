function onCastSpell(creature, variant)
	local attack = Condition(CONDITION_ATTACKPLUS)
	attack:setParameter(CONDITION_PARAM_TICKS, 5000)
	local speed = Condition(CONDITION_HASTE)
	speed:setParameter(CONDITION_PARAM_TICKS, 5000)
	speed:setFormula(0, creature:getTotalSpeed(), 0, creature:getTotalSpeed())
	creature:addCondition(attack)
	creature:addCondition(speed)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(934)
	return true
end
