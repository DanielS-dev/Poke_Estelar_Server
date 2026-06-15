local area = createCombatArea(AREA_CIRCLE2X2)
local damage = 65
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
	for i = 1, 10 do
		addEvent(doTargetCombatHealth, i * 150, creature.uid, target.uid, COMBAT_ROCKDAMAGE, damage/10, damage/10, 0)
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doSendMagicEffect(Position({x = creature:getPosition().x + 2, y = creature:getPosition().y + 1, z = creature:getPosition().z}), 1021) -- East slice
	doSendMagicEffect(Position({x = creature:getPosition().x + 1, y = creature:getPosition().y + 2, z = creature:getPosition().z}), 1044) -- South slice
	doSendMagicEffect(Position({x = creature:getPosition().x - 1, y = creature:getPosition().y + 1, z = creature:getPosition().z}), 1022) -- West slice
	doSendMagicEffect(Position({x = creature:getPosition().x + 1, y = creature:getPosition().y - 1, z = creature:getPosition().z}), 1023) -- North slice
	doAreaCombatHealth(creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	return true
end
