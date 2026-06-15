function onCastSpell(creature, variant)
	local condition = Condition(CONDITION_IMMUNE)
	condition:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(condition)
	creature:getPosition():sendMagicEffect(254)
	return true
end
