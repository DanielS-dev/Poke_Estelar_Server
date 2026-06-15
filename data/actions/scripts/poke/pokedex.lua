local multiplier = 5 -- how many times more exp than killing the monster the player will get when using dex on it for the first time
local pokedexId = 2263
hiddenabilities = {
-- Immune to water type damage and applies AttackUP on receiving an attack.
stormdrain = {"Gastrodon", "Shellos", "Finneon", "Lumineon", "Lileep", "Cradily"},

-- Chance to return physical damage
counter = {"Lucario", "Mega Lucario", "Lopunny", "Mega Lopunny", "Medicham", "Mega Medicham", "Electabuzz", "Electivire", "Lycanroc", "Wobbuffet", "Annihilape"},

-- Immunity to status
goodasgold = {"Gholdengo"},

-- Reduces fire damage and boosts water damage
waterbubble = {"Araquanid"},

-- Immune to electric type damage and applies speed up on receiving an attack.
motordrive = {"Electivire", "Zebstrika", "Emolga"},

-- Reflects status changing moves.
magicbounce = {"Mega Sableye", "Mega Absol", "Mega Diancie", "Xatu", "Espeon", "Hatterene"},

-- STABS for 2.0 instead of 1.5.
adaptability = {"Mega Beedril", "Eevee", "Mega Lucario", "Porygon-Z", "Crawdaunt"},

-- Ignores immunity by ability.
moldbreaker = {"Pinsir", "Mega Gyarados", "Mega Ampharos", "Rampardos", "Haxorus", "Pangoro", "Excadrill", "Druddigon", "Hawlucha"},

-- Passive Hail attack every 10 seconds.
snowwarning = {"Snover", "Abomasnow", "Mega Abomasnow", "Alolan Vulpix", "Alolan Ninetales"},

-- Returns 1/8 of physical damage to attacker
ironbarbs = {"Ferrothorn"},

-- Normal attacks become fairy type
pixilate = {"Mega Gardevoir", "Mega Altaria", "Sylveon"},

-- All attacks become normal type
normalize = {"Delcatty"},

-- Normal attacks become flying type
aerilate = {"Mega Pinsir", "Mega Salamence"},

-- Normal attacks become ice type
refrigerate = {"Mega Glalie"},

-- Normal attacks become electric type
galvanize = {"Alolan Golem"},

-- Returns some damage to attackers.
roughskin = {"Carvanha", "Sharpedo", "Gible", "Gabite", "Garchomp"},

-- Passive Sandstorm attack every 10 seconds.
sandstream = {"Tyranitar", "Hippopotas", "Hippowdon"},

-- Passive dream eater/nightmare
baddreams = {"Darkrai"},

-- Boosts speed in rain.
swiftswim = {"Horsea", "Goldeen", "Seaking", "Magikarp", "Omanyte", "Omastar", "Kabuto", "Kabutops", "Qwilfish", "Mantine", "Kingdra", "Mega Swampert", "Lotad", "Lombre", "Ludicolo", "Surskit", "Feebas", "Huntail", "Gorebyss", "Relicanth", "Luvdisc", "Buizel", "Floatzel", "Finneon", "Lumineon", "Mantyke", "Psyduck", "Golduck", "Poliwag", "Poliwhirl", "Poliwrath", "Anorith", "Armaldo"},

-- Becomes invulnerable for 5 seconds at 1HP
sturdy = {"Geodude", "Alolan Geodude", "Graveler", "Alolan Graveler", "Golem", "Alolan Golem", "Magnemite", "Magneton", "Onix", "Sudowoodo", "Pineco", "Forretress", "Steelix", "Shuckle", "Skarmory", "Donphan", "Nosepass", "Aron", "Lairon", "Aggron", "Shieldon", "Bastiodon", "Bonsly", "Magnezone", "Probopass", "Relicanth", "Regirock", "Avalugg", "Hisuian Avalugg", "Mega Aggron"},

-- Immune to ground damage.
levitate = {"Gastly", "Haunter", "Koffing", "Weezing", "Galarian Weezing", "Misdreavus", "Unown", "Vibrava", "Flygon", "Lunatone", "Solrock", "Baltoy", "Claydol", "Duskull", "Chimecho", "Latias", "Mega Latias", "Latios", "Mega Latios", "Mismagius", "Chingling", "Bronzor", "Bronzong", "Carnivine", "Rotom", "Uxie", "Mesprit", "Azelf", "Cresselia"},

-- Immune to silence
innerfocus = {"Zubat", "Golbat", "Abra", "Kadabra", "Alakazam", "Farfetch'd", "Dragonite", "Crobat", "Girafarig", "Sneasel", "Snorunt", "Glalie", "Riolu", "Lucario", "Mega Gallade", "Drowzee", "Hypno", "Hitmonchan", "Kangaskhan", "Umbreon", "Raikou", "Entei", "Suicune", "Annihilape"},

-- Boosts speed in sunlight.
chlorophyll = {"Oddish", "Gloom", "Vileplume", "Bellsprout", "Weepinbell", "Victreebel", "Exeggcute", "Exeggutor", "Tangela", "Bellossom", "Hoppip", "Skiploom", "Jumpluff", "Sunkern", "Sunflora", "Seedot", "Nuzleaf", "Shiftry", "Tropius", "Cherubi", "Tangrowth", "Bulbasaur", "Ivysaur", "Venusaur", "Leafeon", "Lilligant", "Hisuian Lilligant"},

-- Chance to apply poison, sleep or paralysis on attacker.
effectspore = {"Paras", "Parasect", "Breloom", "Shroomish", "Vileplume"},

-- Ignores immunity spells.
infiltrator = {"Noivern", "Dragapult", "Zubat", "Golbat", "Crobat", "Jumpluff", "Ninjask", "Seviper", "Spiritomb", "Chandelure", "Malamar"},

-- Immune to confusion.
owntempo = {"Slowpoke", "Galarian Slowpoke", "Slowbro", "Galarian Slowbro", "Lickitung", "Slowking", "Galarian Slowking", "Smeargle", "Spoink", "Grumpig", "Spinda", "Glameow", "Purugly", "Lickilicky", "Lotad", "Lombre", "Ludicolo", "Numel", "Avalugg"},

-- Applies evasion in sandstorm
sandveil = {"Sandshrew", "Sandslash", "Diglett", "Alolan Diglett", "Dugtrio", "Alolan Dugtrio", "Gligar", "Cacnea", "Cacturne", "Gible", "Gabite", "Garchomp", "Gliscor", "Geodude", "Graveler", "Golem", "Phanpy", "Donphan", "Larvitar"},

-- Boosts loot rate by 25%
pickup = {"Meowth", "Alolan Meowth", "Aipom", "Teddiursa", "Phanpy", "Zigzagoon", "Linoone", "Pachirisu", "Ambipom", "Munchlax", "Shiny Meowth", "Shiny Alolan Meowth", "Shiny Aipom", "Shiny Teddiursa", "Shiny Phanpy", "Shiny Zigzagoon", "Shiny Linoone", "Shiny Pachirisu", "Shiny Ambipom", "Shiny Munchlax"},

-- Immune to water damage and gains life on taking hit.
waterabsorb = {"Poliwag", "Poliwhirl", "Poliwrath", "Lapras", "Vaporeon", "Politoed", "Wooper", "Quagsire", "Mantine", "Mantyke", "Chinchou", "Lanturn", "Cacnea", "Cacturne", "Clodsire", "Araquanid"},

-- Immune to sleep.
insomnia = {"Drowzee", "Hypno", "Mega Mewtwo Y", "Hoothoot", "Noctowl", "Spinarak", "Ariados", "Murkrow", "Shuppet", "Banette", "Honchkrow", "Delibird", "Shiny Drowzee", "Shiny Hypno", "Shiny Mega Mewtwo Y", "Shiny Hoothoot", "Shiny Noctowl", "Shiny Spinarak", "Shiny Ariados", "Shiny Murkrow", "Shiny Shuppet", "Shiny Banette", "Shiny Honchkrow", "Shiny Delibird"},

-- May cause attacker to become paralyzed.
static = {"Pikachu", "Raichu", "Voltorb", "Electrode", "Electabuzz", "Pichu", "Mareep", "Flaaffy", "Ampharos", "Elekid", "Electrike", "Manectric", "Zapdos", "Shiny Pikachu", "Shiny Raichu", "Shiny Voltorb", "Shiny Electrode", "Shiny Electabuzz", "Shiny Pichu", "Shiny Mareep", "Shiny Flaaffy", "Shiny Ampharos", "Shiny Elekid", "Shiny Electrike", "Shiny Manectric", "Shiny Zapdos"},

-- Cleans condition while its raining.
hydration = {"Seel", "Dewgong", "Wingull", "Phione", "Manaphy", "Lapras", "Vaporeon", "Smoochum", "Barboach", "Whiscash", "Gorebyss", "Luvdisc", "Shiny Seel", "Shiny Dewgong", "Shiny Wingull", "Shiny Phione", "Shiny Manaphy", "Shiny Lapras", "Shiny Vaporeon", "Shiny Smoochum", "Shiny Barboach", "Shiny Whiscash", "Shiny Gorebyss", "Shiny Luvdisc"},

-- Recovers health in snowstorm.
icebody = {"Snorunt", "Glalie", "Spheal", "Sealeo", "Walrein", "Seel", "Dewgong", "Galarian Mr. Mime", "Regice", "Glaceon", "Shiny Snorunt", "Shiny Glalie", "Shiny Spheal", "Shiny Sealeo", "Shiny Walrein", "Shiny Seel", "Shiny Dewgong", "Shiny Galarian Mr. Mime", "Shiny Regice", "Shiny Glaceon"},

-- May cause attacker to become burned.
flamebody = {"Magmar", "Slugma", "Magcargo", "Magby", "Magmortar", "Litwick", "Lampent", "Chandelure", "Larvesta", "Volcarona", "Fletchinder", "Talonflame", "Ponyta", "Rapidash", "Moltres", "Heatran", "Shiny Magmar", "Shiny Slugma", "Shiny Magcargo", "Shiny Magby", "Shiny Magmortar", "Shiny Litwick", "Shiny Lampent", "Shiny Chandelure", "Shiny Larvesta", "Shiny Volcarona", "Shiny Fletchinder", "Shiny Talonflame", "Shiny Ponyta", "Shiny Rapidash", "Shiny Moltres", "Shiny Heatran"},

-- May cause attacker to become poisoned.
poisonpoint = {"Nidoran Female", "Nidorina", "Nidoqueen", "Nidoran Male", "Nidorino", "Nidoking", "Seadra", "Qwilfish", "Roselia", "Budew", "Roserade", "Scolipede", "Clodsire", "Overqwil"},
poisontouch = {"Alolan Muk", "Grimer", "Muk", "Croagunk", "Toxicroak", "Shiny Alolan Muk", "Shiny Grimer", "Shiny Muk", "Shiny Croagunk", "Shiny Toxicroak"},

-- Immune to electric damage and applies AttackUP on receiving an attack.
lightningrod = {"Cubone", "Marowak", "Alolan Marowak", "Rhyhorn", "Rhydon", "Mega Sceptile", "Electrike", "Manectric", "Rhyperior", "Pikachu", "Raichu", "Goldeen", "Seaking", "Pichu", "Plusle", "Shiny Cubone", "Shiny Marowak", "Shiny Alolan Marowak", "Shiny Rhyhorn", "Shiny Rhydon", "Shiny Mega Sceptile", "Shiny Electrike", "Shiny Manectric", "Shiny Rhyperior", "Shiny Pikachu", "Shiny Raichu", "Shiny Goldeen", "Shiny Seaking", "Shiny Pichu", "Shiny Plusle"},

-- Immune to status changing attacks.
clearbody = {"Tentacool", "Tentacruel", "Beldum", "Metang", "Metagross", "Regirock", "Regice", "Registeel", "Diancie", "Dragapult", "Klinklang", "Shiny Tentacool", "Shiny Tentacruel", "Shiny Beldum", "Shiny Metang", "Shiny Metagross", "Shiny Regirock", "Shiny Regice", "Shiny Registeel", "Shiny Diancie", "Shiny Dragapult", "Shiny Klinklang"},

-- Attacker also receives status conditions. (Poison, Burn, Freeze, Paralyze)
synchronize = {"Abra", "Kadabra", "Alakazam", "Mew", "Natu", "Xatu", "Espeon", "Umbreon", "Ralts", "Kirlia", "Gardevoir", "Shiny Abra", "Shiny Kadabra", "Shiny Alakazam", "Shiny Mew", "Shiny Natu", "Shiny Xatu", "Shiny Espeon", "Shiny Umbreon", "Shiny Ralts", "Shiny Kirlia", "Shiny Gardevoir"},

-- Applies AttackUP in sandstorm.
sandforce = {"Mega Steelix", "Mega Garchomp", "Excadrill", "Diglett", "Dugtrio", "Alolan Dugtrio", "Nosepass", "Shellos", "Gastrodon", "Hippopotas", "Hippowdon", "Probopass", "Shiny Mega Steelix", "Shiny Mega Garchomp", "Shiny Excadrill", "Shiny Diglett", "Shiny Dugtrio", "Shiny Alolan Dugtrio", "Shiny Nosepass", "Shiny Shellos", "Shiny Gastrodon", "Shiny Hippopotas", "Shiny Hippowdon", "Shiny Probopass"},

-- Applies evasion in snowstorm
snowcloak = {"Alolan Sandslash", "Alolan Ninetales", "Swinub", "Piloswine", "Glaceon", "Mamoswine", "Froslass", "Articuno", "Shiny Alolan Sandslash", "Shiny Alolan Ninetales", "Shiny Swinub", "Shiny Piloswine", "Shiny Glaceon", "Shiny Mamoswine", "Shiny Froslass", "Shiny Articuno"},

-- Becomes able to hit ghost type pokémon.
scrappy = {"Kangaskhan", "Miltank", "Mega Lopunny", "Galarian Farfetch'd", "Taillow", "Swellow", "Loudred", "Exploud", "Shiny Kangaskhan", "Shiny Miltank", "Shiny Mega Lopunny", "Shiny Galarian Farfetch'd", "Shiny Taillow", "Shiny Swellow", "Shiny Loudred", "Shiny Exploud"},

-- Immune to electric damage and gains life on taking hit.
voltabsorb = {"Jolteon", "Chinchou", "Lanturn", "Zeraora", "Minun", "Pachirisu", "Shiny Jolteon", "Shiny Chinchou", "Shiny Lanturn", "Shiny Zeraora", "Shiny Minun", "Shiny Pachirisu"},

-- Recovers health in rain.
raindish = {"Lotad", "Lombre", "Ludicolo", "Squirtle", "Wartortle", "Blastoise", "Tentacool", "Tentacruel", "Wingull", "Pelipper", "Surskit", "Shiny Lotad", "Shiny Lombre", "Shiny Ludicolo", "Shiny Squirtle", "Shiny Wartortle", "Shiny Blastoise", "Shiny Tentacool", "Shiny Tentacruel", "Shiny Wingull", "Shiny Pelipper", "Shiny Surskit"},

-- May cause attacker to become silenced.
cursedbody = {"Gengar", "Alolan Marowak", "Shuppet", "Banette", "Froslass", "Dragapult"},

-- Passive Refresh every 10 seconds.
healer = {"Audino", "Mega Audino", "Chansey", "Bellossom", "Blissey", "Hatterene", "Shiny Audino", "Shiny Mega Audino", "Shiny Chansey", "Shiny Bellossom", "Shiny Blissey", "Shiny Hatterene"},

-- Immune to fire damage and applies AttackUP on receiving an attack.
flashfire = {"Vulpix", "Ninetales", "Growlithe", "Arcanine", "Ponyta", "Rapidash", "Flareon", "Houndour", "Houndoom", "Heatran", "Litwick", "Lampent", "Chandelure", "Heatmor", "Cyndaquil", "Quilava", "Typhlosion", "Hisuian Arcanine"},
}

