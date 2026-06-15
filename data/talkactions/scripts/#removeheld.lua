local helds = {
	['held attack'] = 36473, -- Aumenta o ataque em porcentagem. 5/10
	['held defense'] = 36472, -- Aumenta a defesa em porcentagem. 5/10
	['held experience'] = 36474, -- Aumenta a experiencia em porcentagem. 25/50
	['held burn'] = 36475, -- Aumenta o dano do burn. 2/3
	['held poison'] = 36488, -- Aumenta o dano do poison. 2/3
	['held wing'] = 36489, -- Aumenta a velocidade de voo. 150/300
	['gold coin'] = 2148, -- Evolui pokemons na troca.
	['platinum coin'] = 2152, -- Evolui pokemons na troca.
	['crystal coin'] = 2160, -- Evolui pokemons na troca.
	['empty pokeball'] = 26662, -- Evolui pokemons na troca.
	['empty greatball'] = 26660, -- Evolui pokemons na troca.
	['empty ultraball'] = 26688, -- Evolui pokemons na troca.
	['empty premierball'] = 26683, -- Evolui pokemons na troca.
	['small potion'] = 27642, -- Evolui pokemons na troca.
	['great potion'] = 27643, -- Evolui pokemons na troca.
	['ultra potion'] = 27641, -- Evolui pokemons na troca.
	['hyper potion'] = 27647, -- Evolui pokemons na troca.
	['ultimate potion'] = 27646, -- Evolui pokemons na troca.
	['revive'] = 27645, -- Evolui pokemons na troca.
	['clean disk'] = 39044, -- Evolui pokemons na troca.
	['water stone'] = 26736, -- Evolui pokemons na troca.
	['fire stone'] = 26728, -- Evolui pokemons na troca.
	['thunder stone'] = 26734, -- Evolui pokemons na troca.
	['leaf stone'] = 26731, -- Evolui pokemons na troca.
	['ice stone'] = 38936, -- Evolui pokemons na troca.
	['moon stone'] = 26733, -- Evolui pokemons na troca.
	['sun stone'] = 26748, -- Evolui pokemons na troca.
	["king's rock"] = 26746, -- Evolui pokemons na troca.
	['upgrade'] = 38940, -- Evolui pokemons na troca.
	['dubious disk'] = 38937, -- Evolui pokemons na troca.
	['metal coat'] = 26747, -- Evolui pokemons na troca.
	['dragon scale'] = 26743, -- Evolui pokemons na troca.
	['protector'] = 38939, -- Evolui pokemons na troca.
	['magmarizer'] = 27738, -- Evolui pokemons na troca.
	['electirizer'] = 27684, -- Evolui pokemons na troca.
	['rusted sword'] = 39143,
	['rusted shield'] = 39144,
	['red orb'] = 39145,
	['blue orb'] = 39146,
	['light ball'] = 39147,
	['griseous orb'] = 39148,
	['gracidea'] = 39149,
	['prison bottle'] = 39150,
	['abomasite'] = 39197,
	['absolite'] = 39173,
	['aerodactylite'] = 39172,
	['aggronite'] = 39171,
	['alakazite'] = 39170,
	['altarianite'] = 39169,
	['ampharosite'] = 39168,
	['audinite'] = 39167,
	['banettite'] = 39166,
	['beedrillite'] = 39165,
	['blastoisinite'] = 39164,
	['blazikenite'] = 39163,
	['cameruptite'] = 39162,
	['charizardite x'] = 39161,
	['charizardite y'] = 39160,
	['diancite'] = 39159,
	['galladite'] = 39158,
	['garchompite'] = 39157,
	['gardevoirite'] = 39156,
	['gengarite'] = 39155,
	['glalitite'] = 39154,
	['gyaradosite'] = 39153,
	['heracronite'] = 39152,
	['houndoominite'] = 39151,
	['kangaskhanite'] = 39174,
	['latiasite'] = 39196,
	['latiosite'] = 39195,
	['lopunnite'] = 39194,
	['lucarionite'] = 39193,
	['manectite'] = 39192,
	['mawilite'] = 39191,
	['medichamite'] = 39190,
	['metagrossite'] = 39189,
	['mewtwonite x'] = 39188,
	['mewtwonite y'] = 39187,
	['pidgeotite'] = 39186,
	['pinsirite'] = 39185,
	['sablenite'] = 39184,
	['salamencite'] = 39183,
	['sceptilite'] = 39182,
	['scizorite'] = 39181,
	['sharpedonite'] = 39180,
	['slowbronite'] = 39179,
	['steelixite'] = 39178,
	['swampertite'] = 39177,
	['tyranitarite'] = 39176,
	['venusaurite'] = 39175,
}

function onSay(player, words, param)
	if player:getUsingBall() and player:getUsingBall():getSpecialAttribute('held') then
		if isInArray({"gold coin", "empty pokeball", "small potion", "clean disk", "empty greatball", "great potion", "platinum coin", "water stone", "fire stone", "leaf stone", "thunder stone", "ice stone", "empty ultraball", "ultra potion", "revive", "rare candy", "crystal coin", "king's rock", "moon stone", "upgrade", "dubious disk", "metal coat", "sun stone", "dragon scale", "protector", "magmarizer", "electirizer", "empty premierball", "hyper potion", 'rusted sword', 'rusted shield', 'red orb', 'blue orb', 'light ball', 'griseous orb', 'gracidea', 'prison bottle'}, player:getUsingBall():getSpecialAttribute('held')) then
			local heldItem = helds[player:getUsingBall():getSpecialAttribute('held')]
			if player:getUsingBall():setSpecialAttribute("held", 0) then
				if isInArray({2148, 26662, 26660, 26688, 27642, 27643, 27641, 27647, 27645}, heldItem) then
					player:addItem(heldItem, math.random(5, 20))
				else
					player:addItem(heldItem, 1)
				end
				player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce removeu o item "..heldItem:getName().." de seu pokemon.")
			end
		elseif helds[player:getUsingBall():getSpecialAttribute('held')] then
			local heldName = player:getUsingBall():getSpecialAttribute('held')
			local heldItem = helds[heldName]
			if player:getUsingBall():setSpecialAttribute("held", 0) then
				player:addItem(heldItem, 1)
				player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce removeu o held "..heldName.." de seu pokemon.")
			end
		end
	end
	return false
end