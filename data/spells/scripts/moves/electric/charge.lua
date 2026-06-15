function onCastSpell(creature, variant)
	local focus = Condition(CONDITION_FOCUS)
	focus:setParameter(CONDITION_PARAM_TICKS, 5000)
	local defense = Condition(CONDITION_DEFENSEPLUS)
	defense:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(focus)
	creature:addCondition(defense)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1 
	pos:sendMagicEffect(942)
	return true
end