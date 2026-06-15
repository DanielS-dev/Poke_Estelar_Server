local damage = 100/4
local area = createCombatArea(AREA_CIRCLE5X5)

function onCastSpell(creature, variant)
	for i = 1, 100 do
		local topos = {x = creature:getPosition().x - math.random(10, 12), y = creature:getPosition().y - math.random(10, 12), z = creature:getPosition().z}
		local pos = {x = creature:getPosition().x - math.random(-6, 6), y = creature:getPosition().y - math.random(-3, 3), z = creature:getPosition().z}
		addEvent(doSendDistanceShoot, 500 + (i * 30), Position(topos), Position(pos), 37)
		Position(pos):getNextPosition(1)
		Position(pos):getNextPosition(2)
		addEvent(doSendMagicEffect, 1250 + (i * 30), Position(pos), 499)
	end
	addEvent(doAreaCombatHealth, 1500, creature.uid, COMBAT_ICEDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 2250, creature.uid, COMBAT_ICEDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 3000, creature.uid, COMBAT_ICEDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 3750, creature.uid, COMBAT_ICEDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	return true
end