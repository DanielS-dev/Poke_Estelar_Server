local boxes = 
	{
		box0 = {itemid = 26764, pokes = {"Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros"} },
		box1 = {itemid = 26812, pokes = {"Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite"} },
		box2 = {itemid = 26813, pokes = {"Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar"} },
		box3 = {itemid = 26814, pokes = {"Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho"} },
		box4 = {itemid = 26815, pokes = {"Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom"} },
		box5 = {itemid = 26816, pokes = {"Serperior", "Emboar", "Samurott", "Audino", "Zoroark", "Scolipede", "Lilligant", "Darmanitan", "Carracosta", "Gothitelle", "Galvantula", "Ferrothorn", "Klinklang", "Eelektross", "Chandelure", "Haxorus", "Beartic", "Accelgor", "Druddigon", "Golurk", "Braviary", "Heatmor", "Hydreigon", "Volcarona", "Escavalier"} }, -- not shiny
		box6 = {itemid = 26817, pokes = {"Chesnaught", "Delphox", "Greninja", "Talonflame", "Gogoat", "Pangoro", "Clawitzer", "Sylveon", "Hawlucha", "Goodra", "Trevenant", "Avalugg", "Noivern"} }, -- not shiny
		box7 = {itemid = 26818, pokes = {"Alolan Raticate", "Alolan Raichu", "Alolan Sandslash", "Alolan Ninetales", "Alolan Dugtrio", "Alolan Persian", "Alolan Golem", "Alolan Muk", "Alolan Exeggutor", "Alolan Marowak", "Decidueye", "Incineroar", "Primarina", "Vikavolt", "Crabominable", "Lycanroc", "Araquanid", "Lurantis", "Salazzle", "Tsareena", "Oranguru", "Passimian", "Turtonator", "Mimikyu"} }, -- not shiny
		box8 = {itemid = 26819, pokes = {"Galarian Rapidash", "Sirfetch'd", "Galarian Weezing", "Mr. Rime", "Galarian Darmanitan", "Cinderace", "Corviknight", "Centiskorch", "Dragapult", "Hatterene", "Grimmsnarl"} },  -- not shiny
	}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local itemId = item:getId()
	for key, value in pairs(boxes) do
		if value.itemid == itemId then
			local random = math.random(1, #boxes[key].pokes)
			local pokeName = boxes[key].pokes[random]
			local monsterType = MonsterType(pokeName)
			if not monsterType then
				print("WARNING! Pokemon " .. pokeName .. " not valid for box.")
				return true
			end
			local egg = player:getInbox():addItem(36570, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
			egg:setSpecialAttribute("eggname", pokeName)
			egg:setSpecialAttribute("steps", 0)
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Congratulations! You have found a pokemon egg.")
			player:getPosition():sendMagicEffect(CONST_ME_MAGIC_GREEN)
			break
		end
	end
	item:remove(1)
	return true
end