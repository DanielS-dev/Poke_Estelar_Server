local damage = 130/5
local area = createCombatArea(AREA_CIRCLE3X3)

function onCastSpell(creature, variant)
	for i = 0, 4 do
		local pos = creature:getPosition()
		pos.x = pos.x + 2
		pos.y = pos.y + 2
		addEvent(doSendMagicEffect, i * 1000, pos, 1006)
		addEvent(doAreaCombatHealth, i * 1000, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0)
	end
	return true
end
