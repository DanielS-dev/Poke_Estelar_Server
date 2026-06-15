local damage = 60

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local target = creature:getTarget()
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 132)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_DRAGONDAMAGE, damage, damage, 391)
	addEvent(doSendDistanceShoot, 150, creature:getPosition(), target:getPosition(), 132)
	addEvent(doTargetCombatHealth, 150, creature.uid, target.uid, COMBAT_DRAGONDAMAGE, damage, damage, 391)
	addEvent(doSendDistanceShoot, 300, creature:getPosition(), target:getPosition(), 132)
	addEvent(doTargetCombatHealth, 300, creature.uid, target.uid, COMBAT_DRAGONDAMAGE, damage, damage, 391)
	if math.random(1, 10) <= 10 then
		setConditionOn(creature.uid, target.uid, 'paralyze')
	end
	return true
end
