function onCastSpell(creature, variant)
	local attack = Condition(CONDITION_ATTACKPLUS)
	attack:setParameter(CONDITION_PARAM_TICKS, 5000)
	local defense = Condition(CONDITION_DEFENSEPLUS)
	defense:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(attack)
	creature:addCondition(defense)
	creature:getPosition():sendMagicEffect(569)
	return true
end
