local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)

local timeBetweenQuests = 12*60*60

local easyPokes = {"Bulbasaur","Charmander","Squirtle","Caterpie","Metapod","Weedle","Kakuna","Pidgey","Rattata","Spearow","Ekans","Pikachu","Sandshrew","Nidoran Female","Nidoran Male","Vulpix","Jigglypuff","Zubat","Oddish","Paras","Venonat","Diglett","Meowth","Psyduck","Mankey","Poliwag","Abra","Machop","Bellsprout","Geodude","Magnemite","Doduo","Shellder","Gastly","Krabby","Cubone","Horsea","Goldeen","Magikarp","Dratini","Unown"}
local mediumPokes = {"Ivysaur","Charmeleon","Wartortle","Butterfree","Beedrill","Pidgeotto","Pidgeot","Raticate","Fearow","Arbok","Raichu","Sandslash","Nidorina","Nidorino","Clefairy","Clefable","Wigglytuff","Golbat","Gloom","Parasect","Venomoth","Dugtrio","Persian","Primeape","Growlithe","Poliwhirl","Kadabra","Machoke","Weepinbell","Tentacool","Graveler","Ponyta","Slowpoke","Magneton","Farfetch'd","Dodrio","Seel","Dewgong","Grimer","Haunter","Onix","Drowzee","Hypno","Kingler","Voltorb","Electrode","Exeggcute","Marowak","Hitmonlee","Hitmonchan","Lickitung","Koffing","Weezing","Rhyhorn","Tangela","Seadra","Seaking","Staryu","Mr._Mime","Jynx","Electabuzz","Eevee","Porygon","Omanyte","Kabuto","Dragonair","Furret","Noctowl","Ledian","Ariados","Lanturn","Xatu","Azumarill","Sudowoodo","Jumpluff","Sunflora","Quagsire","Wobbuffet","Girafarig","Forretress","Dunsparce","Granbull","Qwilfish","Magcargo","Corsola","Octillery","Delibird","Mantine","Skarmory","Stantler","Hitmontop"}
local hardPokes = {"Venusaur","Charizard","Blastoise","Nidoqueen","Nidoking","Ninetales","Vileplume","Golduck","Arcanine","Poliwrath","Alakazam","Machamp","Victreebel","Tentacruel","Golem","Rapidash","Slowbro","Muk","Cloyster","Gengar","Exeggutor","Rhydon","Chansey","Kangaskhan","Starmie","Scyther","Magmar","Pinsir","Tauros","Gyarados","Lapras","Vaporeon","Jolteon","Flareon","Omastar","Kabutops","Aerodactyl","Snorlax","Dragonite","Feraligatr","Crobat","Ampharos","Bellossom","Politoed","Espeon","Umbreon","Slowking","Steelix","Scizor","Shuckle","Heracross","Ursaring","Houndoom","Kingdra","Donphan","Porygon2","Miltank","Blissey","Tyranitar","Ditto"}

function onCreatureAppear(cid)              npcHandler:onCreatureAppear(cid)            end
function onCreatureDisappear(cid)           npcHandler:onCreatureDisappear(cid)         end
function onCreatureSay(cid, type, msg)      npcHandler:onCreatureSay(cid, type, msg)    end
function onThink()                          npcHandler:onThink()                        end

local voices = { {text = 'Estou sempre em busca do melhor catcher.'} }
npcHandler:addModule(VoiceModule:new(voices))

