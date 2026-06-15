filledPokeball = 2325 -- lixo
maxFilledBalls = 6 -- lixo
firstPortrait = 27117 -- lixo

-- Bonus
expVar = 1
catchVar = 1
teraVar = 1
megaVar = 1
lendaVar = 1
tokenVar = 1
talismanVar = 1
catchNature = false


stonesId = { -- lixo
{"Water", 2267},
{"Fire", 1}
}

legendaryPokemons = {"Zapdos", "Articuno", "Moltres", "Mew", "Mewtwo", "Raikou", "Entei", "Suicune", "Ho-oh", "Lugia", "Celebi", "Regirock", "Regice", "Registeel", "Jirachi",  "Latias", "Latios", "Kyogre", "Groudon", "Deoxys", "Rayquaza", "Uxie", "Mesprit", "Azelf", "Dialga", "Palkia", "Heatran", "Regigigas", "Giratina", "Cresselia", "Phione", "Manaphy", "Darkrai", "Shaymin", "Arceus", "Victini", "Keldeo", "Meloetta", "Genesect", "Diancie", "Hoopa", "Volcanion", "Magearna", "Marshadow", "Zeraora", "Melmetal", "Zarude"}

unowns = {
	["a"] = 3468,
	["b"] = 3469,
	["c"] = 3470,
	["d"] = 3471,
	["e"] = 3472,
	["f"] = 3473,
	["g"] = 3474,
	["h"] = 3475,
	["i"] = 3476,
	["j"] = 3477,
	["k"] = 3478,
	["l"] = 3479,
	["m"] = 3480,
	["n"] = 3481,
	["o"] = 3482,
	["p"] = 3483,
	["q"] = 3484,
	["r"] = 3485,
	["s"] = 3486,
	["t"] = 3461,
	["u"] = 3462,
	["v"] = 3463,
	["w"] = 3464,
	["x"] = 3465,
	["y"] = 3466,
	["z"] = 3467,
}

wormadamtype = {
	[3487] = 3487,
	[3488] = 3488,
	[3489] = 3489,
}

