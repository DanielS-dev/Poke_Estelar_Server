function onCastSpell(creature, variant)
	creature:getPosition():sendMagicEffect(683)
	if creature:getName() == "Castform" then
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = 3437})
		creature:addCondition(condition)
	end
	if creature:getCondition(CONDITION_FIRE) ~= nil then
		doRemoveCondition(creature.uid, CONDITION_FIRE)
	end
	if creature:getCondition(CONDITION_POISON) ~= nil then
		doRemoveCondition(creature.uid, CONDITION_POISON)
	end
	if creature:getCondition(CONDITION_FREEZING) ~= nil then
		doRemoveCondition(creature.uid, CONDITION_FREEZING)
	end
	if creature:getCondition(CONDITION_PARALYZE) ~= nil then
		doRemoveCondition(creature.uid, CONDITION_PARALYZE)
	end
	if creature:getCondition(CONDITION_SLEEP) ~= nil then
		doRemoveCondition(creature.uid, CONDITION_SLEEP)
	end
	if isInArray(hiddenabilities.raindish, creature:getName()) then
		local condition = Condition(CONDITION_FOCUS)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addHealth(creature:getMaxHealth() * 0.25)
	end
	if isInArray(hiddenabilities.swiftswim, creature:getName()) then
		local speed = Condition(CONDITION_HASTE)
		speed:setParameter(CONDITION_PARAM_TICKS, 5000)
		speed:setFormula(0, creature:getTotalSpeed(), 0, creature:getTotalSpeed())
		creature:addCondition(speed)
		Game.sendAnimatedText(creature:getPosition(), "SPEED UP", TEXTCOLOR_WHITE)
	end
	if MonsterType(creature:getName()):getRaceName() == "water" or MonsterType(creature:getName()):getRace2Name() == "water" then
		local condition = Condition(CONDITION_FOCUS)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addCondition(condition)
		Game.sendAnimatedText(creature:getPosition(), "FOCUS", TEXTCOLOR_WHITE)
	end
	if creature:getName() == "Castform" then
		local condition = Condition(CONDITION_OUTFIT)
		condition:setTicks(-1)
		condition:setOutfit({lookType = 3437})
		creature:addCondition(condition)
	end
	return true
end