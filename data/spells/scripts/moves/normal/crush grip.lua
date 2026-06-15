function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local damage = 1 + 120 * (creature:getTarget():getHealth() / creature:getTarget():getMaxHealth())
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	local pos = creature:getTarget():getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(1052)
	return true
end

