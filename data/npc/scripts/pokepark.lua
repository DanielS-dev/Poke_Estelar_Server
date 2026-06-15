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
	elseif msgcontains(msg, 'registrar') then
		selfSay('O custo para entrar no PokePark e 1 {pokepark ticket}, voce tem certeza que quer entrar?', cid)
	elseif msgcontains(msg, 'pokepark ticket') then
		if Player(cid):getItemCount(39142) >= 1 and Player(cid):removeItem(39142, 1) then
			Player(cid):teleportTo(Position(942, 1725, 13))
			Player(cid):addItem(39132, 50)
			local condition = Condition(CONDITION_PARK)
			condition:setTicks(-1)
			Player(cid):addCondition(condition)
			npcHandler:releaseFocus(cid)
		else
			selfSay('Voce nao possui PokePark tickets, voce pode comprar pokepark tickets em nossa loja ou em dungeons.', cid)
		end
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
