local damage = 60

local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)	
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	setConditionOn(creature.uid, target.uid, 'burn')
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 100)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIREDAMAGE, damage, damage, 408)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, 0, 0, 0)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(764)
	return true
end
