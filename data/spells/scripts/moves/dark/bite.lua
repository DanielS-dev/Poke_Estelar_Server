local damage = 60

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_DARKDAMAGE, damage, damage, 266, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 100) <= 10 then
		setConditionOn(creature.uid, creature:getTarget().uid, 'silence')
	end
	return true
end

