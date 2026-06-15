local damage = 100

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_WATERDAMAGE, damage, damage, 663, COMBAT_PHYSICALDAMAGE)
	creature:getTarget():getPosition():sendMagicEffect(664)
	return true
end

