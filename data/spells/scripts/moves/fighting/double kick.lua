local damage = 30

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	for i = 0, 1 do
		addEvent(doTargetCombatHealth, i * 175, creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 233, COMBAT_PHYSICALDAMAGE)
	end
	return true
end