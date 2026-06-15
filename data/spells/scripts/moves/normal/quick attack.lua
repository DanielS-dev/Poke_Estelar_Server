local damage = 40

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	creature:teleportTo(creature:getTarget():getClosestFreePosition(creature:getTarget():getPosition(), 1), false)
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 100, COMBAT_PHYSICALDAMAGE)
	return true
end