local damage = 40

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doSendDistanceShoot(creature:getPosition(), creature:getTarget():getPosition(), 61)
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_WATERDAMAGE, damage, damage, 423)
	return true
end
