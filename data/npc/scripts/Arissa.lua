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
	elseif msgcontains(msg, 'ninetales') and Player(cid):getStorageValue(65018) < 1 then
		selfSay('O que? Voce nunca viu uma Ninetales de Alola? Elas sao lindas, elas sao brancas como a neve e tem a tipagem de gelo/fada. Nao me importaria em {trocar} uma com voce.', cid)
	elseif msgcontains(msg, 'trocar') and Player(cid):getStorageValue(65018) < 1 then
		selfSay('E claro que nao sem voce me provar antes que e um grande apreciador das Ninetales. Voce por acaso possui o {registro} e {captura} da Ninetales?', cid)
	elseif (msgcontains(msg, 'registro') or msgcontains(msg, 'captura')) and Player(cid):getStorageValue(65018) < 1 then
		if Player(cid):getStorageValue(180564038) >= 1 and Player(cid):getStorageValue(180567038) >= 0 then
			selfSay('Wow, voce realmente e um grande apreciador das Ninetales. Bom, estou disposta a trocar com voce, basta me trazer um {Arcanine} que trocaremos.', cid)
			npcHandler.topic[cid] = 1
		else
			selfSay('Parece que voce ainda nao e um grande apreciador das Ninetales, volte quando possuir o registro e a captura dela.', cid)
			npcHandler:releaseFocus(cid)
		end
	elseif msgcontains(msg, 'arcanine') and npcHandler.topic[cid] == 1 and Player(cid):getStorageValue(65018) < 1 then
		local player = Player(cid)
		local monsterType = MonsterType("arcanine")
		if monsterType then
			local balls = player:getPokeballs()
			for i=1, #balls do
				local ball = balls[i]
				local name = firstToUpper(ball:getSpecialAttribute("pokeName"))
				local teratype = ball:getSpecialAttribute("teraType") or 0
				if name == "Arcanine" then
					local isBallBeingUsed = ball:getSpecialAttribute("isBeingUsed")
					if isBallBeingUsed and isBallBeingUsed == 1 then
						selfSay('Sorry, not possible while using the Pokemon.', cid)
						return true
					end
					if ball:remove() then
						selfSay('Obrigada, sempre gostei muito do Arcanine, porem nunca fui forte o suficiente para tentar capturar um. Aproveite sua Ninetales!', cid)
						doAddPokeball(player:getId(), "Alolan Ninetales", 1, 0, getBallKey(ball:getId()), false, 0, teratype)
						player:giveQuestPrize(65018)
						return true
					end
					return true
				end
			end
			selfSay('Voce nao trouxe um Arcanine pra mim, volte quando trouxer um.', cid)
			npcHandler:releaseFocus(cid)
		end
	elseif Player(cid):getStorageValue(65018) >= 1 then
		selfSay('Cuide bem da Ninetales por mim!', cid)
		npcHandler:releaseFocus(cid)
	else
		selfSay('Nao entendi, pode repetir?', cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
