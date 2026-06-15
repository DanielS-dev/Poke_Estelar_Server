local damage = 50
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
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 74)
	local effpos = target:getPosition()
	effpos:getNextPosition(1)
	effpos:getNextPosition(2)
	doAreaCombatHealth(creature.uid, COMBAT_BUGDAMAGE, target:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	doAreaCombatHealth(creature.uid, COMBAT_BUGDAMAGE, effpos, area, 0, 0, 831, COMBAT_PHYSICALDAMAGE)
	return true
end
