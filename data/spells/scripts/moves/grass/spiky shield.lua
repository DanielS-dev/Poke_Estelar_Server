function onCastSpell(creature, variant)
	local immune = Condition(CONDITION_IMMUNE)
	immune:setTicks(5000)
	local reflect = Condition(CONDITION_REFLECT)
	reflect:setTicks(5000)
	creature:addCondition(reflect)
	creature:addCondition(immune)
	creature:getPosition():sendMagicEffect(1007)
	return true
end