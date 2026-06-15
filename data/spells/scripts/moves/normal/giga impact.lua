local damage = 150/2
local area = createCombatArea(AREA_CIRCLE2X2_2)

function onCastSpell(creature, variant)
	for i = 0, 1 do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, damage, damage, 238, COMBAT_PHYSICALDAMAGE)
	end
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(247)
	return true
end
