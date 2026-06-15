local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 50

function onCastSpell(creature, variant)
	for i = 0, 4 do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		local pos = creature:getPosition()
		pos.x = pos.x + 2
		pos.y = pos.y + 2
		addEvent(doSendMagicEffect, i * 500, pos, 1019)
	end
	return true
end
