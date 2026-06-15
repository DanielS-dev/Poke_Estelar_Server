local damage = 120/3
local area = createCombatArea(AREA_CIRCLE6X6)
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
		if creature:getMaster():getFreeCapacity() >= 1 and not getTileInfo(getThingPos(creature.uid)).pvp then
			if math.random(1, 100) <= 5 then
				creature:getMaster():addItem(2152, math.random(5, 10))
			else
				creature:getMaster():addItem(2152, math.random(1, 3))
			end
		end
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()	
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		addEvent(doSendDistanceShoot, 250 + (i * 10), creature:getPosition(), place, 197)
		if math.random(1, 2) == 1 then
			addEvent(doSendMagicEffect, 250 + (i * 10), place, 4)
		end
	end
	addEvent(doAreaCombatHealth, 150, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 450, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end