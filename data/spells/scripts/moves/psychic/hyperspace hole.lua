local damage = 80
local area = createCombatArea(AREA_CIRCLE2X2)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE2X2))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	if target:getCondition(CONDITION_IMMUNE) ~= nil then target:removeCondition(CONDITION_IMMUNE) end
	if target:getCondition(CONDITION_REFLECT) ~= nil then target:removeCondition(CONDITION_REFLECT) end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, damage, damage, 0)
	local pos = creature:getPosition()
	pos.x = pos.x + 3
	pos.y = pos.y + 2
	pos:sendMagicEffect(1003)
	return true
end