talismanTable = {
  ['bulbasaur'] = {buff = 'grass', amount = 1.03, desc = 'Aumenta o dano do elemento grass em 3%'},
  ['ivysaur'] = {buff = 'grass', amount = 1.06, desc = 'Aumenta o dano do elemento grass em 6%'},
  ['venusaur'] = {buff = 'grass', amount = 1.09, desc = 'Aumenta o dano do elemento grass em 9%'},
  ['charmander'] = {buff = 'fire', amount = 1.03, desc = 'Aumenta o dano do elemento fire em 3%'},
  ['charmeleon'] = {buff = 'fire', amount = 1.06, desc = 'Aumenta o dano do elemento fire em 6%'},
  ['charizard'] = {buff = 'fire', amount = 1.09, desc = 'Aumenta o dano do elemento fire em 9%'},
  ['squirtle'] = {buff = 'water', amount = 1.03, desc = 'Aumenta o dano do elemento water em 3%'},
  ['wartortle'] = {buff = 'water', amount = 1.06, desc = 'Aumenta o dano do elemento water em 6%'},
  ['blastoise'] = {buff = 'water', amount = 1.09, desc = 'Aumenta o dano do elemento water em 9%'},
  ['caterpie'] = {buff = 'def', amount = 1.01, desc = 'Aumenta a defesa em 1%'},
  ['metapod'] = {buff = 'def', amount = 1.03, desc = 'Aumenta a defesa em 3%'},
  ['butterfree'] = {buff = 'def', amount = 1.05, desc = 'Aumenta a defesa em 5%'},
  ['weedle'] = {buff = 'atk', amount = 1.01, desc = 'Aumenta o ataque em 1%'},
  ['kakuna'] = {buff = 'atk', amount = 1.03, desc = 'Aumenta o ataque em 3%'},
  ['beedrill'] = {buff = 'atk', amount = 1.05, desc = 'Aumenta o ataque em 5%'},
  ['pidgey'] = {buff = 'fly', amount = 150, desc = 'Aumenta a velocidade de voo em 150'},
  ['pidgeotto'] = {buff = 'fly', amount = 300, desc = 'Aumenta a velocidade de voo em 300'},
  ['pidgeot'] = {buff = 'fly', amount = 500, desc = 'Aumenta a velocidade de voo em 500'},
  ['rattata'] = {buff = 'atk', amount = 1.01, desc = 'Aumenta o ataque em 1%'},
  ['raticate'] = {buff = 'atk', amount = 1.04, desc = 'Aumenta o ataque em 4%'},
  ['spearow'] = {buff = 'evade', amount = 3, desc = 'Aumenta a chance de evasao em 3%'},
  ['fearow'] = {buff = 'evade', amount = 5, desc = 'Aumenta a chance de evasao em 5%'},
  ['ekans'] = {buff = 'cure', amount = 10, desc = 'Concede 10% de chance de nao receber condicoes'},
  ['arbok'] = {buff = 'cure', amount = 20, desc = 'Concede 20% de chance de nao receber condicoes'},
  ['pikachu'] = {buff = 'electric', amount = 1.05, desc = 'Aumenta o dano do elemento electric em 5%'},
  ['raichu'] = {buff = 'electric', amount = 1.09, desc = 'Aumenta o dano do elemento electric em 9%'},
  ['sandshrew'] = {buff = 'def', amount = 1.04, desc = 'Aumenta a defesa em 4%'},
  ['sandslash'] = {buff = 'def', amount = 1.08, desc = 'Aumenta a defesa em 8%'},
  ['nidoran female'] = {buff = 'def', amount = 1.03, desc = 'Aumenta a defesa em 2%'},
  ['nidorina'] = {buff = 'def', amount = 1.05, desc = 'Aumenta a defesa em 4%'},
  ['nidoqueen'] = {buff = 'def', amount = 1.10, desc = 'Aumenta a defesa em 10%'},
  ['nidoran male'] = {buff = 'atk', amount = 1.02, desc = 'Aumenta o ataque em 2%'},
  ['nidorino'] = {buff = 'atk', amount = 1.04, desc = 'Aumenta o ataque em 4%'},
  ['nidoking'] = {buff = 'atk', amount = 1.10, desc = 'Aumenta o ataque em 10%'},
  ['clefairy'] = {buff = 'fairy', amount = 1.05, desc = 'Aumenta o dano do elemento fairy em 5%'},
  ['clefable'] = {buff = 'fairy', amount = 1.10, desc = 'Aumenta o dano do elemento fairy em 10%'},
  ['vulpix'] = {buff = 'fire', amount = 1.05, desc = 'Aumenta o dano do elemento fire em 5%'},
  ['ninetales'] = {buff = 'fire', amount = 1.10, desc = 'Aumenta o dano do elemento fire em 10%'},
  ['jigglypuff'] = {buff = 'ret_sleep', amount = 3, desc = '3% de chance de aplicar sleep no atacante'},
  ['wigglytuff'] = {buff = 'ret_sleep', amount = 6, desc = '6% de chance de aplicar sleep no atacante'},
  ['zubat'] = {buff = 'lifesteal', amount = 1.01, desc = 'Cura 1% de todo dano causado'},
  ['golbat'] = {buff = 'lifesteal', amount = 1.02, desc = 'Cura 2% de todo dano causado'},
  ['oddish'] = {buff = 'condi_poison', amount = 1.50, desc = 'Aumenta o dano de condition poison em 50%'},
  ['gloom'] = {buff = 'condi_poison', amount = 2.0, desc = 'Aumenta o dano de condition poison em 100%'},
  ['vileplume'] = {buff = 'condi_poison', amount = 2.5, desc = 'Aumenta o dano de condition poison em 150%'},
  ['paras'] = {buff = 'ret_poison', amount = 3, desc = '3% de chance de aplicar poison no atacante'},
  ['parasect'] = {buff = 'ret_poison', amount = 6, desc = '6% de chance de aplicar poison no atacante'},
  ['venonat'] = {buff = 'bug', amount = 1.02, desc = 'Aumenta o dano do elemento bug em 3%'},
  ['venomoth'] = {buff = 'bug', amount = 1.05, desc = 'Aumenta o dano do elemento bug em 5%'},
  ['diglett'] = {buff = 'ground', amount = 1.03, desc = 'Aumenta o dano do elemento ground em 3%'},
  ['dugtrio'] = {buff = 'ground', amount = 1.07, desc = 'Aumenta o dano do elemento ground em 7%'},
  ['meowth'] = {buff = 'money', amount = 1.02, desc = 'Converte 2% do dano em dinheiro para o jogador'},
  ['persian'] = {buff = 'money', amount = 1.05, desc = 'Converte 5% do dano em dinheiro para o jogador'},
  ['psyduck'] = {buff = 'spell_confusion', amount = 3, desc = 'Concede 3% de chance de utilizar o ataque confusion'},
  ['golduck'] = {buff = 'spell_confusion', amount = 6, desc = 'Concede 6% de chance de utilizar o ataque confusion'},
  ['mankey'] = {buff = 'atk', amount = 1.03, desc = 'Aumenta o ataque em 3%'},
  ['primeape'] = {buff = 'atk', amount = 1.05, desc = 'Aumenta o ataque em 5%'},
  ['growlithe'] = {buff = 'crit', amount = 3, desc = 'Ataques criticos causam 3x o dano'},
  ['arcanine'] = {buff = 'crit', amount = 4, desc = 'Ataques criticos causam 4x o dano'},
  ['poliwag'] = {buff = 'ret_confusion', amount = 2, desc = '2% de chance de aplicar confusion no atacante'},
  ['poliwhirl'] = {buff = 'ret_confusion', amount = 4, desc = '4% de chance de aplicar confusion no atacante'},
  ['poliwrath'] = {buff = 'ret_confusion', amount = 6, desc = '6% de chance de aplicar confusion no atacante'},
  ['abra'] = {buff = 'spatk', amount = 1.03, desc = 'Aumenta o ataque especial em 3%'},
  ['karabra'] = {buff = 'spatk', amount = 1.06, desc = 'Aumenta o ataque especial em 6%'},
  ['alakazam'] = {buff = 'spatk', amount = 1.09, desc = 'Aumenta o ataque especial em 9%'},
  ['machop'] = {buff = 'atk', amount = 1.03, desc = 'Aumenta o ataque em 3%'},
  ['machoke'] = {buff = 'atk', amount = 1.06, desc = 'Aumenta o ataque em 6%'},
  ['machamp'] = {buff = 'atk', amount = 1.09, desc = 'Aumenta o ataque em 9%'},
  ['bellsprout'] = {buff = 'grass', amount = 1.03, desc = 'Aumenta o dano do elemento grass em 3%'},
  ['weepinbell'] = {buff = 'grass', amount = 1.06, desc = 'Aumenta o dano do elemento grass em 6%'},
  ['victreebel'] = {buff = 'grass', amount = 1.10, desc = 'Aumenta o dano do elemento grass em 10%'},
  ['tentacool'] = {buff = 'ret_poison', amount = 5, desc = '5% de chance de aplicar poison no atacante'},
  ['tentacruel'] = {buff = 'ret_poison', amount = 10, desc = '10% de chance de aplicar poison no atacante'},
  ['geodude'] = {buff = 'rock', amount = 1.03, desc = 'Aumenta o dano do elemento rock em 3%'},
  ['graveler'] = {buff = 'rock', amount = 1.06, desc = 'Aumenta o dano do elemento rock em 6%'},
  ['golem'] = {buff = 'rock', amount = 1.10, desc = 'Aumenta o dano do elemento rock em 10%'},
  ['ponyta'] = {buff = 'condi_burn', amount = 1.5, desc = 'Aumenta o dano de condition poison em 50%'},
  ['rapidash'] = {buff = 'condi_burn', amount = 2, desc = 'Aumenta o dano de condition poison em 100%'},
  ['slowpoke'] = {buff = 'immunity', amount = 'confusion', desc = 'Concede imunidade a confusion'},
  ['slowbro'] = {buff = 'spdef', amount = '1.10', desc = 'Aumenta a defesa especial em 10%'},
  ['magnemite'] = {buff = 'eff_steel', amount = '1.10', desc = 'Causa 10% a mais de dano contra steel'},
  ['magneton'] = {buff = 'eff_steel', amount = '1.25', desc = 'Causa 25% a mais de dano contra steel'},
  ["farfetch'd"] = {buff = 'immunity', amount = 'silence', desc = 'Concede imunidade a silence'},
  ['doduo'] = {buff = 'physical', amount = 1.50, desc = 'Aumenta o auto ataque em 50%'},
  ['dodrio'] = {buff = 'physical', amount = 2, desc = 'Aumenta o auto ataque em 100%'},
  ['seel'] = {buff = 'condi_freezing', amount = 1.5, desc = 'Aumenta o dano de condition freeze em 150%'},
  ['dewgong'] = {buff = 'condi_freezing', amount = 3, desc = 'Aumenta o dano de condition freeze em 300%'},
  ['grimer'] = {buff = 'ret_poison', amount = 10, desc = '10% de chance de aplicar poison no atacante'},
  ['muk'] = {buff = 'ret_poison', amount = 20, desc = '20% de chance de aplicar poison no atacante'},
  ['shellder'] = {buff = 'return', amount = 0.01, desc = 'Retorna 1% de todo o dano recebido'},
  ['cloyster'] = {buff = 'return', amount = 0.03, desc = 'Retorna 3% de todo o dano recebido'},
  ['gastly'] = {buff = 'res_ground', amount = 0.50, desc = 'Reduz dano de ground em 50%'},
  ['haunter'] = {buff = 'immunity', amount = 'ground', desc = 'Concede imunidade a ground'},
  ['gengar'] = {buff = 'ret_silence', amount = 3, desc = '3% de chance de aplicar silence no atacante'},
  ['onix'] = {buff = 'rock', amount = 1.09, desc = 'Aumenta o dano do elemento rock em 9%'},
  ['drowzee'] = {buff = 'ret_sleep', amount = 1.04, desc = '4% de chance de aplicar sleep no atacante'},
  ['hypno'] = {buff = 'ret_sleep', amount = 1.08, desc = '8% de chance de aplicar sleep no atacante'},
  ['krabby'] = {buff = 'atk', amount = 1.02, desc = 'Aumenta o ataque em 2%'},
  ['kingler'] = {buff = 'atk', amount = 1.05, desc = 'Aumenta o ataque em 5%'},
  ['voltorb'] = {buff = 'ret_paralyze', amount = 1.03, desc = '3% de chance de aplicar paralyze no atacante'},
  ['electrode'] = {buff = 'ret_paralyze', amount = 1.05, desc = '5% de chance de aplicar paralyze no atacante'},
  ['exeggcute'] = {buff = 'eff_water', amount = '1.10', desc = 'Causa 10% a mais de dano contra water'},
  ['exeggutor'] = {buff = 'eff_water', amount = '1.25', desc = 'Causa 25% a mais de dano contra water'},
  ['cubone'] = {buff = 'res_electric', amount = 0.50, desc = 'Reduz dano de electric em 50%'},
  ['marowak'] = {buff = 'immunity', amount = 'electric', desc = 'Concede imunidade a electric'},
  ["hitmonlee"] = {buff = 'immunity', amount = 'paralyze', desc = 'Concede imunidade a paralyze'},
  ["hitmonchan"] = {buff = 'immunity', amount = 'silence', desc = 'Concede imunidade a silence'},
  ["lickitung"] = {buff = 'hp', amount = 1.10, desc = 'Aumenta HP em 10%'},
  ['koffing'] = {buff = 'ret_silence', amount = 2, desc = '2% de chance de aplicar silence no atacante'},
  ['weezing'] = {buff = 'ret_poison', amount = 15, desc = '15% de chance de aplicar poison no atacante'},
  ['rhyhorn'] = {buff = 'atk', amount = 1.03, desc = 'Aumenta o ataque em 3%'},
  ['rhydon'] = {buff = 'atk', amount = 1.06, desc = 'Aumenta o ataque em 6%'},
  ["chansey"] = {buff = 'exp', amount = 1.10, desc = 'Aumenta experiencia recebida em 10%'},
  ["tangela"] = {buff = 'grass', amount = 1.08, desc = 'Aumenta o dano do elemento grass em 8%'},
  ["kangaskhan"] = {buff = 'normal', amount = 1.10, desc = 'Aumenta o dano do elemento normal em 10%'},
  ['horsea'] = {buff = 'crit', amount = 2.5, desc = 'Ataques criticos causam 2.5x o dano'},
  ['seadra'] = {buff = 'crit', amount = 3, desc = 'Ataques criticos causam 3x o dano'},
  ['goldeen'] = {buff = 'res_electric', amount = 0.50, desc = 'Reduz dano de electric em 50%'},
  ['seaking'] = {buff = 'immunity', amount = 'electric', desc = 'Concede imunidade a electric'},
  ['staryu'] = {buff = 'water', amount = 1.03, desc = 'Aumenta o dano do elemento water em 3%'},
  ['starmie'] = {buff = 'psychic', amount = 1.08, desc = 'Aumenta o dano do elemento psychic em 8%'},
  ['mr. mime'] = {buff = 'psychic', amount = 1.10, desc = 'Aumenta o dano do elemento psychic em 10%'},
  ['scyther'] = {buff = 'flying', amount = 1.10, desc = 'Aumenta o dano do elemento flying em 10%'},
  ['jynx'] = {buff = 'ice', amount = 1.10, desc = 'Aumenta o dano do elemento ice em 10%'},
  ['electabuzz'] = {buff = 'electric', amount = 1.10, desc = 'Aumenta o dano do elemento electric em 10%'},
  ['magmar'] = {buff = 'fire', amount = 1.10, desc = 'Aumenta o dano do elemento fire em 10%'},
  ['pinsir'] = {buff = 'bug', amount = 1.10, desc = 'Aumenta o dano do elemento bug em 10%'},
  ['tauros'] = {buff = 'atk', amount = 1.10, desc = 'Aumenta o ataque em 10%'},
  ['magikarp'] = {buff = 'atk', amount = 1.01, desc = 'Aumenta o ataque em 1%'},
  ['gyarados'] = {buff = 'water', amount = 1.10, desc = 'Aumenta o dano do elemento water em 10%'},
  ['lapras'] = {buff = 'immunity', amount = 'water', desc = 'Concede imunidade a water'},
  ['ditto'] = {buff = 'all', amount = '1.05', desc = 'Aumenta todos os status em 5%'},
  ['eevee'] = {buff = 'love', amount = 2, desc = 'O pokemon recebe o dobro de love points'},
  ['vaporeon'] = {buff = 'immunity', amount = 'water', desc = 'Concede imunidade a water'},
  ['jolteon'] = {buff = 'immunity', amount = 'electric', desc = 'Concede imunidade a electric'},
  ['flareon'] = {buff = 'immunity', amount = 'fire', desc = 'Concede imunidade a fire'},
  ['porygon'] = {buff = 'ev', amount = 2, desc = 'O pokemon recebe o dobro de ev points'},
  ['omanyte'] = {buff = 'def', amount = 1.05, desc = 'Aumenta a defesa em 5%'},
  ['omastar'] = {buff = 'def', amount = 1.10, desc = 'Aumenta a defesa em 10%'},
  ['kabuto'] = {buff = 'atk', amount = 1.05, desc = 'Aumenta o ataque em 5%'},
  ['kabutops'] = {buff = 'atk', amount = 1.10, desc = 'Aumenta o ataque em 10%'},
  ['aerodactyl'] = {buff = 'rock', amount = 1.10, desc = 'Aumenta o dano do elemento rock em 10%'},
  ["snorlax"] = {buff = 'hp', amount = 1.15, desc = 'Aumenta HP em 15%'},
  ['articuno'] = {buff = 'ice', amount = 1.25, desc = 'Aumenta o dano do elemento ice em 25%'},
  ['zapdos'] = {buff = 'electric', amount = 1.25, desc = 'Aumenta o dano do elemento electric em 25%'},
  ['moltres'] = {buff = 'fire', amount = 1.25, desc = 'Aumenta o dano do elemento fire em 25%'},
  ['dratini'] = {buff = 'dragon', amount = 1.03, desc = 'Aumenta o dano do elemento dragon em 3%'},
  ['dragonair'] = {buff = 'dragon', amount = 1.06, desc = 'Aumenta o dano do elemento dragon em 6%'},
  ['dragonite'] = {buff = 'dragon', amount = 1.09, desc = 'Aumenta o dano do elemento dragon em 9%'},
  ['mewtwo'] = {buff = 'spatk', amount = '1.20', desc = 'Aumenta o ataque especial em 20%'},
  ['mew'] = {buff = 'all', amount = '1.10', desc = 'Aumenta todos os status em 10%'},
  
  ['chikorita'] = {buff = 'healing', amount = 1.05, desc = 'Aumenta cura total realiza em 5%'},
  ['bayleef'] = {buff = 'healing', amount = 1.10, desc = 'Aumenta cura total realiza em 10%'},
  ['meganium'] = {buff = 'healing', amount = 1.15, desc = 'Aumenta cura total realiza em 15%'},
  ['cyndaquil'] = {buff = 'evade', amount = 3, desc = 'Aumenta a chance de evasao em 3%'},
  ['quilava'] = {buff = 'evade', amount = 6, desc = 'Aumenta a chance de evasao em 6%'},
  ['typhlosion'] = {buff = 'evade', amount = 9, desc = 'Aumenta a chance de evasao em 9%'},
  ['totodile'] = {buff = 'res_fire', amount = 0.15, desc = 'Reduz dano de fire em 15%'},
  ['croconaw'] = {buff = 'res_fire', amount = 0.30, desc = 'Reduz dano de fire em 30%'},
  ['feraligatr'] = {buff = 'res_fire', amount = 0.50, desc = 'Reduz dano de fire em 50%'},
  ['furret'] = {buff = 'normal', amount = 1.08, desc = 'Aumenta o dano do elemento normal em 8%'},
  ['noctowl'] = {buff = 'immunity', amount = 'sleep', desc = 'Concede imunidade a sleep'},
  ['ledian'] = {buff = 'bug', amount = 1.07, desc = 'Aumenta o dano do elemento bug em 7%'},
  ['ariados'] = {buff = 'crit', amount = 2.5, desc = 'Ataques criticos causam 2.5 o dano'},
  ['crobat'] = {buff = 'lifesteal', amount = 1.05, desc = 'Cura 5% de todo dano causado'},
  ['lanturn'] = {buff = 'electric', amount = 1.08, desc = 'Aumenta o dano do elemento electric em 8%'},
  ['xatu'] = {buff = 'cure', amount = 25, desc = 'Concede 25% de chance de nao receber condicoes'},
  ['ampharos'] = {buff = 'electric', amount = 1.10, desc = 'Aumenta o dano do elemento electric em 10%'},
  ['bellossom'] = {buff = 'healing', amount = 1.25, desc = 'Aumenta cura total realiza em 25%'},
  ['azumarill'] = {buff = 'atk', amount = 1.10, desc = 'Aumenta o Attack em 10%'},
  ['sudowoodo'] = {buff = 'rock', amount = 1.10, desc = 'Aumenta o dano do elemento rock em 10%'},
  ['politoed'] = {buff = 'water', amount = 1.10, desc = 'Aumenta o dano do elemento water em 10%'},
  ['jumpluff'] = {buff = 'res_grass', amount = 0.33, desc = 'Reduz dano de grass em 33%'},
  ['sunflora'] = {buff = 'grass', amount = 1.10, desc = 'Aumenta o dano do elemento grass em 10%'},
  ['quagsire'] = {buff = 'immunity', amount = 'electric', desc = 'Concede imunidade a electric'},
  ['espeon'] = {buff = 'immunity', amount = 'psychic', desc = 'Concede imunidade a psychic'},
  ['umbreon'] = {buff = 'immunity', amount = 'dark', desc = 'Concede imunidade a dark'},
  ['slowking'] = {buff = 'psychic', amount = 1.10, desc = 'Aumenta o dano do elemento psychic em 10%'},
  ['unown'] = {buff = 'psychic', amount = 1.03, desc = 'Aumenta o dano do elemento psychic em 3%'},
  ['wobbuffet'] = {buff = 'return', amount = 0.05, desc = 'Retorna 5% de todo o dano recebido'},
  ['girafarig'] = {buff = 'immunity', amount = 'ghost', desc = 'Concede imunidade a ghost'},
  ['forretress'] = {buff = 'def', amount = 1.15, desc = 'Aumenta a defesa em 15%'},
  ['dunsparce'] = {buff = 'eff_dragon', amount = '1.25', desc = 'Causa 25% a mais de dano contra dragon'},
  ['steelix'] = {buff = 'steel', amount = 1.10, desc = 'Aumenta o dano do elemento steel em 10%'},
  ['granbull'] = {buff = 'fairy', amount = 1.10, desc = 'Aumenta o dano do elemento fairy em 10%'},
  ['scizor'] = {buff = 'spdef', amount = '1.15', desc = 'Aumenta a defesa especial em 15%'},
  ['shuckle'] = {buff = 'def', amount = 1.25, desc = 'Aumenta a defesa em 25%'},
  ['heracross'] = {buff = 'fighting', amount = 1.10, desc = 'Aumenta o dano do elemento fighting em 10%'},
  ["ursaring"] = {buff = 'normal', amount = 1.10, desc = 'Aumenta o dano do elemento normal em 10%'},
  ['magcargo'] = {buff = 'ret_burn', amount = 10, desc = '10% de chance de aplicar burn no atacante'},
  ['octillery'] = {buff = 'crit', amount = 3, desc = 'Ataques criticos causam 3x o dano'},
  ['delibird'] = {buff = 'immunity', amount = 'sleep', desc = 'Concede imunidade a sleep'},
  ["mantine"] = {buff = 'immunity', amount = 'burn', desc = 'Concede imunidade a burn'},
  ['skarmory'] = {buff = 'steel', amount = 1.05, desc = 'Aumenta o dano do elemento steel em 5%'},
  ['houndoom'] = {buff = 'dark', amount = 1.05, desc = 'Aumenta o dano do elemento dark em 5%'},
  ['kingdra'] = {buff = 'crit', amount = 4, desc = 'Ataques criticos causam 4x o dano'},
  ['donphan'] = {buff = 'ground', amount = 1.10, desc = 'Aumenta o dano do elemento ground em 10%'},
  ['porygon2'] = {buff = 'ev', amount = 3, desc = 'O pokemon recebe o triplo de ev points'},
  ["stantler"] = {buff = 'normal', amount = 1.08, desc = 'Aumenta o dano do elemento normal em 8%'},
  ["smeargle"] = {buff = 'exp', amount = 1.05, desc = 'Aumenta experiencia recebida em 5%'},
  ["hitmontop"] = {buff = 'immunity', amount = 'silence', desc = 'Concede imunidade a silence'},
  ['miltank'] = {buff = 'healing', amount = 1.33, desc = 'Aumenta cura total realiza em 33%'},
  ["blissey"] = {buff = 'egg', amount = 2, desc = 'Adiciona 2 passos extras ao chocar um ovo.'},
  ['raikou'] = {buff = 'eff_electric', amount = '2', desc = 'Causa 100% a mais de dano contra electric'},
  ['entei'] = {buff = 'eff_fire', amount = '2', desc = 'Causa 100% a mais de dano contra fire'},
  ['suicune'] = {buff = 'eff_water', amount = '2', desc = 'Causa 100% a mais de dano contra water'},
  ['tyranitar'] = {buff = 'dark', amount = 1.10, desc = 'Aumenta o dano do elemento dark em 10%'},
  ['lugia'] = {buff = 'spdef', amount = '1.25', desc = 'Aumenta a defesa especial em 25%'},
  ['ho-oh'] = {buff = 'spatk', amount = '1.25', desc = 'Aumenta o ataque especial em 25%'},
  ['celebi'] = {buff = 'healing', amount = 2, desc = 'Aumenta cura total realiza em 100%'},
  
  
  ['sceptile'] = {buff = 'res_grass', amount = 0.50, desc = 'Reduz dano de grass em 50%'},
  ['blaziken'] = {buff = 'res_fire', amount = 0.50, desc = 'Reduz dano de fire em 50%'},
  ['swampert'] = {buff = 'res_water', amount = 0.50, desc = 'Reduz dano de water em 50%'},
  ['mightyena'] = {buff = 'dark', amount = 1.08, desc = 'Aumenta o dano do elemento dark em 8%'},
  ['linoone'] = {buff = 'res_normal', amount = 0.33, desc = 'Reduz dano de normal em 33%'},
  ['beautifly'] = {buff = 'flying', amount = 1.05, desc = 'Aumenta o dano do elemento flying em 5%'},
  ['dustox'] = {buff = 'poison', amount = 1.05, desc = 'Aumenta o dano do elemento poison em 5%'},
  ['ludicolo'] = {buff = 'spdef', amount = '1.08', desc = 'Aumenta a defesa especial em 8%'},
  ['shiftry'] = {buff = 'atk', amount = 1.10, desc = 'Aumenta o ataque em 10%'},
  ['swellow'] = {buff = 'fly', amount = 500, desc = 'Aumenta a velocidade de voo em 500'},
  ['pelipper'] = {buff = 'res_electric', amount = 0.33, desc = 'Reduz dano de electric em 33%'},
  ['gardevoir'] = {buff = 'spatk', amount = '1.08', desc = 'Aumenta o ataque especial em 8%'},
  ['masquerain'] = {buff = 'res_rock', amount = 0.33, desc = 'Reduz dano de rock em 33%'},
  ['breloom'] = {buff = 'immunity', amount = 'poison', desc = 'Concede imunidade a poison'},
  ['slaking'] = {buff = 'atk', amount = 1.20, desc = 'Aumenta o ataque em 20%'},
  ['ninjask'] = {buff = 'flying', amount = 1.08, desc = 'Aumenta o dano do elemento flying em 8%'},
  ['shedinja'] = {buff = 'ghost', amount = 1.08, desc = 'Aumenta o dano do elemento ghost em 8%'},
  ['exploud'] = {buff = 'ignore', amount = 1, desc = 'Ignora imunidade por tipagem'},
  ['hariyama'] = {buff = 'fighting', amount = 1.08, desc = 'Aumenta o dano do elemento fighting em 8%'},
  ["delcatty"] = {buff = 'normal', amount = 1.05, desc = 'Aumenta o dano do elemento normal em 5%'},
  ['sableye'] = {buff = 'ghost', amount = 1.10, desc = 'Aumenta o dano do elemento ghost em 10%'},
  ['mawile'] = {buff = 'immunity', amount = 'fighting', desc = 'Concede imunidade a fighting'},
  ['aggron'] = {buff = 'def', amount = '1.15', desc = 'Aumenta a defesa em 15%'},
  ['medicham'] = {buff = 'fighting', amount = 1.05, desc = 'Aumenta o dano do elemento fighting em 5%'},
  ['manectric'] = {buff = 'electric', amount = 1.08, desc = 'Aumenta o dano do elemento electric em 8%'},
  ['plusle'] = {buff = 'spatk', amount = '1.03', desc = 'Aumenta o ataque especial em 3%'},
  ['minun'] = {buff = 'spdef', amount = '1.03', desc = 'Aumenta a defesa especial em 3%'},
  ['volbeat'] = {buff = 'atk', amount = 1.03, desc = 'Aumenta o ataque em 3%'},
  ['plusle'] = {buff = 'spatk', amount = '1.03', desc = 'Aumenta o ataque especial em 3%'},
  ['swalot'] = {buff = 'poison', amount = 1.10, desc = 'Aumenta o dano do elemento ghost em 10%'},
  ['sharpedo'] = {buff = 'atk', amount = 1.08, desc = 'Aumenta o ataque em 8%'},
  ["wailord"] = {buff = 'hp', amount = 1.30, desc = 'Aumenta HP em 30%'},
  ['camerupt'] = {buff = 'ret_burn', amount = 15, desc = '15% de chance de aplicar burn no atacante'},
  ['torkoal'] = {buff = 'fire', amount = 1.08, desc = 'Aumenta o dano do elemento fire em 8%'},
  ['grumpig'] = {buff = 'psychic', amount = 1.08, desc = 'Aumenta o dano do elemento psychic em 8%'},
  ['spinda'] = {buff = 'immunity', amount = 'confusion', desc = 'Concede imunidade a confusion'},
  ['flygon'] = {buff = 'dragon', amount = 1.08, desc = 'Aumenta o dano do elemento dragon em 8%'},
  ['cacturne'] = {buff = 'ret_poison', amount = 15, desc = '15% de chance de aplicar poison no atacante'},
  ['altaria'] = {buff = 'cure', amount = 25, desc = 'Concede 25% de chance de nao receber condicoes'},
  ['zangoose'] = {buff = 'normal', amount = 1.10, desc = 'Aumenta o dano do elemento normal em 10%'},
  ['seviper'] = {buff = 'poison', amount = 1.10, desc = 'Aumenta o dano do elemento ghost em 10%'},
  ['lunatone'] = {buff = 'fairy', amount = 1.15, desc = 'Aumenta o dano do elemento fairy em 15%'},
  ['solrock'] = {buff = 'fire', amount = 1.15, desc = 'Aumenta o dano do elemento fire em 15%'},
  ['whiscash'] = {buff = 'immunity', amount = 'electric', desc = 'Concede imunidade a electric'},
  ['crawdaunt'] = {buff = 'atk', amount = 1.08, desc = 'Aumenta o ataque em 8%'},
  ['claydol'] = {buff = 'spdef', amount = '1.08', desc = 'Aumenta a defesa especial em 8%'},
  ['cradily'] = {buff = 'healing', amount = 1.25, desc = 'Aumenta cura total realiza em 25%'},
  ['armaldo'] = {buff = 'atk', amount = 1.10, desc = 'Aumenta o ataque em 10%'},
  ['milotic'] = {buff = 'water', amount = 1.15, desc = 'Aumenta o dano do elemento water em 15%'},
  ['castform'] = {buff = 'all', amount = '1.02', desc = 'Aumenta todos os status em 2%'},
  ['kecleon'] = {buff = 'all', amount = '1.02', desc = 'Aumenta todos os status em 2%'},
  ['banette'] = {buff = 'ret_silence', amount = 5, desc = '5% de chance de aplicar silence no atacante'},
  ['tropius'] = {buff = 'eff_ground', amount = '1.25', desc = 'Causa 25% a mais de dano contra ground'},
  ['chimecho'] = {buff = 'eff_ghost', amount = '1.15', desc = 'Causa 15% a mais de dano contra ghost'},
  ['absol'] = {buff = 'atk', amount = 1.13, desc = 'Aumenta o ataque em 13%'},
  ['glalie'] = {buff = 'ice', amount = 1.08, desc = 'Aumenta o dano do elemento ice em 8%'},
  ['walrein'] = {buff = 'ret_freezing', amount = 15, desc = '15% de chance de aplicar freezing no atacante'},
  ['huntail'] = {buff = 'atk', amount = 1.05, desc = 'Aumenta o ataque em 5%'},
  ['gorebyss'] = {buff = 'spatk', amount = '1.05', desc = 'Aumenta o ataque especial em 5%'},
  ['relicanth'] = {buff = 'rock', amount = 1.15, desc = 'Aumenta o dano do elemento rock em 15%'},
  ['luvdisc'] = {buff = 'healing', amount = 1.05, desc = 'Aumenta cura total realiza em 5%'},
  ['salamence'] = {buff = 'dragon', amount = 1.10, desc = 'Aumenta o dano do elemento dragon em 15%'},
  ['metagross'] = {buff = 'steel', amount = 1.10, desc = 'Aumenta o dano do elemento dragon em 15%'},
  ['regirock'] = {buff = 'eff_rock', amount = '2', desc = 'Causa 100% a mais de dano contra rock'},
  ['regice'] = {buff = 'eff_ice', amount = '2', desc = 'Causa 100% a mais de dano contra ice'},
  ['registeel'] = {buff = 'eff_steel', amount = '2', desc = 'Causa 100% a mais de dano contra steel'},
  ['latias'] = {buff = 'spdef', amount = '1.20', desc = 'Aumenta a defesa especial em 20%'},
  ['latios'] = {buff = 'spatk', amount = '1.20', desc = 'Aumenta o ataque especial em 20%'},
  ['kyogre'] = {buff = 'water', amount = 1.25, desc = 'Aumenta o dano do elemento water em 25%'},
  ['groudon'] = {buff = 'ground', amount = 1.25, desc = 'Aumenta o dano do elemento ground em 25%'},
  ['rayquaza'] = {buff = 'dragon', amount = 1.25, desc = 'Aumenta o dano do elemento dragon em 25%'},
  ['jirachi'] = {buff = 'steel', amount = 1.25, desc = 'Aumenta o dano do elemento steel em 25%'},
  ['deoxys'] = {buff = 'psychic', amount = 1.25, desc = 'Aumenta o dano do elemento psychic em 25%'},
  
  ['torterra'] = {buff = 'ground', amount = 1.09, desc = 'Aumenta o dano do elemento ground em 9%'},
  ['infernape'] = {buff = 'fighting', amount = 1.09, desc = 'Aumenta o dano do elemento fighting em 9%'},
  ['empoleon'] = {buff = 'steel', amount = 1.09, desc = 'Aumenta o dano do elemento steel em 9%'},
  ['staraptor'] = {buff = 'atk', amount = 1.07, desc = 'Aumenta o ataque em 7%'},
  ['bibarel'] = {buff = 'water', amount = 1.07, desc = 'Aumenta o dano do elemento water em 7%'},
  ['kricketune'] = {buff = 'bug', amount = 1.07, desc = 'Aumenta o dano do elemento bug em 7%'},
  ['luxray'] = {buff = 'electric', amount = 1.07, desc = 'Aumenta o dano do elemento electric em 7%'},
  ['luxray'] = {buff = 'grass', amount = 1.07, desc = 'Aumenta o dano do elemento grass em 7%'},
  ['rampardos'] = {buff = 'atk', amount = 1.10, desc = 'Aumenta o ataque em 10%'},
  ['bastiodon'] = {buff = 'def', amount = '1.10', desc = 'Aumenta a defesa em 10%'},
  ['wormadam'] = {buff = 'spdef', amount = '1.07', desc = 'Aumenta a defesa especial em 7%'},
  ['mothim'] = {buff = 'flying', amount = 1.07, desc = 'Aumenta o dano do elemento flying em 7%'},
  ['vespiquen'] = {buff = 'bug', amount = 1.10, desc = 'Aumenta o dano do elemento bug em 10%'},
  ['pachirisu'] = {buff = 'electric', amount = 1.10, desc = 'Aumenta o dano do elemento electric em 10%'},
  ['floatzel'] = {buff = 'eff_water', amount = '1.25', desc = 'Causa 25% a mais de dano contra water'},
  ['cherrim'] = {buff = 'eff_grass', amount = '1.25', desc = 'Causa 25% a mais de dano contra grass'},
  ['gastrodon'] = {buff = 'immunity', amount = 'water', desc = 'Concede imunidade a water'},
  ['ambipom'] = {buff = 'normal', amount = 1.07, desc = 'Aumenta o dano do elemento normal em 7%'},
  ['drifblim'] = {buff = 'ghost', amount = 1.07, desc = 'Aumenta o dano do elemento ghost em 7%'},
  ['lopunny'] = {buff = 'normal', amount = 1.10, desc = 'Aumenta o dano do elemento normal em 10%'},
  ['mismagius'] = {buff = 'ghost', amount = 1.10, desc = 'Aumenta o dano do elemento ghost em 10%'},
  ['honchkrow'] = {buff = 'dark', amount = 1.07, desc = 'Aumenta o dano do elemento dark em 7%'},
  ['purugly'] = {buff = 'res_fire', amount = 0.25, desc = 'Reduz dano de fire em 25%'},
  ['skuntank'] = {buff = 'poison', amount = 1.07, desc = 'Aumenta o dano do elemento poison em 7%'},
  ['bronzong'] = {buff = 'psychic', amount = 1.10, desc = 'Aumenta o dano do elemento psychic em 10%'},
  ['chatot'] = {buff = 'res_normal', amount = 0.25, desc = 'Reduz dano de normal em 25%'},
  ['spiritomb'] = {buff = 'dark', amount = 1.10, desc = 'Aumenta o dano do elemento dark em 10%'},
  ['garchomp'] = {buff = 'eff_dragon', amount = '1.75', desc = 'Causa 75% a mais de dano contra dragon'},
  ['lucario'] = {buff = 'fighting', amount = 1.10, desc = 'Aumenta o dano do elemento fighting em 10%'},
  ['hippowdon'] = {buff = 'ground', amount = 1.10, desc = 'Aumenta o dano do elemento ground em 10%'},
  ['drapion'] = {buff = 'poison', amount = 1.10, desc = 'Aumenta o dano do elemento poison em 10%'},
  ['toxicroak'] = {buff = 'ret_poison', amount = 25, desc = '25% de chance de aplicar poison no atacante'},
  ['carnivine'] = {buff = 'grass', amount = 1.10, desc = 'Aumenta o dano do elemento grass em 10%'},
  ['lumineon'] = {buff = 'water', amount = 1.10, desc = 'Aumenta o dano do elemento water em 10%'},
  ['abomasnow'] = {buff = 'ice', amount = 1.10, desc = 'Aumenta o dano do elemento ice em 10%'},
  ['weavile'] = {buff = 'ice', amount = 1.10, desc = 'Aumenta o dano do elemento ice em 10%'},
  ['magnezone'] = {buff = 'eff_steel', amount = '1.50', desc = 'Causa 50% a mais de dano contra steel'},
  ["lickilicky"] = {buff = 'hp', amount = 1.20, desc = 'Aumenta HP em 20%'},
  ['rhyperior'] = {buff = 'atk', amount = 1.09, desc = 'Aumenta o ataque em 9%'},
  ["tangrowth"] = {buff = 'grass', amount = 1.10, desc = 'Aumenta o dano do elemento grass em 10%'},
  ['electivire'] = {buff = 'electric', amount = 1.15, desc = 'Aumenta o dano do elemento electric em 15%'},
  ['magmortar'] = {buff = 'fire', amount = 1.15, desc = 'Aumenta o dano do elemento fire em 15%'},
  ['togekiss'] = {buff = 'fairy', amount = 1.15, desc = 'Aumenta o dano do elemento fairy em 15%'},
  ['yanmega'] = {buff = 'bug', amount = 1.15, desc = 'Aumenta o dano do elemento bug em 15%'},
  ['leafeon'] = {buff = 'immunity', amount = 'grass', desc = 'Concede imunidade a grass'},
  ['glaceon'] = {buff = 'immunity', amount = 'ice', desc = 'Concede imunidade a ice'},
  ['gliscor'] = {buff = 'flying', amount = 1.15, desc = 'Aumenta o dano do elemento flying em 15%'},
  ['mamoswine'] = {buff = 'ground', amount = 1.15, desc = 'Aumenta o dano do elemento ground em 15%'},
  ['porygon-z'] = {buff = 'normal', amount = 1.15, desc = 'Aumenta o dano do elemento normal em 15%'},
  ['gallade'] = {buff = 'atk', amount = '1.08', desc = 'Aumenta o ataque em 8%'},
  ['probopass'] = {buff = 'rock', amount = 1.10, desc = 'Aumenta o dano do elemento rock em 10%'},
  ['dusknoir'] = {buff = 'ghost', amount = 1.15, desc = 'Aumenta o dano do elemento ghost em 15%'},
  ['froslass'] = {buff = 'ice', amount = 1.10, desc = 'Aumenta o dano do elemento ice em 10%'},
  ['rotom'] = {buff = 'all', amount = '1.06', desc = 'Aumenta todos os status em 6%'},
  ['uxie'] = {buff = 'psychic', amount = 1.20, desc = 'Aumenta o dano do elemento psychic em 20%'},
  ['mesprit'] = {buff = 'psychic', amount = 1.20, desc = 'Aumenta o dano do elemento psychic em 20%'},
  ['azelf'] = {buff = 'psychic', amount = 1.20, desc = 'Aumenta o dano do elemento psychic em 20%'},
  ['dialga'] = {buff = 'steel', amount = 1.25, desc = 'Aumenta o dano do elemento steel em 25%'},
  ['palkia'] = {buff = 'water', amount = 1.25, desc = 'Aumenta o dano do elemento water em 25%'},
  ['heatran'] = {buff = 'fire', amount = 1.25, desc = 'Aumenta o dano do elemento fire em 25%'},
  ['regigigas'] = {buff = 'normal', amount = 1.25, desc = 'Aumenta o dano do elemento normal em 25%'},
  ['giratina'] = {buff = 'ghost', amount = 1.25, desc = 'Aumenta o dano do elemento ghost em 25%'},
  ['cresselia'] = {buff = 'immunity', amount = 'ghost', desc = 'Concede imunidade a ghost'},
  ['manaphy'] = {buff = 'water', amount = 1.20, desc = 'Aumenta o dano do elemento water em 20%'},
  ['darkrai'] = {buff = 'dark', amount = 1.25, desc = 'Aumenta o dano do elemento dark em 25%'},
  ['shaymin'] = {buff = 'grass', amount = 1.25, desc = 'Aumenta o dano do elemento grass em 25%'},
}

