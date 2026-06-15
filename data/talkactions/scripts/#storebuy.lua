local vip = {
	[' 30 days'] = {days = 30, price = 10},
	[' 90 days'] = {days = 90, price = 29},
	[' 180 days'] = {days = 180, price = 56},
	[' 360 days'] = {days = 360, price = 110},
}
local general = {
	['bless'] = {id = "blessing", quantity = 1, price = 10},
	['1x rare candy'] = {id = 39332, quantity = 1, price = 5},
	['5x rare candy'] = {id = 39332, quantity = 5, price = 25},
	['25x rare candy'] = {id = 39332, quantity = 25, price = 120},
	['50x rare candy'] = {id = 39332, quantity = 50, price = 235},
	['75x rare candy'] = {id = 39332, quantity = 75, price = 350},
	['100x rare candy'] = {id = 39332, quantity = 100, price = 450},
	['tera crystal'] = {id = 39238, quantity = 1, price = 10},
	['10x tera crystal'] = {id = 39238, quantity = 10, price = 90},
	['25x tera crystal'] = {id = 39238, quantity = 25, price = 200},
	['ev reset'] = {id = 39231, quantity = 1, price = 10},
	['nature reset'] = {id = 32220, quantity = 1, price = 15},
	['10x nature reset'] = {id = 32220, quantity = 10, price = 135},
	['25x nature reset'] = {id = 32220, quantity = 25, price = 250},
	['smeargle reset'] = {id = 39259, quantity = 1, price = 10},
	['black bike'] = {id = 39237, quantity = 1, price = 10},
	['pink bike'] = {id = 39234, quantity = 1, price = 10},
	['yellow bike'] = {id = 39232, quantity = 1, price = 10},
	['red bike'] = {id = 39233, quantity = 1, price = 10},
	['blue bike'] = {id = 39236, quantity = 1, price = 10},
	['green bike'] = {id = 39235, quantity = 1, price = 10},
	['mario kart'] = {id = 39306, quantity = 1, price = 25},
	['speed boots'] = {id = 39318, quantity = 1, price = 25},
	['copper whistle'] = {id = 39223, quantity = 1, price = 15},
	['silver whistle'] = {id = 39224, quantity = 1, price = 20},
	['gold whistle'] = {id = 39225, quantity = 1, price = 30},
	['1x pokepark ticket'] = {id = 39142, quantity = 1, price = 1},
	['5x pokepark ticket'] = {id = 39142, quantity = 5, price = 4},
	['10x pokepark ticket'] = {id = 39142, quantity = 10, price = 8},
	['15x pokepark ticket'] = {id = 39142, quantity = 15, price = 10},
	['10x clean disk'] = {id = 39044, quantity = 10, price = 2},
	['25x clean disk'] = {id = 39044, quantity = 25, price = 5},
	['50x clean disk'] = {id = 39044, quantity = 50, price = 10},
	['100x clean disk'] = {id = 39044, quantity = 100, price = 20},
	['rarity charm'] = {id = 39264, quantity = 1, price = 70},
	['exp charm'] = {id = 39320, quantity = 1, price = 10},
	['100% loot charm'] = {id = 39322, quantity = 1, price = 20},
	['200% loot charm'] = {id = 39324, quantity = 1, price = 40},
	['300% loot charm'] = {id = 39326, quantity = 1, price = 60},
	['400% loot charm'] = {id = 39328, quantity = 1, price = 80},
	['500% loot charm'] = {id = 39330, quantity = 1, price = 100},
	['checkpoint console'] = {id = 39261, quantity = 1, price = 25},
	['1x checkpoint register'] = {id = 39262, quantity = 1, price = 10},
	['5x checkpoint register'] = {id = 39262, quantity = 5, price = 40},
	['10x checkpoint register'] = {id = 39262, quantity = 10, price = 75},
}
local outfit = {
	['red & green'] = {male = 3678, female = 3679, price = 15},
	['aqua & kazuma'] = {male = 3682, female = 3668, price = 25},
	['asuna & kirito'] = {male = 3671, female = 3672, price = 25},
	['emilia & subaru'] = {male = 3669, female = 3670, price = 25},
	['nezuko & tanjiro'] = {male = 3681, female = 3680, price = 25},
	['lugia fellowship'] = {male = 3805, female = 3806, price = 25},
	["let's go"] = {male = 3803, female = 3804, price = 25},
	['goku'] = {male = 3791, female = 3791, price = 50},
	['majin boo'] = {male = 3793, female = 3793, price = 50},
	['league of legends'] = {male = 3798, female = 3797, price = 25},
	['pool party'] = {male = 3796, female = 3795, price = 25},
	['psychic trainer'] = {male = 2913, female = 2914, price = 50},
	['gardellade outfit'] = {male = 4017, female = 4016, price = 25},
	['bunny outfit'] = {male = 4021, female = 4020, price = 25},
	['starmie outfit'] = {male = 4015, female = 4015, price = 25},
	['steve'] = {male = 4068, female = 4068, price = 10},
}
local addon = {
	['ancient charizard'] = {add = 3763, price = 15},
	['ancient gyarados'] = {add = 3785, price = 15},
	['ancient metagross'] = {add = 3742, price = 25},
	['armored aggron'] = {add = 3761, price = 10},
	-- ['armored arcanine'] = {add = 3770, price = 15},
	['armored arceus'] = {add = 3789, price = 20},
	['armored dragonite green'] = {add = 3728, price = 15},
	['armored dragonite purple'] = {add = 3730, price = 15},
	['armored gardevoir'] = {add = 3735, price = 15},
	['armored mewtwo'] = {add = 3769, price = 20},
	['armored rhyperior'] = {add = 3751, price = 10},
	['armored salamence'] = {add = 3759, price = 15},
	['armored tropius purple'] = {add = 3694, price = 15},
	['armored tropius red'] = {add = 3696, price = 15},
	['assassin scizor'] = {add = 3700, price = 10},
	['athena jynx'] = {add = 3787, price = 10},
	['aviator altaria'] = {add = 3715, price = 15},
	['white suit machamp'] = {add = 3702, price = 10},
	['black suit machamp'] = {add = 3701, price = 10},
	['black suit slaking'] = {add = 3752, price = 10},
	['carrier mamoswine red'] = {add = 3704, price = 15},
	['carrier mamoswine blue'] = {add = 3705, price = 15},
	['cavalier dusknoir'] = {add = 3720, price = 10},
	['cheerleader sudowoodo'] = {add = 3723, price = 10},
	['cloaked jirachi'] = {add = 3754, price = 20},
	['constructor rhyperior'] = {add = 3750, price = 10},
	['cook crawdaunt'] = {add = 3718, price = 10},
	['cook snorlax'] = {add = 3726, price = 15},
	['corrupted jirachi'] = {add = 3753, price = 20},
	['cyborg mewtwo'] = {add = 3746, price = 20},
	['cyborg salamence'] = {add = 3740, price = 25},
	['djinn machamp'] = {add = 3745, price = 10},
	['dressed gardevoir'] = {add = 3732, price = 10},
	['empress gardevoir purple'] = {add = 3736, price = 10},
	['empress gardevoir red'] = {add = 3737, price = 10},
	['fossil aerodactyl'] = {add = 3758, price = 25},
	['gyaryudos'] = {add = 3755, price = 20},
	['hashirama zoroark'] = {add = 3762, price = 10},
	['iceage mamoswine'] = {add = 3711, price = 15},
	['jimbei feraligatr'] = {add = 3685, price = 15},
	['jojo toxicroak'] = {add = 3706, price = 10},
	['lance dragonite'] = {add = 3772, price = 15},
	['magician mewtwo'] = {add = 3768, price = 20},
	['maid gardevoir'] = {add = 3734, price = 10},
	['majinblissey'] = {add = 3690, price = 10},
	['masked crobat'] = {add = 3691, price = 15},
	['masked ninetales'] = {add = 3721, price = 15},
	['masquerade'] = {add = 3713, price = 10},
	['mermaid milotic'] = {add = 3747, price = 15},
	['milktank'] = {add = 3780, price = 10},
	['ninja noctowl'] = {add = 3698, price = 15},
	['nurse blissey'] = {add = 3689, price = 10},
	['nurse gengar'] = {add = 3687, price = 15},
	['nurse wigglytuff'] = {add = 3714, price = 10},
	['pool party flareon'] = {add = 3776, price = 10},
	['pool party jolteon'] = {add = 3777, price = 10},
	['pool party vaporeon'] = {add = 3774, price = 15},
	['pool party golem'] = {add = 3778, price = 10},
	['saiyajin dugtrio'] = {add = 3744, price = 10},
	['saiyawoodo'] = {add = 3724, price = 10},
	['sannin shiftry'] = {add = 3717, price = 10},
	['saw mr. mime'] = {add = 3788, price = 10},
	['seer mismagius'] = {add = 3779, price = 10},
	['seifuku clefable'] = {add = 3790, price = 10},
	['seifuku meganium'] = {add = 3781, price = 15},
	['stitch sableye'] = {add = 3749, price = 15},
	['trainer sudowoodo'] = {add = 3719, price = 10},
	['trainer typhlosion'] = {add = 3683, price = 10},
	['tribal alakazam'] = {add = 3703, price = 10},
	['trickster mew'] = {add = 3767, price = 20},
	['witch hunter gardevoir'] = {add = 3733, price = 10},
	['witch hunter honchkrow'] = {add = 3738, price = 15},
	['yogi ursaring'] = {add = 3693, price = 10},
	
	['ancient mesprit'] = {add = 3951, price = 20},
	['ancient uxie'] = {add = 3952, price = 20},
	['ancient azelf'] = {add = 3953, price = 20},
	['cosplaying manaphy'] = {add = 3954, price = 20},
	['cosplaying greninja'] = {add = 3959, price = 10},
	['masked gengar'] = {add = 3960, price = 25},
	['cosplaying alakazam'] = {add = 3967, price = 15},
	['cosplaying banette'] = {add = 3968, price = 15},
	['cosplaying beedrill'] = {add = 3972, price = 15},
	['noir blastoise'] = {add = 3974, price = 15},
	['cosplaying blaziken'] = {add = 3976, price = 10},
	['cosplaying heracross'] = {add = 3978, price = 10},
	['cyborg mega charizard x'] = {add = 3979, price = 15},
	['cyborg mega charizard y'] = {add = 3981, price = 15},
	['cosplaying ampharos'] = {add = 3983, price = 10},
	['dressed mawile'] = {add = 3984, price = 10},
	['cosplaying medicham'] = {add = 3985, price = 10},
	['masked pinsir'] = {add = 3988, price = 15},
	['armored sceptile'] = {add = 3991, price = 10},
	['cosplaying scizor'] = {add = 3992, price = 15},
	['donut slowpoke'] = {add = 3994, price = 10},
	['metallic steelix'] = {add = 3995, price = 15},
	['cyborg swampert'] = {add = 3997, price = 15},
	['armored tyranitar'] = {add = 3999, price = 10},
	['trainer venusaur'] = {add = 4000, price = 15},
	['dressed loppuny'] = {add = 4002, price = 10},
	['cosplaying shuckle'] = {add = 4003, price = 10},
	['cosplaying blissey'] = {add = 4004, price = 10},
	['cosplaying wobbuffet'] = {add = 4005, price = 10},
	['cosplaying gardevoir'] = {add = 4006, price = 10},
	['cosplaying vileplume'] = {add = 4007, price = 10},
	['cosplaying sylveon'] = {add = 4011, price = 10},
	['cosplaying rampardos'] = {add = 4012, price = 10},
	['cosplaying audino'] = {add = 4013, price = 10},
	
	
	['cosplaying electivire'] = {add = 4033, price = 10},
	['cosplaying magmortar'] = {add = 4034, price = 10},
	['cosplaying cradily'] = {add = 4035, price = 10},
	['armored magnezone'] = {add = 4036, price = 15},
	['cyborg lapras'] = {add = 4038, price = 10},
	['cyborg flareon'] = {add = 4039, price = 10},
	['cyborg jolteon'] = {add = 4040, price = 10},
	['cyborg vaporeon'] = {add = 4041, price = 15},
	['cyborg espeon'] = {add = 4044, price = 10},
	['cyborg umbreon'] = {add = 4043, price = 10},
	['cyborg leafeon'] = {add = 4046, price = 10},
	['cyborg glaceon'] = {add = 4045, price = 10},
	['cyborg sylveon'] = {add = 4047, price = 10},
	
	['cosplaying espeon'] = {add = 4129, price = 10},
	['cosplaying umbreon'] = {add = 4130, price = 10},
	['cosplaying drapion'] = {add = 4131, price = 10},
	['dressed mismagium'] = {add = 4134, price = 15},
	['cosplaying mega abomasnow'] = {add = 4138, price = 20},
	['cosplaying gallade'] = {add = 4143, price = 20},
	['cosplaying tangrowth'] = {add = 4144, price = 10},
	['cosplaying spiritomb'] = {add = 4148, price = 15},
	['dark pidgeot'] = {add = 4150, price = 25},
	['cosplaying milotic'] = {add = 4158, price = 15},
	['cosplaying hisuian arcanine'] = {add = 4176, price = 15},
	['dressed delcatty'] = {add = 4190, price = 10},
	['cosplaying machamp'] = {add = 4191, price = 10},
	['witch hunter camerupt'] = {add = 4194, price = 25},
	
	
}
local bundle = {
	['eevolution outfit bundle'] = {typeadd = 'outfit', add = {3659, 3660, 3661, 3662, 3663, 3664, 3665, 3666, 3667}, price = 100},
	['fire type bundle'] = {typeadd = 'item', add = {{'Fire Type Backpack', 1}, {'rolled fire type carpet', 1}}, price = 10},
	['dark type bundle'] = {typeadd = 'item', add = {{'Dark Type Backpack', 1}, {'rolled dark type carpet', 1}}, price = 10},
	['electric type bundle'] = {typeadd = 'item', add = {{'Electric Type Backpack', 1}, {'rolled electric type carpet', 1}}, price = 10},
	['fairy type bundle'] = {typeadd = 'item', add = {{'Fairy Type Backpack', 1}, {'rolled fairy type carpet', 1}}, price = 10},
	['ghost type bundle'] = {typeadd = 'item', add = {{'Ghost Type Backpack', 1}, {'rolled ghost type carpet', 1}}, price = 10},
	['ground type bundle'] = {typeadd = 'item', add = {{'Ground Type Backpack', 1}, {'rolled ground type carpet', 1}}, price = 10},
	['normal type bundle'] = {typeadd = 'item', add = {{'Normal Type Backpack', 1}, {'rolled normal type carpet', 1}}, price = 10},
	['psychic type bundle'] = {typeadd = 'item', add = {{'Psychic Type Backpack', 1}, {'rolled psychic type carpet', 1}}, price = 10},
	['steel type bundle'] = {typeadd = 'item', add = {{'Steel Type Backpack', 1}, {'rolled steel type carpet', 1}}, price = 10},
	['bug type bundle'] = {typeadd = 'item', add = {{'Bug Type Backpack', 1}, {'rolled Bug type carpet', 1}}, price = 10},
	['dragon type bundle'] = {typeadd = 'item', add = {{'Dragon Type Backpack', 1}, {'rolled dragon type carpet', 1}}, price = 10},
	['fighting type bundle'] = {typeadd = 'item', add = {{'Fighting Type Backpack', 1}, {'rolled fighting type carpet', 1}}, price = 10},
	['flying type bundle'] = {typeadd = 'item', add = {{'Flying Type Backpack', 1}, {'rolled flying type carpet', 1}}, price = 10},
	['grass type bundle'] = {typeadd = 'item', add = {{'Grass Type Backpack', 1}, {'rolled grass type carpet', 1}}, price = 10},
	['ice type bundle'] = {typeadd = 'item', add = {{'Ice Type Backpack', 1}, {'rolled Ice type carpet', 1}}, price = 10},
	['poison type bundle'] = {typeadd = 'item', add = {{'Poison Type Backpack', 1}, {'rolled poison type carpet', 1}}, price = 10},
	['rock type bundle'] = {typeadd = 'item', add = {{'Rock Type Backpack', 1}, {'rolled rock type carpet', 1}}, price = 10},
	['water type bundle'] = {typeadd = 'item', add = {{'Water Type Backpack', 1}, {'rolled water type carpet', 1}}, price = 10},
}

