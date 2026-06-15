local damage = 150/3
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, 300 + (i * 10), place, 904)
		end
	end
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 900, creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1300, creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, damage, damage, 0)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(904)
	return true
	
end