weight = {
	superheavy = {'Alolan Exeggutor', 'Regigigas', 'Primal Kyogre', 'Heatran', 'Snorlax', 'Hoopa', 'Metagross', 'Zygarde Complete', 'Giratina Origin', 'Dialga', 'Mega Steelix', 'Giratina', 'Melmetal', 'Stakataka', 'Guzzlord', 'Mega Metagross', 'Groudon', 'Eternatus', 'Primal Groudon', 'Celesteela', 'Aggron', 'Mega Rayquaza', 'Mega Aggron', 'Wailord', 'Steelix', 'Shiny Alolan Exeggutor', 'Shiny Regigigas', 'Shiny Primal Kyogre', 'Shiny Heatran', 'Shiny Snorlax', 'Shiny Hoopa Unbound', 'Shiny Metagross', 'Shiny Zygarde Complete', 'Shiny Giratina Origin', 'Shiny Dialga', 'Shiny Mega Steelix', 'Shiny Giratina', 'Shiny Melmetal', 'Shiny Stakataka', 'Shiny Guzzlord', 'Shiny Mega Metagross', 'Shiny Groudon', 'Shiny Eternatus', 'Shiny Primal Groudon', 'Shiny Celesteela', 'Shiny Aggron', 'Shiny Mega Rayquaza', 'Shiny Mega Aggron', 'Shiny Wailord', 'Shiny Steelix'},
	heavy = {'Torterra', 'Alolan Golem', 'Arceus', 'Mega Camerupt', 'Kyurem', 'Golurk', 'Reshiram', 'Buzzwole', 'Palkia', 'Probopass', 'Zekrom', 'Dawn Necrozma', 'Mega Glalie', 'Kyogre', 'Golem', 'Hippowdon', 'Mega Gyarados', 'Zygarde', 'Registeel', 'Rayquaza', 'Onix', 'Dragonite', 'Turtonator', 'Xerneas', 'Lugia', 'Lapras', 'Mantine', 'Camerupt', 'Regirock', 'Solgaleo', 'Necrozma', 'Ultra Necrozma', 'Gyarados', 'Cobalion', 'Hariyama', 'Mega Tyranitar', 'Glalie', 'Beartic', 'Rhyperior', 'Mamoswine', 'Crustle', 'Virizion', 'Regidrago', 'Scolipede', 'Tyranitar', 'Yvetal', 'Shiny Torterra', 'Shiny Alolan Golem', 'Shiny Arceus', 'Shiny Mega Camerupt', 'Shiny Kyurem', 'Shiny Golurk', 'Shiny Reshiram', 'Shiny Buzzwole', 'Shiny Palkia', 'Shiny Probopass', 'Shiny Zekrom', 'Shiny Dawn Necrozma', 'Shiny Mega Glalie', 'Shiny Kyogre', 'Shiny Golem', 'Shiny Hippowdon', 'Shiny Mega Gyarados', 'Shiny Zygarde', 'Shiny Registeel', 'Shiny Rayquaza', 'Shiny Onix', 'Shiny Dragonite', 'Shiny Turtonator', 'Shiny Xerneas', 'Shiny Lugia', 'Shiny Lapras', 'Shiny Mantine', 'Shiny Camerupt', 'Shiny Regirock', 'Shiny Solgaleo', 'Shiny Necrozma', 'Shiny Ultra Necrozma', 'Shiny Gyarados', 'Shiny Cobalion', 'Shiny Hariyama', 'Shiny Mega Tyranitar', 'Shiny Glalie', 'Shiny Beartic', 'Shiny Rhyperior', 'Shiny Mamoswine', 'Shiny Crustle', 'Shiny Virizion', 'Shiny Regidrago', 'Shiny Scolipede', 'Shiny Tyranitar', 'Shiny Yvetal'},
	normal = {'Emboar', 'Naganadel', 'Goodra', 'Walrein', 'Kingdra', 'Solrock', 'Arcanine', 'Mega Venusaur', 'Hydreigon', 'Mega Sableye', 'Milotic', 'Lunatone', 'Regice', 'Raikou', 'Magnezone', 'Mega Abomasnow', 'Suicune', 'Bronzong', 'Volcanion', 'Entei', 'Ho-oh', 'Rampardos', 'Salamence', 'Alolan Raticate', 'Haxorus', 'Urshifu', 'Dusknoir', 'Claydol', 'Spiritomb', 'Ferrothorn', 'Mega Charizard X', 'Mega Salamence', 'Rhyhorn', "Sirfetch'd", 'Scizor', 'Dewgong', 'Mega Slowbro', 'Exeggutor', 'Rhydon', 'Donphan', 'Lunala', 'Galarian Darmanitan', 'Mewtwo', 'Mega Scizor', 'Forretress', 'Ursaring', 'Mega Mewtwo X', 'Tangrowth', 'Machamp', 'Mega Sharpedo', 'Slaking', 'Cloyster', 'Abomasnow', 'Pangoro', 'Electivire', 'Druddigon', 'Lickilicky', 'Regieleki', 'Vikavolt', 'Bastiodon', 'Shiny Emboar', 'Shiny Naganadel', 'Shiny Goodra', 'Shiny Walrein', 'Shiny Kingdra', 'Shiny Solrock', 'Shiny Arcanine', 'Shiny Mega Venusaur', 'Shiny Hydreigon', 'Shiny Mega Sableye', 'Shiny Milotic', 'Shiny Lunatone', 'Shiny Regice', 'Shiny Raikou', 'Shiny Magnezone', 'Shiny Mega Abomasnow', 'Shiny Suicune', 'Shiny Bronzong', 'Shiny Volcanion', 'Shiny Entei', 'Shiny Ho-oh', 'Shiny Rampardos', 'Shiny Salamence', 'Shiny Alolan Raticate', 'Shiny Haxorus', 'Shiny Urshifu', 'Shiny Dusknoir', 'Shiny Claydol', 'Shiny Spiritomb', 'Shiny Ferrothorn', 'Shiny Mega Charizard X', 'Shiny Mega Salamence', 'Shiny Rhyhorn', "Sirfetch'd", 'Shiny Scizor', 'Shiny Dewgong', 'Shiny Mega Slowbro', 'Shiny Exeggutor', 'Shiny Rhydon', 'Shiny Donphan', 'Shiny Lunala', 'Shiny Galarian Darmanitan', 'Shiny Mewtwo', 'Shiny Mega Scizor', 'Shiny Forretress', 'Shiny Ursaring', 'Shiny Mega Mewtwo X', 'Shiny Tangrowth', 'Shiny Machamp', 'Shiny Mega Sharpedo', 'Shiny Slaking', 'Shiny Cloyster', 'Shiny Abomasnow', 'Shiny Pangoro', 'Shiny Electivire', 'Shiny Druddigon', 'Shiny Lickilicky', 'Shiny Regieleki', 'Shiny Vikavolt', 'Shiny Bastiodon'},
}

