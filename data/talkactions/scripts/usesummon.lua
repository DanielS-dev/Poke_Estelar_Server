

function onSay(player, words, param)
	if player:isSummonBlocked() then return false end

	local index = tonumber(param)
	if not index then return false end
	local exhaust = Condition(CONDITION_EXHAUST_WEAPON)
	if player:isDuelingWithNpc() then
		exhaust:setParameter(CONDITION_PARAM_TICKS, 10000)
	else
		exhaust:setParameter(CONDITION_PARAM_TICKS, 1000)
	end
	if player:getCondition(CONDITION_EXHAUST_WEAPON) then
		player:sendTextMessage(MESSAGE_STATUS_SMALL, Game.getReturnMessage(RETURNVALUE_YOUAREEXHAUSTED))
		return false
	end
	
	local pokeballs = player:getPokeballs()
	local ball = pokeballs[index]
--	local ball = player:getSpecialStorage("pokes")[index]

	if not ball then
		print("WARNING! Player " .. player:getName() .. " had problems trying to use pokebar: selected ball not found.")
		player:refreshPokemonBar({}, {})
		return false
	end

	if player:canReleaseSummon(ball:getSummonLevel(), ball:getSummonBoost(), ball:getSummonOwner()) then
		if hasSummons(player) then
			local usingBall = player:getUsingBall()
			if not usingBall then
				print("WARNING! Player " .. player:getName() .. " had problems trying to use pokebar: doRemoveSummon.")
				player:refreshPokemonBar({}, {})
				return false
			end
			if usingBall:getId() == ball:getId() then
				local usingBallKey = getBallKey(usingBall:getId())
				doRemoveSummon(player:getId(), balls[usingBallKey].effectRelease, false, true, balls[usingBallKey].missile)
				usingBall:transform(balls[usingBallKey].usedOn)
				player:addCondition(exhaust)
				return false
			end
			local usingBallKey = getBallKey(usingBall:getId())
			doRemoveSummon(player:getId(), balls[usingBallKey].effectRelease, false, true, balls[usingBallKey].missile)
			usingBall:transform(balls[usingBallKey].usedOn)
			player:addCondition(exhaust)
		end

		local ballKey = getBallKey(ball:getId())
		ball:transform(balls[ballKey].usedOff)
		ball:setSpecialAttribute("isBeingUsed", 1)
		doReleaseSummon(player:getId(), player:getPosition(), balls[ballKey].effectRelease, true, balls[ballKey].missile)
		player:addCondition(exhaust)
	end

	return false
end
