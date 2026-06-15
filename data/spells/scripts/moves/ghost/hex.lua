local damage = 65
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
	if #conditions > 0 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_GHOSTDAMAGE, damage * 2, damage * 2, 569)
	else
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_GHOSTDAMAGE, damage, damage, 607)
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos:sendMagicEffect(479)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, 0, 0, 0)
	return true
end
