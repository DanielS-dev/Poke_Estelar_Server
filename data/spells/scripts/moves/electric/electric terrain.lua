local area = createCombatArea(AREA_CIRCLE5X5)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE5X5))

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
	if MonsterType(target:getName()):getRaceName() == "electric" or MonsterType(target:getName()):getRace2Name() == "electric" then
		local condition = Condition(CONDITION_ATTACKPLUS)
		condition:setTicks(5000)
		if isInArray(hiddenabilities.clearbody, target:getName()) then
			target:getPosition():sendMagicEffect(13)
		else
			target:addCondition(condition)
			target:getPosition():sendMagicEffect(343)
		end
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, 0, 0, 327)
	return true
end
