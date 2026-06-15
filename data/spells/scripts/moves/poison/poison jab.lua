local damage = 15

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
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_POISONDAMAGE, damage, damage, 1036, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 100) <= 30 then
		setConditionOn(creature.uid, target.uid, 'poison')
	end
	return true
end

