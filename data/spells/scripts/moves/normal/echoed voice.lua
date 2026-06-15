local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 40

function onCastSpell(creature, variant)
	for i = 0, 4 do
		addEvent(doAreaCombatHealth, i * 350, creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, damage, damage, 25)
	end
	return true
end
