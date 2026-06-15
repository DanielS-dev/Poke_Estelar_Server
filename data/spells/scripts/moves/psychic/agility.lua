function onCastSpell(creature, variant)
	local speed = Condition(CONDITION_HASTE)
	speed:setParameter(CONDITION_PARAM_TICKS, 5000)
	speed:setFormula(0, creature:getTotalSpeed(), 0, creature:getTotalSpeed())
	creature:addCondition(speed)
	creature:getPosition():sendMagicEffect(14)
	return true
end
