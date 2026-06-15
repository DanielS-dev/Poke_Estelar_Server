local damage = 40

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 563, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 2) == 1 then
		setConditionOn(creature.uid, creature:getTarget().uid, 'defense minus')
	end
	return true
end

