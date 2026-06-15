function onSay(player, words, param)
	local accounts = {"owatari", "tinaco", "JOSHUA", "george1921", "pedrosonego", "winigui", "nottz", "220500", "187110", "george192", "12443631", "voka", "tadashi20", "megamanx", "Somono", "silasgbs", "Alissonkp", "boohmaah", "corre", "mateus55", "Chacal", "amerigo", "thanatoss", "554466", "55223355", "Laxus", "debora123", "f220500", "danijo", "tyssault", "matox321", "fumoloco", "moyinhu", "reformedluxanna", "654321", "waynesouza7", "danielalve", "aldozzv", "393939", "bladebomb118", "wesley12", "helderchenko", "Olimix", "xk4un", "willjack", "duduzim", "asdasdasd", "gustavopk9", "Hyago", "vinidd", "boal123", "moyinhu2", "panyco", "waynesouza", "binladeiro", "brenno", "Luckest", "58713316", "luffy", "tonyrafa15", "nottz2", "aksz", "teta182", "Cimeriano", "ranv22", "evicley", "pguimeuxd", "Ralphz", "tsribs", "32023395", "996633", "998877", "cine", "mutante", "PAIDOZAY", "kakaguil", "kelmerjf", "54696894", "leorato111", "wepe", "Luizbiham", "zargone", "shugara", "lucianomoaz", "164716", "rennanaraujo", "lucasneves", "lucasnevessw", "kiera", "thi123", "bladelottus", "Mystogan", "411071", "bieuh", "marciow", "mateus019", "manoleo", "NbN", "MariahAlice", "deiong", "MariaJulia", "9894112", "belo", "Hallfa", "2310581e", "pave", "xnenel", "brmaru", "954813", "diegof", "gabriel1", "martin", "feargonz", "Kashi", "564540", "Ferored", "BBaessoo", "perusion", "notplayer", "wefis", "seeaa", "naahxfeh", "netotome", "Lokonoog", "andres2201", "maaster", "zagarofgamer", "silveirar", "325255pokefans"}
	local account = db.storeQuery("SELECT `name` FROM `accounts` WHERE `id` = " .. player:getAccountId())
	local accountname = result.getDataString(account, "name")
	if isInArray(accounts, accountname) then
		if player:getStorageValue(65033) == 1 then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce ja resgatou sua recompensa.")
			return false
		end
		if param:lower() == "articuno" then
			player:addOutfit(3656)
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce recebeu sua outfit exclusiva do Beta.")
			player:giveQuestPrize(65033)
		elseif param:lower() == "moltres" then
			player:addOutfit(3658)
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce recebeu sua outfit exclusiva do Beta.")
			player:giveQuestPrize(65033)
		elseif param:lower() == "zapdos" then
			player:addOutfit(3657)
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce recebeu sua outfit exclusiva do Beta.")
			player:giveQuestPrize(65033)
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Por favor, digite o nome da outfit que voce deseja, ex: !betareward articuno")
		end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Sua conta nao possui um nome utilizado no beta.")
		return false
	end
	return false
end
	