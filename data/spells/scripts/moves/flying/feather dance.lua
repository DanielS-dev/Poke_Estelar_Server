local area = createCombatArea(AREA_CIRCLE2X2)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE2X2))
combatEvent:setParameter(COMBAT_PARAM_AGGRESSIVE, false)

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if not isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) and target ~= creature then return false end
			if Player(getPlayerByName(target:getMaster():getName())):isDuelingWithNpc() and target ~= creature then return false end
		elseif target:isPlayer() then
			if not isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) and target ~= creature:getMaster() then return false end
			if Player(getPlayerByName(target:getName())):isDuelingWithNpc() and target ~= creature:getMaster() then return false end
		end
	else
		if target:getMaster() or target:isPlayer() then return false end
	end
	setConditionOn(creature.uid, target.uid, 'attack minus')
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_FLYINGDAMAGE, creature:getPosition(), area, 0, 0, 0)
	local pos = creature:getPosition()
	pos:sendMagicEffect(1008)
	return true
end