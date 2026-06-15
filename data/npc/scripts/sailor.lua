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
	
	if msgcontains(msg, 'bye') or msgcontains(msg, 'no') or msgcontains(msg, 'nao') then
		selfSay('Talvez uma outra hora.', cid)
		npcHandler:releaseFocus(cid)
	elseif msgcontains(msg, 'aventurar') or msgcontains(msg, 'yes') or msgcontains(msg, 'sim') then
		selfSay('O custo para entrar na {zona de distorcao} e 500 tokens, voce so pode voar la se for premium, caso contrario leve um surf, voce deseja entrar mesmo assim?', cid)
	elseif msgcontains(msg, 'yes') or msgcontains(msg, 'sim') or msgcontains(msg, 'zona de distorcao') then
		if Player(cid):removeTokens(500) then
			Player(cid):teleportTo(Position(2577, 60, 7))
			npcHandler:releaseFocus(cid)
		else
			selfSay('Voce nao possui 500 tokens para custear essa viagem.', cid)
		end
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
