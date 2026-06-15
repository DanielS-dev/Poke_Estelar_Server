local area = createCombatArea(AREA_CIRCLE6X6)
local damage = 100/2

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		addEvent(doSendDistanceShoot, 1000 + (i * 10), creature:getPosition(), place, 123)
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, 1000 + (i * 10), place, 744)
		end
	end
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(933)
	addEvent(doAreaCombatHealth, 1000, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 1250, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 100) <= 50 then
		local defense = Condition(CONDITION_DEFENSEPLUS)
		defense:setParameter(CONDITION_PARAM_TICKS, 10000)
		creature:addCondition(defense)
	end
	return true
end