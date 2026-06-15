local damage = 50

function onCastSpell(creature, variant)
	if not target then return true end
	local target = creature:getTarget()
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	local types = {COMBAT_NORMALDAMAGE, COMBAT_FIREDAMAGE, COMBAT_WATERDAMAGE, COMBAT_ICEDAMAGE, COMBAT_ROCKDAMAGE}
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 101)
	addEvent(doTargetCombatHealth, 125, creature.uid, target.uid, types[math.random(1, 5)], damage, damage, 4)
	return true
end
