function onCastSpell(creature, variant)
	local reflect = Condition(CONDITION_COAT)
	reflect:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(reflect)
	creature:getPosition():sendMagicEffect(255)
	return true
end
