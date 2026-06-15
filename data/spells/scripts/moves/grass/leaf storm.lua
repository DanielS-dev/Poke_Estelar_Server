local damage = 130/3
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()	
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		addEvent(doSendDistanceShoot, 250 + (i * 10), creature:getPosition(), place, 63)
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			addEvent(doSendMagicEffect, 250 + (i * 10), place, 407)
		end
	end
	addEvent(doAreaCombatHealth, 150, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 450, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end