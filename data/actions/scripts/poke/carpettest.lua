local carpets = {38975, 38977, 38979, 38981, 38983, 38985, 38987, 38989, 38991, 38993, 38995, 38997, 38999, 39001, 39003, 39005, 39007, 39009, 39011, 39013, 39015, 39017, 39019, 39021, 39023, 39025, 39027, 39029, 39031, 39033, 39035, 39037, 39039, 39041, 39043}
local rolled = {38974, 38976, 38978, 38980, 38982, 38984, 38986, 38988, 38990, 38992, 38994, 38996, 38998, 39000, 39002, 39004, 39006, 39008, 39010, 39012, 39014, 39016, 39018, 39020, 39022, 39024, 39026, 39028, 39030, 39032, 39034, 39036, 39038, 39040, 39042}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local carpid = 0
	if not Tile(player:getPosition()):getHouse() then
		return false
	end
	for i = 1, #rolled do
		if item:getId() == rolled[i] then
			carpid = i
		end
	end
	local pos = toPosition
	pos.x = pos.x + 10
	pos.y = pos.y + 10
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
					if not tile:hasFlag(TILESTATE_BLOCKPATH) then 
						pos.stackpos = 1
						local itemz = 0
						for i = 1, #carpets do
							 if Tile(pos):getItemById(carpets[i]) then
								itemz = Tile(pos):getItemById(carpets[i])
							 end
						end
						if itemz ~= 0 then
							itemz:transform(carpets[carpid])
						else
							Game.createItem(carpets[carpid], 1, pos)
							pos:sendMagicEffect(CONST_ME_POFF)
						end
					end
				end	
			end
		end
	end
	item:remove(1)
	return true
end