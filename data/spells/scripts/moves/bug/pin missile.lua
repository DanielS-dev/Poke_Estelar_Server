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
	for i = 0, math.random(1, 4) do
		addEvent(doSendDistanceShoot, i * 150, creature:getPosition(), target:getPosition(), 72)
		addEvent(doTargetCombatHealth, i * 175, creature.uid, target.uid, COMBAT_BUGDAMAGE, damage, damage, 10, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
