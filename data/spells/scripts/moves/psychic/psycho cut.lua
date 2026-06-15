local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 70/2

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 2
	pos.y = pos.y + 1
	for i = 0, 1 do
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doSendMagicEffect, i * 300, pos, 992)
	end
	return true
end