local function creatureSayCallback(cid, type, msg)
	if not npcHandler:isFocused(cid) then
		return false
	end

	local player = Player(cid)
	if not player then
		return false
	end

	if msgcontains(msg, "yes") or msgcontains(msg, "sim") or msgcontains(msg, "missao") or msgcontains(msg, "help") or msgcontains(msg, "task") and npcHandler.topic[cid] == 0 then
		local questStorage = player:getStorageValue(storageCatchQuest)
		if questStorage < 1 then
			if player:getStorageValue(baseStorageCatches + 19) < 2 then
				npcHandler:say("Gostaria que voce capturasse {2 rattatas} para mim. Quando capturar volte aqui! Caso nao queira, pode entrar no portal ali em baixo para ir para a cidade principal.", cid)
				npcHandler:releaseFocus(cid)
			else
				npcHandler:say("Bom trabalho! Pegue isso como uma recompensa. Tenho outra {missao} para voce.", cid)
				player:addItem(2152, 2)
				player:addItem(26660, 25)
				player:setStorageValue(storageCatchQuest, 1)
			end
		elseif questStorage == 1 then
			if player:getStorageValue(baseStorageCatches + 69) < 2 then
				npcHandler:say("Sua proxima missao e capturar {2 bellsprouts}. Depois disso retorne aqui que te darei um premio.", cid)
				npcHandler:releaseFocus(cid)
			else
				npcHandler:say("Incrivel, pegue esta bicicleta para auxiliar sua jornada! Entre no portal para ir a cidade principal, e lembre-se, eu tenho uma {missao} nova a cada 6 horas, caso queira receber mais premios!", cid)
				player:addItem(2152, 3)
				player:addItem(26660, 25)
				player:addItem(27634, 1)
				player:setStorageValue(storageCatchQuest, 2)
			end
		elseif questStorage > 1 then
			local timeSinceLast = os.time() - player:getStorageValue(storageCatchQuestTime)
			local timeRemaining = timeBetweenQuests - timeSinceLast
			if (timeSinceLast > timeBetweenQuests) then
				npcHandler:say("Posso te passar uma missao {facil}, {media} ou {dificil}, mas lembre-se que missoes dificeis geralmente trazem melhores recompensas. Qual prefere?", cid)
				npcHandler.topic[cid] = 1
			elseif player:getStorageValue(storageCatchQuestDay) == 0 then
				local pokeNumber = player:getStorageValue(storageCatchQuestPoke)
				local pokeName = monstersTable[pokeNumber]
				local number =  player:getStorageValue(storageCatchQuestNumber)
				local startCatch = player:getStorageValue(storageCatchQuestStartCatch)
				local currentCatch = player:getStorageValue(baseStorageCatches + pokeNumber)
				local catches = currentCatch - startCatch
				if catches < number then
					npcHandler:say("Volte depois de capturar {" .. number .." " .. pokeName .. "} ou daqui " .. timeRemaining .. " segundos.", cid)
					npcHandler:releaseFocus(cid)
				else
					local tokens = 1
					local premier
					if player:getStorageValue(storageCatchQuestDifficulty) == 1 then
						tokens = math.random(1,10) * tokenVar
					elseif player:getStorageValue(storageCatchQuestDifficulty) == 2 then
						tokens = math.random(11,20) * tokenVar
						premier = math.random(1, 3)
					elseif player:getStorageValue(storageCatchQuestDifficulty) == 3 then
						tokens = math.random(21,30) * tokenVar
						premier = math.random(1, 5)
						local eggname = {"Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros", "Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite", "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar", "Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho", "Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom", "Serperior", "Emboar", "Samurott", "Chesnaught", "Delphox", "Greninja", "Decidueye", "Incineroar", "Primarina", "Alolan Raticate", "Alolan Raichu", "Alolan Sandslash", "Alolan Ninetales", "Alolan Dugtrio", "Alolan Persian", "Alolan Golem", "Alolan Muk", "Alolan Exeggutor", "Alolan Marowak", "Galarian Rapidash", "Sirfetch'd", "Galarian Weezing", "Mr. Rime", "Galarian Darmanitan", "Hisuian Arcanine", "Hisuian Electrode", "Hisuian Typhlosion", "Hisuian Samurott", "Hisuian Decidueye", "Hisuian Lilligant", "Hisuian Zoroark", "Hisuian Braviary", "Hisuian Goodra", "Hisuian Avalugg", "Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros", "Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite", "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar", "Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho", "Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom", "Serperior", "Emboar", "Samurott", "Chesnaught", "Delphox", "Greninja", "Decidueye", "Incineroar", "Primarina", "Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros", "Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite", "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar", "Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho", "Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom", "Serperior", "Emboar", "Samurott", "Chesnaught", "Delphox", "Greninja", "Decidueye", "Incineroar", "Primarina"}
						if not MonsterType(eggname[math.random(1, #eggname)]) then
							print("Player: "..player:getName().." with error, egg without name: "..eggname.."")
						end
						local egg = player:getInbox():addItem(36570, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
						egg:setSpecialAttribute("eggname", eggname[math.random(1, #eggname)])
						egg:setSpecialAttribute("steps", 0)
						player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Um pokemon egg foi enviado para seu depot.")
					end
					local monsterType = MonsterType(pokeName)
					local rawPrice = math.abs(((monsterType:getHealth()/100) + (monsterType:getBaseSpeed() - 100) + monsterType:getMeleeDamage(self) + monsterType:getDefense() + monsterType:getMoveMagicAttackBase() + monsterType:getMoveMagicDefenseBase())* 12 - 1900)
					player:addMoney(rawPrice * 50)
					player:addTokens(tokens)
					player:addItem(26683, premier)
					npcHandler:say("Bom trabalho! Pegue " .. tokens .. " tokens como recompensa. Novo saldo: " .. player:getTokens() .. ".", cid)
					player:setStorageValue(storageCatchQuestDay, -1)
					player:save()
					npcHandler:releaseFocus(cid)
				end
			else
				npcHandler:say("Ja pegou seu premio de hoje. Voce podera fazer uma missao novamente depois de 6 horas desde que me entregou a ultima missao." , cid)
				npcHandler:releaseFocus(cid)
			end
		end
	elseif (msgcontains(msg, "facil") or msgcontains(msg, "easy") or msgcontains(msg, "media") or msgcontains(msg, "medium") or msgcontains(msg, "dificil") or msgcontains(msg, "hard")) and npcHandler.topic[cid] == 1 then
		player:setStorageValue(storageCatchQuestDay, 0)
		player:setStorageValue(storageCatchQuestTime, os.time())
		local pokeName
		local number = 2
		if msgcontains(msg, "facil") or msgcontains(msg, "easy") then
			number = tostring(math.random(3, 4))
			pokeName = easyPokes[math.random(#easyPokes)]
			player:setStorageValue(storageCatchQuestDifficulty, 1)
		elseif msgcontains(msg, "media") or msgcontains(msg, "medium") then
			number = tostring(math.random(2, 3))
			pokeName = mediumPokes[math.random(#mediumPokes)]
			player:setStorageValue(storageCatchQuestDifficulty, 2)
		elseif msgcontains(msg, "dificil") or msgcontains(msg, "hard") then
			number = tostring(math.random(1, 2))
			pokeName = hardPokes[math.random(#hardPokes)]
			player:setStorageValue(storageCatchQuestDifficulty, 3)
		end
		local monsterType = MonsterType(pokeName)
		if not monsterType then
			print("WARNING! Poke " .. pokeName .. " not found on NPC catcher.")
			npcHandler:say("Encontramos um problema que ja foi reportado para os GMs.", cid)
			npcHandler:releaseFocus(cid)
			return true
		end
		local pokeNumber = monsterType:dexEntry()
		local startCatch = player:getStorageValue(baseStorageCatches + pokeNumber)
		player:setStorageValue(storageCatchQuestNumber, number)
		player:setStorageValue(storageCatchQuestPoke, pokeNumber)
		player:setStorageValue(storageCatchQuestStartCatch, startCatch)
		npcHandler:say("Sei que voce e bom. Vamos ver se hoje voce consegue capturar {" .. number .." " .. pokeName .. "}.", cid)
		npcHandler:releaseFocus(cid)
	else
		if npcHandler.topic[cid] == 0 then
			npcHandler:say("Nao entendi. Gostaria de me {ajudar} com uma {task}?", cid)
			return tue
		elseif npcHandler.topic[cid] == 1 then
			npcHandler:say("Nao entendi. Gostaria de uma task {facil}, {media} ou {dificil}?", cid)
			return tue
		end
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
