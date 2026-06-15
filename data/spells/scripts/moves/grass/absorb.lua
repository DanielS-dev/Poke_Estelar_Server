local damage = 20

function onCastSpell(creature, variant)
	local target = creature:getTarget()
	if not target then return true end
	local creaturePosition = creature:getPosition()
	local targetPosition = target:getPosition()
	doSendDistanceShoot(targetPosition, creaturePosition, 122)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_GRASSDAMAGE, damage, damage, 342)
	doTargetCombatHealth(0, creature.uid, COMBAT_HEALING, creature:getMaxHealth() * 0.1, creature:getMaxHealth() * 0.1, 504)
	return true
end

