local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 35

function onCastSpell(creature, variant)
	for i = 0, 4 do
		local pos = creature:getPosition()
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_WATERDAMAGE, pos, area, damage, damage, 440)
	end
	return true
end
