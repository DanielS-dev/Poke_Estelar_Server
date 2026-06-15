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
	if getGlobalStorageValue(3000) == "close" then
		selfSay('Nao operamos hoje, volte nos dias: {sexta} ou {sabado}. As {11:00} our as {21:00}. ', cid)
		npcHandler:releaseFocus(cid)
	end
	
	if msgcontains(msg, 'bye') or msgcontains(msg, 'no') or msgcontains(msg, 'nao') then
		selfSay('Talvez uma outra hora.', cid)
		npcHandler:releaseFocus(cid)
	elseif msgcontains(msg, 'registrar') then
		selfSay('Para participar do evento basta ficar dentro do quadrado demarcado e aguardar o inicio do evento. Lembre-se, sem revives e potions la dentro hein!', cid)
		npcHandler:releaseFocus(cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
