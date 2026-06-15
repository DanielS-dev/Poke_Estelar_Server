local damage = 60/3
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()	
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		addEvent(doSendDistanceShoot, 1000 + (i * 10), creature:getPosition(), place, 72)
	end
	addEvent(doAreaCombatHealth, 800, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 1100, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 1400, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	return true
end