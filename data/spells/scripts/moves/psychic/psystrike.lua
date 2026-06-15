local damage = 100/4

local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)	

function onCastSpell(creature, variant)
	for i = 1, 100 do
		local topos = {x = creature:getPosition().x - math.random(10, 12), y = creature:getPosition().y - math.random(10, 12), z = creature:getPosition().z}
		local pos = {x = creature:getPosition().x - math.random(-6, 6), y = creature:getPosition().y - math.random(-3, 3), z = creature:getPosition().z}
		addEvent(doSendDistanceShoot, i * 10, creature:getPosition(), Position(topos), 172)
		addEvent(doSendDistanceShoot, 500 + (i * 30), Position(topos), Position(pos), 172)
		pos.x = pos.x + 3
		pos.y = pos.y + 3
		addEvent(doSendMagicEffect, 1150 + (i * 30), Position(pos), 1000)
	end
	addEvent(doAreaCombatHealth, 1500, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 2250, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 3000, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 3750, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end
