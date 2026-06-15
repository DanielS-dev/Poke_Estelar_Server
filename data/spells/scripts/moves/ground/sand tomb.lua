local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 35

function onCastSpell(creature, variant)
	for i = 0, 4 do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_GROUNDDAMAGE, creature:getPosition(), area, damage, damage, 527, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
