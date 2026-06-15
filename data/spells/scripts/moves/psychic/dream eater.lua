local damage = 100
local area = createCombatArea(AREA_CIRCLE3X3)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE3X3))

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
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_PSYCHICDAMAGE, damage, damage, 259)
		doTargetCombatHealth(0, creature.uid, COMBAT_HEALING, damage, damage, 252)
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
