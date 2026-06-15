local damage = 80

local area = createCombatArea(AREA_CIRCLE2X2)	

function onCastSpell(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_FAIRYDAMAGE, creature:getPosition(), area, damage, damage, 1049)
	return true
end