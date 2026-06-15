local damage = 50

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doSendDistanceShoot(creature:getPosition(), creature:getTarget():getPosition(), 165)
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_ROCKDAMAGE, damage, damage, 747)
	return true
end
