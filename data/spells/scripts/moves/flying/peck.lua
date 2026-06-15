local damage = 35

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FLYINGDAMAGE, damage, damage, 100, COMBAT_PHYSICALDAMAGE)
	return true
end

