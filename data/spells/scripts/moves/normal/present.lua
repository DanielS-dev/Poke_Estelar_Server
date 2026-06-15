local area = createCombatArea(AREA_CIRCLE2X2)

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
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 154)
	local chance = math.random(1, 100)
	local damage = 1
	if chance <= 15 then
		damage = 120
	elseif chance <= 50 then
		damage = 80
	else
		damage = 40
	end
	doAreaCombatHealth(creature.uid, COMBAT_BUGDAMAGE, target:getPosition(), area, damage, damage, 916, COMBAT_PHYSICALDAMAGE)
	return true
end
