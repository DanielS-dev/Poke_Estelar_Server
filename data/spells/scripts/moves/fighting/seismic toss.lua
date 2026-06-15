local area = createCombatArea(AREA_CIRCLE2X2)

function onCastSpell(creature, variant)
	if not creature:getTarget() then return false end
	local target = creature:getTarget()
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	target:getPosition():sendMagicEffect(331)
	doHide(target.uid, true)
	addEvent(doHide, 3000, target.uid, false)
	addEvent(doTargetCombatHealth, 3001, creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, creature:getLevel(), creature:getLevel(), 0, COMBAT_PHYSICALDAMAGE)
	local pos = target:getPosition()
	pos:getNextPosition(1)
	addEvent(doSendMagicEffect, 3001, pos, 706)
	return true
end