local eggs = {
	['kanto egg'] = {add = {"Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros", "Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite"}, price = 5},
	['johto egg'] = {add = {"Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar"}, price = 10},
	['hoenn egg'] = {add = {"Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho"}, price = 15},
	['sinnoh egg'] = {add = {"Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom"}, price = 15},
	['unova egg'] = {add = {"Serperior", "Emboar", "Samurott", "Audino", "Zoroark", "Scolipede", "Lilligant", "Darmanitan", "Carracosta", "Gothitelle", "Galvantula", "Ferrothorn", "Klinklang", "Eelektross", "Chandelure", "Haxorus", "Beartic", "Accelgor", "Druddigon", "Golurk", "Braviary", "Heatmor", "Hydreigon", "Volcarona", "Escavalier"}, price = 25},
	['kalos egg'] = {add = {"Chesnaught", "Delphox", "Greninja", "Talonflame", "Gogoat", "Pangoro", "Clawitzer", "Sylveon", "Hawlucha", "Goodra", "Trevenant", "Avalugg", "Noivern"}, price = 25},
	['alola egg'] = {add = {"Alolan Raticate", "Alolan Raichu", "Alolan Sandslash", "Alolan Ninetales", "Alolan Dugtrio", "Alolan Persian", "Alolan Golem", "Alolan Muk", "Alolan Exeggutor", "Alolan Marowak", "Decidueye", "Incineroar", "Primarina", "Vikavolt", "Crabominable", "Lycanroc", "Araquanid", "Lurantis", "Salazzle", "Tsareena", "Oranguru", "Passimian", "Turtonator", "Mimikyu"}, price = 25},
	['galar egg'] = {add = {"Galarian Rapidash", "Sirfetch'd", "Galarian Weezing", "Mr. Rime", "Galarian Darmanitan", "Cinderace", "Corviknight", "Centiskorch", "Dragapult", "Hatterene", "Grimmsnarl"}, price = 25},
	['hisuian egg'] = {add = {"Hisuian Arcanine", "Hisuian Electrode", "Hisuian Typhlosion", "Hisuian Samurott", "Hisuian Decidueye", "Hisuian Lilligant", "Hisuian Zoroark", "Hisuian Braviary", "Hisuian Goodra", "Hisuian Avalugg"}, price = 25},
}

