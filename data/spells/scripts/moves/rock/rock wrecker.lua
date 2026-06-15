local damage = 150/3
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			addEvent(doSendMagicEffect, i * 10, place, 349)
		end
	end
	addEvent(doAreaCombatHealth, 250, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	return true
end