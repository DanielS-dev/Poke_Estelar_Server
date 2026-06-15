local damage = 30
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
	if math.random(1, 100) <= 40 then
		setConditionOn(creature.uid, target.uid, 'poison')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local position = creature:getPosition()
	doAreaCombatHealth(creature.uid, COMBAT_POISONDAMAGE, creature:getPosition(), area, damage, damage, 705)
	return true
end
