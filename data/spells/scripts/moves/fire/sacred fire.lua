local area = createCombatArea(AREA_CIRCLE2X2)
local damage = 100/2

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_2X2_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	if math.random(1, 2) == 1 then
		setConditionOn(creature.uid, target.uid, 'burn')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-3, 3), y = pos.y + math.random(-2, 2), z = pos.z}
		addEvent(doSendDistanceShoot, 1000 + (i * 10), creature:getPosition(), place, 100)
		if math.random(1, 2) == 1 then
			addEvent(doSendMagicEffect, 1000 + (i * 10), place, 408)
		end
	end
	pos:sendMagicEffect(402)
	addEvent(doAreaCombatHealth, 1000, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1250, creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end