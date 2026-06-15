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
		selfSay('...', cid)
		npcHandler:releaseFocus(cid)
	elseif (msgcontains(msg, 'ajuda') or msgcontains(msg, 'help') or msgcontains(msg, 'mission')) and Player(cid):getStorageValue(65033) < 1 then
		selfSay('Sou apenas um {espirito} condenado a ficar aqui pelo resto da eternidade.', cid)
	elseif msgcontains(msg, 'espirito') and Player(cid):getStorageValue(65033) < 1 then
		selfSay('Meu barco afundou aqui faz muito tempo, hoje eu passo o tempo oferencendo {recompensas} a aventureiros experientes.', cid)
	elseif msgcontains(msg, 'recompensas') and Player(cid):getStorageValue(65033) < 1 then
		selfSay('Dou recompensas a jogadores que possuem o registro de todos os pokemons raros que vem na pesca e possuem nivel de pesca 105, voce atende estes requisitos?', cid)
	elseif msgcontains(msg, 'yes') and Player(cid):getStorageValue(65033) < 1 then
		local dexneed = {"Greninja", "Primarina", "Crawdaunt", "Sharpedo", "Whiscash", "Relicanth", "Walrein", "Uxie", "Azelf", "Mesprit", "Kyogre", "Frogadier", "Brionne", "Gastrodon", "Gorebyss", "Huntail", "Floatzel", "Froakie", "Popplio", "Bibarel", "Lumineon", "Luvdisc", "Magikarp"}
		for i = 1, #dexneed do
			if Player(cid):getStorageValue(180567000 + MonsterType(dexneed[i]):dexEntry()) < 0 then
				selfSay('Voce nao tem todos os requisitos.', cid)
				npcHandler:releaseFocus(cid)
			end
		end
		if Player(cid):getSkillLevel(SKILL_FISHING) < 105 then
			selfSay('Voce nao tem todos os requisitos.', cid)
			npcHandler:releaseFocus(cid)
		end
		player:giveQuestPrize(65033)
		selfSay('Voce e realmente experiente, pegue este presente.', cid)
		npcHandler:releaseFocus(cid)
	else
		selfSay('...', cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())