naturedesc = {
	["Hardy"] = "Neutro",
	["Docile"] = "Neutro",
	["Bashful"] = "Neutro",
	["Quirky"] = "Neutro",
	["Serious"] = "Neutro",
	["Lonely"] = "+ATK -DEF",
	["Adamant"] = "+ATK -SP.ATK",
	["Naughty"] = "+ATK -SP.DEF",
	["Brave"] = "+ATK -HP",
	["Bold"] = "+DEF -ATK",
	["Impish"] = "+DEF -SP.ATK",
	["Lax"] = "+DEF -SP.DEF",
	["Relaxed"] = "+DEF -HP",
	["Modest"] = "+SP.ATK -ATK",
	["Mild"] = "+SP.ATK -DEF",
	["Rash"] = "+SP.ATK -SP.DEF",
	["Quiet"] = "+SP.ATK -HP",
	["Calm"] = "+SP.DEF -ATK",
	["Gentle"] = "+SP.DEF -DEF",
	["Careful"] = "+SP.DEF -SP.ATK",
	["Sassy"] = "+SP.DEF -HP",
	["Timid"] = "+HP -ATK",
	["Hasty"] = "+HP -DEF",
	["Jolly"] = "+HP -SP.ATK",
	["Naive"] = "+HP -SP.DEF"
}

megas = {
["audinite"] = {id = 3547, name = "Audino"},
["sharpedonite"] = {id = 3948, name = "Sharpedo"},
["abomasite"] = {id = 3494, name = "Abomasnow"},
["absolite"] = {id = 3495, name = "Absol"},
["aerodactylite"] = {id = 3496, name = "Aerodactyl"},
["aggronite"] = {id = 3498, name = "Aggron"},
["alakazite"] = {id = 3499, name = "Alakazam"},
["altarianite"] = {id = 3500, name = "Altaria"},
["ampharosite"] = {id = 3502, name = "Ampharos"},
["banettite"] = {id = 3503, name = "Banette"},
["beedrillite"] = {id = 3504, name = "Beedrill"},
["blastoisinite"] = {id = 3505, name = "Blastoise"},
["blazikenite"] = {id = 3507, name = "Blaziken"},
["cameruptite"] = {id = 3508, name = "Camerupt"},
["charizardite x"] = {id = 3509, name = "Charizard"},
["charizardite y"] = {id = 3511, name = "Charizard"},
["galladite"] = {id = 3513, name = "Gallade"},
["garchompite"] = {id = 3514, name = "Garchomp"},
["gardevoirite"] = {id = 3515, name = "Gardevoir"},
["gengarite"] = {id = 3516, name = "Gengar"},
["glalitite"] = {id = 3518, name = "Glalie"},
["gyaradosite"] = {id = 3520, name = "Gyarados"},
["heracronite"] = {id = 3521, name = "Heracross"},
["houndoominite"] = {id = 3522, name = "Houndoom"},
["kangaskhanite"] = {id = 3523, name = "Kangaskhan"},
["lopunnite"] = {id = 3524, name = "Lopunny"},
["lucarionite"] = {id = 3525, name = "Lucario"},
["manectite"] = {id = 3526, name = "Manectric"},
["mawilite"] = {id = 3528, name = "Mawile"},
["medichamite"] = {id = 3529, name = "Medicham"},
["metagrossite"] = {id = 3530, name = "Metagross"},
["pidgeotite"] = {id = 3532, name = "Pidgeot"},
["pinsirite"] = {id = 3534, name = "Pinsir"},
["sablenite"] = {id = 3536, name = "Sableye"},
["salamencite"] = {id = 3537, name = "Salamence"},
["sceptilite"] = {id = 3539, name = "Sceptile"},
["scizorite"] = {id = 3540, name = "Scizor"},
["slowbronite"] = {id = 3541, name = "Slowbro"},
["steelixite"] = {id = 3542, name = "Steelix"},
["swampertite"] = {id = 3544, name = "Swampert"},
["tyranitarite"] = {id = 3545, name = "Tyranitar"},
["venusaurite"] = {id = 3546, name = "Venusaur"},
}

heldt1 = {36423, 36422, 36424, 36425, 36438, 36439}
heldt2 = {36473, 36472, 36474, 36475, 36488, 36489}

balls = {
pokeball = {emptyId = 26662, usedOn = 26661, usedOff = 26672, effectFail = 1087, effectSucceed = 1088, missile = 192, effectRelease = 1060, chanceMultiplier = 1.0},
greatball = {emptyId = 26660, usedOn = 26663, usedOff = 26675, effectFail = 1064, effectSucceed = 1065, missile = 191, effectRelease = 1061, chanceMultiplier = 1.5},
ultraball = {emptyId = 26688, usedOn = 26670, usedOff = 26681, effectFail = 1080, effectSucceed = 1081, missile = 194, effectRelease = 1062, chanceMultiplier = 2.0},
masterball = {emptyId = 39139, usedOn = 39140, usedOff = 39141, effectFail = 0, effectSucceed = 1059, missile = 185, effectRelease = 1058, chanceMultiplier = 255},
premierball = {emptyId = 26683, usedOn = 26666, usedOff = 26678, effectFail = 1056, effectSucceed = 1055, missile = 129, effectRelease = 1057, chanceMultiplier = 1.0},
saffariball = {emptyId = 26685, usedOn = 26668, usedOff = 26680, effectFail = 1082, effectSucceed = 1083, missile = 184, effectRelease = 1063, chanceMultiplier = 1.5},
parkball = {emptyId = 39132, usedOn = 39133, usedOff = 39134, effectFail = 1085, effectSucceed = 1086, missile = 193, effectRelease = 1084, chanceMultiplier = 1.5},
fastball = {emptyId = 39129, usedOn = 39130, usedOff = 39131, effectFail = 1073, effectSucceed = 1072, missile = 177, effectRelease = 1074, chanceMultiplier = 3.0},
netball = {emptyId = 32344, usedOn = 32356, usedOff = 39138, effectFail = 1079, effectSucceed = 1078, missile = 181, effectRelease = 1054, chanceMultiplier = 3.5},
loveball = {emptyId = 32338, usedOn = 32350, usedOff = 39135, effectFail = 1067, effectSucceed = 1066, missile = 189, effectRelease = 1068, chanceMultiplier = 4.0},
duskball = {emptyId = 32339, usedOn = 32351, usedOff = 39136, effectFail = 1070, effectSucceed = 1069, missile = 190, effectRelease = 1071, chanceMultiplier = 3.0},
heavyball = {emptyId = 32341, usedOn = 32353, usedOff = 39137, effectFail = 1076, effectSucceed = 1075, missile = 178, effectRelease = 1077, chanceMultiplier = 1.0},
lamp = {emptyId = 2272, usedOn = 2325, usedOff = 23255, effectFail = 734, effectSucceed = 735, missile = 55, effectRelease = 308, chanceMultiplier = 1.0}
}

skullToTera = {
	[11] = "normal",
	[12] = "fire",
	[13] = "fighting",
	[14] = "water",
	[15] = "flying",
	[16] = "grass",
	[17] = "poison",
	[18] = "electric",
	[19] = "ground",
	[20] = "psychic",
	[21] = "rock",
	[22] = "ice",
	[23] = "bug",
	[24] = "dragon",
	[25] = "ghost",
	[26] = "dark",
	[27] = "steel",
	[28] = "fairy",
}

addonmega = {
[3960] = 3962,
[3967] = 3966,
[3968] = 3969,
[3972] = 3973,
[3988] = 3989,
[3992] = 3993,
[3735] = 3977,
[3740] = 3964,
[3742] = 3986,
[3749] = 3990,
[3758] = 3970,
[4000] = 4000,
[3995] = 3995,
[3997] = 3997,
[3974] = 3974,
[3979] = 3979,
[3981] = 3981,
[4143] = 4149,
[4150] = 4178,
[4151] = 4177,
[4194] = 4154
}

addonnumber = {
	[3970] = {name = "Fossil Aerodactyl", hab = 3971, poke = "Aerodactyl"},
	[3986] = {name = "Ancient Metagross", hab = 3987, poke = "Metagross"},
	[3962] = {name = 'masked gengar', hab = 3963, poke = 'Gengar'},
	[3763] = {name = "Ancient Charizard", hab = 3764, poke = "Charizard"},
	[3785] = {name = "Ancient Gyarados", hab = 3786, poke = "Gyarados"},
	[3742] = {name = "Ancient Metagross", hab = 3743, poke = "Metagross"},
	[3761] = {name = "Armored Aggron", poke = "Aggron"},
	[3789] = {name = "Armored Arceus", poke = "Arceus"},
	[3728] = {name = "Armored Dragonite Green", hab = 3729, poke = "Dragonite"},
	[3730] = {name = "Armored Dragonite Purple", hab = 3731, poke = "Dragonite"},
	[3735] = {name = "Armored Gardevoir", poke = "Gardevoir"},
	[3769] = {name = "Armored Mewtwo", poke = "Mewtwo"},
	[3751] = {name = "Armored Rhyperior", poke = "Rhyperior"},
	[3759] = {name = "Armored Salamence", poke = "Salamence"},
	[3694] = {name = "Armored Tropius Purple", hab = 3695, poke = "Tropius"},
	[3696] = {name = "Armored Tropius Red", hab = 3697, poke = "Tropius"},
	[3700] = {name = "Assassin Scizor", poke = "Scizor"},
	[3787] = {name = "Athena Jynx", poke = "Jynx"},
	[3715] = {name = "Aviator Altaria", hab = 3716, poke = "Altaria"},
	[3702] = {name = "White Suit Machamp", poke = "Machamp"},
	[3701] = {name = "Black Suit Machamp", poke = "Machamp"},
	[3752] = {name = "Black Suit Slaking", poke = "Slaking"},
	[3704] = {name = "Carrier Mamoswine Red", hab = 3707, poke = "Mamoswine"},
	[3705] = {name = "Carrier Mamoswine Blue", hab = 3708, poke = "Mamoswine"},
	[3720] = {name = "Cavalier Dusknoir", poke = "Dusknoir"},
	[3723] = {name = "Cheerleader Sudowoodo", poke = "Sudowoodo"},
	[3754] = {name = "Cloaked Jirachi", poke = "Jirachi"},
	[3750] = {name = "Constructor Rhyperior", poke = "Rhyperior"},
	[3718] = {name = "Cook Crawdaunt", poke = "Crawdaunt"},
	[3726] = {name = "Cook Snorlax", hab = 3727, poke = "Snorlax"},
	[3753] = {name = "Corrupted Jirachi", poke = "Jirachi"},
	[3746] = {name = "Cyborg Mewtwo", poke = "Mewtwo"},
	[3740] = {name = "Cyborg Salamence", hab = 3741, poke = "Salamence"},
	[3964] = {name = "Cyborg Salamence", hab = 3965, poke = "Salamence"},
	[3745] = {name = "Djinn Machamp", poke = "Machamp"},
	[3732] = {name = "Dressed Gardevoir", poke = "Gardevoir"},
	[3736] = {name = "Empress Gardevoir Purple", poke = "Gardevoir"},
	[3737] = {name = "Empress Gardevoir Red", poke = "Gardevoir"},
	[3758] = {name = "Fossil Aerodactyl", hab = 3757, poke = "Aerodactyl"},
	[3755] = {name = "Gyaryudos", hab = 3756, poke = "Gyarados"},
	[3762] = {name = "Hashirama Zoroark", poke = "Zoroark"},
	[3711] = {name = "Iceage Mamoswine", hab = 3712, poke = "Mamoswine"},
	[3685] = {name = "Jimbei Feraligatr", hab = 3686, poke = "Feraligatr"},
	[3706] = {name = "Jojo Toxicroak", poke = "Toxicroak"},
	[3772] = {name = "Lance Dragonite", hab = 3773, poke = "Dragonite"},
	[3768] = {name = "Magician Mewtwo", poke = "Mewtwo"},
	[3734] = {name = "Maid Gardevoir", poke = "Gardevoir"},
	[3690] = {name = "Majinblissey", poke = "Blissey"},
	[3691] = {name = "Masked Crobat", hab = 3692, poke = "Crobat"},
	[3721] = {name = "Masked Ninetales", hab = 3722, poke = "Ninetales"},
	[3713] = {name = "Masquerade", poke = "Roserade"},
	[3747] = {name = "Mermaid Milotic", hab = 3747, poke = "Milotic"},
	[3780] = {name = "Milktank", poke = "Miltank"},
	[3698] = {name = "Ninja Noctowl", hab = 3699, poke = "Noctowl"},
	[3689] = {name = "Nurse Blissey", poke = "Blissey"},
	[3687] = {name = "Nurse Gengar", hab = 3688, poke = "Gengar"},
	[3714] = {name = "Nurse Wigglytuff", poke = "Wigglytuff"},
	[3776] = {name = "Pool Party Flareon", poke = "Flareon"},
	[3777] = {name = "Pool Party Jolteon", poke = "Jolteon"},
	[3774] = {name = "Pool Party Vaporeon", hab = 3775, poke = "Vaporeon"},
	[3778] = {name = "Pool Party Golem", poke = "Golem"},
	[3744] = {name = "Saiyajin Dugtrio", poke = "Dugtrio"},
	[3724] = {name = "Saiyawoodo", poke = "Sudowoodo"},
	[3717] = {name = "Sannin Shiftry", poke = "Shiftry"},
	[3788] = {name = "Saw Mr. Mime", poke = "Mr. Mime"},
	[3779] = {name = "Seer Mismagius", poke = "Mismagius"},
	[3790] = {name = "Seifuku Clefable", poke = "Clefable"},
	[3781] = {name = "Seifuku Meganium", hab = 3782, poke = "Meganium"},
	[3749] = {name = "Stitch Sableye", poke = "Sableye"},
	[3719] = {name = "Trainer Sudowoodo", poke = "Sudowoodo"},
	[3683] = {name = "Trainer Typhlosion", poke = "Typhlosion"},
	[3703] = {name = "Tribal Alakazam", poke = "Alakazam"},
	[3767] = {name = "Trickster Mew", poke = "Mew"},
	[3733] = {name = "Witch Hunter Gardevoir", poke = "Gardevoir"},
	[3738] = {name = "Witch Hunter Honchkrow", hab = 3739, poke = "Honchkrow"},
	[3693] = {name = "Yogi Ursaring", poke = "Ursaring"},
	
	[3951] = {name = 'ancient mesprit', poke = 'Mesprit'},
	[3952] = {name = 'ancient uxie', poke = 'Uxie'},
	[3953] = {name = 'ancient azelf', poke = 'Azelf'},
	[3954] = {name = 'cosplaying manaphy', poke = 'Manaphy'},
	[3959] = {name = 'cosplaying greninja', poke = "Greninja"},
	[3960] = {name = 'masked gengar', hab = 3961, poke = 'Gengar'},
	[3967] = {name = 'cosplaying alakazam', poke = 'Alakazam'},
	[3968] = {name = 'cosplaying banette', poke = 'Banette'},
	[3972] = {name = 'cosplaying beedrill', poke = 'Beedrill'},
	[3974] = {name = 'noir blastoise', hab = 3975, poke = 'Mega Blastoise'},
	[3976] = {name = 'cosplaying blaziken', poke = "Mega Blaziken"},
	[3978] = {name = 'cosplaying heracross', poke = 'Mega Heracross'},
	[3979] = {name = 'cyborg mega charizard x', hab = 3980, poke = 'Mega Charizard X'},
	[3981] = {name = 'cyborg mega charizard y', hab = 3982, poke = 'Mega Charizard Y'},
	[3983] = {name = 'cosplaying ampharos', poke = 'Mega Ampharos'},
	[3984] = {name = 'dressed mawile', poke = 'Mega Mawile'},
	[3985] = {name = 'cosplaying medicham', poke = 'Mega Medicham'},
	[3988] = {name = 'masked pinsir', poke = 'Pinsir'},
	[3991] = {name = 'armored sceptile', poke = 'Mega Sceptile'},
	[3992] = {name = 'cosplaying scizor', poke = 'Scizor'},
	[3994] = {name = 'donut slowpoke', poke = 'Mega Slowpoke'},
	[3995] = {name = 'metallic steelix', hab = 3996, poke = 'Mega Steelix'},
	[3997] = {name = 'cyborg swampert', hab = 3998, poke = 'Mega Swampert'},
	[3999] = {name = 'armored tyranitar', poke = 'Mega Tyranitar'},
	[4000] = {name = 'trainer venusaur', hab = 4001, poke = 'Mega Venusaur'},
	[4002] = {name = 'dressed lopunny', poke = 'Mega Lopunny'},
	[4003] = {name = 'cosplaying shuckle', poke = 'Shuckle'},
	[4004] = {name = 'cosplaying blissey', poke = 'Blissey'},
	[4005] = {name = 'cosplaying wobbuffet', poke = 'Wobbuffet'},
	[4006] = {name = 'cosplaying gardevoir', poke = 'Gardevoir'},
	[4007] = {name = 'cosplaying vileplume', poke = 'Vileplume'},
	[4011] = {name = 'cosplaying sylveon', poke = 'Sylveon'},
	[4012] = {name = 'cosplaying rampardos', poke = 'Rampardos'},
	[4013] = {name = 'cosplaying audino', poke = 'Audino'},
	
	[4033] = {name = 'cosplaying electivire', poke = 'Electivire'},
	[4034] = {name = 'cosplaying magmortar', poke = 'Magmortar'},
	[4035] = {name = 'cosplaying cradily', poke = 'Cradily'},
	[4036] = {name = 'armored magnezone', hab = 4037, poke = 'Magnezone'},
	[4038] = {name = 'cyborg lapras', poke = 'Lapras'},
	[4039] = {name = 'cyborg flareon', poke = 'Flareon'},
	[4040] = {name = 'cyborg jolteon', poke = 'Jolteon'},
	[4041] = {name = 'cyborg vaporeon', hab = 4042, poke = 'Vaporeon'},
	[4043] = {name = 'cyborg umbreon', poke = 'Umbreon'},
	[4044] = {name = 'cyborg espeon', poke = 'Espeon'},
	[4045] = {name = 'cyborg glaceon', poke = 'Glaceon'},
	[4046] = {name = 'cyborg leafeon', poke = 'Leafeon'},
	[4047] = {name = 'cyborg flareon', poke = 'Sylveon'},
	
	[4129] = {name = 'cosplaying espeon', poke = 'Espeon'},
	[4130] = {name = 'cosplaying umbreon', poke = 'Umbreon'},
	[4131] = {name = 'cosplaying drapion', poke = 'Drapion'},
	[4134] = {name = 'dressed mismagium', hab = 4133, poke = 'Mismagius'},
	[4138] = {name = 'cosplaying mega abomasnow', poke = 'Mega Abomasnow'},
	[4143] = {name = 'cosplaying gallade', poke = 'Gallade'},
	[4144] = {name = 'cosplaying tangrowth', poke = 'Tangrowth'},
	[4148] = {name = 'cosplaying spirtomb', hab = 4147, poke = 'Spiritomb'},
	[4150] = {name = 'dark pidgeot', hab = 4151, poke = 'Pidgeot'},
	[4158] = {name = 'cosplaying milotic', hab = 4157, poke = 'Milotic'},
	[4176] = {name = 'cosplaying hisuian arcanine', hab = 4175, poke = 'Hisuian Arcanine'},
	[4190] = {name = 'dressed delcatty', poke = 'Delcatty'},
	[4191] = {name = 'cosplaying machamp', poke = 'Machamp'},
	[4194] = {name = 'witch hunter camerupt', hab = 4193, poke = 'Camerupt'},
}

