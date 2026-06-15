local function doIngrain(creature, times)
	if not Creature(creature) then return false end
	creature = Creature(creature)
	doTargetCombatHealth(0, creature.uid, COMBAT_HEALING, creature:getMaxHealth() * 0.10, creature:getMaxHealth() * 0.10, 0)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:sendMagicEffect(712)
	local paralyze = Condition(CONDITION_PARALYZE)
	paralyze:setParameter(CONDITION_PARAM_TICKS, 1000)
	paralyze:setParameter(CONDITION_PARAM_SPEED, -1000)
	creature:addCondition(paralyze)
	if times < 10 then
		addEvent(doIngrain, 1000, creature.uid, times + 1)
	end
end

function onCastSpell(creature, variant)
	doIngrain(creature.uid, 1)
	return true
end

