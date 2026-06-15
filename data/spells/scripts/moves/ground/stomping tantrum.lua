local areas = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2)}
local areadamage = createCombatArea(AREA_CIRCLE2X2)
local damage = 75/4

function onCastSpell(creature, variant)
	for i = 1, 4 do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_GROUNDDAMAGE, creature:getPosition(), areadamage, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_GROUNDDAMAGE, creature:getPosition(), areas[i], 0, 0, 238, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
