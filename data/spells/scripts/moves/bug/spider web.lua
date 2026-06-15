local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_3X3_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	local pos = creature:getClosestFreePosition(creature:getPosition(), 1)
	if isInArray(legendaryPokemons, target:getName()) then return false end
	if isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turrent", "porygon turret"}, target:getName():lower()) then return false end
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 116)
	doSendDistanceShoot(target:getPosition(), pos, 116)
	target:teleportTo(pos, true)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	return true
end