function Monster.getSummonStatus(self)
	local output = "Status of " .. self:getName()	
	if self:isPokemon() then
		local master = self:getMaster()
		output = output ..  " that belongs to " .. master:getName() 
	end

	local monsterType = MonsterType(self:getName())
	local race = monsterType:getRaceName()
	local race2 = monsterType:getRace2Name()
	local raceName = race
	if race2 ~= "none" then
		raceName = raceName .. "/" .. race2
	end
	output = output .. "\nType: \t" .. raceName .. "\nLevel: \t" .. self:getLevel() .. "\nLove: \t" .. self:getLove()
	output = output .. "\n\nStats:\n"
	output = output .. "\nHealth: \t" .. self:getTotalHealth() 
			.. "\nAttack: \t" .. self:getTotalMeleeAttack() 
			.. "\nSpecial Attack: \t" .. self:getTotalMagicAttack() 
			.. "\nDefense: \t" .. self:getTotalDefense() 
			.. "\nSpecial Defense: \t" .. self:getTotalMagicDefense() 
			.. "\nSpeed: \t" .. self:getTotalSpeed()
	local moveList = monsterType:getMoveList()
	if #moveList >= 1 then
		output = output .. "\n\nMoves:" .. "\n"
		for i = 1, #moveList do
			local move = moveList[i]
			if move then
				output = output .. "\n" .. moveWords[i] .. " - \t" .. move.name .. ". Cooldown: \t" .. move.speed / 1000 .. " seconds."
			else
				break
			end
		end
	end
	local evolutionList = monsterType:getEvolutionList()
	if #evolutionList >= 1 then
		output = output .. "\n\nEvolutions:" .. "\n"
		for i = 1, #evolutionList do
			local evolution = evolutionList[i]
			local evolutionName = evolution.name
			if evolutionName ~= "" then
				if evolution.level ~= 1000 then
					output = output .. "\nEvolui para " .. evolutionName .. " no nivel " .. evolution.level
				end
				if evolution.itemName ~= "troca" and evolution.itemName ~= "none" then
					output = output .. "\nEvolui para " .. evolutionName .. " utlizando uma " .. evolution.itemName .. "."
				end
				if evolution.itemName == "linking cord" then
					output = output .. "\nEvolui para " .. evolutionName .. " ao trocar com outro jogador ou utilizando um Linking Cord."
				end
				if evolution.love ~= 0 then
					output = output .. "\nEvolui para  " .. evolutionName .. " com " .. evolution.love .. " pontos de amor."
				end
			end
		end
	else
		output = output .. "\n\nEsse pokemon nao evolui."
	end
	if monsterType:isFlyable() > 0 or monsterType:isRideable() > 0 or monsterType:isSurfable() > 0 or monsterType:canTeleport() > 0 or race == "rock" or race2 == "rock" or race == "grass" or race2 == "grass" or race == "ground" or race2 == "ground" or race == "fighting" or race2 == "fighting" or self:getName() == "Ditto" or self:getName() == "Shiny Ditto" then
		output = output .. "\n\nHabilities:" .. "\n"
		if monsterType:isFlyable() > 0 then 
			output = output .. "\nFly"
		end
		if monsterType:isRideable() > 0 then 
			output = output .. "\nRide"
		end
		if monsterType:isSurfable() > 0 then 
			output = output .. "\nSurf"
		end
		if monsterType:canTeleport() > 0 then 
			output = output .. "\nTeleport"
		end
		if monsterType:getRaceName() == "rock" or monsterType:getRace2Name() == "rock" or monsterType:getRaceName() == "fighting" or monsterType:getRace2Name() == "fighting" then 
			output = output .. "\nRock Smash"
		end
		if monsterType:getRaceName() == "grass" or monsterType:getRace2Name() == "grass" then 
			output = output .. "\nCut"
		end
		if monsterType:getRaceName() == "ground" or monsterType:getRace2Name() == "ground" then 
			output = output .. "\nDig"
		end
		if self:getName() == "Ditto" or self:getName() == "Shiny Ditto" then 
			output = output .. "\nTransform"
		end
	else
		output = output .. "\n\nThis monster has no habilities."
	end
	output = output .. "\n\nPassivas:" .. "\n\n"
	if isInArray(hiddenabilities.stormdrain, self:getName()) then
		output = output .. "Storm Drain: Recebe bonus de ataque quando atingido por um ataque agua e ignora o dano.\n"
	end
	if self:getName() == 'Mimikyu' then
		output = output .. "Disguise: Possui uma chance de ignorar o dano de um ataque.\n"
	end
	if isInArray(hiddenabilities.counter, self:getName()) then
		output = output .. "Counter: Possui uma chance de retornar o dano fisico para o pokemon atacante.\n"
	end
	if isInArray(hiddenabilities.goodasgold, self:getName()) then
		output = output .. "Good as Gold: Imune a todo o tipo de status.\n"
	end
	if isInArray(hiddenabilities.waterbubble, self:getName()) then
		output = output .. "Water Bubble: Reduz o dano recebido de ataques do tipo fogo em 50%.\nAumenta o dano causado por ataques do tipo agua em 50%.\nImune a queimadura.\n"
	end
	if isInArray(hiddenabilities.magicbounce, self:getName()) then
		output = output .. "Magic Bounce: Reflete todas as condicoes para o atacante.\n"
	end
	if isInArray(hiddenabilities.adaptability, self:getName()) then
		output = output .. "Adaptability: Efetividade do STAB se torna 2.0 no lugar de 1.5.\n"
	end
	if isInArray(hiddenabilities.moldbreaker, self:getName()) then
		output = output .. "Mold Breaker: Ignora passivas de imunidades.\n"
	end
	if isInArray(hiddenabilities.normalize, self:getName()) then
		output = output .. "Normalize: Todos os ataques se tornam do tipo normal e aumenta o dano em 20%.\n"
	end
	if isInArray(hiddenabilities.pixilate, self:getName()) then
		output = output .. "Pixilate: Ataques do tipo normal se tornam do tipo fada e aumenta o dano em 30%.\n"
	end
	if isInArray(hiddenabilities.aerilate, self:getName()) then
		output = output .. "Aerilate: Ataques do tipo normal se tornam do tipo voador e aumenta o dano em 30%.\n"
	end
	if isInArray(hiddenabilities.refrigerate, self:getName()) then
		output = output .. "Refrigerate: Ataques do tipo normal se tornam do tipo gelo e aumenta o dano em 30%.\n"
	end
	if isInArray(hiddenabilities.galvanize, self:getName()) then
		output = output .. "Galvanize: Ataques do tipo normal se tornam do tipo eletrico e aumenta o dano em 20%.\n"
	end
	if isInArray(hiddenabilities.snowwarning, self:getName()) then
		output = output .. "Snow Warning: O pokemon causa uma tempestade de gelo a cada 10 segundos.\n"
	end
	if isInArray(hiddenabilities.ironbarbs, self:getName()) then
		output = output .. "Iron Barbs: O pokemon retorna 1/8 de todo dano fisico recebido.\n"
	end
	if isInArray(hiddenabilities.roughskin, self:getName()) then
		output = output .. "Rough Skin: Caso seja atingido por um ataque fisico, retorna 8% do dano.\n"
	end
	if isInArray(hiddenabilities.sandstream, self:getName()) then
		output = output .. "Sand Stream: O pokemon causa uma tempestade de areia a cada 10 segundos.\n"
	end
	if isInArray(hiddenabilities.swiftswim, self:getName()) then
		output = output .. "Swift Swim: O pokemon tem sua velocidade aumentada na chuva.\n"
	end
	if isInArray(hiddenabilities.sturdy, self:getName()) then
		output = output .. "Sturdy: Quando o pokemon recebe dano letal, o mesmo fica com 1 de vida por 5 segundos, imune a todo o dano.\n"
	end
	if isInArray(hiddenabilities.levitate, self:getName()) then
		output = output .. "Levitate: O pokemon se torna imune a ataques do tipo terra.\n"
	end
	if isInArray(hiddenabilities.innerfocus, self:getName()) then
		output = output .. "Inner Focus: O pokemon se torna imune a silence.\n"
	end
	if isInArray(hiddenabilities.chlorophyll, self:getName()) then
		output = output .. "Chlorophyll: O pokemon tem sua velocidade aumentada no sol.\n"
	end
	if isInArray(hiddenabilities.effectspore, self:getName()) then
		output = output .. "Effect Spore: Ao receber dano fisico o pokemon pode envenenar o adversario.\n"
	end
	if isInArray(hiddenabilities.infiltrator, self:getName()) then
		output = output .. "Infiltrator: O pokemon ignora habilidades de imunidade.\n"
	end
	if isInArray(hiddenabilities.owntempo, self:getName()) then
		output = output .. "Own Tempo: O pokemon se torna imune a confusion.\n"
	end
	if isInArray(hiddenabilities.sandveil, self:getName()) then
		output = output .. "Sand Veil: O pokemon tem sua evasao aumentada na tempestade de areia.\n"
	end
	if isInArray(hiddenabilities.pickup, self:getName()) then
		output = output .. "Pickup: O pokemon tem chance de encontrar itens pelo chao.\n"
	end
	if isInArray(hiddenabilities.waterabsorb, self:getName()) then
		output = output .. "Water Absorb: Absorve todo o dano recebido quando atingido por um ataque de agua.\n"
	end
	if isInArray(hiddenabilities.insomnia, self:getName()) then
		output = output .. "Insomnia: O pokemon se torna imune a sleep.\n"
	end
	if isInArray(hiddenabilities.static, self:getName()) then
		output = output .. "Static: Ao receber dano fisico o pokemon pode paralizar o adversario.\n"
	end
	if isInArray(hiddenabilities.hydration, self:getName()) then
		output = output .. "Hydration: O pokemon se cura de todas as condicoes na chuva.\n"
	end
	if isInArray(hiddenabilities.icebody, self:getName()) then
		output = output .. "Ice Body: O pokemon se cura na tempestade de neve.\n"
	end
	if isInArray(hiddenabilities.flamebody, self:getName()) then
		output = output .. "Flame Body: Ao receber dano fisico o pokemon pode queimar o adversario.\n"
	end
	if isInArray(hiddenabilities.poisontouch, self:getName()) then
		output = output .. "Poison Touch: Ao receber dano fisico o pokemon pode envenenar o adversario.\n"
	end
	if isInArray(hiddenabilities.poisonpoint, self:getName()) then
		output = output .. "Poison Point: Ao receber dano fisico o pokemon pode envenenar o adversario.\n"
	end
	if isInArray(hiddenabilities.lightningrod, self:getName()) then
		output = output .. "Lightning Rod: Recebe bonus de ataque quando atingido por um ataque eletrico e ignora o dano.\n"
	end
	if isInArray(hiddenabilities.clearbody, self:getName()) then
		output = output .. "Clear Body: O pokemon se torna imune a mudanca de status.\n"
	end
	if isInArray(hiddenabilities.synchronize, self:getName()) then
		output = output .. "Synchronize: Ao receber uma condicao de status, o adversario tambem recebe.\n"
	end
	if isInArray(hiddenabilities.sandforce, self:getName()) then
		output = output .. "Sand Force: Aumenta o ataque em uma tempestade de areia.\n"
	end
	if isInArray(hiddenabilities.snowcloak, self:getName()) then
		output = output .. "Snow Cloak: O pokemon tem sua evasao aumentada na tempestade de neve.\n"
	end
	if isInArray(hiddenabilities.scrappy, self:getName()) then
		output = output .. "Scrappy: O pokemon pode atingir pokemons do tipo fantasma.\n"
	end
	if isInArray(hiddenabilities.voltabsorb, self:getName()) then
		output = output .. "Volt Absorb: Absorve todo o dano recebido quando atingido por um ataque eletrico.\n"
	end
	if isInArray(hiddenabilities.raindish, self:getName()) then
		output = output .. "Rain Dish: O pokemon se cura na chuva.\n"
	end
	if isInArray(hiddenabilities.cursedbody, self:getName()) then
		output = output .. "Cursed Body: Ao receber um ataque fisico o pokemon pode silenciar o adversario.\n"
	end
	if isInArray(hiddenabilities.healer, self:getName()) then
		output = output .. "Healer: O pokemon cura seus aliados de condicoes de status periodicamente.\n"
	end
	if isInArray(hiddenabilities.flashfire, self:getName()) then
		output = output .. "Flash Fire: Recebe bonus de ataque quando atingido por um ataque fogo e ignora o dano.\n"
	end
	if self:getName() == "Shuckle" then
		output = output .. "Power Trick: Tem 33% de chance de utilizar a defesa como status principal para o ataque.\n"
	end
	
	return output
