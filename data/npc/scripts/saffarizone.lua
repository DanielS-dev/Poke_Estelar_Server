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
	elseif msgcontains(msg, 'entrar') then
		selfSay('O custo para entrar na {Saffari Zone} e 10.000 gold coins, voce deseja entrar mesmo assim?', cid)
	elseif msgcontains(msg, 'yes') or msgcontains(msg, 'sim') or msgcontains(msg, 'saffari') then
		if Player(cid):removeMoney(10000) then
			Player(cid):addItem("empty saffariball", 50)
			local condition = Condition(CONDITION_SAFFARI)
			condition:setTicks(-1)
			Player(cid):addCondition(condition)
			Player(cid):teleportTo(Position(1209, 1664, 14))
			npcHandler:releaseFocus(cid)
		else
			selfSay('Voce nao possui 10.000 gold coins para acessar o saffari.', cid)
		end
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
