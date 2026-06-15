local pokemon
local price


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
	elseif msgcontains(msg, 'daycare') then
		selfSay('Bom, nos contratamos um treinador profissional para capturar todos os pokemons para nos, sendo assim, conseguimos produzir qualquer ovo de pokemon com nossos Dittos. Os nossos ovos sao especiais, os pokemons que chocam deles ja nascem em sua forma evoluida, ainda nao sabemos porque. Para produzir um ovo basta me dizer o {nome} do pokemon que voce deseja.', cid)
	elseif MonsterType(msg) and not isInArray({"ditto", "smeargle"}, msg:lower()) and not isInArray(legendaryPokemons, firstToUpper(msg)) and not string.find(msg, "Mega ") then
		pokemon = firstToUpper(msg)
		local monsterType = MonsterType(pokemon)
		price = math.abs(((monsterType:getHealth()/100) + (monsterType:getBaseSpeed() - 100) + monsterType:getMeleeDamage(self) + monsterType:getDefense() + monsterType:getMoveMagicAttackBase() + monsterType:getMoveMagicDefenseBase())* 12 - 1900)
		selfSay('Para produzir um ovo de '..msg..', ira custar: '..price..' gold coins cada, voce gostaria de prosseguir?', cid)
		npcHandler.topic[cid] = 1
	elseif npcHandler.topic[cid] == 1 and (msgcontains(msg, 'sim') or msgcontains(msg, 'yes')) then
		local player = Player(cid)
		if player:removeMoney(price) then
			local egg = player:addItem(36570, 1, false)
			egg:setSpecialAttribute("eggname", pokemon)
			egg:setSpecialAttribute("steps", 0)
		else
			selfSay('Voce nao possui dinheiro necessario!', cid)
			npcHandler.topic[cid] = 0
			npcHandler:releaseFocus(cid)
		end
	else
		selfSay('Desculpa, nao entendi.', cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())