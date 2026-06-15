local carpets = {38975, 38977, 38979, 38981, 38983, 38985, 38987, 38989, 38991, 38993, 38995, 38997, 38999, 39001, 39003, 39005, 39007, 39009, 39011, 39013, 39015, 39017, 39019, 39021, 39023, 39025, 39027, 39029, 39031, 39033, 39035, 39037, 39039, 39041, 39043}
local rolled = {38974, 38976, 38978, 38980, 38982, 38984, 38986, 38988, 38990, 38992, 38994, 38996, 38998, 39000, 39002, 39004, 39006, 39008, 39010, 39012, 39014, 39016, 39018, 39020, 39022, 39024, 39026, 39028, 39030, 39032, 39034, 39036, 39038, 39040, 39042}

function onSay(player, words, param)
    local positions = player:getPosition()

    if player:getDirection() == 0 then
        positions = {x=positions.x, y=positions.y-1, z=positions.z}
    elseif player:getDirection() == 1 then
        positions = {x=positions.x+1, y=positions.y, z=positions.z}
    elseif player:getDirection() == 2 then
        positions = {x=positions.x, y=positions.y+1, z=positions.z}
    elseif player:getDirection() == 3 then
        positions = {x=positions.x-1, y=positions.y, z=positions.z}
    end

    if not Tile(Position(positions)):getHouse() then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce precisa estar na frente a porta da casa para usar o comando.")
		return false
    end

    local days = 5*24*60*60*1000
    local own = Tile(Position(positions)):getHouse():getOwnerGuid()
    local qry = db.storeQuery("SELECT `name`, `lastlogin` FROM `players` WHERE `id` = "..own)
    if qry ~= false then
        local last = tonumber(result.getDataInt(qry, "lastlogin"))
		local hasremoved = 0
        if last < os.time() - days then
			local pos = player:getPosition()
			pos.x = pos.x + 10
			pos.y = pos.y + 10
			local tocarpet = 0
			for xx = 1, 40 do
				if xx <= 20 then
					pos.x = pos.x - 1
				else
					pos.x = pos.x + 1
				end
				for yy = 1, 40 do
					if yy <= 20 then
						pos.y = pos.y - 1
					else
						pos.y = pos.y + 1
					end
					for zz = 0, 15 do
						pos.z = zz
						local tile = Tile(pos)
						local house = tile and tile:getHouse()
						if house and house:getOwnerGuid() == player:getGuid() then
							local itemz = 0
							for i = 1, #carpets do
								if Tile(pos):getItemById(carpets[i]) then
									itemz = Tile(pos):getItemById(carpets[i])
									tocarpet = rolled[i]
								end
							end
							if itemz ~= 0 then
								itemz:remove()
							end
						end
					end	
				end
			end
			local nome = getPlayerByName(result.getDataString(qry, "name"))
			Player(nome):getInbox():addItem(tocarpet, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
            Tile(Position(positions)):getHouse():setOwnerGuid(0)
			player:sendTextMessage(MESSAGE_INFO_DESCR, "A Casa agora esta sem dono, voce ou outro jogador pode compra-la.")
        end
        if last > os.time() - days then
			player:sendTextMessage(MESSAGE_INFO_DESCR, "O proprierario desta casa ainda esta ativo no servidor, tente outra casa.")
        end
    end
    return false
end