local damage = 150/3
local area = createCombatArea(AREA_CIRCLE4X4)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, i * 10, place, 823)
		end
	end
	addEvent(doAreaCombatHealth, 250, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end