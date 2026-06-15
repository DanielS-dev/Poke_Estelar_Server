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
	elseif msgcontains(msg, 'name') or msgcontains(msg, 'sell') or msgcontains(msg, 'buy') then
		selfSay('Hoje estou procurando: '..getGlobalStorageValue(1001)..', '..getGlobalStorageValue(1002)..' e '..getGlobalStorageValue(1003)..'.', cid)
	elseif msgcontains(msg, 'yes') or msgcontains(msg, 'sim') and npcHandler.topic[cid] == 1 then
		local player = Player(cid)
		local amount = player:getStorageValue(666666) or 0
		if amount < 3 then
			if player:removeItem(chosen, 1) then
				selfSay('Tome '..price..' packs de pe pela mega stone ['..chosen..'].', cid)
				player:addItem(38942, price)
				player:setStorageValue(666666, amount + 1)
				npcHandler:releaseFocus(cid)
				return true
			end
		else
			selfSay('Voce esgotou todo meu estoque de pack de pe essa semana, volte semana que vem.', cid)
			npcHandler:releaseFocus(cid)
			return true
		end
	else
		local player = Player(cid)
		if msg then
			if msg:lower() == getGlobalStorageValue(1001):lower() then
				chosen = msg
				price = 10
				selfSay('Eu compro a mega stone ['..chosen..'] por '..price..' packs de pe, voce aceita?', cid)
				npcHandler.topic[cid] = 1
			elseif msg:lower() == getGlobalStorageValue(1002):lower() then
				chosen = msg
				price = 20
				selfSay('Eu compro a mega stone ['..chosen..'] por '..price..' packs de pe, voce aceita?', cid)
				npcHandler.topic[cid] = 1
			elseif msg:lower() == getGlobalStorageValue(1003):lower() then
				chosen = msg
				price = 30
				selfSay('Eu compro a mega stone ['..chosen..'] por '..price..' packs de pe, voce aceita?', cid)
				npcHandler.topic[cid] = 1
			end
		else
			selfSay('Eu so compro mega stones.', cid)
		end
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
