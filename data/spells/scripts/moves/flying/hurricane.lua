local area = createCombatArea(AREA_CIRCLE2X2_2)
local areas = {createCombatArea(AREA_CIRCLE2X2_OUTER1), createCombatArea(AREA_CIRCLE2X2_OUTER2), createCombatArea(AREA_CIRCLE2X2_OUTER3), createCombatArea(AREA_CIRCLE2X2_OUTER4), createCombatArea(AREA_CIRCLE2X2_OUTER5), createCombatArea(AREA_CIRCLE2X2_OUTER6), createCombatArea(AREA_CIRCLE2X2_OUTER7), createCombatArea(AREA_CIRCLE2X2_OUTER8), createCombatArea(AREA_CIRCLE2X2_OUTER1)}

local damage = 110/#areas

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 9 do
		addEvent(doAreaCombatHealth, i * 250, creature.uid, COMBAT_FLYINGDAMAGE, pos, area, damage, damage, 567)
		addEvent(doAreaCombatHealth, i * 250, creature.uid, COMBAT_FLYINGDAMAGE, pos, areas[i], 0, 0, 576)
	end
	return true
end