maxBoost = 50
summonMaxLevel = 100 -- maximum level of pokes
maxVitamins = 10
shinyChance = 2
flyFloor = 460 
moveWords = {"m1", "m2", "m3", "m4", "m5", "m6", "m7", "m8", "m9", "m10", "m11", "m12"}
legendaryIndex = {144, 145, 146, 150, 151, 243, 244, 245, 249, 250, 251, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386}
arenaLastPlayerId = 0

damageMultiplierMoves = {areawaves = 2.75, singletargetweak = 2.0, singletarget = 3.5, singletargetstrong = 4.0, areatarget = 3.0, frontlinear = 5.0, frontarea = 4.0, passive = 3.0, ultimate = 6.0}
summonLevelDamageBuff = 0.008 -- buff due to summon's level
playerLevelDamageBuff = 0.0005 -- buff due to player's level
summonBoostDamageBuff = 0.008 -- buff due to summon's boost
summonLoveDamageBuff = 0.0002 -- buff due to summon's love
vitaminStatusBuff = 1.2
hunterDamageBuff = 1.1
blockerHealthBuff = 1.25
catcherCatchBuff = 1.1
explorerExperienceBuff = 1.15
healerHealBuff = 2.0

storageDelay = 1000
storageDelayBag = 1001
baseStorageTries = 180561000
baseStorageCatches = 180564000
baseStorageDex = 180567000
baseStorageMove = 45000

storageRide = 5000
storageFly = 5001
storageSurf = 5002
storageEvolving = 5003
storageTutorial = 5004
storageDelayTeleport = 5005
storageBike = 5006
storageDelayDesbugar = 5007
storageDive = 5008
storageAutoLoot = 5009
storageBagEvent = 5010
storageArenaEvent = 5011
storageSoccerEvent = 5012
storageEvent = 5013
storageTokens = 5014
storageLastLegendaryKilled = 5015
storageDuelNpc = 5016
storageDuelNpcStatus = 5017
storageTeleportTc = 5018
storageEvolutionAncient = 5019
storageArenaPvpEvent = 5020
storageLogoutSpeed = 5021

storageCatchQuest = 91000
storageCatchQuestDay = 91001
storageCatchQuestNumber = 91002
storageCatchQuestStartCatch = 91003
storageCatchQuestTime = 91004
storageCatchQuestDifficulty = 91005

storageLeague = 91006
storageLeagueDone = 91007
storageLeagueTime = 91008
storageLeaguePotion = 91009
storageLeagueRevive = 910010

storageVictoryRoadTime = 91011

storageRedRequestPre = 91012

storageCatchQuestPoke = 91013

storageItemQuest = 91014
storageItemQuestDay = 91015
storageItemQuestNumber = 91016
storageItemQuestItem = 91017
storageItemQuestTime = 91018
storageItemQuestDifficulty = 91019
slotItems = {38680, 38681, 38682, 2263, 2270, 26820}
badgesPortraits = {26614, 26609, 26615, 26612, 26613, 26616, 26610, 26611, 38689, 38683, 38685, 38690, 38684, 38688, 38686, 38687}
badgeContainer = 38680

waterIds = {493, 4608, 4609, 4610, 4611, 4612, 4613, 4614, 4615, 4616, 4617, 4618, 4619, 4620, 4621, 4622, 4623, 4624, 4625, 7236, 10499, 15401, 15402, 4820, 4821, 4822, 4823, 4824, 4825, 4664, 4665, 4666}

