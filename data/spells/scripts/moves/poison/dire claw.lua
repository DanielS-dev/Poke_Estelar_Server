local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 80/2

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 2
	pos.y = pos.y + 1
	for i = 1, 2 do
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_POISONDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doSendMagicEffect, i * 300, pos, 993)
	end
	return true
end
