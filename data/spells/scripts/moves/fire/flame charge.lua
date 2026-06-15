local damage = 50
local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turrent", "porygon turret"}, target:getName():lower()) then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	addEvent(doSendMagicEffect, 150, creature:getPosition(), 920)
	addEvent(doTargetCombatHealth, 200, creature.uid, target.uid, COMBAT_FIREDAMAGE, damage, damage, 16, COMBAT_PHYSICALDAMAGE)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local condition = Condition(CONDITION_HASTE)
	condition:setParameter(CONDITION_PARAM_TICKS, 5000)
	condition:setFormula(0, (creature:getTotalSpeed() * 1.25), 0, (creature:getSpeed() * 1.25))
	creature:addCondition(condition)
	return true
end