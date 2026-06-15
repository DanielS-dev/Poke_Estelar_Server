local damage = 60
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
	local conditions = getNegativeConditions(target)
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 151)
	if #conditions > 0 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_POISONDAMAGE, damage * 2, damage * 2, 1036, COMBAT_PHYSICALDAMAGE)
	else
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_POISONDAMAGE, damage, damage, 1036, COMBAT_PHYSICALDAMAGE)
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, 0, 0, 0)
	return true
end
