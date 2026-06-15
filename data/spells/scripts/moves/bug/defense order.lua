function onCastSpell(creature, variant)
	for i = 0, 10 do
		local pos = {x = creature:getPosition().x + math.random(-2, 2), y = creature:getPosition().y + math.random(-2, 2), z = creature:getPosition().z}
		addEvent(doSendDistanceShoot, i * 25, Position(pos), creature:getPosition(), 196)
	end
	creature:getPosition():sendMagicEffect(693)
	local condition = Condition(CONDITION_DEFENSEPLUS)
	condition:setTicks(5000)
	creature:addCondition(condition)
	return true
end
