local damage = 150

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_ROCKDAMAGE, damage, damage, 406, COMBAT_PHYSICALDAMAGE)
	return true
end

