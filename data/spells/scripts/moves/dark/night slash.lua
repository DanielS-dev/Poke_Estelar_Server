local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 70/2

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 2
	pos.y = pos.y + 1
	for i = 0, 1 do
		addEvent(doSendMagicEffect, i * 300, pos, 990)
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_DARKDAMAGE, creature:getPosition(), area, damage, damage, 0)
	end
	return true
end