function onSay(player, words, param)
	local category = tonumber(param:split(',')[1])
	local thing = param:split(',')[2]
	if category == 1 then -- vip
		if player:removeItem(38942, vip[thing].price) then
			player:addPremiumDays(vip[thing].days)
		end
	elseif category == 2 then -- general
		if general[thing].id == "blessing" then
			if player:hasBlessing(7) then
				player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce ja possui bless.")
				return true
			end
			if player:removeItem(38942, general[thing].price) then
				player:addBlessing(1)
				player:addBlessing(2)
				player:addBlessing(3)
				player:addBlessing(4)
				player:addBlessing(5)
				player:addBlessing(6)
				player:addBlessing(7)
			end
		else
			if player:removeItem(38942, general[thing].price) then
				player:addItem(general[thing].id, general[thing].quantity)
			end
		end
	elseif category == 3 then -- outfit
		if player:removeItem(38942, outfit[thing].price) then
			if player:getSex() == PLAYERSEX_MALE then
				player:addOutfit(outfit[thing].male)
			else
				player:addOutfit(outfit[thing].female)
			end
		end
	elseif category == 4 then -- addon
		if player:removeItem(38942, addon[thing].price) then
			local item = player:addItem(39239, 1)
			item:setSpecialAttribute("addon", ""..addon[thing].add)
		end
	elseif category == 5 then -- bundle
		if player:removeItem(38942, bundle[thing].price) then
			if bundle[thing].typeadd == "item" then
				for i = 1, #bundle[thing].add do
					player:addItem(bundle[thing].add[i][1], bundle[thing].add[i][2])
				end
			elseif bundle[thing].typeadd == "outfit" then
				for i = 1, #bundle[thing].add do
					player:addOutfit(bundle[thing].add[i])
				end
			end
		end
	elseif category == 6 then
		if player:removeItem(38942, eggs[thing].price) then
			if player:getSlotItem(CONST_SLOT_BACKPACK) and player:getSlotItem(CONST_SLOT_BACKPACK):getEmptySlots() >= 1 and player:getFreeCapacity() >= 1 then
				local pokename = eggs[thing].add[math.random(1, #eggs[thing].add)]
				local egg = player:addItem(36570, 1, false)
				egg:setSpecialAttribute("eggname", pokename)
				egg:setSpecialAttribute("steps", 0)
			else
				local pokename = eggs[thing].add[math.random(1, #eggs[thing].add)]
				local egg = player:getInbox():addItem(36570, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
				egg:setSpecialAttribute("eggname", pokename)
				egg:setSpecialAttribute("steps", 0)
			end
		end
	end
	return false
end
