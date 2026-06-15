local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)

local timeBetweenQuests = 12*60*60

local easyItems = {"bat wing", "bee sting", "bird beak", "bird feather", "bitten apple", "blue vines", "bone", "bug antenna", "bug venom", "bulb", "butterfly wing"}
local mediumItems = {"armadillo claw", "bear paw", "belt of champion", "big bat wing", "blue ball tail", "blue kick machine", "blue rat ear", "brush tail", "bull tail", "cat ear", "comb"}
local hardItems = {"aerodactyl wing", "bass horn", "big egg", "black spinner", "branch of stone", "electric paw", "technological zap", "volcano exhaust", "witch hat", "power banana", "zangoose fur", "electric fur", "volcano shell", "giant piece of fur", "giant green wing", "ice bra", "scythe", "scizor claw", "stone shell", "steel wings", "stranger tail", "bear paw", "cotton wings", "monkey paw", "wool ball", "dojo palm", "fighting cap", "metal scale"}

function onCreatureAppear(cid)              npcHandler:onCreatureAppear(cid)            end
function onCreatureDisappear(cid)           npcHandler:onCreatureDisappear(cid)         end
function onCreatureSay(cid, type, msg)      npcHandler:onCreatureSay(cid, type, msg)    end
function onThink()                          npcHandler:onThink()                        end

local voices = { {text = 'Nao encontro esses itens em lugar algum.'} }
npcHandler:addModule(VoiceModule:new(voices))

