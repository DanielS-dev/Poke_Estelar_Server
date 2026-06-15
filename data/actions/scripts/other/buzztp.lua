function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if item:getId() == 9890 then
		player:teleportTo(Position({x=906,y=579,z=11}), false)
	elseif item:getId() == 9889 then
		player:teleportTo(Position({x=906,y=579,z=9}), false)
	end
	return true
end
