local damage = 80/2

local area = createCombatArea(AREA_CIRCLE6X6)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6))

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
		setConditionOn(creature.uid, target.uid, 'defense minus')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, 1000 + (i * 10), place, 1047)
		end
	end
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(1047)
	addEvent(doAreaCombatHealth, 1000, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1250, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end