local area = {createCombatArea(AREA_SOUND4), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND1)}
local areadmg = createCombatArea(AREA_CIRCLE4X4)
local damage = 90/4

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE4X4))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	setConditionOn(creature.uid, target.uid, 'defense minus')
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	for i = 1, #area do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_GROUNDDAMAGE, creature:getPosition(), areadmg, damage, damage, 0)
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_GROUNDDAMAGE, pos, area[i], 0, 0, 706)
	end
	return true
end
