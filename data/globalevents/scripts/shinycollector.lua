local datas = {"Thursday", "Tuesday", "Saturday"}
local poke1 = {"medichamite", "houndoominite", "banettite", "pinsirite", "absolite", "sablenite", "altarianite", "slowbronite", "pidgeotite", "glalitite", "beedrillite"}
local poke2 = {"gengarite", "gardevoirite", "ampharosite", "venusaurite", "charizardite x", "charizardite y", "blastoisinite", "blazikeninte", "scizorite", "lucarionite", "abomasnite", "gyaradosite", "alakazite", "swampertite", "sceptilite", "galladite", "cameruptite"}
local poke3 = {"aggronite", "tyranitarite", "aerodactylite", "kangaskhanite", "audinite", "metagrossite", "steelixite", "salamencite"}
local function doBroad()
	broadcastMessage("O NPC [Mega Collector] esta visitando o TRADING CENTER. Ele ficara ate as 22:00.", MESSAGE_STATUS_WARNING)
end

function onTime(interval)
	local dia = os.date("%A")
	if isInArray(datas, dia) then
		local npc = Game.createNpc("Mega Collector", Position(692, 854, 2))
		local npc2 = Game.createNpc("Mega Collector", Position(671, 854, 2))
		addEvent(doRemoveCreature, 12*60*60*1000, npc.uid)
		addEvent(doRemoveCreature, 12*60*60*1000, npc2.uid)
		setGlobalStorageValue(1001, poke1[math.random(1, #poke1)])
		setGlobalStorageValue(1002, poke2[math.random(1, #poke2)])
		setGlobalStorageValue(1003, poke3[math.random(1, #poke3)])
		broadcastMessage("O NPC [Mega Collector] esta visitando o TRADING CENTER. Ele ficara ate as 22:00.", MESSAGE_STATUS_WARNING)
		for i = 1, 23 do
			addEvent(doBroad, i * (30*60*1000))
		end
	end
	return true
end
