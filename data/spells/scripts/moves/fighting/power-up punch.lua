local damage = 40

function onCastSpell(creature, variant)
	local target = creature:getTarget()
	if not target then return true end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	local targetPosition = target:getPosition()
	doTargetCombatHealth(creature.uid, target, COMBAT_FIGHTINGDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	targetPosition:getNextPosition(1)
	targetPosition:getNextPosition(2)
	targetPosition:sendMagicEffect(767)
	local condition = Condition(CONDITION_ATTACKPLUS)
	condition:setParameter(CONDITION_PARAM_TICKS, 5000)
	creature:addCondition(condition)
	return true
end

