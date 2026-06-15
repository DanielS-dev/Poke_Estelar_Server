local damage = 25

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local target = creature:getTarget()
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	if target:getCondition(CONDITION_POISON) ~= nil then
		doSendDistanceShoot(creature:getPosition(), target:getPosition(), 15)
		for i = 0, 9 do
			addEvent(doTargetCombatHealth, i * 1000, creature.uid, target.uid, COMBAT_POISONDAMAGE, damage, damage, 9)
		end
	else
		doSendDistanceShoot(creature:getPosition(), target:getPosition(), 15)
		setConditionOn(creature.uid, target.uid, 'poison')
	end
	return true
end
