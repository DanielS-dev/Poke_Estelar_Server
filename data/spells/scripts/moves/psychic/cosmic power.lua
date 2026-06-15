function onCastSpell(creature, variant)
	local defense = Condition(CONDITION_DEFENSEPLUS)
	defense:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(defense)
	local pos = creature:getPosition()
	pos.x = pos.x + 3
	pos.y = pos.y + 3
	pos:sendMagicEffect(967)
	return true
end
