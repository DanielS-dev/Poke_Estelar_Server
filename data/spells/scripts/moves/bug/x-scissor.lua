local damage = 80
local area = createCombatArea(AREA_CIRCLE2X2)

function onCastSpell(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_BUGDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(649)
	return true
end