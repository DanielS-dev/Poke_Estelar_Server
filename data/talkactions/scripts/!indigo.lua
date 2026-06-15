function onSay(player, words, param)
	local prizes = {"abomasite", "absolite", "aerodactylite", "aggronite", "alakazite", "altarianite", "ampharosite", "banettite", "beedrillite", "blastoisinite", "blazikenite", "cameruptite", "charizardite x", "charizardite y", "galladite", "garchompite", "gardevoirite", "gengarite", "glalitite", "gyaradosite", "heracronite", "houndoominite", "kangaskhanite", "lopunnite", "lucarionite", "manectite", "mawilite", "medichamite", "metagrossite", "pidgeotite", "pinsirite", "sablenite", "salamencite", "sceptilite", "scizorite", "slowbronite", "steelixite", "swampertite", "tyranitarite", "venusaurite", "empty masterball"}
	if not isInArray(prizes, param:lower()) then
		local txt = "Abomasite, "
		for i = 2, #prizes do
			txt = txt .. firstToUpper(prizes[i]) .. ", "
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Escolha um dos premios a seguir e digite !indigo xxxxxx.")
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, txt)
	elseif isInArray(prizes, param:lower()) then
		if player:removeItem(26197, 1) then
			player:addItem(param, 1)
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce resgatou um "..param..".")
			return false
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao possui um indigo prize orb.")
			return false
		end
	end
	return false
end
	