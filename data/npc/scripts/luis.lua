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
	elseif msgcontains(msg, 'muk') and Player(cid):getStorageValue(65024) < 1 then
		selfSay('Pois e, ela fica reclamando o tempo inteiro sobre como ela nao gosta dele, como ele fede, etc... Mas ela nao entende o quao {forte} ele realmente e.', cid)
	elseif msgcontains(msg, 'Forte') and Player(cid):getStorageValue(65024) < 1 then
		selfSay('Pois e, mas ela insiste que quer um pokemon {fada} agora, nem sei o que fazer com esse Muk.', cid)
	elseif msgcontains(msg, 'fada') and Player(cid):getStorageValue(65024) < 1 then
		selfSay('Voce realmente trocaria um pokemon fada pelo Muk?', cid)
	elseif msgcontains(msg, 'yes') and Player(cid):getStorageValue(65024) < 1 then
		selfSay('Qual pokemon voce gostaria de me entregar?', cid)
		npcHandler.topic[cid] = 1
	elseif msg and npcHandler.topic[cid] == 1 and Player(cid):getStorageValue(65024) < 1 then
		local player = Player(cid)
		local monsterType = MonsterType(msg:lower())
		if monsterType and (monsterType:getRaceName() == "fairy" or monsterType:getRace2Name() == "fairy") then
			local balls = player:getPokeballs()
			for i=1, #balls do
				local ball = balls[i]
				local name = firstToUpper(ball:getSpecialAttribute("pokeName"))
				local teratype = ball:getSpecialAttribute("teraType") or 0
				if name == msg then
					local isBallBeingUsed = ball:getSpecialAttribute("isBeingUsed")
					if isBallBeingUsed and isBallBeingUsed == 1 then
						selfSay('Sorry, not possible while using the Pokemon.', cid)
						return true
					end
					if ball:remove() then
						selfSay('Obrigado, cuide bem do Muk, acredito que seja importante um pokemon ser amado!', cid)
						doAddPokeball(player:getId(), "Alolan Muk", 1, 0, getBallKey(ball:getId()), false, 0, teratype)
						player:giveQuestPrize(65024)
						return true
					end
					return true
				end
			end
			selfSay('Voce nao trouxe um pokemon fada pra mim, volte quando trouxer um.', cid)
			npcHandler:releaseFocus(cid)
		end
	else
		selfSay('Cuide bem do Muk por mim!', cid)
		npcHandler:releaseFocus(cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
