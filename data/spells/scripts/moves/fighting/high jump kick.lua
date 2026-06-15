local damage = 130

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	if math.random(1, 100) <= 10 then
		creature:addHealth(-(creature:getMaxHealth() * 0.10))
	end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 563, COMBAT_PHYSICALDAMAGE)
	creature:teleportTo(creature:getTarget():getPosition(), 1)
	return true
end