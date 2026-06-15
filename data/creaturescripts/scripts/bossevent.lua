function onDeath(creature, corpse, killer, mostDamage, unjustified, mostDamage_unjustified)
	if type(corpse) ~= "userdata" then
		return true
	end
	if corpse and creature and not isSummon(creature) then
		if isInRange(corpse:getPosition(), Position(2411, 0, 0), Position(2733, 351, 7)) then
			local bosschance = 1
			local boss = {"Kleavor", "Wyrdeer", "Ursaluna", "Basculegion", "Sneasler", "Overqwil", "Toedscruel", "Wugtrio", "Annihilape", "Clodsire", "Farigiraf", "Dudunsparce", "Iron Bundle"}
			if 100 <= math.random(1, 100) then
				Game.createMonster(boss[math.random(1, #boss)], player:getClosestFreePosition(player:getPosition()))
			end
		end
	end
	return true
end
