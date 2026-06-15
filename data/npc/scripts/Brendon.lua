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
	elseif msgcontains(msg, 'dugtrio') and Player(cid):getStorageValue(65020) < 1 then
		selfSay('Voce nao poderia descer nessa caverna e {capturar} um Sandslash pra mim? Eu tenho medo do escuro...', cid)
	elseif (msgcontains(msg, 'capturar') or msgcontains(msg, 'yes')) and Player(cid):getStorageValue(65020) < 1 then
		selfSay('Muito obrigado, vou ficar aguardando voce voltar com o {Sandslash}.', cid)
		npcHandler.topic[cid] = 1
	elseif msgcontains(msg, 'sandslash') and npcHandler.topic[cid] == 1 and Player(cid):getStorageValue(65020) < 1 then
		local player = Player(cid)
		local monsterType = MonsterType("sandslash")
		if monsterType then
			local balls = player:getPokeballs()
			for i=1, #balls do
				local ball = balls[i]
				local name = firstToUpper(ball:getSpecialAttribute("pokeName"))
				local teratype = ball:getSpecialAttribute("teraType") or 0
				if name == "Sandslash" then
					local isBallBeingUsed = ball:getSpecialAttribute("isBeingUsed")
					if isBallBeingUsed and isBallBeingUsed == 1 then
						selfSay('Sorry, not possible while using the Pokemon.', cid)
						return true
					end
					if ball:remove() then
						selfSay('O que? Os Sandslash daqui nao sao de gelo? Bom, uma promessa e uma promessa, aqui esta o Dugtrio.', cid)
						doAddPokeball(player:getId(), "Alolan Dugtrio", 1, 0, getBallKey(ball:getId()), false, 0, teratype)
						player:giveQuestPrize(65020)
						return true
					end
					return true
				end
			end
			selfSay('Voce nao trouxe um Sandslash pra mim, volte quando trouxer um.', cid)
			npcHandler:releaseFocus(cid)
		end
	else
		selfSay('Cuide bem do Dugtrio por mim!', cid)
		npcHandler:releaseFocus(cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
