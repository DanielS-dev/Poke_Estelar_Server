local damage = 60

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 880, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 100) <= 30 then
		setConditionOn(creature.uid, creature:getTarget().uid, 'paralyze')
	end
	return true
end

