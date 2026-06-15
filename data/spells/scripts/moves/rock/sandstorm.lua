function onCastSpell(creature, variant)
	creature:getPosition():sendMagicEffect(416)
	if isInArray(hiddenabilities.sandforce, creature:getName()) then
		local condition = Condition(CONDITION_EVASION)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addCondition(condition)
		Game.sendAnimatedText(creature:getPosition(), "EVASION UP", TEXTCOLOR_WHITE)
	end
	if isInArray(hiddenabilities.sandveil, creature:getName()) then
		local condition = Condition(CONDITION_FOCUS)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addCondition(condition)
		Game.sendAnimatedText(creature:getPosition(), "FOCUS", TEXTCOLOR_WHITE)
	end
	if MonsterType(creature:getName()):getRaceName() == "rock" or MonsterType(creature:getName()):getRace2Name() == "rock" then
		local condition = Condition(CONDITION_DEFENSEPLUS)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		creature:addCondition(condition)
		Game.sendAnimatedText(creature:getPosition(), "DEFENSE UP", TEXTCOLOR_WHITE)
	end
	return true
end