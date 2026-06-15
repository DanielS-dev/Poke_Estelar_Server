local area = createCombatArea(AREA_CIRCLE6X6)
local damage = 60/2

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		addEvent(doSendDistanceShoot, 1000 + (i * 10), creature:getPosition(), place, 118)
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, 1000 + (i * 10), place, 831)
		end
	end
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(821)
	addEvent(doAreaCombatHealth, 1000, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1250, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0)
	if math.random(1, 100) <= 10 then
		local attack = Condition(CONDITION_ATTACKPLUS)
		attack:setParameter(CONDITION_PARAM_TICKS, 5000)
		local defense = Condition(CONDITION_DEFENSEPLUS)
		defense:setParameter(CONDITION_PARAM_TICKS, 5000)
		local speed = Condition(CONDITION_HASTE)
		speed:setParameter(CONDITION_PARAM_TICKS, 5000)
		speed:setFormula(0, creature:getTotalSpeed(), 0, creature:getTotalSpeed())
		creature:addCondition(attack)
		creature:addCondition(defense)
		creature:addCondition(speed)
	end
	return true
end