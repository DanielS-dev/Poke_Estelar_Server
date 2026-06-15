local damage = 90/3
local area = createCombatArea(AREA_CIRCLE1X1)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE5X5))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if target:getCondition(CONDITION_SLEEP) ~= nil then
		target:removeCondition(CONDITION_SLEEP)
		target:getPosition():sendMagicEffect(13)
	elseif creature:getCondition(CONDITION_SLEEP) ~= nil then
		creature:removeCondition(CONDITION_SLEEP)
		creature:getPosition():sendMagicEffect(13)
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	for i = 1, 3 do
		addEvent(doAreaCombatHealth, i * 333, creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, damage, damage, 25)
	end
	return true
end