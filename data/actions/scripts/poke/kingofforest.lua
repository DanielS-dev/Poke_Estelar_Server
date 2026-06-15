function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if areaHasOtherPlayer(player, Position(150, 46, 15), 26, 26) then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce ainda nao e o Rei da Floresta, elimine os outros jogadores.")
		return true
	end
	player:teleportTo(player:getTown():getTemplePosition())
	player:addItem("vale token", 100)
	player:addItem('empty premierball', 50)
	local pokename = {"Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros", "Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite", "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar", "Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho", "Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom", "Serperior", "Emboar", "Samurott", "Chesnaught", "Delphox", "Greninja", "Decidueye", "Incineroar", "Primarina", "Alolan Raticate", "Alolan Raichu", "Alolan Sandslash", "Alolan Ninetales", "Alolan Dugtrio", "Alolan Persian", "Alolan Golem", "Alolan Muk", "Alolan Exeggutor", "Alolan Marowak", "Galarian Rapidash", "Sirfetch'd", "Galarian Weezing", "Mr. Rime", "Galarian Darmanitan", "Hisuian Arcanine", "Hisuian Electrode", "Hisuian Typhlosion", "Hisuian Samurott", "Hisuian Decidueye", "Hisuian Lilligant", "Hisuian Zoroark", "Hisuian Braviary", "Hisuian Goodra", "Hisuian Avalugg", "Audino", "Zoroark", "Scolipede", "Lilligant", "Darmanitan", "Carracosta", "Gothitelle", "Galvantula", "Ferrothorn", "Klinklang", "Eelektross", "Chandelure", "Haxorus", "Beartic", "Accelgor", "Druddigon", "Golurk", "Braviary", "Heatmor", "Hydreigon", "Volcarona", "Escavalier", "Talonflame", "Gogoat", "Pangoro", "Clawitzer", "Sylveon", "Hawlucha", "Goodra", "Trevenant", "Avalugg", "Noivern", "Vikavolt", "Crabominable", "Lycanroc", "Araquanid", "Lurantis", "Salazzle", "Tsareena", "Oranguru", "Passimian", "Turtonator", "Mimikyu", "Cinderace", "Corviknight", "Centiskorch", "Dragapult", "Hatterene", "Grimmsnarl"}
	if not MonsterType(pokename[math.random(1, #pokename)]) then
		print("Player: "..player:getName().." with error, egg without name: "..pokename.."")
		return false
	end
	for i = 1, 2 do
		local egg = player:getInbox():addItem(36570, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
		egg:setSpecialAttribute("eggname", pokename[math.random(1, #pokename)])
		egg:setSpecialAttribute("steps", 0)
	end
	player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Parabens, voce venceu o evento e recebeu: 100 Vale Tokens, 50 Clean Disk e 2 Pokemon Egg")
	broadcastMessage("O jogador "..player:getName().." venceu o evento e agora e o novo Rei da Floresta.", MESSAGE_STATUS_WARNING)
	return true
end


		
	