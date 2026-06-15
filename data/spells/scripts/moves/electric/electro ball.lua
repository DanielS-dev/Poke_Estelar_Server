local damage = 0

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
	local myspeed = creature:getTotalSpeed()
	local theirspeed = target:getTotalSpeed()
	damage = myspeed / theirspeed
	if damage >= 4 then
		damage = 150
	elseif damage < 4 and damage >= 3 then
		damage = 120
	elseif damage < 3 and damage >= 2 then
		damage = 80
	elseif damage < 2 and damage >= 1 then
		damage = 60
	elseif damage < 1 then
		damage = 40
	end
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 105)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_ELECTRICDAMAGE, damage, damage, 381)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, 0, 0, 0)
	return true
end