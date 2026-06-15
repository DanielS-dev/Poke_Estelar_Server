local area = createCombatArea(AREA_CIRCLE2X2)
local damage = 80/2

function onCastSpell(creature, variant)
	for i = 0, 1 do
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_DRAGONDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		local pos = creature:getPosition()
		pos.x = pos.x + 2
		pos.y = pos.y + 1
		addEvent(doSendMagicEffect, i * 300, pos, 900)
	end
	return true
end
