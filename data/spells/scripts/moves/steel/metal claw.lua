local damage = 50/4

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_STEELDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doTargetCombatHealth, 250, creature.uid, creature:getTarget().uid, COMBAT_STEELDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doTargetCombatHealth, 500, creature.uid, creature:getTarget().uid, COMBAT_STEELDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doTargetCombatHealth, 750, creature.uid, creature:getTarget().uid, COMBAT_STEELDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	local pos = creature:getTarget():getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(819)
	if math.random(1, 100) <= 10 then
		local condition = Condition(CONDITION_ATTACKPLUS)
		condition:setTicks(5000)
		creature:addCondition(condition)
	end
	return true
end