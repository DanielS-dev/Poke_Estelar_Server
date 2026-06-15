local damage = 100

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	local pos = creature:getTarget():getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(1033)
	setConditionOn(creature.uid, creature:getTarget().uid, 'confusion')
	return true
end

