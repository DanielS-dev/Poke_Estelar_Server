function onCastSpell(creature, variant)
	local condition = Condition(CONDITION_IMMUNE)
	condition:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(condition)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(942)
	return true
end
