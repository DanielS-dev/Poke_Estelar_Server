local area = createCombatArea(AREA_CIRCLE2X2)

function onCastSpell(creature, variant)
	local damage = creature:getLevel()
	doAreaCombatHealth(creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, damage, damage, 722)
	return true
end