end

function Player.getPokedexStatus(self, firstStorage)
	local output = "Status of " .. self:getName() .. ".\n\n[id]Pokemon Tries/Catch-Shiny Tries/Catch\n\n"
	for i,v in pairs(monstersTable) do
		if self:getStorageValue(firstStorage + i) ~= -1 then
			if i <= 1000 or i > 3000 then
				if monstersTable[i] then
					output = output .. "[" .. i .. "]" .. monstersTable[i] 
					if self:getStorageValue(baseStorageTries + i) > 0 then
						output = output .. " " .. self:getStorageValue(baseStorageTries + i) 
					else
						output = output .. " 0"
					end
					if self:getStorageValue(baseStorageCatches + i) > 0 then
						output = output .. "/" .. self:getStorageValue(baseStorageCatches + i) 
					else
						output = output .. "/0"
					end
					if i <= 1000 then
						if self:getStorageValue(baseStorageTries + 2000 + i) > 0 then
							output = output .. "-" .. self:getStorageValue(baseStorageTries + 2000 + i)
						else
							output = output .. "-0"
						end
						if self:getStorageValue(baseStorageCatches + 2000 + i) > 0 then
							output = output .. "/" .. self:getStorageValue(baseStorageCatches + 2000 + i)
						else
							output = output .. "/0"
						end
					end
					output = output .. "\n"
				end
			end			
		end
	end
	return output
