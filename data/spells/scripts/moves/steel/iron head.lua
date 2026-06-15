local damage = 80

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_STEELDAMAGE, damage, damage, 881, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 100) <= 30 then
		setConditionOn(creature.uid, creature:getTarget().uid, 'silence')
	end
	return true
end

