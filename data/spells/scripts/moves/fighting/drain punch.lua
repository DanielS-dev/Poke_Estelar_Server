local damage = 75

function onCastSpell(creature, variant)
	local target = creature:getTarget()
	if not target then return true end
	local creaturePosition = creature:getPosition()
	local targetPosition = target:getPosition()
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	targetPosition:getNextPosition(1)
	targetPosition:getNextPosition(2)
	targetPosition:sendMagicEffect(428)
	doTargetCombatHealth(0, creature.uid, COMBAT_HEALING, damage, damage, 252)
	return true
end

