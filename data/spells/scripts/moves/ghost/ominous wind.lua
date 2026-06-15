local damage = 60/3
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-5, 5), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 5) == 1 then
			place.x = place.x + 3
			place.y = place.y + 2
			addEvent(doSendMagicEffect, i * 10, place, 972)
		end
	end
	addEvent(doAreaCombatHealth, 250, creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1250, creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, damage, damage, 0)
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