function onCastSpell(creature, variant)
	local immune = Condition(CONDITION_IMMUNE)
	immune:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(immune)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(936)
	return true
end
