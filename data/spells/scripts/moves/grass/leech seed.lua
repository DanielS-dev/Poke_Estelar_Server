local combat = Combat()
combat:setArea(createCombatArea(AREA_CIRCLE6X6))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	setConditionOn(creature.uid, target.uid, 'seed')
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 60)
	target:getPosition():sendMagicEffect(CONST_ME_SMALLPLANTS)
	return true
end

combat:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combat:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, 0, 0, 0)
	local pos = creature:getPosition()
	pos:sendMagicEffect(46)
	return true
end