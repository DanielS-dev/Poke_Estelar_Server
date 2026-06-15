local damage = 90

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
		setConditionOn(creature.uid, target.uid, 'paralyze')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		local frompos = Position(place)
		frompos.x = frompos.x - 5
		frompos.y = frompos.y - 5
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendDistanceShoot, i * 5, frompos, place, 93)
			addEvent(doSendMagicEffect, i * 10, place, 820)
		end
	end
	addEvent(doAreaCombatHealth, 250, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end