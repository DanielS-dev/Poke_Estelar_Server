local damage = 150/6
local areas = {createCombatArea(psy1), createCombatArea(psy2), createCombatArea(psy3), createCombatArea(psy4), createCombatArea(psy5), createCombatArea(LeafStorm1)}
local area = createCombatArea(AREA_CIRCLE5X5)

function onCastSpell(creature, variant)	
	for i = 1, #areas do
		local pos = creature:getPosition()
		pos:getNextPosition(1)
		addEvent(doAreaCombatHealth, i * 750, creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area, damage, damage, 0)
		addEvent(doAreaCombatHealth, i * 750, creature.uid, COMBAT_WATERDAMAGE, pos, areas[i], 0, 0, 554)
	end
	return true
end