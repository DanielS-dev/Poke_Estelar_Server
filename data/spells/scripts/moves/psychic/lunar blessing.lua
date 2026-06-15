function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 3
	pos.y = pos.y + 2
	pos:sendMagicEffect(1003)
	doTargetCombatHealth(0, creature.uid, COMBAT_HEALING, (creature:getMaxHealth() * 0.50), (creature:getMaxHealth() * 0.50), 0)
	local condition = Condition(CONDITION_EVASION)
	condition:setTicks(5000)
	creature:addCondition(condition)
	return true
end