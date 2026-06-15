local damage = 80

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_DARKDAMAGE, damage, damage, 266, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 100) <= 20 then
		setConditionOn(creature.uid, creature:getTarget().uid, 'defense minus')
	end
	return true
end

