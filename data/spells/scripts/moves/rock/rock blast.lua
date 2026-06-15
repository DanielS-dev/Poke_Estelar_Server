local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 25

function onCastSpell(creature, variant)
	for i = 0, 4 do
		local pos = creature:getPosition()
		addEvent(doAreaCombatHealth, i * 333, creature.uid, COMBAT_ROCKDAMAGE, pos, area, damage * (i + 1), damage * (i + 1), 608)
	end
	return true
end
