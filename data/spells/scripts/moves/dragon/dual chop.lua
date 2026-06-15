local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 40

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 2
	pos.y = pos.y + 2
	for i = 0, 1 do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_DRAGONDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doSendMagicEffect, i * 500, pos, 1018)
	end
	return true
end
