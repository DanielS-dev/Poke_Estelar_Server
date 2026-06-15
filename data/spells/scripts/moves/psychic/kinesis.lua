function onCastSpell(creature, variant)
	local evasion = Condition(CONDITION_EVASION)
	evasion:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(evasion)
	local pos = creature:getPosition()
	pos.x = pos.x + 1 
	pos.y = pos.y + 1
	pos:sendMagicEffect(945)
	return true
end