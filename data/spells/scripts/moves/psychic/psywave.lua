local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local areadmg = {createCombatArea(AREA_CIRCLE1X1), createCombatArea(AREA_CIRCLE2X2), createCombatArea(AREA_CIRCLE3X3), createCombatArea(AREA_CIRCLE4X4)}

function onCastSpell(creature, variant)
	for i = 0, 3 do
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), areadmg[i + 1], creature:getLevel() * 0.5, creature:getLevel() * 1.5, 0)
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area[i + 1], 0, 0, 253)
	end
	return true
end