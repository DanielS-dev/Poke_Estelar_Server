local damage = 50

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 563, COMBAT_PHYSICALDAMAGE)
	return true
end

