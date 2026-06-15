local damage = 40
local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turrent", "porygon turret"}, target:getName():lower()) then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	addEvent(doSendMagicEffect, 150, creature:getPosition(), 331)
	addEvent(doTargetCombatHealth, 200, creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 10, COMBAT_PHYSICALDAMAGE)
	addEvent(doSendDistanceShoot, 175, target:getPosition(), creature:getClosestFreePosition(creature:getPosition(), 1), 131)
	if not isInArray(legendaryPokemons, target:getName()) then addEvent(doTeleportThing, 175, target.uid, creature:getClosestFreePosition(creature:getPosition(), 1), true) end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(767)
	return true
end