local function creatureSayCallback(cid, type, msg)
	if not npcHandler:isFocused(cid) then
		return false
	end

	local player = Player(cid)
	if not player then
		return false
	end

	if msgcontains(msg, "yes") or msgcontains(msg, "sim") or msgcontains(msg, "quest") or msgcontains(msg, "task") or msgcontains(msg, "ajudar") or msgcontains(msg, "ajuda") and npcHandler.topic[cid] == 0 then
		local timeSinceLast = os.time() - player:getStorageValue(storageItemQuestTime)
		local timeRemaining = timeBetweenQuests - timeSinceLast
		if (timeSinceLast > timeBetweenQuests) then
			npcHandler:say("Posso te passar uma missao {facil}, {media} ou {dificil}, mas lembre-se que missoes dificeis geralmente trazem melhores recompensas. Qual prefere?", cid)
			npcHandler.topic[cid] = 1
		elseif player:getStorageValue(storageItemQuestDay) == 0 then
			local itemId = player:getStorageValue(storageItemQuestItem)
			local number =  player:getStorageValue(storageItemQuestNumber)

			if not player:removeItem(itemId, number) then
				npcHandler:say("Volte com {" .. number .." " .. ItemType(itemId):getName() .. "} ou daqui " .. timeRemaining .. " segundos.", cid)
				npcHandler:releaseFocus(cid)
			else
				local tokens = 1
				if player:getStorageValue(storageItemQuestDifficulty) == 1 then
					tokens = math.random(1,10) * tokenVar
				elseif player:getStorageValue(storageItemQuestDifficulty) == 2 then
					tokens = math.random(11,20) * tokenVar
				elseif player:getStorageValue(storageItemQuestDifficulty) == 3 then
					tokens = math.random(21,30) * tokenVar
					local pokename = {"Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros", "Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite", "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar", "Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho", "Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom", "Serperior", "Emboar", "Samurott", "Chesnaught", "Delphox", "Greninja", "Decidueye", "Incineroar", "Primarina", "Alolan Raticate", "Alolan Raichu", "Alolan Sandslash", "Alolan Ninetales", "Alolan Dugtrio", "Alolan Persian", "Alolan Golem", "Alolan Muk", "Alolan Exeggutor", "Alolan Marowak", "Galarian Rapidash", "Sirfetch'd", "Galarian Weezing", "Mr. Rime", "Galarian Darmanitan", "Hisuian Arcanine", "Hisuian Electrode", "Hisuian Typhlosion", "Hisuian Samurott", "Hisuian Decidueye", "Hisuian Lilligant", "Hisuian Zoroark", "Hisuian Braviary", "Hisuian Goodra", "Hisuian Avalugg", "Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros", "Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite", "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar", "Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho", "Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom", "Serperior", "Emboar", "Samurott", "Chesnaught", "Delphox", "Greninja", "Decidueye", "Incineroar", "Primarina", "Butterfree", "Beedrill", "Raticate", "Fearow", "Arbok", "Vileplume", "Parasect", "Dugtrio", "Persian", "Primeape", "Rapidash", "Slowbro", "Farfetch'd", "Dodrio", "Cloyster", "Hypno", "Kingler", "Electrode", "Marowak", "Hitmonchan", "Hitmonlee", "Weezing", "Seaking", "Tauros", "Venusaur", "Charizard", "Blastoise", "Pidgeot", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Venomoth", "Golduck", "Arcanine", "Poliwrath", "Alakazam", "Machamp", "Victreebel", "Tentacruel", "Golem", "Dewgong", "Muk", "Gengar", "Exeggutor", "Kangaskhan", "Starmie", "Scyther", "Jynx", "Pinsir", "Gyarados", "Lapras", "Ditto", "Eevee", "Omastar", "Kabutops", "Aerodactyl", "Snorlax", "Dragonite", "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Sunflora", "Quagsire", "Slowking", "Wobbuffet", "Girafarig", "Forretress", "Dunsparce", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Ursaring", "Magcargo", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Tyranitar", "Sceptile", "Blaziken", "Swampert", "Mightyena", "Linoone", "Beautifly", "Dustox", "Ludicolo", "Shiftry", "Ninjask", "Shedinja", "Swellow", "Breloom", "Spinda", "Pelipper", "Masquerain", "Wailord", "Delcatty", "Kecleon", "Claydol", "Torkoal", "Sableye", "Whiscash", "Luvdisc", "Crawdaunt", "Milotic", "Sharpedo", "Flygon", "Hariyama", "Manectric", "Camerupt", "Walrein", "Cacturne", "Glalie", "Lunatone", "Solrock", "Grumpig", "Plusle", "Minun", "Mawile", "Medicham", "Altaria", "Slaking", "Swalot", "Tropius", "Exploud", "Huntail", "Gorebyss", "Absol", "Banette", "Seviper", "Zangoose", "Relicanth", "Aggron", "Castform", "Volbeat", "Illumise", "Cradily", "Armaldo", "Gardevoir", "Salamence", "Metagross", "Chimecho", "Torterra", "Infernape", "Empoleon", "Staraptor", "Bibarel", "Kricketune", "Luxray", "Roserade", "Rampardos", "Bastiodon", "Mothim", "Vespiquen", "Pachirisu", "Floatzel", "Cherrim", "Gastrodon", "Ambipom", "Drifblim", "Lopunny", "Mismagius", "Honchkrow", "Purugly", "Skuntank", "Bronzong", "Chatot", "Spiritomb", "Garchomp", "Lucario", "Hippowdon", "Drapion", "Toxicroak", "Carnivine", "Lumineon", "Abomasnow", "Weavile", "Magnezone", "Lickilicky", "Rhyperior", "Tangrowth", "Electivire", "Magmortar", "Togekiss", "Yanmega", "Gliscor", "Mamoswine", "Porygon-Z", "Gallade", "Probopass", "Dusknoir", "Froslass", "Rotom", "Serperior", "Emboar", "Samurott", "Chesnaught", "Delphox", "Greninja", "Decidueye", "Incineroar", "Primarina"}
					if not MonsterType(pokename[math.random(1, #pokename)]) then
							print("Player: "..player:getName().." with error, egg without name: "..pokename.."")
						end
						local egg = player:getInbox():addItem(36570, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
						egg:setSpecialAttribute("eggname", pokename[math.random(1, #pokename)])
						egg:setSpecialAttribute("steps", 0)
						player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Um pokemon egg foi enviado para seu depot.")
				end
				player:addTokens(tokens)
				npcHandler:say("Bom trabalho! Pegue " .. tokens .. " tokens como recompensa. Novo saldo: " .. player:getTokens() .. ".", cid)
				player:setStorageValue(storageItemQuestDay, -1)
				player:save()
				npcHandler:releaseFocus(cid)
			end
		else
			npcHandler:say("Ja pegou seu premio de hoje. Retorne daqui " .. timeRemaining .. " segundos." , cid)
			npcHandler:releaseFocus(cid)
		end
	elseif (msgcontains(msg, "facil") or msgcontains(msg, "easy") or msgcontains(msg, "media") or msgcontains(msg, "medium") or msgcontains(msg, "dificil") or msgcontains(msg, "hard") )and npcHandler.topic[cid] == 1 then
		player:setStorageValue(storageItemQuestDay, 0)
		player:setStorageValue(storageItemQuestTime, os.time())
		local itemName
		local number = 2
		if msgcontains(msg, "facil") or msgcontains(msg, "easy") then
			number = tostring(5*math.random(4, 8))
			itemName = easyItems[math.random(#easyItems)]
			player:setStorageValue(storageItemQuestDifficulty, 1)
		elseif msgcontains(msg, "media") or msgcontains(msg, "medium") then
			number = tostring(15*math.random(2, 4))
			itemName = mediumItems[math.random(#mediumItems)]
			player:setStorageValue(storageItemQuestDifficulty, 2)
		elseif msgcontains(msg, "dificil") or msgcontains(msg, "hard") then
			number = tostring(25*math.random(1, 2))
			itemName = hardItems[math.random(#hardItems)]
			player:setStorageValue(storageItemQuestDifficulty, 3)
		end
		local itemType = ItemType(itemName)
		if not itemType then
			print("WARNING! Item " .. itemName .. " not found on NPC Nate.")
			npcHandler:say("Encontramos um problema que ja foi reportado para os GMs.", cid)
			npcHandler:releaseFocus(cid)
		end
		player:setStorageValue(storageItemQuestNumber, number)
		player:setStorageValue(storageItemQuestItem, itemType:getId())
		npcHandler:say("Sei que voce e bom. Vamos ver se hoje voce consegue me trazer {" .. number .." " .. itemName .. "}.", cid)
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
