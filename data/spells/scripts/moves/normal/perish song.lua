local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local areadmg = createCombatArea(AREA_CIRCLE4X4)
local damage = 120/4

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, #area do
		addEvent(doAreaCombatHealth, i * 333, creature.uid, COMBAT_NORMALDAMAGE, pos, areadmg, damage, damage, 0)
		addEvent(doAreaCombatHealth, i * 333, creature.uid, COMBAT_NORMALDAMAGE, pos, area[i], 0, 0, 25)
	end
	return true
end
