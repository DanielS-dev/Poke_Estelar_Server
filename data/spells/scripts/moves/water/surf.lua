local area = createCombatArea(AREA_CIRCLE6X6)
local damage = 90/3

function onCastSpell(creature, variant)
	local pos = creature:getPosition()	
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			addEvent(doSendMagicEffect, 300 + (i * 10), place, 1039)
		end
	end
	addEvent(doAreaCombatHealth, 800, creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1100, creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1400, creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end