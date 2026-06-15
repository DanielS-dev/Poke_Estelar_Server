local damage = 50
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			addEvent(doSendMagicEffect, i * 10, place, 1093)
		end
	end
	addEvent(doAreaCombatHealth, 350, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end