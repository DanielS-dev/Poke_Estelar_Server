local damage = 50/3
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()	
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, i * 10, place, 903)
		end
	end
	addEvent(doAreaCombatHealth, 250, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	if math.random(1, 100) <= 70 then
		local attackup = Condition(CONDITION_ATTACKPLUS)
		attackup:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addCondition(attackup)
	end
	return true
end