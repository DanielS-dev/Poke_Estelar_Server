local damage = 65

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local target = creature:getTarget()
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 74)
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 10, COMBAT_PHYSICALDAMAGE)
	return true
end

