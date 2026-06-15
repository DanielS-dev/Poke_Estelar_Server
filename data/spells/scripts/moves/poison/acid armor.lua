function onCastSpell(creature, variant)
	local defense = Condition(CONDITION_DEFENSEPLUS)
	defense:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(defense)
	creature:getPosition():sendMagicEffect(264)
	return true
end
