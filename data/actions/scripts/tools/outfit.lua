function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if item.itemid == 39226 then -- moltres
		if item:remove(1) then
			player:addOutfit(3674)
		end
	elseif item.itemid == 39227 then -- articuno
		if item:remove(1) then
			player:addOutfit(3673)
		end
	elseif item.itemid == 39228 then -- zapdos
		if item:remove(1) then
			player:addOutfit(3675)
		end
	elseif item.itemid == 39229 then -- mew
		if item:remove(1) then
			player:addOutfit(3676)
		end
	elseif item.itemid == 39230 then -- mewtwo
		if item:remove(1) then
			player:addOutfit(3678)
		end
	end
	return true
end
