function onCastSpell(creature, variant)
	local attack = Condition(CONDITION_ATTACKPLUS)
	attack:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(attack)
	creature:getPosition():sendMagicEffect(943)
	return true
end
