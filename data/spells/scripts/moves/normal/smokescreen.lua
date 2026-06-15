function onCastSpell(creature, variant)
	local evasion = Condition(CONDITION_EVASION)
	evasion:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(evasion)
	creature:getPosition():sendMagicEffect(919)
	return true
end
