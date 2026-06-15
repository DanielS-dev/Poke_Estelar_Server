local damage = 130/6
local areas = {createCombatArea(psy1), createCombatArea(psy2), createCombatArea(psy3), createCombatArea(psy4), createCombatArea(psy5), createCombatArea(LeafStorm1)}
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	for i = 1, #areas do
		addEvent(doAreaCombatHealth, (i - 1) * 750, creature.uid, COMBAT_ICEDAMAGE, creature:getPosition(), area, damage, damage, 0)
		addEvent(doAreaCombatHealth, (i - 1) * 750, creature.uid, COMBAT_ICEDAMAGE, creature:getPosition(), areas[i], 0, 0, 44)
	end
	return true
end
