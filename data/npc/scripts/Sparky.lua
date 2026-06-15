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
	elseif msgcontains(msg, 'descobertas') and Player(cid):getStorageValue(65023) < 1 then
		selfSay('Voce sabia que o golem de alola e de uma tipagem diferente do golem que temos aqui?', cid)
	elseif msgcontains(msg, 'yes') and Player(cid):getStorageValue(65023) < 1 then
		selfSay('Bom, ja que voce sabe sobre o golem de alola, deve saber sobre os outros pokemons de alola. Voce topa um {quiz} valendo um Golem de Alola?', cid)
	elseif msgcontains(msg, 'quiz') and Player(cid):getStorageValue(65023) < 1 then
		selfSay('Qual pokemon de Kanto que teve sua tipagem transformada para planta/dragao em Alola?', cid)
	elseif msgcontains(msg, 'Exeggutor') and Player(cid):getStorageValue(65023) < 1 then
		selfSay('Correto! Qual habilidade faz com que o Alola Marowak seja imune a dano eletrico?', cid)
	elseif msgcontains(msg, 'Lightning Rod') and Player(cid):getStorageValue(65023) < 1 then
		selfSay('Correto! Qual ave lendaria de Kanto teve sua tipagem transformada para psiquico/voador em Alola?', cid)
		npcHandler.topic[cid] = 1
	elseif (msgcontains(msg, 'nenhum') or msgcontains(msg, 'nenhuma')) and npcHandler.topic[cid] == 1 and Player(cid):getStorageValue(65023) < 1 then
		selfSay('Correto! Wow, voce realmente sabe tudo sobre Alola. Aqui esta seu Alola Golem!!', cid)
		Player(cid):giveQuestPrize(65023)
		npcHandler:releaseFocus(cid)
	elseif npcHandler.topic[cid] == 1 and Player(cid):getStorageValue(65023) < 1 then
		selfSay('Incorreto, tente de novo!', cid)
		npcHandler:releaseFocus(cid)
	elseif Player(cid):getStorageValue(65023) >= 1 then
		selfSay('Cuide bem do Golem por mim!', cid)
		npcHandler:releaseFocus(cid)
	else
		selfSay('Nao entendi, pode repetir?', cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
