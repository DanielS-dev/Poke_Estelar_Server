local damage = 120/2

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local target = creature:getTarget()
	for i = 0, 1 do
		addEvent(doSendDistanceShoot, i * 150, creature:getPosition(), target:getPosition(), 173)
		addEvent(doTargetCombatHealth, i * 175, creature.uid, target.uid, COMBAT_FIREDAMAGE, damage, damage, 909)
	end
	return true
end
