local damage = 85
local area = createCombatArea(AREA_CIRCLE2X2_2)

function onCastSpell(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_DARKDAMAGE, creature:getPosition(), area, damage, damage, 0)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(958)
	return true
end
