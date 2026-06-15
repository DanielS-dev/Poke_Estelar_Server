local area = createCombatArea(AREA_CIRCLE1X1)
local damage = 50/12

function onCastSpell(creature, variant)
		for i = 1, 12 do
			addEvent(doCreatureSetLookDir, i * 50, creature.uid, math.fmod(i-1, 4))
			addEvent(doAreaCombatHealth, i * 50, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		end
	return true
end