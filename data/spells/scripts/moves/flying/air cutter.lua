local damage = 60/2
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, 10 + (i * 10), place, 251)
		end
	end
	addEvent(doAreaCombatHealth, 200, creature.uid, COMBAT_FLYINGDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 450, creature.uid, COMBAT_FLYINGDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end
