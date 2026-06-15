local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 120/5

function onCastSpell(creature, variant)
	for i = 0, 4 do
		addEvent(doAreaCombatHealth, i * 350, creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, damage, damage, 231, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
