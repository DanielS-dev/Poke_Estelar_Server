local damage = 90

local area = createCombatArea(AREA_CIRCLE3X3)
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE3X3))

local condition = Condition(CONDITION_ATTACKPLUS)
condition:setParameter(CONDITION_PARAM_TICKS, 5000)

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_STEELDAMAGE, 0, 0, 279, COMBAT_PHYSICALDAMAGE)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_STEELDAMAGE, damage, damage, 466, COMBAT_PHYSICALDAMAGE)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, 0, 0, 0)
	if math.random(1, 100) <= 20 then
		creature:addCondition(condition)
		creature:getPosition():sendMagicEffect(757)
	end
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(823)
	return true
end