end

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if not target then return false end

	if type(target) ~= "userdata" then
		return true
	end

	if target ~= item and target:isCreature() ~= true then return false end

	if target:isCreature() then -- check if it is on dex or add to dex
		if not target:isMonster() then			
			local text = player:getPokedexStatus(baseStorageDex)
			if #text >= 1000 then
				player:showTextDialog(pokedexId, string.sub(text, math.floor(#text/2) + 1 , #text))
				player:showTextDialog(pokedexId, string.sub(text, 1 , math.floor(#text/2)))
			else
				player:showTextDialog(pokedexId, text)
			end
			return true 
		end
		local monsterNumber = MonsterType(target:getName()):dexEntry() --target:getMonsterNumber() 
		if monsterNumber == 0 then
			print("WARNING: Monster " .. target:getName() .. " does not have info entry.")
			player:sendCancelMessage("Sorry, not possible. This problem was reported.")			
			return true
		end
		local storage = baseStorageDex + monsterNumber
		if player:getStorageValue(storage) == -1 then -- add to dex	
			local givenExp = target:getExperience() * configManager.getNumber(configKeys.RATE_EXPERIENCE) * multiplier
			player:setStorageValue(storage, 0)
			getPlayerPosition(player):sendMagicEffect(329)
			player:addExperience(givenExp, true)
		else -- open status of monster
			getPlayerPosition(player):sendMagicEffect(300)
			local monsterType = MonsterType(target:getName())
			local portraitId = monsterType:portraitId()
			local portraitItemType = ItemType(portraitId)
			if portraitId == 0 or portraitItemType:getId() == 0 then portraitId = pokedexId end
			player:showTextDialog(portraitId, target:getSummonStatus())
		end -- add tries after this
--	else -- open dex general dialog
--		player:showTextDialog(pokedexId, player:getPokedexStatus(baseStorageDex))
	end
	return true
end
