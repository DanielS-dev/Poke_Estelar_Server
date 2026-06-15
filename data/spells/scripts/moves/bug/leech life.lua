local damage = 80
local area = createCombatArea(AREA_CIRCLE3X3)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE3X3))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 74)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_BUGDAMAGE, damage, damage, 442, COMBAT_PHYSICALDAMAGE)
	addEvent(doSendDistanceShoot, 200, target:getPosition(), creature:getPosition(), 133)
	addEvent(doTargetCombatHealth, 200, 0, creature.uid, COMBAT_HEALING, damage, damage, 252)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, 0, 0, 0)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(844)
	return true
end
