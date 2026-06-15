local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)	
local damage = 80

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
	target:getPosition():sendMagicEffect(708)
	local pos = creature:getClosestFreePosition(creature:getPosition(), 1)
	addEvent(doTeleportThing, 450, target.uid, pos, true)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 2
	pos.y = pos.y + 1
	pos:sendMagicEffect(709)
	doAreaCombatHealth(creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	return true
end