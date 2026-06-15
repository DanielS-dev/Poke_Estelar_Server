local damage = 50
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
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 67)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_GROUNDDAMAGE, damage, damage, 237, COMBAT_PHYSICALDAMAGE)
	if math.random(1, 100) <= 10 then
		setConditionOn(creature.uid, target.uid, 'defense minus')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	return true
end