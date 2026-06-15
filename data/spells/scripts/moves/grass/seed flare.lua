local damage = 120
local area = createCombatArea(AREA_CIRCLE2X2_2)

function onCastSpell(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:sendMagicEffect(1035)
	return true
end
