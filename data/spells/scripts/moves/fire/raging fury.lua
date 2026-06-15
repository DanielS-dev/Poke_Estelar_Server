local damage = 130/6
local areas = {createCombatArea(psy1), createCombatArea(psy2), createCombatArea(psy3), createCombatArea(psy4), createCombatArea(psy5), createCombatArea(LeafStorm1)}
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)	
	for i = 1, #areas do
		local pos = creature:getPosition()
		pos:getNextPosition(1)
		pos:getNextPosition(2)
		addEvent(doAreaCombatHealth, i * 750, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doAreaCombatHealth, i * 750, creature.uid, COMBAT_FIREDAMAGE, pos, areas[i], 0, 0, 761)
	end
	return true
end