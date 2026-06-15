function onCastSpell(creature, variant)
	local attack = Condition(CONDITION_ATTACKPLUS)
	attack:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(attack)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(437)
	return true
end
