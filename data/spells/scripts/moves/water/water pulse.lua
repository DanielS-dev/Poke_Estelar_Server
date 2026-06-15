local damage = 60
local area = createCombatArea(AREA_CIRCLE2X2_2)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE2X2))

local condition = Condition(CONDITION_DRUNK)
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
	if math.random(1, 100) <= 20 then
		setConditionOn(creature.uid, target.uid, 'confusion')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area, damage, damage, 423)
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_WATERDAMAGE, creature:getPosition(), area, 0, 0, 750)
	return true
end
