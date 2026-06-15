local damage = 90/4

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
	if math.random(1, 100) <= 10 then
		setConditionOn(creature.uid, target.uid, 'burn')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	for i = 1, 100 do
		local topos = {x = creature:getPosition().x - math.random(10, 12), y = creature:getPosition().y - math.random(10, 12), z = creature:getPosition().z}
		local pos = {x = creature:getPosition().x - math.random(-6, 6), y = creature:getPosition().y - math.random(-3, 3), z = creature:getPosition().z}
		addEvent(doSendDistanceShoot, i * 10, creature:getPosition(), Position(topos), 4)
		addEvent(doSendDistanceShoot, 500 + (i * 30), Position(topos), Position(pos), 4)
		Position(pos):getNextPosition(1)
		Position(pos):getNextPosition(2)
		addEvent(doSendMagicEffect, 1250 + (i * 30), Position(pos), 761)
	end
	addEvent(doAreaCombatHealth, 1500, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 2250, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 3000, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 3750, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end
