local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND4), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND2)}
local areadmg = createCombatArea(AREA_CIRCLE3X3)
local damage = 90/12

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	for i = 1, 12 do
		addEvent(doAreaCombatHealth, (i - 1) * 500, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), areadmg, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doAreaCombatHealth, (i - 1) * 500, creature.uid, COMBAT_ELECTRICDAMAGE, pos, area[math.fmod(i, 4) + 1], 0, 0, 820)
	end
	return true
end
