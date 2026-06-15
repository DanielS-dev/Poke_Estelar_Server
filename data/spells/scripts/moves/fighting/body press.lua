function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local damage = math.floor(creature:getTotalDefense()/1000 * 80) + 80
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 344, COMBAT_PHYSICALDAMAGE)
	creature:teleportTo(creature:getTarget():getPosition(), true)
	return true
end

