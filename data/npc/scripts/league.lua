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
	elseif (msgcontains(msg, 'liga') or msgcontains(msg, 'entrar')) and getBadgeQuantity(Player(cid)) ~= 8 then
		selfSay('Voce nao tem 8 insignias, volte quando estiver preparado.', cid)
		npcHandler:releaseFocus(cid)
	elseif (msgcontains(msg, 'liga') or msgcontains(msg, 'entrar')) and getBadgeQuantity(Player(cid)) == 8 then
		if not areaHasPlayer(Position(283, 870, 5), 2, 2) and not areaHasPlayer(Position(283, 870, 4), 2, 2) and not areaHasPlayer(Position(283, 870, 3), 2, 2) and not areaHasPlayer(Position(283, 870, 2), 2, 2) and not areaHasPlayer(Position(283, 870, 1), 2, 2) then
			Player(cid):teleportTo(Position(282, 872, 5))
			npcHandler:releaseFocus(cid)
		else
			selfSay('Alguem esta tentando a liga agora, tente novamente mais tarde.', cid)
			npcHandler:releaseFocus(cid)
		end
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
