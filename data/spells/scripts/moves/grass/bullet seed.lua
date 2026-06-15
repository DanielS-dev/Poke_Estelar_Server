local damage = 25

function onCastSpell(creature, variant)
	local target = creature:getTarget()
	if not target then return true end
	for i = 1, 4 do
		if math.random(1, 2) == 1 then
			addEvent(doSendDistanceShoot, i * 200, creature:getPosition(), target:getPosition(), 60)
			addEvent(doTargetCombatHealth, i * 200, creature.uid, target.uid, COMBAT_GRASSDAMAGE, damage, damage, 46)
		end
	end
	
	return true
end
