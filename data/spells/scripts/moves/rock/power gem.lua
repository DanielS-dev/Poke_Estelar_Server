local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local areadmg = {createCombatArea(AREA_CIRCLE1X1), createCombatArea(AREA_CIRCLE2X2), createCombatArea(AREA_CIRCLE3X3), createCombatArea(AREA_CIRCLE4X4)}
local damage = 80/4

function onCastSpell(creature, variant)
	for i = 0, 3 do
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), areadmg[i + 1], damage, damage, 0)
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area[i + 1], 0, 0, 744)
	end
	return true
end