function onSay(player, words, param)
	local summon = player:getSummon()
	if not summon then
		player:sendCancelMessage("Sorry, not possible. You need a summon to conjure spells.")
		player:getPosition():sendMagicEffect(CONST_ME_POFF)
		return false
	end

	local tile = Tile(player:getPosition())
	if tile:hasFlag(TILESTATE_PROTECTIONZONE) then
		player:sendCancelMessage("Sorry, not possible in protection zone.")
		player:getPosition():sendMagicEffect(CONST_ME_POFF)
		return false
	end

	local summonName = summon:getName()
	local monsterType = MonsterType(summonName)
	local move = monsterType:getMoveList()
	local target = summon:getTarget()
	
	for i = 1, #moveWords do		
			if move[i] then
				local verify = 0
				local istarget = player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) or 0
				if istarget ~= 0 then
					istarget = player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[3]
				end
				if (move[i].isTarget == 1 and not target) or (istarget == "1" and not target) then
					verify = 1
				end
				if target and move[i].isTarget == 1 and move[i].range ~= 0 and summon:getPosition():getDistance(target:getPosition()) > move[i].range then
					verify = 1
				end
				if getCreatureCondition(summon, CONDITION_SLEEP) then
					verify = 1
				end
				
				local speed = move[i].speed
				
				if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) then
					speed = tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[2])
				end
				
				local exhausted = player:checkMoveExhaustion(i, speed / 1000)
				if not exhausted then
					local moveName = move[i].name
					
					if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) then
						moveName = player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[1]
					end
					if verify == 0 then
						doCreatureCastSpell(summon, moveName)
						player:say(summonName .. ", use " .. moveName .. "!", TALKTYPE_MONSTER_SAY)
					end
				end
			else
				return false
			end
	end
	return false
end
