local damage = 85
local area = createCombatArea(AREA_CIRCLE2X2_2)

function onCastSpell(creature, variant)
	
	doAreaCombatHealth(creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area, damage, damage, 907)
	return true
end
