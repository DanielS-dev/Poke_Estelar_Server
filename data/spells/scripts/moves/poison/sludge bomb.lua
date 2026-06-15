local damage = 90
local area = createCombatArea(AREA_SQUARE1X1)

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
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 39)
	doAreaCombatHealth(creature.uid, COMBAT_POISONDAMAGE, target:getPosition(), area, damage, damage, 521)
	if math.random(1, 100) <= 30 then
		setConditionOn(creature.uid, target.uid, 'poison')
	end
	return true
end
