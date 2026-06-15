local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local areadmg = createCombatArea(AREA_CIRCLE4X4)
local damage = 60/4

function onCastSpell(creature, variant)
	for i = 1, #area do
		addEvent(doAreaCombatHealth, i * 200, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), areadmg, damage, damage, 0)
		addEvent(doAreaCombatHealth, i * 200, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area[i], 0, 0, 768)
	end
	return true
end
