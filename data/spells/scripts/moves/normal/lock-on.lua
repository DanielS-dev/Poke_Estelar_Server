local area = createCombatArea(AREA_CIRCLE5X5)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE5X5))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	if isInArray(legendaryPokemons, target:getName()) then return false end
	if isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turrent", "porygon turret"}, target:getName():lower()) then return false end
	doTeleportThing(target.uid, creature:getClosestFreePosition(creature:getPosition(), 1), true)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(524)
	local condition = Condition(CONDITION_ATTACKPLUS)
	condition:setTicks(5000)
	creature:addCondition(condition)
	return true
end
