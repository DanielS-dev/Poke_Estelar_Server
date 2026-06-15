local priceLinearSlope = 12
local priceLinearIntercept = 1900
local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)

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
		selfSay('Okay entao ate logo.', cid)
		npcHandler:releaseFocus(cid)
	elseif msgcontains(msg, 'gatos') and Player(cid):getStorageValue(65021) < 1 then
		selfSay('A-ha! Eu sabia, eu nunca erro! Voce poderia me ajudar com um {favor}?', cid)
	elseif msgcontains(msg, 'favor') and Player(cid):getStorageValue(65021) < 1 then
		selfSay('Voce poderia me trazer alguns itens? Te darei uma recompensa se aceitar!', cid)
	elseif msgcontains(msg, 'yes') and Player(cid):getStorageValue(65021) < 1 then
		selfSay('Okay, eu preciso de 100 {wool ball}s para os meus gatos, haha. Me avise quando voce trouxer elas.', cid)
		npcHandler.topic[cid] = 1
	elseif msgcontains(msg, 'wool ball') and npcHandler.topic[cid] == 1 and Player(cid):getStorageValue(65021) < 1 then
		local player = Player(cid)
		if Player(cid):removeItem('wool ball', 100) then
			selfSay('Obrigada, precisava muito dessas wool balls, os persians que tenho acabam com todas muito rapido. Ah, claro, sua recompensa! Aqui esta um Persian de outra regiao, garanto que voce nao ira encontra outro por aqui!', cid)
			Player(cid):giveQuestPrize(65021)
			return true
		else
			selfSay('Voce nao trouxe 100 {wool ball}s pra mim, volte quando trouxer.', cid)
			npcHandler:releaseFocus(cid)
		end
	else
		selfSay('Cuide bem do Persian por mim!', cid)
		npcHandler:releaseFocus(cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
