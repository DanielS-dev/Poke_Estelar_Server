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
	elseif msgcontains(msg, 'raticate') and Player(cid):getStorageValue(65019) < 1 then
		selfSay('O que, voce esta interessado nesse Raticate?', cid)
	elseif msgcontains(msg, 'yes') and Player(cid):getStorageValue(65019) < 1 then
		selfSay('Bom, eu ia usar ele para iniciar minha jornada pokemon, se voce quiser eu troco ele por um {Gloom}, assim posso pescar.', cid)
		npcHandler.topic[cid] = 1
	elseif msgcontains(msg, 'gloom') and npcHandler.topic[cid] == 1 and Player(cid):getStorageValue(65019) < 1 then
		local player = Player(cid)
		local monsterType = MonsterType("gloom")
		if monsterType then
			local balls = player:getPokeballs()
			for i=1, #balls do
				local ball = balls[i]
				local name = firstToUpper(ball:getSpecialAttribute("pokeName"))
				local teratype = ball:getSpecialAttribute("teraType") or 0
				if name == "Gloom" then
					local isBallBeingUsed = ball:getSpecialAttribute("isBeingUsed")
					if isBallBeingUsed and isBallBeingUsed == 1 then
						selfSay('Sorry, not possible while using the Pokemon.', cid)
						return true
					end
					if ball:remove() then
						selfSay('Obrigado, cuide bem do Raticate, acredito que seja importante um pokemon ser amado!', cid)
						doAddPokeball(player:getId(), "Alolan Raticate", 1, 0, getBallKey(ball:getId()), false, 0, teratype)
						player:giveQuestPrize(65019)
						return true
					end
					return true
				end
			end
			selfSay('Voce nao trouxe um Gloom pra mim, volte quando trouxer um.', cid)
			npcHandler:releaseFocus(cid)
		end
	elseif Player(cid):getStorageValue(65019) >= 1 then
		selfSay('Cuide bem do Raticate por mim!', cid)
		npcHandler:releaseFocus(cid)
	else
		selfSay('Nao entendi, pode repetir?', cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
