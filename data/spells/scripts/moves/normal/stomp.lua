local damage = 65
local area = createCombatArea(psy4)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(psy4))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	setConditionOn(creature.uid, target.uid, 'silence')
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, damage, damage, 238, COMBAT_PHYSICALDAMAGE)
	return true
end
