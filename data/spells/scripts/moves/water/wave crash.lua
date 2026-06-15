local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local damage = 120

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:sendMagicEffect(287)
	for i = 1, 4 do
		addEvent(doAreaCombatHealth, i * 350, creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area[i], damage, damage, 691)
	end
	return true
end
