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
	local rangetm = 0
	local rangesketch = 0
	if #move < 12 then
		for i = #move + 1, 12 do
			local hastm = player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) or 0
			if hastm ~= 0 then
				local movie = {level = 1, isTarget = 1, range = 1, name = 1, speed = 1}
				movie.level = tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[3])
				movie.isTarget = tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[4])
				movie.range = tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[5])
				movie.name = player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[1]
				movie.speed = tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[2])
				table.insert(move, movie)
			end
		end
	end
	for i = 1, #moveWords do
		if words == moveWords[i] then			
			if move[i] then
				local hastm = player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) or 0
				local hassketch = player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) or 0
				local levelneeded = move[i].level
				if hastm ~= 0 then
					levelneeded = player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[3]
					levelneeded = tonumber(levelneeded)
				end
				if hassketch ~= 0  then
					levelneeded = player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[3]
					levelneeded = tonumber(levelneeded)
				end
				if levelneeded > player:getUsingBall():getSpecialAttribute("pokeLevel") then
					player:sendCancelMessage("Seu pokemon precisa ser do nivel "..levelneeded.." ou maior para usar este ataque.")
					player:getPosition():sendMagicEffect(CONST_ME_POFF)
					break
				end
				if hastm == 0 and hassketch == 0 then
					if move[i].isTarget == 1 and not target then
						player:sendCancelMessage("Sorry, not possible. You need a target.")
						player:getPosition():sendMagicEffect(CONST_ME_POFF)
						break
					end
				elseif hastm ~= 0 and hassketch == 0 then
					if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[4] == "1" and not target then
						player:sendCancelMessage("Sorry, not possible. You need a target.")
						player:getPosition():sendMagicEffect(CONST_ME_POFF)
						break
					end
					rangetm = tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[5]) or 0
				elseif hassketch ~= 0 and hastm == 0 then
					if player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[4] == "1" and not target then
						player:sendCancelMessage("Sorry, not possible. You need a target.")
						player:getPosition():sendMagicEffect(CONST_ME_POFF)
						break
					end
					rangesketch = tonumber(player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[5]) or 0
				end
				if target and move[i].isTarget == 1 and move[i].range ~= 0 and summon:getPosition():getDistance(target:getPosition()) > move[i].range then
					player:sendCancelMessage("Sorry, not possible. You are too far.")
					player:getPosition():sendMagicEffect(CONST_ME_POFF)
					break
				elseif target and hastm ~= 0 and rangetm ~= 0 and summon:getPosition():getDistance(target:getPosition()) > rangetm then
					player:sendCancelMessage("Sorry, not possible. You are too far.")
					player:getPosition():sendMagicEffect(CONST_ME_POFF)
					break
				elseif target and hassketch ~= 0 and rangesketch ~= 0 and summon:getPosition():getDistance(target:getPosition()) > rangesketch then
					player:sendCancelMessage("Sorry, not possible. You are too far.")
					player:getPosition():sendMagicEffect(CONST_ME_POFF)
					break
				end
				if getCreatureCondition(summon, CONDITION_SLEEP) and not isInArray({"Refresh"}, move[i].name) then
					player:sendCancelMessage("Sorry, not possible. Your pokemon is sleeping.")
					player:getPosition():sendMagicEffect(CONST_ME_POFF)
					break
				end
				if getCreatureCondition(summon, CONDITION_SILENCE) then
					player:sendCancelMessage("Sorry, not possible. Your pokemon is silenced.")
					player:getPosition():sendMagicEffect(CONST_ME_POFF)
					break
				end
				
				local speed = move[i].speed
				
				if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0 then
					speed = tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[2])
				end
				if player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) and player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) ~= 0 then
					speed = tonumber(player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[2])
				end
				
				local exhausted = player:checkMoveExhaustion(i, (speed / 1000) - 1)
				if not exhausted then
					local moveName = move[i].name
					
					if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0 then
						moveName = player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[1]
					end
					if player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) and player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) ~= 0 then
						moveName = player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[1]
					end
					doCreatureCastSpell(summon, moveName)
					player:say(summonName .. ", use " .. moveName .. "!", TALKTYPE_MONSTER_SAY)
					if isInArray({"Slaking", "Shiny Slaking", "Durant", "Shiny Durant"}, summonName) then
						local condition = Condition(CONDITION_SILENCE)
						condition:setTicks(2000)
						summon:addCondition(condition)
					end
				end
			else
				player:sendCancelMessage("Sorry, not possible.")
				player:getPosition():sendMagicEffect(CONST_ME_POFF)
				break
			end
		end
	end
	return false
end
