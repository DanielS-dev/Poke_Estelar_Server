local dungeons = {{{x=621,y=714,z=15}, {x=581,y=714,z=15}, {x=541,y=714,z=15}}, {{x=621,y=711,z=15}, {x=581,y=711,z=15}, {x=541,y=711,z=15}}, {{x=621,y=699,z=15}, {x=581,y=699,z=15}, {x=541,y=699,z=15}}}
local config = {
	["mew dungeon"] = {poke = "Mew", action = 1, price = 100},
	["celebi dungeon"] = {poke = "Celebi", action = 2, price = 100},
	["jirachi dungeon"] = {poke = "Jirachi", action = 3, price = 100},
	["deoxys dungeon"] = {poke = "Deoxys", action = 4, price = 200},
	["darkrai dungeon"] = {poke = "Darkrai", action = 5, price = 300},
	["shaymin dungeon"] = {poke = "Shaymin", action = 6, price = 150},
	["arceus dungeon"] = {poke = "Arceus", action = 7, price = 300},
	["victini dungeon"] = {poke = "Victini", action = 8, price = 100},
	["keldeo dungeon"] = {poke = "Keldeo", action = 9, price = 100},
	["meloetta dungeon"] = {poke = "Meloetta", action = 10, price = 150},
	["genesect dungeon"] = {poke = "Genesect", action = 11, price = 200},
	["diancie dungeon"] = {poke = "Diancie", action = 12, price = 300},
	["hoopa dungeon"] = {poke = "Hoopa", action = 13, price = 300},
	["volcanion dungeon"] = {poke = "Volcanion", action = 14, price = 300},
	["magearna dungeon"] = {poke = "Magearna", action = 15, price = 300},
	["marshadow dungeon"] = {poke = "Marshadow", action = 16, price = 100},
	["zeraora dungeon"] = {poke = "Zeraora", action = 17, price = 100},
	["melmetal dungeon"] = {poke = "Melmetal", action = 18, price = 100},
	["zarude dungeon"] = {poke = "Zarude", action = 19, price = 300},
}
local checkpos = {x=719,y=785,z=5}

function onSay(player, words, param)
	if not param:split("|")[1] then return false end
	if not param:split("|")[2] then return false end
	if not isInArea(Position(checkpos), 1, 1, player.uid) then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce precisa estar perto do computador.")
		return false
	end
	local dungeon = param:split("|")[1]
	local size = tonumber(param:split("|")[2])
	
	if not config[dungeon] then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Esta dungeon nao existe.")
		return false
	end
	
	if player:getParty() then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Dungeons em grupo desativadas.")
		return false
	end
	
	if config[dungeon] then
		for i = 1, 3 do
			local multi = (config[dungeon].action * 40) - 40
			if not areaHasPlayer(Position(dungeons[3][i].x, dungeons[3][i].y + multi, dungeons[3][i].z), 15, 15) then
				if not player:removeTokens(config[dungeon].price) then
					player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tem "..config[dungeon].price.." tokens.")
					return false
				end
				cleanArea(Position(dungeons[1][i].x, dungeons[1][i].y + multi, dungeons[1][i].z), 9, 9)
				player:teleportTo(Position(dungeons[1][i].x, dungeons[1][i].y + multi, dungeons[1][i].z))
				if config[dungeon].poke == "Hoopa" then
					local monster = Game.createMonster(config[dungeon].poke, Position(dungeons[2][i].x, dungeons[2][i].y + multi, dungeons[2][i].z))
					local condition = Condition(CONDITION_OUTFIT)
					condition:setOutfit({lookType = 4026})
					condition:setTicks(-1)
					monster:addCondition(condition)
				else
					Game.createMonster(config[dungeon].poke, Position(dungeons[2][i].x, dungeons[2][i].y + multi, dungeons[2][i].z))
				end
				return false
			end
		end
	end -- last end
	return false
end