quests = 
{

betateste = {
		prizes = {
			[1] = {
				uid = 65033,
				items = {
				},
				pokes = {					
				},
				badges = {
				}
			}
		},
		experience = 0,
		level = 1, 
		teleportCP = 0
	},

catches = {
		prizes = {
			[1] = {
				uid = storageCatchQuest,
				items = {
				},
				pokes = {					
				},
				badges = {
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

itemTask = {
		prizes = {
			[1] = {
				uid = storageItemQuest,
				items = {
				},
				pokes = {					
				},
				badges = {
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

indigoLeague = {
		prizes = {
			[1] = {
				uid = storageLeagueDone,
				items = {
					[1] = {item = "indigo league trophy", count = 1}, 
					[2] = {item = "crystal coin", count = 100}, 
					[2] = {item = "indigo prize orb", count = 1}, 
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 10000000,
		level = 400, 
		teleportCP = 0
	},



boulderBadge = {
		prizes = {
			[1] = {
				uid = 92000,
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 26614, add = 26608}, 
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

cascadeBadge = {
		prizes = {
			[1] = {
				uid = 92001,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 26609, add = 26607}, 
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

thunderBadge = {
		prizes = {
			[1] = {
				uid = 92002,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 26615, add = 26603}, 
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

rainbowBadge = {
		prizes = {
			[1] = {
				uid = 92003,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 26612, add = 26602}, 
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

soulBadge = {
		prizes = {
			[1] = {
				uid = 92004,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 26613, add = 26605}, 
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

marshBadge = {
		prizes = {
			[1] = {
				uid = 92005,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 26616, add = 26606}, 
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

volcanoBadge = {
		prizes = {
			[1] = {
				uid = 92006,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 26610, add = 26601}, 
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

earthBadge = {
		prizes = {
			[1] = {
				uid = 92007,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 26611, add = 26604}, 
				}
			}
		},
		experience = 50000,
		level = 1, 
		teleportCP = 0
	},

zephyrBadge = {
		prizes = {
			[1] = {
				uid = 92008,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 38689, add = 38695}, 
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},
hiveBadge = {
		prizes = {
			[1] = {
				uid = 92009,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 38683, add = 38694}, 
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

plainBadge = {
		prizes = {
			[1] = {
				uid = 92010,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 38685, add = 38691}, 
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

fogBadge = {
		prizes = {
			[1] = {
				uid = 92011,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 38690, add = 38693}, 
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

stormBadge = {
		prizes = {
			[1] = {
				uid = 92012,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 38684, add = 38697}, 
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

mineralBadge = {
		prizes = {
			[1] = {
				uid = 92013,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 38688, add = 38698}, 
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

glacierBadge = {
		prizes = {
			[1] = {
				uid = 92014,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 38686, add = 38692}, 
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

risingBadge = {
		prizes = {
			[1] = {
				uid = 92015,				
				items = {
				},
				pokes = {
				},
				badges = {
					[1] = {remove = 38687, add = 38696}, 
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

oakRequest = {
		prizes = {
			[1] = {
				uid = 92016,
				items = {
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		level = 100, 
		teleportCP = 1
	},
	
boxone1 = {
		prizes = {
			[1] = {
				uid = 65001,
				items = {
					[1] = {item = "vale token", count = 2},
					[2] = {item = "box 1", count = 1},		
				},
				pokes = {
					-- [1] = {name = "Shiny Porygon", level = 35, boost = 10}
				},
				badges = {
				}
			}
		},
		experience = 10000,
		level = 150, 
		teleportCP = 1
	},

underwaterChest = {
		prizes = {
			[1] = {
				uid = 65002,
				items = {
					-- [1] = {item = "vale token", count = 1},		
				},
				pokes = {
					[1] = {name = "Phione", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 500000,
		level = 200, 
		teleportCP = 1,
		message = "Um pokemon tao raro no fundo do oceano? Me pergunto o que aconteceu com a tripulacao..."
	},
	
boxzero1 = {
		prizes = {
			[1] = {
				uid = 65003,
				items = {
					[1] = {item = "vale token", count = 1},	
					[2] = {item = "box 0", count = 1},							
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 10000,
		level = 50, 
		teleportCP = 1
	},

boxone2 = {
		prizes = {
			[1] = {
				uid = 65004,
				items = {
					[1] = {item = "vale token", count = 2},		
					[2] = {item = "box 1", count = 1},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 10000,
		level = 150, 
		teleportCP = 1
	},

boxzero2 = {
		prizes = {
			[1] = {
				uid = 65005,
				items = {
					[1] = {item = "vale token", count = 1},		
					[2] = {item = "box 0", count = 1},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 10000,
		level = 50, 
		teleportCP = 1
	},
	
boxone3 = {
		prizes = {
			[1] = {
				uid = 65006,
				items = {
					[1] = {item = "vale token", count = 1},		
					[2] = {item = "box 1", count = 1},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 10000,
		level = 150, 
		teleportCP = 1
	},

boxone4 = {
		prizes = {
			[1] = {
				uid = 65007,
				items = {
					[1] = {item = "vale token", count = 2},		
					[2] = {item = "box 1", count = 1},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 10000,
		level = 150, 
		teleportCP = 1
	},
	
bagquest = {
		prizes = {
			[1] = {
				uid = 65008,
				items = {
					[1] = {item = "grey backpack", count = 1},	
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 5000,
		level = 1, 
		teleportCP = 1
	},
	
gymtrial1 = {
		prizes = {
			[1] = {
				uid = 65009,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial2 = {
		prizes = {
			[1] = {
				uid = 65010,
				items = {
					[1] = {item = "crystal coin", count = 5},		
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},
	
gymtrial3 = {
		prizes = {
			[1] = {
				uid = 65011,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial4 = {
		prizes = {
			[1] = {
				uid = 65012,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},
	
gymtrial5 = {
		prizes = {
			[1] = {
				uid = 65013,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial6 = {
		prizes = {
			[1] = {
				uid = 65014,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial7 = {
		prizes = {
			[1] = {
				uid = 65015,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},			
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial8 = {
		prizes = {
			[1] = {
				uid = 65016,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

alolaninetales = {
		prizes = {
			[1] = {
				uid = 65018,
				items = {
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

alolaraticate = {
		prizes = {
			[1] = {
				uid = 65019,
				items = {
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},
	
aloladugtrio = {
		prizes = {
			[1] = {
				uid = 65020,
				items = {
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

alolapersian = {
		prizes = {
			[1] = {
				uid = 65021,
				items = {
				},
				pokes = {
					[1] = {name = "Alolan persian", level = 1, boost = 0, tera = math.random(11, 28)}
				},
				badges = {
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

alolamarowak = {
		prizes = {
			[1] = {
				uid = 65022,
				items = {
				},
				pokes = {
					[1] = {name = "Alolan marowak", level = 1, boost = 0, tera = math.random(11, 28)}
				},
				badges = {
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

alolagolem = {
		prizes = {
			[1] = {
				uid = 65023,
				items = {
				},
				pokes = {
					[1] = {name = "Alolan golem", level = 1, boost = 0, tera = math.random(11, 28)}
				},
				badges = {
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

alolamuk = {
		prizes = {
			[1] = {
				uid = 65024,
				items = {
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},

alolaexeggutor = {
		prizes = {
			[1] = {
				uid = 65025,
				items = {
				},
				pokes = {
					[1] = {name = "Alolan raichu", level = 1, boost = 0, tera = math.random(11, 28)},
					[2] = {name = "Alolan exeggutor", level = 1, boost = 0, tera = math.random(11, 28)},
					[3] = {name = "Alolan sandslash", level = 1, boost = 0, tera = math.random(11, 28)}
				},
				badges = {
				}
			}
		},
		level = 1, 
		teleportCP = 0
	},
darkrai1 = {
		prizes = {
			[1] = {
				uid = 65028,
				items = {
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 1000000,
		level = 1,
		teleportCP = 1
	},
hooh = {
		prizes = {
			[1] = {
				uid = 65026,
				items = {
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 1000000,
		level = 1,
		teleportCP = 1
	},
lugia = {
		prizes = {
			[1] = {
				uid = 65027,
				items = {
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 1000000,
		level = 1,
		teleportCP = 1
	},

boxsinnoh = {
		prizes = {
			[1] = {
				uid = 65030,
				items = {
					[1] = {item = "vale token", count = 10},		
					[2] = {item = "box 4", count = 1},		
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 50000,
		level = 300, 
		teleportCP = 0
	},

boxhoenn = {
		prizes = {
			[1] = {
				uid = 65031,
				items = {
					[1] = {item = "vale token", count = 7},		
					[2] = {item = "box 3", count = 1},		
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 50000,
		level = 250, 
		teleportCP = 0
	},

boxjohto = {
		prizes = {
			[1] = {
				uid = 65032,
				items = {
					[1] = {item = "vale token", count = 5},		
					[2] = {item = "box 2", count = 1},		
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 50000,
		level = 200, 
		teleportCP = 0
	},

sailor = {
		prizes = {
			[1] = {
				uid = 65033,
				items = {
					[1] = {item = "model ship", count = 1},		
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 666,
		level = 1, 
		teleportCP = 0
	},
	
gymtrial9 = {
		prizes = {
			[1] = {
				uid = 65034,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial10 = {
		prizes = {
			[1] = {
				uid = 65035,
				items = {
					[1] = {item = "crystal coin", count = 5},		
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},
	
gymtrial11 = {
		prizes = {
			[1] = {
				uid = 65036,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial12 = {
		prizes = {
			[1] = {
				uid = 65037,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},
	
gymtrial13 = {
		prizes = {
			[1] = {
				uid = 65038,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial14 = {
		prizes = {
			[1] = {
				uid = 65039,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial15 = {
		prizes = {
			[1] = {
				uid = 65040,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},			
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

gymtrial16 = {
		prizes = {
			[1] = {
				uid = 65041,
				items = {
					[1] = {item = "crystal coin", count = 5},
					[2] = {item = "vale token", count = 10},		
				},
				pokes = {
					-- [1] = {name = "Celebi", level = 1, boost = 0}
				},
				badges = {
				}
			}
		},
		experience = 100000,
		level = 1, 
		teleportCP = 0
	},

johtoLeague = {
		prizes = {
			[1] = {
				uid = 65042,
				items = {
					[1] = {item = "johto league trophy", count = 1}, 
					[2] = {item = "crystal coin", count = 100}, 
					[2] = {item = "johto prize shell", count = 1}, 
				},
				pokes = {
				},
				badges = {
				}
			}
		},
		experience = 10000000,
		level = 500, 
		teleportCP = 0
	},
}

function buildDex()
	monstersTable = {}
	local monstersName = getMonstersName()
	for i = 1, #monstersName do
		local monsterNumber = MonsterType(monstersName[i]):dexEntry()
		if monsterNumber > 0 then
			monstersTable[monsterNumber] = monstersName[i]
		end
	end
	return print("WARNING! Pokedex successfully built.")
end

function getBlessingsCost(level)
	if level <= 30 then
		return 2000
	elseif level >= 120 then
		return 20000
	else
		return (level - 20) * 200
	end
end

function getPvpBlessingCost(level)
	if level <= 30 then
		return 2000
	elseif level >= 270 then
		return 50000
	else
		return (level - 20) * 200
	end
end

function getTibianTime()
	local worldTime = getWorldTime()
	local hours = math.floor(worldTime / 60)

	local minutes = worldTime % 60
	if minutes < 10 then
		minutes = '0' .. minutes
	end
	return hours .. ':' .. minutes
end

function getNeededExp(level) return (50 * (level * level * level - 6 * level * level + 17 * level - 12) / 3) end

function statusGainFormula(playerLevel, summonLevel, summonBoost, pokeLove)
	return (1.0 + summonLevel * summonLevelDamageBuff + playerLevel * playerLevelDamageBuff + summonBoost * summonBoostDamageBuff + pokeLove * summonLoveDamageBuff)
end
summonLevelDamageBuff = 0.008 -- buff due to summon's level
playerLevelDamageBuff = 0.0005 -- buff due to player's level
summonBoostDamageBuff = 0.008 -- buff due to summon's boost
summonLoveDamageBuff = 0.0002

function damageFormula(playerLevel, summonLevel, summonBoost, pokeLove)
	return statusGainFormula(playerLevel, summonLevel, summonBoost, pokeLove)
end

function defenseFormula(playerLevel, summonLevel, summonBoost, pokeLove)
	return (1.0 / 600.0 * statusGainFormula(playerLevel, summonLevel, summonBoost, pokeLove))
end

function getConditions(uid)-- Helena
	if not Creature(uid) then return false end
	uid = Creature(uid)
	local conditions = {CONDITION_FIRE, CONDITION_POISON, CONDITION_FREEZING, CONDITION_SLEEP, CONDITION_SILENCE, CONDITION_PARALYZE, CONDITION_DRUNK, CONDITION_FOCUS, CONDITION_EVASION, CONDITION_DEFENSEPLUS, CONDITION_DEFENSEMINUS, CONDITION_ATTACKPLUS, CONDITION_ATTACKMINUS, CONDITION_IMMUNE}
	local hascondis = {}
	for i = 1, #conditions do
		if uid:getCondition(conditions[i]) ~= nil then
			table.insert(hascondis, conditions[i])
		end
	end
	return hascondis
end

function getPositiveConditions(uid) -- Helena
	if not Creature(uid) then return false end
	uid = Creature(uid)
	local conditions = {CONDITION_FOCUS, CONDITION_EVASION, CONDITION_DEFENSEPLUS, CONDITION_ATTACKPLUS, CONDITION_IMMUNE}
	local hascondis = {}
	for i = 1, #conditions do
		if uid:getCondition(conditions[i]) ~= nil then
			table.insert(hascondis, conditions[i])
		end
	end
	return hascondis
end

function getNegativeConditions(uid) -- Helena
	if not Creature(uid) then return false end
	uid = Creature(uid)
	local conditions = {CONDITION_FIRE, CONDITION_POISON, CONDITION_FREEZING, CONDITION_SLEEP, CONDITION_SILENCE, CONDITION_PARALYZE, CONDITION_DRUNK, CONDITION_DEFENSEMINUS, CONDITION_ATTACKMINUS}
	local hascondis = {}
	for i = 1, #conditions do
		if uid:getCondition(conditions[i]) ~= nil then
			table.insert(hascondis, conditions[i])
		end
	end
	return hascondis
end

function getBallKey(uid)
	for key, value in pairs(balls) do
		if uid == value.emptyId or uid == value.usedOn or uid == value.usedOff then
			return key
		end
	end
	return "pokeball"
end

function getEggmove(uid)
	local moves = {}
	for key, value in pairs(eggmoves) do
		if isInArray(value.canlearn, uid) then
			table.insert(moves, key)
		end
	end
	return moves
end

function getUnownKey(uid)
	for key, value in pairs(unowns) do
		if uid == value then
			return key
		end
	end
	return 0
end

function getMegaOutfit(uid)
	for key, value in pairs(megas) do
		if uid == value.name then
			return value.id
		end
	end
	return 0
end

function getMegaStone(uid)
	for key, value in pairs(megas) do
		if uid == value.id then
			return key
		end
	end
	return 0
end

function Monster.getTotalHealth(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then -- Life Formula
		local hp = monsterType:getMaxHealth()
		local lv = self:getLevel()
		local total = math.floor((lv * 20) + (hp * 0.10)) + hp
		if self:getMaster() and self:getMaster():getUsingBall() and self:getMaster():getUsingBall():getSpecialAttribute("nature") then
			if isInArray({"Timid", "Hasty", "Jolly", "Naive"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 1.10
			elseif isInArray({"Brave", "Relaxed", "Quiet", "Sassy"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 0.90
			end
		end
		if self:getMaster():getVocation():getName() == "Blocker" then
			total = total * blockerHealthBuff
		end
		local talisman = self:getMaster():getUsingBall():getSpecialAttribute("talisman") or 0
		if talismanTable[talisman] and (talismanTable[talisman].buff == 'hp' or talismanTable[talisman].buff == 'all') then
			total = total * talismanTable[talisman].amount
		end
		return total
	elseif self:isMonster() then
		local hp = self:getMaxHealth()
		local lv = self:getLevel()
		local formula = ((lv * 20) + (hp * 0.10)) + hp
		return math.floor(formula)
	end
	return 0
end

function Monster.getTotalHealthVocationContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then
		if self:getMaster():getVocation():getName() == "Blocker" then
			return math.floor(monsterType:getMaxHealth() * statusGainFormula(self:getMaster():getLevel(), self:getLevel(), self:getBoost(), self:getLove()) * (blockerHealthBuff - 1.0))
		end
	end
	return 0
end

function Monster.getTotalHealthPlayerContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMaxHealth() * (statusGainFormula(self:getMaster():getLevel(), 0, 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalHealthSummonLevelContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMaxHealth() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	elseif self:isMonster() then
		return math.floor(monsterType:getMaxHealth() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))	
	end	
	return 0
end

function Monster.getTotalHealthSummonBoostContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMaxHealth() * (statusGainFormula(0, 0, self:getBoost(), 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalHealthSummonVitaminContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		local vitamins = self:getUsedVitaminsNumber("hp")
		if vitamins > 0 then
			return math.floor(monsterType:getMaxHealth() * vitamins / maxVitamins * vitaminStatusBuff)
		end
	end
	return 0
end

function MonsterType.getMeleeDamage(self)
	local minMelee = 0
	local maxMelee = 0
	for i = 1, #self:getAttackList() do
		if self:getAttackList()[i].isMelee == 1 then	
			minMelee = minMelee - self:getAttackList()[i].minCombatValue		
			maxMelee = maxMelee - self:getAttackList()[i].maxCombatValue			
		end
	end
	local aveMelee = (minMelee + maxMelee) / 2
	return math.floor(aveMelee)
end

function Monster.getTotalMeleeAttack(self)
	local monsterType = MonsterType(self:getName())
	local minMelee = 0
	local maxMelee = 0
	for i = 1, #monsterType:getAttackList() do
		if monsterType:getAttackList()[i].isMelee == 1 then	
			minMelee = minMelee - monsterType:getAttackList()[i].minCombatValue		
			maxMelee = maxMelee - monsterType:getAttackList()[i].maxCombatValue			
		end
	end
	local aveMelee = (minMelee + maxMelee) / 2
	if self:isPokemon() then 
		local total = math.floor(aveMelee + ( 2 * self:getLevel()))
		if self:getMaster() and self:getMaster():getUsingBall() and self:getMaster():getUsingBall():getSpecialAttribute("nature") then
			if isInArray({"Lonely", "Adamant", "Naughty", "Brave"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 1.10
			elseif isInArray({"Bold", "Modest", "Calm", "Timid"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 0.90
			end
		end
		if self:getMaster():getVocation():getName() == "Hunter" then
			total = total * hunterDamageBuff
		end
		local talisman = self:getMaster():getUsingBall():getSpecialAttribute("talisman") or 0
		if talismanTable[talisman] and (talismanTable[talisman].buff == 'atk' or talismanTable[talisman].buff == 'all') then
			total = total * talismanTable[talisman].amount
		end
		return total
	elseif self:isMonster() then
		return math.floor(aveMelee + self:getLevel())
	end
	return 0
end

function Monster.getTotalMeleeAttackPlayerContribution(self)
	local monsterType = MonsterType(self:getName())
	local minMelee = 0
	local maxMelee = 0
	for i = 1, #monsterType:getAttackList() do
		if monsterType:getAttackList()[i].isMelee == 1 then	
			minMelee = minMelee - monsterType:getAttackList()[i].minCombatValue		
			maxMelee = maxMelee - monsterType:getAttackList()[i].maxCombatValue			
		end
	end
	local aveMelee = (minMelee + maxMelee) / 2
	if self:isPokemon() then 
		return math.floor(aveMelee * (statusGainFormula(self:getMaster():getLevel(), 0, 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMeleeAttackSummonLevelContribution(self)
	local monsterType = MonsterType(self:getName())
	local minMelee = 0
	local maxMelee = 0
	for i = 1, #monsterType:getAttackList() do
		if monsterType:getAttackList()[i].isMelee == 1 then	
			minMelee = minMelee - monsterType:getAttackList()[i].minCombatValue		
			maxMelee = maxMelee - monsterType:getAttackList()[i].maxCombatValue			
		end
	end
	local aveMelee = (minMelee + maxMelee) / 2
	if self:isPokemon() then 
		return math.floor(aveMelee * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	elseif self:isMonster() then
		return math.floor(aveMelee * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMeleeAttackSummonBoostContribution(self)
	local monsterType = MonsterType(self:getName())
	local minMelee = 0
	local maxMelee = 0
	for i = 1, #monsterType:getAttackList() do
		if monsterType:getAttackList()[i].isMelee == 1 then	
			minMelee = minMelee - monsterType:getAttackList()[i].minCombatValue		
			maxMelee = maxMelee - monsterType:getAttackList()[i].maxCombatValue			
		end
	end
	local aveMelee = (minMelee + maxMelee) / 2
	if self:isPokemon() then 
		return math.floor(aveMelee * (statusGainFormula(0, 0, self:getBoost(), 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMeleeAttackVocationContribution(self)
	local monsterType = MonsterType(self:getName())
	local minMelee = 0
	local maxMelee = 0
	for i = 1, #monsterType:getAttackList() do
		if monsterType:getAttackList()[i].isMelee == 1 then	
			minMelee = minMelee - monsterType:getAttackList()[i].minCombatValue		
			maxMelee = maxMelee - monsterType:getAttackList()[i].maxCombatValue			
		end
	end
	local aveMelee = (minMelee + maxMelee) / 2
	if self:isPokemon() then 
		if self:getMaster():getVocation():getName() == "Hunter" then
			return math.floor(aveMelee * statusGainFormula(self:getMaster():getLevel(), self:getLevel(), self:getBoost(), self:getLove()) * (hunterDamageBuff - 1.0))
		end
	end
	return 0
end

function Monster.getTotalMeleeAttackVitaminContribution(self)
	local monsterType = MonsterType(self:getName())
	local minMelee = 0
	local maxMelee = 0
	for i = 1, #monsterType:getAttackList() do
		if monsterType:getAttackList()[i].isMelee == 1 then	
			minMelee = minMelee - monsterType:getAttackList()[i].minCombatValue		
			maxMelee = maxMelee - monsterType:getAttackList()[i].maxCombatValue			
		end
	end
	local aveMelee = (minMelee + maxMelee) / 2
	if self:isPokemon() then
		local vitamins = self:getUsedVitaminsNumber("attack")
		if vitamins > 0 then
			return math.floor(aveMelee * vitamins / maxVitamins * vitaminStatusBuff)
		end
	end
	return 0
end

function Monster.getTotalMagicAttack(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then
		local total = math.floor(monsterType:getMoveMagicAttackBase() + (2 * self:getLevel()))
		if self:getMaster() and self:getMaster():getUsingBall() and self:getMaster():getUsingBall():getSpecialAttribute("nature") then
			if isInArray({"Modest", "Mild", "Rash", "Quiet"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 1.10
			elseif isInArray({"Adamant", "Impish", "Careful", "Jolly"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 0.90
			end
		end
		if self:getMaster():getVocation():getName() == "Hunter" then
			total = total * hunterDamageBuff
		end
		local talisman = self:getMaster():getUsingBall():getSpecialAttribute("talisman") or 0
		if talismanTable[talisman] and (talismanTable[talisman].buff == 'spatk' or talismanTable[talisman].buff == 'all') then
			total = total * talismanTable[talisman].amount
		end
		return total
	elseif self:isMonster() then
		return math.floor(monsterType:getMoveMagicAttackBase() + self:getLevel())
	end
	return 0
end

function Monster.getTotalMagicAttackVocationContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then
		if self:getMaster():getVocation():getName() == "Hunter" then
			return math.floor(monsterType:getMoveMagicAttackBase() * statusGainFormula(self:getMaster():getLevel(), self:getLevel(), self:getBoost(), self:getLove()) * (hunterDamageBuff - 1.0))
		end
	end
	return 0
end

function Monster.getTotalMagicAttackPlayerContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMoveMagicAttackBase() * (statusGainFormula(self:getMaster():getLevel(), 0, 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMagicAttackSummonLevelContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMoveMagicAttackBase() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	elseif self:isMonster() then
		return math.floor(monsterType:getMoveMagicAttackBase() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMagicAttackSummonBoostContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMoveMagicAttackBase() * (statusGainFormula(0, 0, self:getBoost(), 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMagicAttackVitaminContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		local vitamins = self:getUsedVitaminsNumber("magicAttack")
		if vitamins > 0 then
			return math.floor(monsterType:getMoveMagicAttackBase() * vitamins / maxVitamins * vitaminStatusBuff)
		end
	end
	return 0
end

function Monster.getTotalDefense(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then
		local total = math.floor(monsterType:getDefense()+ (2 * self:getLevel()))
		if self:getMaster() and self:getMaster():getUsingBall() and self:getMaster():getUsingBall():getSpecialAttribute("nature") then
			if isInArray({"Bold", "Impish", "Lax", "Relaxed"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 1.10
			elseif isInArray({"Lonely", "Mild", "Gentle", "Hasty"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 0.90
			end
		end
		local talisman = self:getMaster():getUsingBall():getSpecialAttribute("talisman") or 0
		if talismanTable[talisman] and (talismanTable[talisman].buff == 'def' or talismanTable[talisman].buff == 'all') then
			total = total * talismanTable[talisman].amount
		end
		return total
	elseif self:isMonster() then
		return math.floor(monsterType:getDefense() + self:getLevel())
	end
	return 0
end

function Monster.getTotalDefensePlayerContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getDefense() * (statusGainFormula(self:getMaster():getLevel(), 0, 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalDefenseSummonLevelContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getDefense() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	elseif self:isMonster() then
		return math.floor(monsterType:getDefense() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalDefenseSummonBoostContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getDefense() * (statusGainFormula(0, 0, self:getBoost(), 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalDefenseVitaminContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		local vitamins = self:getUsedVitaminsNumber("defense")
		if vitamins > 0 then
			return math.floor(monsterType:getDefense() * vitamins / maxVitamins * vitaminStatusBuff)
		end
	end
	return 0
end

function Monster.getTotalMagicDefense(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		local total = math.floor(monsterType:getMoveMagicDefenseBase() + (2 * self:getLevel()))
		if self:getMaster() and self:getMaster():getUsingBall() and self:getMaster():getUsingBall():getSpecialAttribute("nature") then
			if isInArray({"Calm", "Gentle", "Careful", "Sassy"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 1.10
			elseif isInArray({"Naughty", "Lax", "Rash", "Naive"}, self:getMaster():getUsingBall():getSpecialAttribute("nature")) then
				total = total * 0.90
			end
		end
		local talisman = self:getMaster():getUsingBall():getSpecialAttribute("talisman") or 0
		if talismanTable[talisman] and (talismanTable[talisman].buff == 'spdef' or talismanTable[talisman].buff == 'all') then
			total = total * talismanTable[talisman].amount
		end
		return total
	elseif self:isMonster() then
		return math.floor(monsterType:getMoveMagicDefenseBase() + self:getLevel())
	end
	return 0
end

function Monster.getTotalMagicDefensePlayerContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMoveMagicDefenseBase() * (statusGainFormula(self:getMaster():getLevel(), 0, 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMagicDefenseSummonLevelContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMoveMagicDefenseBase() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	elseif self:isMonster() then
		return math.floor(monsterType:getMoveMagicDefenseBase() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMagicDefenseSummonBoostContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getMoveMagicDefenseBase() * (statusGainFormula(0, 0, self:getBoost(), 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalMagicDefenseVitaminContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		local vitamins = self:getUsedVitaminsNumber("magicDefense")
		if vitamins > 0 then
			return math.floor(monsterType:getMoveMagicDefenseBase() * vitamins / maxVitamins * vitaminStatusBuff)
		end
	end
	return 0
end

function Monster.getTotalSpeed(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		local total = math.floor(monsterType:getBaseSpeed() + (2 * self:getLevel()))
		local vitamins = self:getUsedVitaminsNumber("speed")
		if vitamins > 0 then
			total = total + math.floor(monsterType:getBaseSpeed() * vitamins / maxVitamins * vitaminStatusBuff)
		end
		return total
	elseif self:isMonster() then
		return math.floor(monsterType:getBaseSpeed() + (2 * self:getLevel()))
	end
	return 0
end

function Monster.getTotalSpeedPlayerContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getBaseSpeed() * (statusGainFormula(self:getMaster():getLevel(), 0, 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalSpeedSummonLevelContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getBaseSpeed() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	elseif self:isMonster() then
		return math.floor(monsterType:getBaseSpeed() * (statusGainFormula(0, self:getLevel(), 0, 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function setConditionOn(creature, target, condi) -- Helena
	local dmg = 0.03
	local condivar = 1
	if not Creature(target) then return false end
	if not Creature(creature) then return false end
	creature = Creature(creature)
	target = Creature(target)
	if target:getName() == "Gholdengo" then return false end
	
	-- Talisman Immunity
	
	if target:getMaster() and target:getMaster():isPlayer() then
		local talisman = target:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
		if talismanTable[talisman] and talismanTable[talisman].buff == 'cure' then
			if math.random(1, 100) <= talismanTable[talisman].amount then
				return false
			end
		end
	end
	
	if isInArray(hiddenabilities.magicbounce, target:getName()) then target = creature end
	if string.find(target:getName(), "Mega ") and not target:isPokemon() then dmg = dmg / 10 end
	if isInRange(target:getPosition(), Position(2411, 0, 0), Position(2733, 351, 7)) and not isInArray({"Kleavor", "Wyrdeer", "Ursaluna", "Basculegion", "Sneasler", "Overqwil", "Toedscruel", "Wugtrio", "Annihilape", "Clodsire", "Farigiraf", "Dudunsparce", "Iron Bundle"}, target:getName()) then dmg = dmg / 10 end
	if isInArray({"Kleavor", "Wyrdeer", "Ursaluna", "Basculegion", "Sneasler", "Overqwil", "Toedscruel", "Wugtrio", "Annihilape", "Clodsire", "Farigiraf", "Dudunsparce", "Iron Bundle"}, target:getName()) then dmg = dmg / 25 end
	if target:getMaster() and target:getMaster():isNpc() then dmg = dmg / 10 end
	if creature:getMaster() and creature:getMaster():isPlayer() and creature:getMaster():getUsingBall() and creature:getMaster():getUsingBall():getSpecialAttribute('held') and creature:getMaster():getUsingBall():getSpecialAttribute('held') ~= 0 and creature:getMaster():getUsingBall():getSpecialAttribute('held') == 'held poison' and condi == 'poison' then
		condivar = 3
	elseif creature:getMaster() and creature:getMaster():isPlayer() and creature:getMaster():getUsingBall() and creature:getMaster():getUsingBall():getSpecialAttribute('held') and creature:getMaster():getUsingBall():getSpecialAttribute('held') ~= 0 and creature:getMaster():getUsingBall():getSpecialAttribute('held') == 'held burn' and condi == 'burn' then
		condivar = 3
	end	
	if creature:getMaster() and creature:getMaster():isPlayer() and creature:getMaster():getUsingBall() and creature:getMaster():getUsingBall():getSpecialAttribute('talisman') and creature:getMaster():getUsingBall():getSpecialAttribute('talisman') ~= 0 then
		local talisman = creature:getMaster():getUsingBall():getSpecialAttribute('talisman') or 0
		local retcondi = talismanTable[talisman].buff:split("_") or 0
		if retcondi ~= 0 and retcondi == "condi" and retcondi[2] == condi then condivar = condivar * talismanTable[talisman].amount end
	end
	if condi == 'confusion' then
		local condition = Condition(CONDITION_DRUNK)
		condition:setTicks(3000)
		if isInArray(hiddenabilities.owntempo, target:getName()) then
			target:getPosition():sendMagicEffect(13)
		else
			target:addCondition(condition)
		end
	elseif condi == 'defense minus' then
		local condition = Condition(CONDITION_DEFENSEMINUS)
		condition:setTicks(5000)
		if isInArray(hiddenabilities.clearbody, target:getName()) then
			target:getPosition():sendMagicEffect(13)
		else
			target:addCondition(condition)
		end
	elseif condi == 'attack minus' then
		local condition = Condition(CONDITION_ATTACKMINUS)
		condition:setTicks(5000)
		if isInArray(hiddenabilities.clearbody, target:getName()) then
			target:getPosition():sendMagicEffect(13)
		else
			target:addCondition(condition)
		end
	elseif condi == 'silence' then
		local condition = Condition(CONDITION_SILENCE)
		condition:setTicks(1500)
		if isInArray(hiddenabilities.innerfocus, target:getName()) then
			target:getPosition():sendMagicEffect(13)
		else
			target:addCondition(condition)
		end
	elseif condi == 'poison' then
		local condition = Condition(CONDITION_POISON)
		if creature:getMaster() and creature:getMaster():isPlayer() then
			condition:setParameter(CONDITION_PARAM_OWNER, creature:getMaster():getId())
		end
		condition:addDamage(5, 1000, -(target:getMaxHealth() * (dmg * condivar)))
		if isInArray(hiddenabilities.synchronize, target:getName()) then
			target:getPosition():sendMagicEffect(949)
			target:addCondition(condition)
			creature:addCondition(condition)
		else
			target:addCondition(condition)
		end
	elseif condi == 'burn' then
		local condition = Condition(CONDITION_FIRE)
		if creature:getMaster() and creature:getMaster():isPlayer() then
			condition:setParameter(CONDITION_PARAM_OWNER, creature:getMaster():getId())
		end
		if MonsterType(target:getName()):getRaceName() == 'fire' or MonsterType(target:getName()):getRace2Name() == 'fire' then return false end
		condition:addDamage(5, 1000, -(target:getMaxHealth() * (dmg * condivar)))
		if isInArray(hiddenabilities.synchronize, target:getName()) then
			target:getPosition():sendMagicEffect(949)
			target:addCondition(condition)
			creature:addCondition(condition)
		else
			target:addCondition(condition)
		end
	elseif condition == 'freezing' then
		local condition = Condition(CONDITION_FREEZING)
		if creature:getMaster() and creature:getMaster():isPlayer() then
			condition:setParameter(CONDITION_PARAM_OWNER, creature:getMaster():getId())
		end
		if MonsterType(target:getName()):getRaceName() == 'ice' or MonsterType(target:getName()):getRace2Name() == 'ice' then return false end
		condition:addDamage(5, 1000, -(target:getMaxHealth() * (dmg * condivar)))
		if isInArray(hiddenabilities.synchronize, target:getName()) then
			target:getPosition():sendMagicEffect(949)
			target:addCondition(condition)
			creature:addCondition(condition)
		else
			target:addCondition(condition)
		end
	elseif condi == 'slow' then
		local condition = Condition(CONDITION_HASTE)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		condition:setFormula(0, -(target:getSpeed() * 0.4), 0, -(target:getSpeed() * 0.4))
		if isInArray(hiddenabilities.clearbody, target:getName()) then
			target:getPosition():sendMagicEffect(13)
		else
			target:addCondition(condition)
		end
	elseif condi == 'paralyze' then
		local condition = Condition(CONDITION_PARALYZE)
		condition:setParameter(CONDITION_PARAM_TICKS, 5000)
		condition:setParameter(CONDITION_PARAM_SPEED, -1000)
		if isInArray(hiddenabilities.synchronize, target:getName()) then
			target:getPosition():sendMagicEffect(949)
			target:addCondition(condition)
			creature:addCondition(condition)
		else
			target:addCondition(condition)
		end
	elseif condi == 'sleep' then
		local condition = Condition(CONDITION_SLEEP)
		condition:setTicks(5000)
		if isInArray(hiddenabilities.insomnia, target:getName()) then
			target:getPosition():sendMagicEffect(13)
		else
			target:addCondition(condition)
		end
	elseif condi == 'seed' then
		local condition = Condition(CONDITION_SEED)
		condition:setParameter(CONDITION_PARAM_PERIODICDAMAGE, -(target:getMaxHealth() * dmg))
		condition:setParameter(CONDITION_PARAM_TICKS, 10000)
		if creature:getMaster() and creature:getMaster():isPlayer() then
			condition:setParameter(CONDITION_PARAM_OWNER, creature:getMaster():getId())
		end

		local conditionn = Condition(CONDITION_REGENERATION)
		conditionn:setParameter(CONDITION_PARAM_SUBID, 1)
		conditionn:setParameter(CONDITION_PARAM_TICKS, 10000)
		conditionn:setParameter(CONDITION_PARAM_HEALTHGAIN, (target:getMaxHealth() * dmg)/10)
		conditionn:setParameter(CONDITION_PARAM_HEALTHTICKS, 2000)
		conditionn:setParameter(CONDITION_PARAM_BUFF_SPELL, true)
		target:addCondition(condition)
		creature:addCondition(conditionn)
	end
	return true
end

function Monster.getTotalSpeedSummonBoostContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		return math.floor(monsterType:getBaseSpeed() * (statusGainFormula(0, 0, self:getBoost(), 0) - statusGainFormula(0, 0, 0, 0)))
	end
	return 0
end

function Monster.getTotalSpeedVitaminContribution(self)
	local monsterType = MonsterType(self:getName())
	if self:isPokemon() then 
		local vitamins = self:getUsedVitaminsNumber("speed")
		if vitamins > 0 then
			return math.floor(monsterType:getBaseSpeed() * vitamins / maxVitamins * vitaminStatusBuff)
		end
	end
	return 0
end

function botKick(player) -- Helena
	if not Player(player) then return false end
	if Player(player):getCondition(CONDITION_MANASHIELD) ~= nil then
		if Player(player):getCondition(CONDITION_SAFFARI) ~= nil then Player(player):removeCondition(CONDITION_SAFFARI) end
		if Player(player):getCondition(CONDITION_PARK) ~= nil then Player(player):removeCondition(CONDITION_PARK) end
		Player(player):removeCondition(CONDITION_MANASHIELD)
		Player(player):teleportTo(Player(player):getTown():getTemplePosition())
		addEvent(botCheck, 10*60*1000, Player(player).uid)
	else
		addEvent(botCheck, 10*60*1000, Player(player).uid)
	end
	return true
end

function botCheck(player) -- Helena
	if not Player(player) then return false end
	Player(player):setStorageValue(564561, math.random(1000, 9999))
	Player(player):sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "SISTEMA ANTI-BOT: Digite !antibot "..Player(player):getStorageValue(564561).." para nao ser movido para o Centro Pokemon.")
	Player(player):sendTextMessage(MESSAGE_STATUS_CONSOLE_RED, "SISTEMA ANTI-BOT: Digite !antibot "..Player(player):getStorageValue(564561).." para nao ser movido para o Centro Pokemon.")
	Player(player):sendTextMessage(MESSAGE_EVENT_ADVANCE, "SISTEMA ANTI-BOT: Digite !antibot "..Player(player):getStorageValue(564561).." para nao ser movido para o Centro Pokemon.")
	Player(player):sendTextMessage(MESSAGE_STATUS_WARNING, "SISTEMA ANTI-BOT: Digite !antibot "..Player(player):getStorageValue(564561).." para nao ser movido para o Centro Pokemon.")
	local condition = Condition(CONDITION_MANASHIELD)
	condition:setTicks(-1)
	Player(player):addCondition(condition)
	addEvent(botKick, math.random(10, 45)*60*1000, Player(player).uid)
	return true
end

function Creature.isPokemon(self)
	local master = self:getMaster()
	if master and master:isPlayer() then return true end
	return false
end

function Monster.getMonsterNumber(self)
	return MonsterType(self:getName()):dexEntry()

end

function MonsterType.getNumber(self)
	return self:dexEntry()
end

function hasSummons(cid)
	local summons = cid:getSummons()
	if #summons > 0 then
		return true
	end
	return false
end

function doHide(creature, hide) -- Helena
	if not Creature(creature) then return false end
	creature = Creature(creature)
	creature:setHiddenHealth(hide)
	local inv = Condition(CONDITION_OUTFIT)
	inv:setTicks(-1)
	inv:setOutfit({lookType = 169})
	local immune = Condition(CONDITION_IMMUNE)
	immune:setTicks(-1)
	local silence = Condition(CONDITION_SILENCE)
	silence:setTicks(-1)
	if hide == true then
		creature:addCondition(inv)
		creature:addCondition(immune)
		creature:addCondition(silence)
	else
		creature:removeCondition(CONDITION_OUTFIT)
		creature:removeCondition(CONDITION_IMMUNE)
		creature:removeCondition(CONDITION_SILENCE)
		if creature:getMaster() and creature:getMaster():getUsingBall() and creature:getMaster():getUsingBall():getSpecialAttribute('usingaddon') and creature:getMaster():getUsingBall():getSpecialAttribute('usingaddon') ~= 0 then
			local addon = Condition(CONDITION_OUTFIT)
			addon:setTicks(-1)
			addon:setOutfit({lookType = creature:getMaster():getUsingBall():getSpecialAttribute('usingaddon')})
			creature:addCondition(addon)
		elseif creature:getMaster() and creature:getMaster():getUsingBall() and creature:getMaster():getUsingBall():getSpecialAttribute('held') and creature:getMaster():getUsingBall():getSpecialAttribute('held') == "griseous orb" then
			local addon = Condition(CONDITION_OUTFIT)
			addon:setTicks(-1)
			addon:setOutfit({lookType = 3433})
			creature:addCondition(addon)
		end
	end
	return true
end

function Player.checkExhaustion(self, storage, delay)
	if os.time() > self:getStorageValue(storage) then
		self:setStorageValue(storage, os.time() + delay)
	else
		self:sendCancelMessage(RETURNVALUE_YOUAREEXHAUSTED)
		self:getPosition():sendMagicEffect(CONST_ME_POFF)
		return true		
	end
	return false
end

function Container.getBackpacks(self)
	local ret = 0
	local size = self:getSize()
	for i = size - 1, 0, -1 do
		local item = self:getItem(i)
		if item:isContainer() then
			local itemsInside = item:getBackpacks() or 0
			ret = ret + 1 + itemsInside
		end
	end
	return ret
end

function Player.getBackpacks(self)
	local bags = 0

	local backpack = self:getSlotItem(CONST_SLOT_BACKPACK)
	if backpack then
		bags = backpack:getBackpacks()
	end	
	
	return bags
end

function Player.checkMoveExhaustion(self, storage, delay)
--	local item = self:getSlotItem(CONST_SLOT_AMMO)
	local item = self:getUsingBall()
	if item then
		local move = "cd" .. tostring(storage)
		local moveCooldown = item:getSpecialAttribute(move) or 0
		if os.time() > moveCooldown then
			item:setSpecialAttribute(move, os.time() + delay)
		else
			-- self:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "You must wait " .. math.floor(item:getSpecialAttribute(move) + 1 - os.time()) .. " seconds to use this move again")
			self:sendCancelMessage("You must wait " .. math.floor(item:getSpecialAttribute(move) + 1 - os.time()) .. " seconds to use this move again")
			self:getPosition():sendMagicEffect(CONST_ME_POFF)
			return true		
		end
	end
	return false
end

function Player.getSummonNameFromBall(self)
	local item = self:getUsingBall()
	if item then
		local pokeName = item:getSpecialAttribute("pokeName")
		if pokeName ~= nil then			
			return pokeName
		end
	end
	return "unamed"
end

function Player.getSummonLevelFromBall(self)
	local item = self:getUsingBall()
	if item then
		local pokeLevel = item:getSpecialAttribute("pokeLevel")
		if pokeLevel ~= nil then			
			return pokeLevel
		end
	end
	return 1
end

function Player.getSummonBoostFromBall(self)
	local item = self:getUsingBall()
	if item then
		local pokeBoost = item:getSpecialAttribute("pokeBoost")
		if pokeBoost ~= nil then			
			return pokeBoost
		end
	end
	return 0
end

function Player.getUsingBall(self)
	local pokeballs = self:getPokeballs()
	if not pokeballs then
		print("WARNING! UsingBall not found player " .. self:getName())
		return nil
	end
	for i = 1, #pokeballs do

		local ball = pokeballs[i]
		if not ball then return end
		local isBallBeingUsed = ball:getSpecialAttribute("isBeingUsed")
		if isBallBeingUsed and isBallBeingUsed == 1 then
			return ball
		end
	end
end

function MonsterType.getRaceName(self)
	local raceNumber = self:getRace()
	if raceNumber == 1 then return "venon" end
	if raceNumber == 2 then return "blood" end
	if raceNumber == 3 then return "undead" end
	if raceNumber == 4 then return "fire" end
	if raceNumber == 5 then return "energy" end
	if raceNumber == 6 then return "grass" end
	if raceNumber == 7 then return "normal" end
	if raceNumber == 8 then return "water" end
	if raceNumber == 9 then return "flying" end
	if raceNumber == 10 then return "poison" end
	if raceNumber == 11 then return "electric" end
	if raceNumber == 12 then return "ground" end
	if raceNumber == 13 then return "psychic" end
	if raceNumber == 14 then return "rock" end
	if raceNumber == 15 then return "ice" end
	if raceNumber == 16 then return "bug" end
	if raceNumber == 17 then return "dragon" end
	if raceNumber == 18 then return "ghost" end
	if raceNumber == 19 then return "dark" end
	if raceNumber == 20 then return "steel" end
	if raceNumber == 21 then return "fairy" end
	if raceNumber == 22 then return "fighting" end
	return "none"
end

function MonsterType.getRace2Name(self)
	local raceNumber = self:getRace2()
	if raceNumber == 1 then return "venon" end
	if raceNumber == 2 then return "blood" end
	if raceNumber == 3 then return "undead" end
	if raceNumber == 4 then return "fire" end
	if raceNumber == 5 then return "energy" end
	if raceNumber == 6 then return "grass" end
	if raceNumber == 7 then return "normal" end
	if raceNumber == 8 then return "water" end
	if raceNumber == 9 then return "flying" end
	if raceNumber == 10 then return "poison" end
	if raceNumber == 11 then return "electric" end
	if raceNumber == 12 then return "ground" end
	if raceNumber == 13 then return "psychic" end
	if raceNumber == 14 then return "rock" end
	if raceNumber == 15 then return "ice" end
	if raceNumber == 16 then return "bug" end
	if raceNumber == 17 then return "dragon" end
	if raceNumber == 18 then return "ghost" end
	if raceNumber == 19 then return "dark" end
	if raceNumber == 20 then return "steel" end
	if raceNumber == 21 then return "fairy" end
	if raceNumber == 22 then return "fighting" end
	return "none"
end
 
function Player.getSummon(self)
	if hasSummons(self) then
		return self:getSummons()[1]
	end
	return false
end

function Player.isOnRide(self)
	if self:getStorageValue(storageRide) > 0 then
		return true
	end
	return false
end

function Player.isOnFly(self)
	if self:getStorageValue(storageFly) > 0 then
		return true
	end
	return false
end

function Player.isOnSurf(self)
	if self:getStorageValue(storageSurf) > 0 then
		return true
	end
	return false
end

function Player.isOnBike(self)
	if self:getStorageValue(storageBike) == 1 then
		return true
	end
	return false
end

function Player.isOnEvent(self)
	if self:getStorageValue(storageEvent) == 1 then
		return true
	end
	return false
end

function Player.isOnDive(self)
	if self:getStorageValue(storageDive) == 1 then
		return true
	end
	return false
end

function Player.isAutoLooting(self)
	if self:getStorageValue(storageAutoLoot) == 1 then
		return true
	end
	return false
end

function Player.enableAutoLoot(self)
	if self:getStorageValue(storageAutoLoot) < 0 then
		self:setStorageValue(storageAutoLoot, 1)
		return true
	end
	return false
end

function Player.disableAutoLoot(self)
	if self:getStorageValue(storageAutoLoot) == 1 then
		self:setStorageValue(storageAutoLoot, -1)
		return true
	end
	return false
end

function Monster.getSummonLevel(self)
	if self:isPokemon() then
		local master = self:getMaster()
		local item = master:getUsingBall()
		local pokeLevel = item:getSpecialAttribute("pokeLevel")
		if pokeLevel ~= nil then			
			return pokeLevel
		end
	elseif isMonster(self) then
		return self:getLevel()
	end
	return 1
end

function Monster.getSummonBoost(self)
	if self:isPokemon() then
		local master = self:getMaster()
--		local item = master:getSlotItem(CONST_SLOT_AMMO)
		local item = master:getUsingBall()
		local pokeBoost = item:getSpecialAttribute("pokeBoost")
		if pokeBoost ~= nil then
			return pokeBoost
		end
	end
	return 0
end

function Monster.getLove(self)
	if self:isPokemon() then
		local master = self:getMaster()
--		local item = master:getSlotItem(CONST_SLOT_AMMO)
		local item = master:getUsingBall()
		local pokeLove = item:getSpecialAttribute("pokeLove")
		if pokeLove ~= nil then
			return pokeLove
		end
	end
	return 0
end

function Monster.getMasterLevel(self)
	if self:isPokemon() then
		local master = self:getMaster()
		if master then			
			return master:getLevel()
		end
	end
	return 1
end

function Monster.getSummonName(self)
	if isSummon(self) then
		local master = self:getMaster()
--		local item = master:getSlotItem(CONST_SLOT_AMMO)
		local item = master:getUsingBall()
		local pokeName = item:getSpecialAttribute("pokeName")
		if pokeName ~= nil then			
			return pokeName
		end
	end
	return "unamed"
end

function Monster.isEvolving(self)
	if self:isPokemon() then
		local master = self:getMaster()
		if master and master:getStorageValue(storageEvolving) == 1 then return true end
	end
	return false
end

function doChangeOutfit(cid, outfit, time)
	local creature = Creature(cid)
	if not creature then return false end
	if time == nil then time = -1 end
	doSetCreatureOutfit(creature.uid, outfit, time)
	return true
end

function doSendDelayedEffect(pos, effect)
	local tile = Tile(pos)
	if tile then
		pos:sendMagicEffect(effect)
	end
	return true
end

function doTransformPokeball(item)
	if not item:isPokeball() then return false end
	for key, value in pairs(balls) do
		if value.usedOn == item:getId() then
			doTransformItem(item.uid, value.usedOff)
			return true			
		end
		if value.usedOff == item:getId() then
			doTransformItem(item.uid, value.usedOn)
			return true			
		end
	end
	return false
end

function doReleaseSummon(cid, pos, effect, message, missile)
	local player = Player(cid)
	if not player then return false end
--	local ball = player:getSlotItem(CONST_SLOT_AMMO)
	local ball = player:getUsingBall()
	if not ball then return false end
	if effect == nil then effect = CONST_ME_TELEPORT end
	if message == nil then message = true end
	local name = ball:getSpecialAttribute("pokeName")
	-- to fix ball bug
	if not name then
		ball:remove()
		return false
	end
	if name == "Ditto" and ball:getSpecialAttribute("dittoTransform") then
		-- local dittoTime = ball:getSpecialAttribute("dittoTime")
		-- if dittoTime and os.time() < dittoTime then
			name = ball:getSpecialAttribute("dittoTransform")
		-- end
	end

	local monsterType = MonsterType(name)
	if not monsterType:isConvinceable() then
		print("WARNING: Monster " .. name .. " is not convinceable.")
		player:sendCancelMessage("Sorry, not possible. This problem was reported.")
		ball:setSpecialAttribute("isBeingUsed", 0)
		return false 
	end
	if not monsterType:isIllusionable() then
		print("WARNING: Monster " .. name .. " is not illusionable.")
		player:sendCancelMessage("Sorry, not possible. This problem was reported.")
		ball:setSpecialAttribute("isBeingUsed", 0)
		return false 
	end
	if not monsterType:isSummonable() then
		print("WARNING: Monster " .. name .. " is not illusionable.")
		player:sendCancelMessage("Sorry, not possible. This problem was reported.")
		ball:setSpecialAttribute("isBeingUsed", 0)
		return false 
	end

	local health = ball:getSpecialAttribute("pokeHealth") or 0
	if health <= 0 then
		player:sendCancelMessage("Sorry, not possible. Your summon is dead.")
		ball:setSpecialAttribute("isBeingUsed", 0)
		return true
	end	

	local summonLevel = ball:getSpecialAttribute("pokeLevel")
	local summonBoost = ball:getSpecialAttribute("pokeBoost") or 0
	
	local newPos = player:getClosestFreePosition(pos, 2) or pos
	if newPos.x == 0 then
		newPos = pos
	end
	
	if ball:getSpecialAttribute("held") ~= 0 and megas[ball:getSpecialAttribute("held")] and megas[ball:getSpecialAttribute("held")].name and megas[ball:getSpecialAttribute("held")].name == name then
		local topos = player:getPosition()
		topos:getNextPosition(1)
		topos:getNextPosition(2)
		topos:sendMagicEffect(1040)
		name = "Mega "..name
		if name == "Mega Charizard" and ball:getSpecialAttribute("held") == "charizardite x" then
			name = name.." X"
		elseif name == "Mega Charizard" and ball:getSpecialAttribute("held") == "charizardite y" then
			name = name.." Y"
		end
	end
	
	monsterType = MonsterType(name)
	
	local monster = Game.createMonster(name, newPos, true, true, summonLevel, summonBoost)

	if monster ~= nil then
		if message then
			player:say(monster:getName() .. ", I need your help!", TALKTYPE_MONSTER_SAY)
		end
		player:addSummon(monster)
		monster:setDirection(ball:getSpecialAttribute("pokeLookDir") or DIRECTION_SOUTH)
		if summonBoost >= maxBoost then
			doStartAurea(monster)
		end
		local maxHealth = monster:getTotalHealth()
		local evhp = ball:getSpecialAttribute("evhp") or 0
		monster:setMaxHealth(maxHealth + (evhp * 10)) 
		monster:setHealth(health)
		monster:changeSpeed(-monster:getSpeed() + monster:getTotalSpeed())
		if ball:getId() == 26678 or ball:getId() == 26666 then
			monster:setSkull(30)
		end
		if ball:getSpecialAttribute("teraType") and ball:getSpecialAttribute("teraType") ~= 0 and ball:getSpecialAttribute("teraType") > 10 then
			monster:setSkull(ball:getSpecialAttribute("teraType"))
		end
		-- Form Change System
		
		if name == "Unown" then
			local letter = ball:getSpecialAttribute("unown")
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = unowns[letter]})
			Creature(monster):addCondition(condition)
		elseif name == "Wormadam" then
			local letter = ball:getSpecialAttribute("wormadam")
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = tonumber(letter)})
			Creature(monster):addCondition(condition)
		elseif name == "Giratina" and ball:getSpecialAttribute("held") and ball:getSpecialAttribute("held") ~= 0 and ball:getSpecialAttribute("held") == "griseous orb" then
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = 3433})
			Creature(monster):addCondition(condition)
		elseif name == "Zacian" and ball:getSpecialAttribute("held") and ball:getSpecialAttribute("held") ~= 0 and ball:getSpecialAttribute("held") == "rusted sword" then
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = 3433})
			Creature(monster):addCondition(condition)
		elseif name == "Zamazenta" and ball:getSpecialAttribute("held") and ball:getSpecialAttribute("held") ~= 0 and ball:getSpecialAttribute("held") == "rusted shield" then
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = 3433})
			Creature(monster):addCondition(condition)
		elseif name == "Groudon" and ball:getSpecialAttribute("held") and ball:getSpecialAttribute("held") ~= 0 and ball:getSpecialAttribute("held") == "red orb" then
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = 3433})
			Creature(monster):addCondition(condition)
		elseif name == "Kyogre" and ball:getSpecialAttribute("held") and ball:getSpecialAttribute("held") ~= 0 and ball:getSpecialAttribute("held") == "blue orb" then
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = 3433})
			Creature(monster):addCondition(condition)
		elseif name == "Pikachu" and ball:getSpecialAttribute("held") and ball:getSpecialAttribute("held") ~= 0 and ball:getSpecialAttribute("held") == "light ball" then
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = 3433})
			Creature(monster):addCondition(condition)
		elseif name == "Hoopa" and ball:getSpecialAttribute("held") and ball:getSpecialAttribute("held") ~= 0 and ball:getSpecialAttribute("held") == "prison bottle" then
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = 4026})
			Creature(monster):addCondition(condition)
		elseif name == "Shaymin" and ball:getSpecialAttribute("held") and ball:getSpecialAttribute("held") ~= 0 and ball:getSpecialAttribute("held") == "gracidea" then
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			condition:setOutfit({lookType = 3492})
			Creature(monster):addCondition(condition)
		elseif name == "Deoxys" and ball:getSpecialAttribute("form") and ball:getSpecialAttribute("form") ~= 0 then
			local form = ball:getSpecialAttribute("form")
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			if form == "attack" then
				condition:setOutfit({lookType = 3444})
			elseif form == "defense" then
				condition:setOutfit({lookType = 3445})
			elseif form == "speed" then
				condition:setOutfit({lookType = 3439})
			elseif form == "base" then
				condition:setOutfit({lookType = 3636})
			end
			Creature(monster):addCondition(condition)
		elseif name == "Rotom" and ball:getSpecialAttribute("form") and ball:getSpecialAttribute("form") ~= 0 then
			local form = ball:getSpecialAttribute("form")
			local condition = Condition(CONDITION_OUTFIT)
			condition:setTicks(-1)
			if form == "heat" then
				condition:setOutfit({lookType = 3458})
			elseif form == "fan" then
				condition:setOutfit({lookType = 3456})
			elseif form == "mow" then
				condition:setOutfit({lookType = 3452})
			elseif form == "wash" then
				condition:setOutfit({lookType = 3460})
			elseif form == "frost" then
				condition:setOutfit({lookType = 3450})
			elseif form == "normal" then
				condition:setOutfit({lookType = 3454})
			end
			Creature(monster):addCondition(condition)
		end
		
		if ball:getSpecialAttribute('usingaddon') and ball:getSpecialAttribute('usingaddon') ~= 0 then
			local addon = Condition(CONDITION_OUTFIT)
			addon:setTicks(-1)
			if string.find(player:getSummon():getName() , "Mega ") then
				if addonmega[ball:getSpecialAttribute('usingaddon')] then
					addon:setOutfit({lookType = addonmega[ball:getSpecialAttribute('usingaddon')]})
				else
					addon:setOutfit({lookType = ball:getSpecialAttribute('usingaddon')})
				end
			else
				addon:setOutfit({lookType = ball:getSpecialAttribute('usingaddon')})
			end
			Creature(monster):addCondition(addon)
		end

		if effect then
			monster:getPosition():sendMagicEffect(effect)
		end
		if missile then
			doSendDistanceShoot(player:getPosition(), monster:getPosition(), missile)
		end
		monster:removeTarget(player)
		monster:registerEvent("MonsterHealthChange")
		monster:registerEvent("MonsterDeath")
		player:registerEvent("RemoveSummon")

		local attackers = Game.getSpectators(newPos, true, false) 
		for i = 1, #attackers do
			local attacker = attackers[i]
			if attacker and attacker:isMonster() then
				local hostile = MonsterType(Monster(attacker):getName()):isHostile()
				if hostile then
					if attacker:getTarget() == player then
						attacker:addTarget(monster, true)
						attacker:removeTarget(Creature(player:getId()))
						attacker:searchTarget()
--						for i = 1, #attacker:getTargetList() do
--							print(attacker:getTargetList()[i]:getName())
--						end
					end
				end
			end
		end

		local movesTable = {}
		local moves = monsterType:getMoveList()
		for i = 1, #moveWords do
			local move = moves[i]
			if move or (player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0) then
				if i == 1 then
					if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0 then
						table.insert(movesTable, player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[1])
					elseif player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) and player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) ~= 0 then
						table.insert(movesTable, player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[1])
					else
						table.insert(movesTable, move.name)
					end
				else
					if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0 then
						table.insert(movesTable, "," .. player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[1])
					elseif player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) and player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) ~= 0 then
						table.insert(movesTable, "," .. player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[1])
					else
						table.insert(movesTable, "," .. move.name)
					end
				end
			end
		end
		for i = 1, #moveWords do
			local move = moves[i]
			if move or (player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0) then
				if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0 then
					table.insert(movesTable, "," .. tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[2]))
				elseif player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) and player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) ~= 0 then
					table.insert(movesTable, "," .. tonumber(player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[2]))
				else
					table.insert(movesTable, "," .. move.speed)
				end
			end
		end
		for i = 1, #moveWords do
			local move = "cd" .. tostring(i)
			local moveCooldown = ball:getSpecialAttribute(move) or 0
			if os.time() > moveCooldown then
				table.insert(movesTable, ",0")
			else
				table.insert(movesTable, "," .. 1000 * math.floor(ball:getSpecialAttribute(move) - os.time()))
			end
		end
		for i = 1, #moveWords do
			local move = moves[i]
			if move or (player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0) then
				if player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) and player:getUsingBall():getSpecialAttribute("plate"..tostring(i)) ~= 0 then
					table.insert(movesTable, "," .. tonumber(player:getUsingBall():getSpecialAttribute("plate"..tostring(i)):split("|")[3]))
				elseif player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) and player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)) ~= 0 then
					table.insert(movesTable, "," .. tonumber(player:getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[3]))
				else
					table.insert(movesTable, "," .. move.level)
				end
			end
		end
		table.insert(movesTable, "," ..summonLevel)
		table.insert(movesTable, ",")
		player:sendExtendedOpcode(52, table.concat(movesTable))
		-- print(table.concat(movesTable))
		return monster:getId()
	end
	return true
end

function doRemoveSummon(cid, effect, uid, message, missile)
	local player = Player(cid)
	if not player then return false end
	if effect == nil then effect = CONST_ME_POFF end
	if message == nil then message = true end
	local summons = player:getSummons()
	if not summons then return false end
	local summon = Creature(summons[1])
	if not summon then
		return false
	end
	local summonPos = summon:getPosition()
	local attackers = Game.getSpectators(summonPos, true, false) 
	for i = 1, #attackers do
		local attacker = attackers[i]
		if attacker and attacker:isMonster() then
--			attacker:say(attacker:getTargetCount(), TALKTYPE_SAY)
			local targetList = attacker:getTargetList()
			for j = 1, #targetList do
				if targetList[j] == summon then
					attacker:removeTarget(summon)
					attacker:setIdle()
				end
			end
		end
	end
	if effect then
		summonPos:sendMagicEffect(effect)
	end
	if missile then
		doSendDistanceShoot(summonPos, player:getPosition(), missile)
	end
	summon:unregisterEvent("MonsterGetExperience")
	summon:unregisterEvent("MonsterHealthChange")
	player:unregisterEvent("RemoveSummon")
--	local ball = player:getSlotItem(CONST_SLOT_AMMO)
	local ball = player:getUsingBall()
	if uid and not ball then
		ball = Item(uid)
	end
	if ball and ball:isPokeball() then
		ball:setSpecialAttribute("pokeHealth", summon:getHealth())
		ball:setSpecialAttribute("pokeLookDir", summon:getDirection())
	end
	if not (player:isOnFly() or player:isOnRide() or player:isOnSurf() or summon:isEvolving()) then
		if ball then
			ball:setSpecialAttribute("isBeingUsed", 0)
		else
			print("WARNING! Player " .. player:getName() .. " had problems on remove summon: ball does not exist.")
		end
	end
	if summon:isEvolving() then 
		player:setStorageValue(storageEvolving, -1)
	end
	if message then
		player:say("Thanks, " .. summon:getName() .. "!", TALKTYPE_MONSTER_SAY)
	end
	summon:remove()	
	return true
end

function doEvolveSummon(cid, evolutionName, ancient)
	if not ancient then ancient = false end
	local monsterType = MonsterType(evolutionName)
	local summon = Creature(cid)
	local master = summon:getMaster()
	local summonPos = summon:getPosition()
--	local item = master:getSlotItem(CONST_SLOT_AMMO)
	local item = master:getUsingBall()
	if monsterType and summon:isMonster() then
		master:say("Wow, my " .. summon:getName() .. " is evolving!", TALKTYPE_SAY)
		master:getPosition():sendMagicEffect(292)
		master:setStorageValue(storageEvolving, 1)
		summon:changeSpeed(-summon:getSpeed())
		item:setSpecialAttribute("pokeName", evolutionName)
		if ancient then
			item:setSpecialAttribute("owner", master:getName())
			master:setStorageValue(storageEvolutionAncient, 1)
		end
--		local portrait = master:getSlotItem(CONST_SLOT_HEAD)
--		local removePortrait = nil
--		if portrait then
--			removePortrait = master:removeItem(portrait:getId(), 1)
--		end
--		local portraitId = monsterType:portraitId()
--		if portraitId ~= 0 then 
--			local putPortrait = master:addItem(portraitId, 1, false, 1, CONST_SLOT_HEAD)
--			if not removePortrait or not putPortrait and master:getSlotItem(CONST_SLOT_HEAD):getId() ~= portraitId then
--				print("WARNING! Problem on put portrait after evolution " .. evolutionName .. " player " .. master:getName())
--			end
--		end

		local baseHealth = MonsterType(evolutionName):getMaxHealth()
		local newMaxHealth = math.floor(baseHealth * statusGainFormula(master:getLevel(), item:getSpecialAttribute("pokeLevel"), item:getSpecialAttribute("pokeBoost"), item:getSpecialAttribute("pokeLove") or 0))
		summon:setMaxHealth(newMaxHealth)
		summon:setHealth(newMaxHealth)

		addEvent(doChangeOutfit, 500, summon:getId(), monsterType:getOutfit(), 500)
		addEvent(doSendDelayedEffect, 500, summon:getPosition(), 10)
		addEvent(doSendDelayedEffect, 1000, summon:getPosition(), 12)
		addEvent(doChangeOutfit, 1500, summon:getId(), monsterType:getOutfit(), 500)
		addEvent(doSendDelayedEffect, 1500, summon:getPosition(), 10)
		addEvent(doSendDelayedEffect, 2000, summon:getPosition(), 12)
		addEvent(doSendDelayedEffect, 4000, summon:getPosition(), CONST_ME_HEARTS)

		addEvent(doRemoveSummon, 4000, master:getId(), false, nil, false)
		addEvent(doReleaseSummon, 4001, master:getId(), summonPos, false, false)
		master:refreshPokemonBar({}, {})
		return true
	else
		print("WARNING! Problem on evolution to " .. evolutionName .. " player " .. master:getName())
	end
	return false
end

function Position:sendAnimatedNumber(message_type, text, value, color)
	local message_type = message_type or MESSAGE_EXPERIENCE
	local color = color or TEXTCOLOR_BLUE
	local valid_message_types = {
		MESSAGE_DAMAGE_DEALT,
		MESSAGE_DAMAGE_OTHERS,
		MESSAGE_DAMAGE_RECEIVED,
		MESSAGE_EXPERIENCE,
		MESSAGE_EXPERIENCE_OTHERS,
		MESSAGE_HEALED,
		MESSAGE_HEALED_OTHERS,
	}
	assert(isInArray(valid_message_types, message_type), "invalid 'message_type', must output to server log")
	for _, v in ipairs(Game.getSpectators(self, false, true)) do
		if v:isPlayer() then
			v:sendTextMessage(message_type, text, self, value, color)
		end
	end
	return
end

function Item.isPokeball(self)
	for key, value in pairs(balls) do
		if value.usedOn == self:getId() or value.usedOff == self:getId() then
			return true			
		end
	end
	return false
end

function doAddPokeball(cid, name, level, boost, ballKey, dp, msg, teratype)
	local player = Player(cid)
	local letter
	local worm
	if player then
		name = firstToUpper(name)
		if string.find(name, "Unown") then
			letter = name:split("|")[2]
			name = "Unown"
		end
		if string.find(name, "Wormadam") then
			worm = name:split("|")[2]
			name = "Wormadam"
		end
		local monsterType = MonsterType(name)
		if not monsterType then 
			print("WARNING: Monster " .. name .. " impossible to catch.") 
			player:sendCancelMessage("Sorry, not possible. This problem was reported.")
			return false 
		end
		local addBall
		if dp == false then
			addBall = player:addItem(balls[ballKey].usedOn, 1, false)
		else
			local depot = player:getInbox()
			addBall = depot:addItem(balls[ballKey].usedOn, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
		end
		if not addBall then
			if dp == false then -- try send to CP because BP is full
				local depot = player:getInbox()
				addBall = depot:addItem(balls[ballKey].usedOn, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
				addEvent(doPlayerSendTextMessage, msg, cid, MESSAGE_EVENT_ADVANCE, "Since you are at maximum capacity, your ball was sent to CP.")
--				print("WARNING! Player " .. player:getName() .. " sending pokemon " .. name .. " to CP after first try.")
				dp = true
			else
				addBall = player:addItem(balls[ballKey].usedOn, 1)
				addEvent(doPlayerSendTextMessage, msg, cid, MESSAGE_STATUS_WARNING, "Pokemon lost. Your CP is full!")
				print("WARNING! Player " .. player:getName() .. " lost pokemon " .. name .. " because CP is full.")
			end
		end
		if addBall then
			local baseHealth = monsterType:getMaxHealth()
			local maxHealth = math.floor(baseHealth * statusGainFormula(player:getLevel(), level, boost, 0))
			addBall:setSpecialAttribute("pokeName", name)
			addBall:setSpecialAttribute("pokeLevel", level)
			addBall:setSpecialAttribute("pokeBoost", boost)
			addBall:setSpecialAttribute("pokeExperience", getNeededExp(level))
			addBall:setSpecialAttribute("pokeMaxHealth", maxHealth)
			addBall:setSpecialAttribute("pokeHealth", maxHealth)
			addBall:setSpecialAttribute("evhp", 0)
			addBall:setSpecialAttribute("evatk", 0)
			addBall:setSpecialAttribute("evdef", 0)
			addBall:setSpecialAttribute("evpoints", 0)
			addBall:setSpecialAttribute("evkills", 0)
			addBall:setSpecialAttribute("pokeLove", 0)
			if catchNature or ballKey == "parkball" then
				local natures = {"Hardy", "Docile", "Bashful", "Quirky", "Serious", "Lonely", "Naughty", "Brave", "Bold", "Impish", "Lax", "Relaxed", "Mild", "Rash", "Quiet", "Calm", "Gentle", "Careful", "Sassy", "Timid", "Hasty", "Jolly", "Naive", "Adamant", "Modest", "Hardy", "Docile", "Bashful", "Quirky", "Serious", "Lonely", "Naughty", "Brave", "Bold", "Impish", "Lax", "Relaxed", "Mild", "Rash", "Quiet", "Calm", "Gentle", "Careful", "Sassy", "Timid", "Hasty", "Jolly", "Naive", "Hardy", "Docile", "Bashful", "Quirky", "Serious", "Lonely", "Naughty", "Brave", "Bold", "Impish", "Lax", "Relaxed", "Mild", "Rash", "Quiet", "Calm", "Gentle", "Careful", "Sassy", "Timid", "Hasty", "Jolly", "Naive", "Hardy", "Docile", "Bashful", "Quirky", "Serious", "Lonely", "Naughty", "Brave", "Bold", "Impish", "Lax", "Relaxed", "Mild", "Rash", "Quiet", "Calm", "Gentle", "Careful", "Sassy", "Timid", "Hasty", "Jolly", "Naive"}
				addBall:setSpecialAttribute("nature", natures[math.random(1, #natures)])
			end
			if ballKey == "masterball" then
				local atk = monsterType:getMeleeDamage()
				local spatk = monsterType:getMoveMagicAttackBase()
				local def = monsterType:getDefense()
				local spdef = monsterType:getMoveMagicDefenseBase()
				local higher1
				local higher2
				
				if atk > spatk then higher1 = atk elseif atk <= spatk then higher1 = spatk end
				if def > spdef then higher2 = def elseif def <= spdef then higher2 = spdef end
				if higher1 >= higher2 then
					if higher1 == atk then
						addBall:setSpecialAttribute("nature", "Adamant")
					elseif higher1 == spatk then
						addBall:setSpecialAttribute("nature", "Modest")
					end
				else
					if higher2 == def then
						addBall:setSpecialAttribute("nature", "Bold")
					elseif higher2 == spdef then
						addBall:setSpecialAttribute("nature", "Calm")
					end
				end
			end
			if teratype ~= 0 then
				addBall:setSpecialAttribute("teraType", teratype)
			end
			if letter ~= nil then
				addBall:setSpecialAttribute("unown", letter)
			end
			if worm ~= nil then
				addBall:setSpecialAttribute("wormadam", tonumber(worm))
			end
			if dp == false then
				player:refreshPokemonBar({}, {})
			end
			player:save()
			return true
		else
			print("ERROR! Player " .. player:getName() .. " lost pokemon " .. name .. " for unknown reason.")
		end
	end
	print("WARNING! Player not found to add pokeball.")
	return false	
end

function Player.getPokeballCount(self)
	local nBalls = 0
	for key, value in pairs(balls) do
		nBalls = nBalls + self:getItemCount(value.usedOn) + self:getItemCount(value.usedOff)
	end	
	return nBalls
end

function searchInContainer(container, itemId)
	local count = 0
	if container:isContainer() then
		local items = container:getItem()
		for i = 0, container:getSize() do
			local item = container:getItem(i)
			if item then
				if item:isContainer() then
					if item:getId() == itemId then
						count = count + item:getCount()
					end
					count = count + searchInContainer(item, itemId)
				elseif item:getId() == itemId then
					count = count + item:getCount()
				end
			end
		end
	end
	return count
end

function hasEmptySpace(container)
	if container:isContainer() then
		if container:getEmptySlots() >= 1 then
			return true
		else
			for i = 0, container:getSize() do
				local item = container:getItem(i)
				if item and item:isContainer() and item:getEmptySlots() >= 1 then
					return true	
				elseif item and item:isContainer() and item:getEmptySlots() < 1 then
					if hasEmptySpace(item) then
						return true
					end
				end
			end
		end
	end
	return false
end

function Item.isStone(self)
	if isInArray(stonesId[1], self:getId()) then
		return true
	end
	return false
end

function Container.getPokeballs(self)
	local ret = {}
		local size = self:getSize()
		for i = size - 1, 0, -1 do
			local item = self:getItem(i)
			if item:isPokeball() then
				table.insert(ret, item)
			elseif item:isContainer() then
				local itemsInside = item:getPokeballs()
				for i=0, #itemsInside do
					table.insert(ret, itemsInside[i])
				end
			end
		end
	return ret
end

function Player.getPokeballs(self)
	local pokeballs = {}

	local backpack = self:getSlotItem(CONST_SLOT_BACKPACK)
	if backpack then
		pokeballs = backpack:getPokeballs()
	end	

	local ballOn = self:getSlotItem(CONST_SLOT_AMMO)
	if ballOn and ballOn:isPokeball() then
		table.insert(pokeballs, ballOn)
	end

	return pokeballs
end

function Player.getBags(self)
	local size = self:getSlotItem(CONST_SLOT_BACKPACK):getSize()
	for i = size - 1, 0, -1 do
		local item = self:getItem(i)
		if item:isContainer() then
			return item
		end
	end
	return self:getSlotItem(CONST_SLOT_BACKPACK)
end

function Player.updateQuestLog(self)
	for key, value in pairs(quests) do
		if self:getLevel() >= value.level then
			for j = 1, #value.prizes do
				for k = 1, #value.prizes do
					if self:getStorageValue(value.prizes[k].uid) < 0 then
						self:setStorageValue(value.prizes[k].uid, 0)
					end
				end
			end
		end
	end
	return
end

function firstToUpper(str)
    return (str:gsub("^%l", string.upper))
end

function Position:createFlyFloor()
	local toTile = Tile(self)
	if not toTile or not toTile:getItems() or not toTile:getGround() then
		doAreaCombatHealth(0, 0, self, 0, 0, 0, CONST_ME_NONE)
		Game.createItem(flyFloor, 1, self):decay()
	end
	return true
end

function isInRange(position, fromPosition, toPosition) -- Helena
    return (position.x >= fromPosition.x and position.y >= fromPosition.y and position.z >= fromPosition.z and position.x <= toPosition.x and position.y <= toPosition.y and position.z <= toPosition.z)
end

function isInArea(position, range1, range2, thing) -- Helena
	local area = Game.getSpectators(position, false, false, range1, range2)
	for i = 1, #area do
		local spectator = area[i]
		if spectator and spectator.uid == thing then
			return true
		end
	end
	return false
end

function areaHasPlayer(position, range1, range2) -- Helena
	local area = Game.getSpectators(position, false, true, range1, range1, range2, range2)
	for i = 1, #area do
		local spectator = area[i]
		if spectator and spectator:isPlayer() then
			return true
		end
	end
	return false
end

function areaHasOtherPlayer(player, position, range1, range2) -- Helena
	local area = Game.getSpectators(position, false, true, range1, range1, range2, range2)
	for i = 1, #area do
		local spectator = area[i]
		if spectator and spectator:isPlayer() and Player(spectator):getId() ~= Player(player):getId() then
			return true
		end
	end
	return false
end

function cleanArea(position, range1, range2) -- Helena
	local area = Game.getSpectators(position, false, false, range1, range1, range2, range2)
	for i = 1, #area do
		local spectator = area[i]
		if spectator and isNpc(spectator) then
			doRemoveCreature(Npc(spectator))
			return true
		elseif spectator and spectator:isMonster() then
			doRemoveCreature(Creature(spectator))
			return true
		end
	end
	return false
end
 
function Tile:hasValidGround()
	local ground = self:getGround()
	local nilItem = self:getItemById(flyFloor)
	if ground and not nilItem then
		return true
	end 
	return false
end
 
function Player:activateFly()
	self:setStorageValue(storageFly, 1)
	self:registerEvent("FlyEvent")
	return true
end
 
function Player:deactivateFly()
	local can, floor = self:canDeactivateFly()
	local pos = self:getPosition()
	if can then
		local curtile = Tile(pos)
		local nilItem = curtile:getItemById(flyFloor)
		if nilItem then
			nilItem:remove()
		end
		self:unregisterEvent("FlyEvent")
		if pos.z ~= floor then
			pos.z = floor
			self:teleportTo(pos)
			pos:sendMagicEffect(CONST_ME_TELEPORT)
		end
	end 
	return can
end

function Player:canDeactivateFly()
    local pos = self:getPosition()
--    for z = pos.z, 15 do
        local tmp = Tile(pos.x, pos.y, pos.z)
        if tmp and tmp:hasValidGround() then
            if self:canFlyDown(pos.z) then
                return true, pos.z
            else
                return false
            end
        end
--    end
 
    return false
end
 
function Player:canFlyUp()
	local pos = self:getPosition()
	local tmp = Tile(pos.x, pos.y, pos.z-1)
	local topos = pos.z-1
	if tmp and tmp:hasValidGround() then
		return false
	end 
	tmp = Tile(pos.x, pos.y, pos.z-1)

	if tmp and (tmp:getHouse() or tmp:hasFlag(TILESTATE_PROTECTIONZONE) or tmp:hasFlag(TILESTATE_FLOORCHANGE) or tmp:hasFlag(TILESTATE_BLOCKSOLID) ) then
		return false
	end 
	
	if topos == 0 or topos == 1 then
		return false
	end

	if tmp and tmp:getGround() and isInArray(waterIds, tmp:getGround():getId()) then
		return false
	end
	return true
end
 
function Player:canFlyDown(floor)
	local pos = self:getPosition()
	local tmp = Tile(pos)
	if floor and floor == pos.z then
		return true
	end 
	if tmp:hasValidGround() then
		return false
	end 
	tmp = Tile(pos.x, pos.y, floor or pos.z+1)

	if tmp and (tmp:getHouse() or tmp:hasFlag(TILESTATE_PROTECTIONZONE) or tmp:hasFlag(TILESTATE_FLOORCHANGE) or tmp:hasFlag(TILESTATE_BLOCKSOLID) ) then
		return false
	end 

	if tmp and tmp:getGround() and isInArray(waterIds, tmp:getGround():getId()) then
		return false
	end
    return true
end
 
function Player:flyUp()
	if self:isOnFly() then
		if self:canFlyUp() then
			local pos = self:getPosition()
			local tile = Tile(pos)
			local itemfloor = tile:getItemById(flyFloor)
			if itemfloor then
				itemfloor:remove()
			end 
			pos.z = pos.z-1
			pos:createFlyFloor()
			self:teleportTo(pos)
			pos:sendMagicEffect(CONST_ME_TELEPORT) 
			return true
		end 
		return false
	else
		self:sendCancelMessage("You are not flying.")
		return false
	end
end
 
function Player:flyDown()
	if self:isOnFly() then
		if self:canFlyDown() then
			local pos = self:getPosition()
			local tile = Tile(pos)
			local itemfloor = tile:getItemById(flyFloor)
			if itemfloor then
				itemfloor:remove()
			end 
			pos.z = pos.z+1
			pos:createFlyFloor()
			self:teleportTo(pos)
			pos:sendMagicEffect(CONST_ME_TELEPORT)
			return true
		end 
		return false
	else
		self:sendCancelMessage("You are not flying.")
		return false
	end
end

function Player:addTokens(number)
	if self:getStorageValue(storageTokens) < 0 then
		self:setStorageValue(storageTokens, number)
	else
		self:setStorageValue(storageTokens, self:getStorageValue(storageTokens) + number)
	end
	return true
end

function Player:removeTokens(number)
	if self:getStorageValue(storageTokens) < number then
		return false
	else
		self:setStorageValue(storageTokens, self:getStorageValue(storageTokens) - number)
	end
	return true
end

function Player:getTokens()
	if self:getStorageValue(storageTokens) < 0 then
		return 0
	end
	return self:getStorageValue(storageTokens)
end

function Creature:hasKilledLegendaryPokemon()
	if self:isPlayer() and (os.time() < self:getStorageValue(storageLastLegendaryKilled)) then
		return true
	end
	return false
end

function Player:setKilledLegendaryPokemon()
	self:setStorageValue(storageLastLegendaryKilled, os.time() + 10 * 60)
	return true
end

function Player:isDuelingWithNpc()
	if self:getStorageValue(storageDuelNpc) > 0 then
		return true
	end
	return false
end

function Player:setDuelWithNpc()
	self:setStorageValue(storageDuelNpc, 1)
	self:setStorageValue(storageDuelNpcStatus, 1)
	return true
end

function Player:setOnLeague()
	self:setStorageValue(storageLeague, 1)
	self:setStorageValue(storageLeaguePotion, 0)
	self:setStorageValue(storageLeagueRevive, 0)
	self:setStorageValue(storageLeagueTime, os.time())
	return true
end

function Player:setOutLeague()
	self:setStorageValue(storageLeague, -1)
	return true
end

function Player:isOnLeague()
	if self:getStorageValue(storageLeague) == 1 then
		return true
	end
	return false
end

function Player:canUsePotionOnLeague()
	if self:getStorageValue(storageLeaguePotion) < 0 then self:setStorageValue(storageLeaguePotion, 0) end
	if self:getStorageValue(storageLeaguePotion) < 25 then
		self:setStorageValue(storageLeaguePotion, self:getStorageValue(storageLeaguePotion) + 1)
		self:sendTextMessage(MESSAGE_INFO_DESCR, "Usando potion " .. self:getStorageValue(storageLeaguePotion) .. " de 25.")
		return true
	end
	return false
end

function Player:canUseReviveOnLeague()
	if self:getStorageValue(storageLeagueRevive) < 0 then self:setStorageValue(storageLeagueRevive, 0) end
	if self:getStorageValue(storageLeagueRevive) < 5 then
		self:setStorageValue(storageLeagueRevive, self:getStorageValue(storageLeagueRevive) + 1)
		self:sendTextMessage(MESSAGE_INFO_DESCR, "Usando revive " .. self:getStorageValue(storageLeagueRevive) .. " de 5.")
		return true
	end
	return false
end

function Player:unsetDuelWithNpc()
	self:setStorageValue(storageDuelNpc, -1)
	return true
end

function Player:getDuelWithNpcStatus()
	if self:getStorageValue(storageDuelNpcStatus) < 1 then
		return 1
	end
	return self:getStorageValue(storageDuelNpcStatus)
end

function Player:increaseDuelWithNpcStatus()
	if self:getStorageValue(storageDuelNpcStatus) < 1 then
		self:setStorageValue(storageDuelNpcStatus, 1)
	else
		self:setStorageValue(storageDuelNpcStatus, self:getStorageValue(storageDuelNpcStatus) + 1)
	end	
	return true
end

function getBadgeQuantity(player) -- Helena
	local badges = {quests.boulderBadge.prizes[1].uid, quests.cascadeBadge.prizes[1].uid, quests.thunderBadge.prizes[1].uid, quests.rainbowBadge.prizes[1].uid, quests.soulBadge.prizes[1].uid, quests.marshBadge.prizes[1].uid, quests.volcanoBadge.prizes[1].uid, quests.earthBadge.prizes[1].uid}
	local qt = 0
	for i = 1, #badges do
		if player:getStorageValue(badges[i]) >= 1 then
			qt = qt + 1
		end
	end
	return qt
end

function Player:giveQuestPrize(uid, ignore)
	local playerCap = self:getFreeCapacity()
	local totalWeight = 0
	if ignore == nil then ignore = false end

	for key, value in pairs(quests) do
		for j = 1, #value.prizes do
			if uid == value.prizes[j].uid then
				if self:getLevel() >= value.level then
					local questDone = false
					for k = 1, #value.prizes do
						if self:getStorageValue(value.prizes[k].uid) > 0 then
							questDone = true
						end
					end
					if ignore == true then questDone = false end
					if questDone == false then
						for i = 1, #value.prizes[j].items do
							totalWeight = totalWeight + ItemType(value.prizes[j].items[i].item):getWeight()
						end
						if playerCap >= totalWeight then
							if value.teleportCP == 1 then
								self:teleportTo(self:getTown():getTemplePosition())
							end
							for i = 1, #value.prizes[j].pokes do
								local dp = 1
								local container = self:getSlotItem(CONST_SLOT_BACKPACK)							
								if self:getFreeCapacity() >= 1 and container and container:getEmptySlots() > 0 then
									dp = 0
								end
								local tera = value.prizes[j].pokes[i].tera or 0
								if math.random(1, 1000) >= 2 then tera = 0 end
								doAddPokeball(self:getId(), value.prizes[j].pokes[i].name, value.prizes[j].pokes[i].level, value.prizes[j].pokes[i].boost, getBallKey(balls.ultraball.usedOn), dp, 0, tera)
								local msg = 'You have found: ' .. value.prizes[j].pokes[i].name .. ', level ' .. value.prizes[j].pokes[i].level ..', boost ' .. value.prizes[j].pokes[i].boost .. '.'
								if dp == 1 then
									msg = msg .. " It was sent do CP because you do not have enough capacity."
								end
								self:sendTextMessage(MESSAGE_INFO_DESCR, msg)

							end
							
							for i = 1, #value.prizes[j].items do
								local itemzinho = value.prizes[j].items[i].item
								if itemzinho == heldt1[1] then
									itemzinho = heldt1[math.random(1, 6)]
								elseif itemzinho == heldt2[1] then
									itemzinho = heldt2[math.random(1, 6)]
								end
								if self:isPremium() and isInArray({65009, 65010, 65011, 65012, 65013, 65014, 65015, 65016, 65029, 65026, 65027}, uid) then
									self:addItem(itemzinho, math.ceil(value.prizes[j].items[i].count * 1.25))
									self:sendTextMessage(MESSAGE_INFO_DESCR, 'You have found: ' .. math.ceil(value.prizes[j].items[i].count * 1.25) .. " " .. ItemType(itemzinho):getName() .. '.')
								else
									self:addItem(itemzinho, value.prizes[j].items[i].count)
									self:sendTextMessage(MESSAGE_INFO_DESCR, 'You have found: ' .. value.prizes[j].items[i].count .. " " .. ItemType(itemzinho):getName() .. '.')
								end
							end

							for i = 1, #value.prizes[j].badges do
								local item = self:getItemById(value.prizes[j].badges[i].remove, true)
								if item then
									item:transform(value.prizes[j].badges[i].add)
									self:sendTextMessage(MESSAGE_INFO_DESCR, 'You have found: ' .. ItemType(value.prizes[j].badges[i].add):getName() .. '.')
								else
									print("WARNING! Player " .. self:getName() .. " with problems while adding " .. ItemType(value.prizes[j].badges[i].add):getName() .. ".")
								end
							end
							if value.experience then
								self:addExperience(value.experience, true)
							end
							self:setStorageValue(uid, 1)
							if value.message then
								self:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, value.message)
							end
							for k = 1, #value.prizes do
								if self:getStorageValue(value.prizes[k].uid) <= 0 then
									self:setStorageValue(value.prizes[k].uid, 1)
								end
							end
							self:save()
						else
							self:sendTextMessage(MESSAGE_INFO_DESCR, 'Too heavy for you.')
						end

					else
						self:sendTextMessage(MESSAGE_INFO_DESCR, "It is empty.")
					end
				else
					self:sendTextMessage(MESSAGE_INFO_DESCR, "You need level " .. value.level .. " to open.")
				end
				return true
			end
		end
	end

	self:sendTextMessage(MESSAGE_INFO_DESCR, "It is empty.")
	return false
end

function Player:addSlotItems()
	for i = 1, #slotItems do
		local itemId = slotItems[i]
		if itemId == 26820 then
			if self:getItemById(38897) or self:getItemById(38898) or self:getItemById(38899) then return false end
		end
		if not self:getItemById(itemId) then
			local item = self:addItem(itemId)
			if item and itemId == badgeContainer and ItemType(itemId) then
				local container = Container(item.uid)
				if container then
					for j = 1, #badgesPortraits do
						container:addItem(badgesPortraits[j])
					end
				end
			end
		end
	end
	return
end

function Position:getClosestTownId()
	local distances = {}

	for i = 1, 59 do
		local town = Town(i)
		if town then
			local templePosition = town:getTemplePosition()
			distances[i] = getDistanceBetween(templePosition, self)
		end
	end

	local key = next(distances)
	local min = distances[key]

	for k, v in pairs(distances) do
	    if distances[k] < min then
		key, min = k, v
	    end
	end

	return key
end

function MonsterType:isLegendary()
	if isInArray(self:getCreatureEvents(), "LegendariesDeath") then
		return true
	end
	return false
end

function Player:refreshPokemonBar(add, remove)
	local pokeballs = self:getPokeballs()
	local pokemonsTable = {}
	for i = 1, #pokeballs do
		local ball = pokeballs[i]
		local pokeName = ball:getSpecialAttribute("pokeName")
		if not pokeName then -- fix ball bug
			ball:remove()
			print("WARNING! Player " .. self:getName() .. " had one ball removed!")
		else
			if not isInArray(remove, pokeName) then
				table.insert(pokemonsTable, "," .. pokeName)
			end
		end
		
	end
	for i = 1, #add do
		table.insert(pokemonsTable, "," .. add[i])
	end
	table.insert(pokemonsTable, ",")
	self:sendExtendedOpcode(53, table.concat(pokemonsTable))
--	self:setSpecialStorage("pokes", pokeballs)
	return true
end

function Player:isSummonBlocked()
--	if os.time() > self:getStorageValue(storageDelay) then
--	       	self:setStorageValue(storageDelay, os.time() + delay)
--	else
--		self:sendCancelMessage(RETURNVALUE_YOUAREEXHAUSTED)
--		return true
--	end

--	if item ~= self:getSlotItem(CONST_SLOT_AMMO) then
--		self:sendCancelMessage("Sorry, not possible. Please put the pokeball in the right place.")
--              return true
--	end

	if self:getSlotItem(CONST_SLOT_LEFT) == nil then
		self:sendCancelMessage("Sorry, not possible. You need a wand to control your summon.")
                return true
	end

	if self:getStorageValue(storageRide) == 1 then
		self:sendCancelMessage("Sorry, not possible while on ride.")
		return true
	end

	if self:getStorageValue(storageFly) == 1 then
		self:sendCancelMessage("Sorry, not possible while on fly.")
		return true
	end

	if self:getStorageValue(storageSurf) > 0 then
		self:sendCancelMessage("Sorry, not possible while on surf.")
		return true
	end

	if self:getStorageValue(storageEvent) > 0 then
		self:sendCancelMessage("Sorry, not possible while on event.")
		return true
	end

	if self:getStorageValue(storageEvolving) == 1 then
		self:sendCancelMessage("Sorry, not possible while evolving.")
		return true
	end

	return false
end


function Player:canReleaseSummon(pokeLevel, pokeBoost, ownerName)

	-- to fix ball bug
	if not pokeLevel then return false end

	local playerLevel = self:getLevel() + (10 * getBadgeQuantity(self))
	local minimumLevel = (pokeLevel + pokeBoost) - 10

	if playerLevel < minimumLevel then
		self:sendCancelMessage("Sorry, not possible. You need level " .. minimumLevel .. " to use this pokemon.")
		return false
	end

	if ownerName then
		if self:getStorageValue(quests.cathemAll.prizes[1].uid) < 2 then
			print("WARNING! Player " .. self:getName() .. " using unique Pokemon without finish the quest!")
		end
	end

	if ownerName and ownerName ~= self:getName() then
		self:sendCancelMessage("Sorry, it belongs to " .. ownerName .. ".")
		return false
	end

	return true
end

function Item:getSummonLevel()
	return self:getSpecialAttribute("pokeLevel")
end

function Item:getSummonName()
	return self:getSpecialAttribute("pokeName")
end

function Item:getSummonBoost()
	return self:getSpecialAttribute("pokeBoost")
end

function Item:getSummonOwner()
	return self:getSpecialAttribute("owner")
end

function Item:isBeingUsed()
	local isBallBeingUsed = self:getSpecialAttribute("isBeingUsed")
	if isBallBeingUsed and isBallBeingUsed == 1 then
		return true
	end
	return false
end

function Item:setBeingUsed()
	self:setSpecialAttribute("isBeingUsed", 1)
	return true
end

function Item:unsetBeingUsed()
	self:setSpecialAttribute("isBeingUsed", 0)
	return true
end

function Player:getCatchRemain(table)
	local catchRemain = 0
	local msg = "Pokemons que faltam catalogar: \n"
	for i = 1, #table do
		if self:getStorageValue(baseStorageCatches + table[i]) <= 0 then
			catchRemain = catchRemain + 1
--			msg = msg .. "[" .. table[i] .. "] " .. monsterNumber[table[i]][1] .. "\n"
			msg = msg .. "[" .. table[i] .. "] " .. monstersTable[tonumber(table[i])] .. "\n"
		end
	end
	if msg ~= "Pokemons que faltam catalogar: \n" then
		self:showTextDialog(2263, msg)
	end
	return catchRemain
end

function Monster:getUsedVitaminsNumber(status)
	if status == nil then status = "vitTotal" end
	local total = 0
	if self:isPokemon() then
		local item = self:getMaster():getUsingBall()
		if item then
			total = item:getSpecialAttribute(status)
			if not total or total < 0 then total = 0 end
		end		
	end	
	return total
end

function Monster:increaseUsedVitaminsNumber()
	if self:isPokemon() then
		local item = self:getMaster():getUsingBall()
		if item then
			local total = item:getSpecialAttribute("vitTotal")
			if not total or total < 0 then total = 0 end
			if total < maxVitamins then
				item:setSpecialAttribute("vitTotal", total + 1)
				return true
			end
		end		
	end
	return false
end

function Monster:increaseStatus(statusName)
	if self:isPokemon() then
		local master = self:getMaster()
		local item = master:getUsingBall()
		if item then
			local total = item:getSpecialAttribute(statusName)
			if not total or total < 0 then total = 0 end
			item:setSpecialAttribute(statusName, total + 1)
			if statusName == "pokeLevel" then
				item:setSpecialAttribute("pokeExperience", getNeededExp(total + 1))
				doRemoveSummon(master:getId(), false, nil, false)
				item:setSpecialAttribute("isBeingUsed", 1)
				doReleaseSummon(master:getId(), self:getPosition(), false, false)
			end
			return true
		end		
	end
	return false
end

function Player:getCatchRemainNumber(table)
	local catchRemain = 0
	for i = 1, #table do
		if self:getStorageValue(baseStorageCatches + table[i]) <= 0 then
			catchRemain = catchRemain + 1
		end
	end
	return catchRemain
end
