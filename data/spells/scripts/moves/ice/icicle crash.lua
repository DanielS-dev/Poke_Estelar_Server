local damage = 85/2
local area = createCombatArea(AREA_CIRCLE5X5)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE5X5))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	if math.random(1, 100) <= 30 then
		setConditionOn(creature.uid, target.uid, 'silence')
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
			addEvent(doSendMagicEffect, 10 + (i * 10), place, 756)
		end
	end
	addEvent(doAreaCombatHealth, 200, creature.uid, COMBAT_ICEDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	addEvent(doAreaCombatHealth, 450, creature.uid, COMBAT_ICEDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	return true
end