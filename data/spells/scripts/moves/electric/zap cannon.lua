local damage = 120/3
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()	
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		addEvent(doSendDistanceShoot, 1000 + (i * 10), creature:getPosition(), place, 102)
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			addEvent(doSendMagicEffect, 1000 + (i * 10), place, 847)
		end
	end
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(898)
	addEvent(doAreaCombatHealth, 800, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1100, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1400, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end