local damage = 60

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doSendMagicEffect(creature:getPosition(), creature:getTarget():getPosition(), 98)
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 22)
	local focus = Condition(CONDITION_FOCUS)
	focus:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(focus)
	return true
end
