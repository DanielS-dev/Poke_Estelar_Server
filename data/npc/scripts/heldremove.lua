local priceLinearSlope = 12
local priceLinearIntercept = 1900
local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)
local chosen
local price
function onCreatureAppear(cid)              npcHandler:onCreatureAppear(cid)            end
function onCreatureDisappear(cid)           npcHandler:onCreatureDisappear(cid)         end
function onCreatureSay(cid, type, msg)      npcHandler:onCreatureSay(cid, type, msg)    end
function onThink()                          npcHandler:onThink()                        end

function creatureSayCallback(cid, type, msg)
	if not npcHandler:isFocused(cid) then
		return false
	end
	
	msg = firstToUpper(msg)

	if msgcontains(msg, 'bye') then
		selfSay('Ok then.', cid)
		npcHandler:releaseFocus(cid)
	elseif msgcontains(msg, 'remover') or msgcontains(msg, 'remove') then
		local player = Player(cid)
		if not player:getUsingBall() then
			selfSay('Solte o pokemon com o held para ser removido.', cid)
			npcHandler:releaseFocus(cid)
		end
		if player:getUsingBall() and player:getUsingBall():getSpecialAttribute("held") and player:getUsingBall():getSpecialAttribute("held") ~= 0 and not isInArray({"gold coin", "empty pokeball", "small potion", "clean disk", "empty greatball", "great potion", "platinum coin", "water stone", "fire stone", "leaf stone", "thunder stone", "ice stone", "empty ultraball", "ultra potion", "revive", "rare candy", "crystal coin", "king's rock", "moon stone", "upgrade", "dubious disk", "metal coat", "sun stone", "dragon scale", "protector", "magmarizer", "electirizer", "empty premierball", "hyper potion", 'rusted sword', 'rusted shield', 'red orb', 'blue orb', 'light ball', 'griseous orb', 'gracidea', 'prison bottle'}, player:getUsingBall():getSpecialAttribute("held")) and not isInArray({"abomasite", "absolite", "aerodactylite", "aggronite", "alakazite", "altarianite", "ampharosite", "audinite", "banettite", "beedrillite", "blastoisinite", "blazikenite", "cameruptite", "charizardite x", "charizardite y", "diancite", "galladite", "garchompite", "gardevoirite", "gengarite", "glalitite", "gyaradosite", "heracronite", "houndoominite", "kangaskhanite", "latiasite", "latiosite", "lopunnite", "lucarionite", "manectite", "mawilite", "medichamite", "metagrossite", "mewtwonite x", "mewtwonite y", "pidgeotite", "pinsirite", "sablenite", "salamencite", "sceptilite", "scizorite", "sharpedonite", "slowbronite", "steelixite", "swampertite", "tyranitarite", "venusaurite"}, player:getUsingBall():getSpecialAttribute("held")) then
			player:getUsingBall():setSpecialAttribute("held", 0)
			player:addTokens(50)
			selfSay('HELD REMOVIDO E 50 TOKENS ADICIONADOS A SUA CONTA.', cid)
		end
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
