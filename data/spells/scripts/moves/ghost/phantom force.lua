local area = createCombatArea(AREA_CIRCLE2X2_2)
local areas = {createCombatArea(AREA_CIRCLE2X2_OUTER1), createCombatArea(AREA_CIRCLE2X2_OUTER2), createCombatArea(AREA_CIRCLE2X2_OUTER3), createCombatArea(AREA_CIRCLE2X2_OUTER4), createCombatArea(AREA_CIRCLE2X2_OUTER5), createCombatArea(AREA_CIRCLE2X2_OUTER6), createCombatArea(AREA_CIRCLE2X2_OUTER7), createCombatArea(AREA_CIRCLE2X2_OUTER8), createCombatArea(AREA_CIRCLE2X2_OUTER1)}

local combat = COMBAT_GHOSTDAMAGE
local damage = 90/#areas

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 1	
	pos.y = pos.y + 1
	pos:sendMagicEffect(933)
	for i = 0, 8 do
		addEvent(doAreaCombatHealth, i * 350, creature.uid, combat, creature:getPosition(), area, damage, damage, 928)
		addEvent(doAreaCombatHealth, i * 350, creature.uid, combat, creature:getPosition(), areas[i+1], 0, 0, 392)
	end
	return true
end