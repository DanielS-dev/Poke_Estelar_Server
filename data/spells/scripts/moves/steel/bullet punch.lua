local damage = 40/5

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	for i = 0, 4 do
		addEvent(doTargetCombatHealth, i * 300, creature.uid, creature:getTarget().uid, COMBAT_STEELDAMAGE, damage, damage, 232, COMBAT_PHYSICALDAMAGE)
	end
	return true
end

