local area = createCombatArea(AREA_CIRCLE2X2)	
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))
combatEvent:setParameter(COMBAT_PARAM_AGGRESSIVE, false)

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if not isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) and target ~= creature then return false end
			if Player(getPlayerByName(target:getMaster():getName())):isDuelingWithNpc() and target ~= creature then return false end
		elseif target:isPlayer() then
			if not isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) and target ~= creature:getMaster() then return false end
			if Player(getPlayerByName(target:getName())):isDuelingWithNpc() and target ~= creature:getMaster() then return false end
		elseif not target:getMaster() then return false
		end
	else
		if target:getMaster() or target:isPlayer() then return false end
	end
	doTargetCombatHealth(0, target.uid, COMBAT_HEALING, target:getMaxHealth(), target:getMaxHealth(), 946)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, 0, 0, 510)
	local pos = creature:getPosition()
	local bixo = Creature(creature)
	if creature:getHealth() > 0 then
		if isSummon(creature) then
			bixo:setHealth(0)
			bixo:getMaster():getUsingBall():setSpecialAttribute("pokeHealth", 0)
			doRemoveSummon(bixo:getMaster():getId(), false, false, false)
		else
			bixo:setHealth(0)
		end
	end
end
