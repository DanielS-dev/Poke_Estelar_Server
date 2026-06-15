function onCastSpell(creature, variant)
	local speed = Condition(CONDITION_HASTE)
	speed:setParameter(CONDITION_PARAM_TICKS, 5000)
	speed:setFormula(0, creature:getTotalSpeed() * 2, 0, creature:getTotalSpeed() * 2)
	creature:addCondition(speed)
	creature:getPosition():sendMagicEffect(960)
	return true
end