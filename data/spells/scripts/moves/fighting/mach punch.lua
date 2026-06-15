local damage = 60

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	for i = 0, 10 do
		local pos = {x = creature:getTarget():getPosition().x + math.random(-2, 2), y = creature:getTarget():getPosition().y + math.random(-2, 2), z = creature:getTarget():getPosition().z}
		addEvent(doSendDistanceShoot, i * 25, Position(pos), creature:getTarget():getPosition(), 83)
	end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 230, COMBAT_PHYSICALDAMAGE)
	return true
end

