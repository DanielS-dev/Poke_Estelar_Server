local damage = 110

local area = createCombatArea(AREA_MAGMA2)
local areadmg = createCombatArea(AREA_CIRCLE4X4)
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	if math.random(1, 100) <= 30 then
		setConditionOn(creature.uid, target.uid, 'paralyze')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	addEvent(doAreaCombatHealth, 250, creature.uid, COMBAT_ELECTRICDAMAGE, pos, area, 0, 0, 492)
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_ELECTRICDAMAGE, creature:getPosition(), areadmg, damage, damage, 0)
	return true
end
