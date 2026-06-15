local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local damage = 140

function onCastSpell(creature, variant)
	for i = 1, #area do
		addEvent(doAreaCombatHealth, (i - 1) * 200, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area[i], damage, damage, 569)
	end
	setConditionOn(creature, creature, 'attack minus')
	return true
end