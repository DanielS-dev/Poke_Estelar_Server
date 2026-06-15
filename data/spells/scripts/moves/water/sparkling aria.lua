local area = createCombatArea(AREA_CIRCLE3X3)	
local damage = 90

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE4X4))
combatEvent:setParameter(COMBAT_PARAM_AGGRESSIVE, false)

local condition = Condition(CONDITION_IMMUNE)
condition:setTicks(5000)

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if target:getCondition(CONDITION_FIRE) ~= nil then
		target:removeCondition(CONDITION_FIRE)
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area, damage, damage, 949)
	return true
end