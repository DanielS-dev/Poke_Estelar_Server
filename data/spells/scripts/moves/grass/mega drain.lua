local area = createCombatArea(AREA_SOUND1)
local damage = 40

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_1X1_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_GRASSDAMAGE, damage, damage, 15)
	doTargetCombatHealth(0, creature.uid, COMBAT_HEALING, creature:getMaxHealth() * 0.05, creature:getMaxHealth() * 0.05, 504)
	
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_POISONDAMAGE, creature:getPosition(), area, 0, 0, 15)
	return true
end
