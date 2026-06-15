local damage = 10

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
	for i = 0, 2 do
		addEvent(doTargetCombatHealth, i * 175, creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 233, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
