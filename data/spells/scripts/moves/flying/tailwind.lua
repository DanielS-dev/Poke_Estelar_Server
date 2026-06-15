local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)	
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))
combatEvent:setParameter(COMBAT_PARAM_AGGRESSIVE, false)

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	local condition = Condition(CONDITION_HASTE)
	condition:setParameter(CONDITION_PARAM_TICKS, 5000)
	if creature:getMaster() then
		if target:getMaster() then
			if not isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) and target ~= creature then return false end
			if Player(getPlayerByName(target:getMaster():getName())):isDuelingWithNpc() and target ~= creature then return false end
			condition:setFormula(0, target:getTotalSpeed(), 0, target:getTotalSpeed())
			doSendDistanceShoot(creature:getPosition(), target:getPosition(), 127)
			target:getPosition():sendMagicEffect(1008)
		elseif target:isPlayer() then
			if not isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) and target ~= creature:getMaster() then return false end
			if Player(getPlayerByName(target:getName())):isDuelingWithNpc() and target ~= creature:getMaster() then return false end
			condition:setFormula(0, target:getSpeed(), 0, target:getSpeed())
			doSendDistanceShoot(creature:getPosition(), target:getPosition(), 127)
			target:getPosition():sendMagicEffect(1008)
		elseif not target:getMaster() then return false
		end
	else
		if target:getMaster() or target:isPlayer() then return false end
		condition:setFormula(0, target:getTotalSpeed(), 0, target:getTotalSpeed())
		doSendDistanceShoot(creature:getPosition(), target:getPosition(), 127)
		target:getPosition():sendMagicEffect(1008)
	end
	target:addCondition(condition)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	return true
end