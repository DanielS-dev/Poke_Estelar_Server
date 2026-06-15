local damage = 100
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
	if target:getCondition(CONDITION_SLEEP) ~= nil then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_GHOSTDAMAGE, damage, damage, 930)
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, 0, 0, 0)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(1019)
	return true
end