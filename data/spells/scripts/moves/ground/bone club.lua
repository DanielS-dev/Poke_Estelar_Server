local damage = 65

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_GROUNDDAMAGE, damage, damage, 237, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 100) <= 10 then
		setConditionOn(creature.uid, creature:getTarget().uid, 'silence')
	end
	return true
end

