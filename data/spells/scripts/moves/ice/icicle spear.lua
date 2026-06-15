local damage = 25

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	for i = 1, math.random(2, 5) do
		addEvent(doSendDistanceShoot, (i - 1) * 125, creature:getPosition(), creature:getTarget():getPosition(), 110)
		addEvent(doTargetCombatHealth, (i - 1) * 155, creature.uid, creature:getTarget().uid, COMBAT_ICEDAMAGE, damage, damage, 746, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
