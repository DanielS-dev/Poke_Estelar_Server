local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local eff = {19, 22, 24, 23}
local damage = 65

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(947)
	for i = 1, 4 do
		addEvent(doAreaCombatHealth, i * 250, creature.uid, COMBAT_FLYINGDAMAGE, creature:getPosition(), area[i], damage, damage, eff[i])
	end
	return true
end
