local heldss = {
	[39143] = {name = 'rusted sword', poke = "Zacian"},
	[39144] = {name = 'rusted shield', poke = "Zamazenta"},
	[39145] = {name = 'red orb', poke = "Groudon"},
	[39146] = {name = 'blue orb', poke = "Kyogre"},
	[39147] = {name = 'light ball', poke = "Pikachu"},
	[39148] = {name = 'griseous orb', poke = "Giratina"},
	[39149] = {name = 'gracidea', poke = "Shaymin"},
	[39150] = {name = 'prison bottle', poke = "Hoopa"},
	
	[39197] = {name = "abomasite", poke = "Abomasnow"},
	[39173] = {name = "absolite", poke = "Absol"},
	[39172] = {name = "aerodactylite", poke = "Aerodactyl"},
	[39171] = {name = "aggronite", poke = "Aggron"},
	[39170] = {name = "alakazite", poke = "Alakazam"},
	[39169] = {name = "altarianite", poke = "Altaria"},
	[39168] = {name = "ampharosite", poke = "Ampharos"},
	[39167] = {name = "audinite", poke = "Audino"},
	[39166] = {name = "banettite", poke = "Banette"},
	[39165] = {name = "beedrillite", poke = "Beedrill"},
	[39164] = {name = "blastoisinite", poke = "Blastoise"},
	[39163] = {name = "blazikenite", poke = "Blaziken"},
	[39162] = {name = "cameruptite", poke = "Camerupt"},
	[39161] = {name = "charizardite x", poke = "Charizard"},
	[39160] = {name = "charizardite y", poke = "Charizard"},
	[39159] = {name = "diancite", poke = "Diancie"},
	[39158] = {name = "galladite", poke = "Gallade"},
	[39157] = {name = "garchompite", poke = "Garchomp"},
	[39156] = {name = "gardevoirite", poke = "Gardevoir"},
	[39155] = {name = "gengarite", poke = "Gengar"},
	[39154] = {name = "glalitite", poke = "Glalie"},
	[39153] = {name = "gyaradosite", poke = "Gyarados"},
	[39152] = {name = "heracronite", poke = "Heracross"},
	[39151] = {name = "houndoominite", poke = "Houndoom"},
	[39174] = {name = "kangaskhanite", poke = "Kangaskhan"},
	[39196] = {name = "latiasite", poke = "Latias"},
	[39195] = {name = "latiosite", poke = "Latios"},
	[39194] = {name = "lopunnite", poke = "Lopunny"},
	[39193] = {name = "lucarionite", poke = "Lucario"},
	[39192] = {name = "manectite", poke = "Manectric"},
	[39191] = {name = "mawilite", poke = "Mawile"},
	[39190] = {name = "medichamite", poke = "Medicham"},
	[39189] = {name = "metagrossite", poke = "Metagross"},
	[39188] = {name = "mewtwonite x", poke = "Mewtwo"},
	[39187] = {name = "mewtwonite y", poke = "Mewtwo"},
	[39186] = {name = "pidgeotite", poke = "Pidgeot"},
	[39185] = {name = "pinsirite", poke = "Pinsir"},
	[39184] = {name = "sablenite", poke = "Sableye"},
	[39183] = {name = "salamencite", poke = "Salamence"},
	[39182] = {name = "sceptilite", poke = "Sceptile"},
	[39181] = {name = "scizorite", poke = "Scizor"},
	[39180] = {name = "sharpedonite", poke = "Sharpedo"},
	[39179] = {name = "slowbronite", poke = "Slowbro"},
	[39178] = {name = "steelixite", poke = "Steelix"},
	[39177] = {name = "swampertite", poke = "Swampert"},
	[39176] = {name = "tyranitarite", poke = "Tyranitar"},
	[39175] = {name = "venusaurite", poke = "Venusaur"},
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if hasSummons(player) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon precisa estar para dentro para evoluir.")
		return false
	end
	
	if not target:isPokeball() then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce so pode usar isso em uma pokebola.")
		return false
	end
	
	if not isInArray(player:getPokeballs(), target) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce so pode usar isso em uma pokebola que seja sua.")
		return false
	end

	if target:isPokeball() then
		if heldss[item:getId()] then
			local heldName = heldss[item:getId()].name
			local pokeName = heldss[item:getId()].poke
			if target:getSpecialAttribute("held") and target:getSpecialAttribute("held") ~= 0 then
				player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon ja possui um held, por favor, remova o held em um celular.")
				return false
			end
			if target:getSpecialAttribute("pokeName") ~= pokeName then
				player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Este pokemon nao pode usar o held "..name..".")
				return false
			end
			if target:setSpecialAttribute("held", heldName) then
				item:remove()
			end
		else
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Held desabilitado no momento, por favor informe a equipe sobre o held.")
			return false
		end
	end
	return true
end
