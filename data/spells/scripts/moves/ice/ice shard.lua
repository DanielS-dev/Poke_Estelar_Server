local damage = 40

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doSendDistanceShoot(creature:getPosition(), creature:getTarget():getPosition(), 147)
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_ICEDAMAGE, damage, damage, 743, COMBAT_PHYSICALDAMAGE)
	return true
end
