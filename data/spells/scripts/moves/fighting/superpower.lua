local damage = 120/5
local area = createCombatArea(AREA_CIRCLE3X3)

function onCastSpell(creature, variant)
	for i = 0, 4 do
		local pos = creature:getPosition()
		pos.x = pos.x + 3
		pos.y = pos.y + 2
		addEvent(doSendMagicEffect, i * 1000, pos, 1004)
		addEvent(doAreaCombatHealth, i * 1000, creature.uid, COMBAT_FIGHTINGDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
