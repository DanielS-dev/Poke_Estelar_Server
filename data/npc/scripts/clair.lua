local storage = 92015
local pokemons = 
{
	[1] = 
		{
			name = "Gyarados",
			level = 55
		},
	[2] = 
		{
			name = "Dragonair",
			level = 52
		},

	[3] = 
		{
			name = "Kingdra",
			level = 54
		},

	[4] = 
		{
			name = "Dragonite",
			level = 55
		},
	
	[5] = 
		{
			name = "Dragonite",
			level = 60
		}
}
local rebattle =
{
	[1] = 
		{
			name = "Kingdra",
			level = 100
		},
	[2] = 
		{
			name = "Dragonite",
			level = 100
		},

	[3] = 
		{
			name = "Altaria",
			level = 100
		},

	[4] = 
		{
			name = "Salamence",
			level = 100
		},
	
	[5] = 
		{
			name = "Druddigon",
			level = 100
		},
		
	[6] = 
		{
			name = "Garchomp",
			level = 100
		}
}

local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)

function onCreatureAppear(cid)              npcHandler:onCreatureAppear(cid)            end
function onCreatureDisappear(cid)           npcHandler:onCreatureDisappear(cid)         end
function onCreatureSay(cid, type, msg)      npcHandler:onCreatureSay(cid, type, msg)    end
function onThink()                          npcHandler:onThink()                        end

local function creatureGreetCallback(cid, message)
	if message == nil then
		return true
	end
	if npcHandler:hasFocus() then
		selfSay("Espere sua vez, " .. Player(cid):getName() .. "!")
		return false
	end
	return true
end

local function creatureSayCallback(cid, type, msg)
	if not npcHandler:isFocused(cid) then
		return false
	end	
	if msgcontains(msg, 'bye') or msgcontains(msg, 'no') or msgcontains(msg, 'nao') then
		selfSay('Volte quando estiver pronto!', cid)
		npcHandler:releaseFocus(cid)
	elseif (msgcontains(msg, 'yes') or msgcontains(msg, 'sim')) and not Player(cid):getParty() then
		local player = Player(cid)
		if player then
			if player:getStorageValue(storage) <= 0 or player:getStorageValue(65041) <= 0 then
				selfSay('Te derrotarei com todos meus pokemons!', cid)
				npcHandler.topic[cid] = 1
				npcHandler:setMaxIdleTime(600)
				player:setDuelWithNpc()	
			elseif player:getStorageValue(storage) >= 1 and player:getStorageValue(65041) >= 1 then
				selfSay('Voce ja me derrotou esta semana, volte semana que vem que estarei preparado!', cid)
				npcHandler:releaseFocus(cid)
			else
				selfSay('Voce ja me derrotou!', cid)
				npcHandler:releaseFocus(cid)
			end
		end
	elseif Player(cid):getParty() then
		selfSay('Saia do grupo para me enfrentar!', cid)
		npcHandler:releaseFocus(cid)
	end
	return true
end

local function creatureOnReleaseFocusCallback(cid)
	local npc = Npc()
	if hasSummons(npc) then
		local monster = npc:getSummons()[1]
		monster:getPosition():sendMagicEffect(balls.pokeball.effectRelease)
		monster:remove()
	end
	local player = Player(cid)
	if player then
		player:unsetDuelWithNpc()
	end
	return true
end

local function creatureOnDisapearCallback(cid)
	local player = Player(cid)
	if not player then
		npcHandler:updateFocus()
		return true
	end
	if npcHandler:isFocused(cid) then
		if getDistanceTo(cid) >= 0 and getDistanceTo(cid) <= 8 then
			return false
		end
		selfSay("Mais sorte na proxima tentativa, " .. player:getName() .. "!", cid)
		npcHandler:releaseFocus(cid)
	end
	return true
end

local function creatureOnThinkCallback()
	if npcHandler:hasFocus() then
		local npc = Npc()
		local npcPosition = npc:getPosition()
		local spectators = Game.getSpectators(npcPosition, false, true)
		for i = 1, #spectators do
			local player = spectators[i]
			local cid = player:getId()
			if npcHandler:isFocused(cid) and npcHandler.topic[cid] == 1 then
				local duelStatus = player:getDuelWithNpcStatus()
				local monster = npc:getSummons()[1]
				if not monster then
					if player:getStorageValue(storage) <= 0 and player:getStorageValue(65041) <= 0 then
						if pokemons[duelStatus] then
							selfSay(pokemons[duelStatus].name .. ", eu escolho voce!")
							npcPosition:getNextPosition(npc:getDirection())
							monster = Game.createMonster(pokemons[duelStatus].name, npcPosition, false, true, pokemons[duelStatus].level, 0)
							npcPosition:sendMagicEffect(balls.pokeball.effectRelease)
							monster:setMaster(npc)
							local health = monster:getTotalHealth() * 3
							monster:setMaxHealth(health)
							monster:setHealth(health)
							monster:changeSpeed(-monster:getSpeed() + monster:getTotalSpeed())
							player:increaseDuelWithNpcStatus()
						else
							selfSay('Incrivel, ' .. player:getName() .. "! Voce e muito habilidoso na batalha pokemon, acredito que um dia podera ser o campeao da liga. Estarei aqui para batalhar novamente toda semana!", cid)
							player:giveQuestPrize(storage)
							player:giveQuestPrize(65041)
							npcHandler:releaseFocus(cid)
						end
					elseif player:getStorageValue(storage) >= 1 then
						if rebattle[duelStatus] then
							selfSay(rebattle[duelStatus].name .. ", eu escolho voce!")
							npcPosition:getNextPosition(npc:getDirection())
							monster = Game.createMonster(rebattle[duelStatus].name, npcPosition, false, true, rebattle[duelStatus].level, 0)
							npcPosition:sendMagicEffect(balls.pokeball.effectRelease)
							monster:setMaster(npc)
							local health = monster:getTotalHealth() * 10
							monster:setMaxHealth(health)
							monster:setHealth(health)
							monster:changeSpeed(-monster:getSpeed() + monster:getTotalSpeed())
							player:increaseDuelWithNpcStatus()
						else
							selfSay('Incrivel, ' .. player:getName() .. "! Voce continua forte como nunca, volte semana que vem para termos outro duelo.", cid)
							player:giveQuestPrize(65041)
							player:addItem('pokepark ticket', 1)
							npcHandler:releaseFocus(cid)
						end
					end
				end
				if hasSummons(player) and hasSummons(npc) then
					monster:selectTarget(player:getSummons()[1])
				end
				local pokeballs = player:getPokeballs()
				local pokemonsAlive = 0
				for i=1, #pokeballs do
					local ball = pokeballs[i]					
					if ball:getSpecialAttribute("pokeHealth") > 0 then
						pokemonsAlive = pokemonsAlive + 1
					end
				end
				if pokemonsAlive == 0 then
					selfSay("Mais sorte na proxima tentativa, " .. player:getName() .. "!", cid)
					npcHandler:releaseFocus(cid)				
				end
			end
		end

	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:setCallback(CALLBACK_ONTHINK, creatureOnThinkCallback)
npcHandler:setCallback(CALLBACK_ONRELEASEFOCUS, creatureOnReleaseFocusCallback)
npcHandler:setCallback(CALLBACK_CREATURE_DISAPPEAR, creatureOnDisapearCallback)
npcHandler:setCallback(CALLBACK_GREET, creatureGreetCallback)
npcHandler:addModule(FocusModule:new())
