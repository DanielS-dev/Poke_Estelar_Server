local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 100/2

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	for i = 1, 2 do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_FIGHTINGDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doSendMagicEffect, i * 500, pos, 611)
	end
	return true
end
