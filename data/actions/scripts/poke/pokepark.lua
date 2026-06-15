function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local pokes = {"Milotic", "Wailord", "Hippowdon", "Garchomp", "Rampardos", "Bastiodon", "Rhyperior", "Drapion", "Flygon", "Gliscor", "Cradily", "Armaldo", "Vespiquen", "Kricketune", "Yanmega", "Pachirisu", "Roserade", "Kecleon", "Cherrim", "Lopunny", "Beautifly", "Tropius", "Breloom", "Dustox", "Toxicroak", "Carnivine", "Shiftry", "Seviper", "Tangrowth", "Mothim", "Pelipper", "Ludicolo", "Drifblim"}
	local buyable = {","}
	for i = 1, #pokes do
		if player:getStorageValue(180564000 + MonsterType(pokes[i]):dexEntry()) >= 1 then
			table.insert(buyable, pokes[i]..",")
		end
	end
	player:sendExtendedOpcode(64, table.concat(buyable))
end