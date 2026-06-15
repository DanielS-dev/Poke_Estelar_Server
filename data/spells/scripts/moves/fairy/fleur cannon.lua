local area = createCombatArea(AREA_CIRCLE1X1)
local damage = 130

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(899)
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_FAIRYDAMAGE, creature:getPosition(), area, damage, damage, 1049)
	return true
end
