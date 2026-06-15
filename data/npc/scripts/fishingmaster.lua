local varas = {}

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
	local numbervara
	if Player(cid):getStorageValue(64001) <= 0 and Player(cid):getStorageValue(64002) <= 0 and Player(cid):getStorageValue(64003) <= 0 then numbervara = 1 end
	if Player(cid):getStorageValue(64001) >= 1 and Player(cid):getStorageValue(64002) <= 0 and Player(cid):getStorageValue(64003) <= 0 then numbervara = 2 end
	if Player(cid):getStorageValue(64001) >= 1 and Player(cid):getStorageValue(64002) >= 1 and Player(cid):getStorageValue(64003) <= 0 then numbervara = 3 end
	if Player(cid):getStorageValue(64001) >= 1 and Player(cid):getStorageValue(64002) >= 1 and Player(cid):getStorageValue(64003) >= 1 then numbervara = 4 end
	if msgcontains(msg, 'bye') or msgcontains(msg, 'no') or msgcontains(msg, 'nao') then
		selfSay('Talvez uma outra hora.', cid)
		npcHandler:releaseFocus(cid)
	elseif msgcontains(msg, 'vara') and numbervara == 1 then
		selfSay('Vejo que voce so possui a Old Rod, gostaria de liberar a proxima vara?', cid)
	elseif msgcontains(msg, 'yes') and numbervara == 1 then
		selfSay('Bom, vou precisar que voce tenha o {registro} e {captura} do Magikarp e nivel 20 de pesca!', cid)
		npcHandler.topic[cid] = 1
	elseif (msgcontains(msg, 'registro') or msgcontains(msg, 'captura')) and numbervara == 1 and npcHandler.topic[cid] == 1 then
		local catch = Player(cid):getStorageValue(180564129)
		local dex = Player(cid):getStorageValue(180567129)
		local lv = Player(cid):getSkillLevel(SKILL_FISHING)
		if catch >= 1 and dex >= 0 and lv >= 20 then
			selfSay('Perfeito! Voce realmente e um bom pescador, aqui esta a Great Rod!', cid)
			Player(cid):setStorageValue(64001, 1)
			npcHandler:releaseFocus(cid)
		else		
			selfSay('Voce nao fez o que pedi.', cid)
		end
	elseif msgcontains(msg, 'vara') and numbervara == 2 then
		selfSay('Vejo que voce possui a old rod e a great rod, gostaria de liberar a proxima vara?', cid)
	elseif msgcontains(msg, 'yes') and numbervara == 2 then
		selfSay('Bom, vou precisar que voce tenha o {registro} e {captura} dos pokemons: Totodile, Squirtle e Oshawott e nivel 50 de pesca!', cid)
		npcHandler.topic[cid] = 1
	elseif (msgcontains(msg, 'registro') or msgcontains(msg, 'captura')) and numbervara == 2 and npcHandler.topic[cid] == 1 then
		local dex = {7, 158, 501}
		local lv = Player(cid):getSkillLevel(SKILL_FISHING)
		for i = 1, #dex do
			if Player(cid):getStorageValue(180564000 + dex[i]) <= 0 then
				selfSay('Voce nao tem a captura de um dos pokemons!', cid)
				npcHandler:releaseFocus(cid)
				return false
			end
			if Player(cid):getStorageValue(180567000 + dex[i]) < 0 then
				selfSay('Voce nao tem o registro de um dos pokemons!', cid)
				npcHandler:releaseFocus(cid)
				return false
			end
		end
		if lv < 50 then
			selfSay('Voce nao tem o nivel de pesca necessario que pedi!', cid)
			npcHandler:releaseFocus(cid)
			return false
		end
		selfSay('Perfeito! Voce realmente e um bom pescador, aqui esta a Super Rod!', cid)
		Player(cid):setStorageValue(64002, 1)
		npcHandler:releaseFocus(cid)
	elseif msgcontains(msg, 'vara') and numbervara == 3 then
		selfSay('Vejo que voce possui a old rod, great rod e a super rod, gostaria de liberar a ultima vara?', cid)
	elseif msgcontains(msg, 'yes') and numbervara == 3 then
		selfSay('Bom, vou precisar que voce tenha o {registro} e {captura} dos pokemons: Tentacruel, Omanyte e Kabuto e nivel 75 de pesca!', cid)
		npcHandler.topic[cid] = 1
	elseif (msgcontains(msg, 'registro') or msgcontains(msg, 'captura')) and numbervara == 3 and npcHandler.topic[cid] == 1 then
		local dex = {73, 138, 140}
		local lv = Player(cid):getSkillLevel(SKILL_FISHING)
		for i = 1, #dex do
			if Player(cid):getStorageValue(180564000 + dex[i]) <= 0 then
				selfSay('Voce nao tem a captura de um dos pokemons!', cid)
				npcHandler:releaseFocus(cid)
				return false
			end
			if Player(cid):getStorageValue(180567000 + dex[i]) < 0 then
				selfSay('Voce nao tem o registro de um dos pokemons!', cid)
				npcHandler:releaseFocus(cid)
				return false
			end
		end
		if lv < 75 then
			selfSay('Voce nao tem o nivel de pesca necessario que pedi!', cid)
			npcHandler:releaseFocus(cid)
			return false
		end
		selfSay('Perfeito! Voce realmente e um bom pescador, aqui esta a Ultra Rod!', cid)
		Player(cid):setStorageValue(64003, 1)
		npcHandler:releaseFocus(cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())