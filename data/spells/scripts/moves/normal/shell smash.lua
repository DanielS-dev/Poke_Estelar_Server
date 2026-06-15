function onCastSpell(creature, variant)
	local attack = Condition(CONDITION_ATTACKPLUS)
	attack:setParameter(CONDITION_PARAM_TICKS, 5000)
	local defense = Condition(CONDITION_DEFENSEMINUS)
	defense:setParameter(CONDITION_PARAM_TICKS, 5000)
	local speed = Condition(CONDITION_HASTE)
	speed:setParameter(CONDITION_PARAM_TICKS, 5000)
	speed:setFormula(0, creature:getTotalSpeed(), 0, creature:getTotalSpeed())
	creature:addCondition(attack)
	creature:addCondition(defense)
	creature:addCondition(speed)
	creature:getPosition():sendMagicEffect(280)
	return true
end
