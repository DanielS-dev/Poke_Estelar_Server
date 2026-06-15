local storage = 65026
local pokemons = 
{
	[1] = 
		{
			name = "Charizard",
			level = 70
		},
	[2] = 
		{
			name = "Blastoise",
			level = 70
		},

	[3] = 
		{
			name = "Venusaur",
			level = 70
		},
	
	[4] = 
		{
			name = "Arcanine",
			level = 80
		},
	
	[5] = 
		{
			name = "Gyarados",
			level = 80
		},

	[6] = 
		{
			name = "Dragonite",
			level = 90
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
	elseif msgcontains(msg, 'yes') or msgcontains(msg, 'sim') then
		local player = Player(cid)
		if player then
			selfSay('...', cid)
			npcHandler.topic[cid] = 1
			npcHandler:setMaxIdleTime(600)
			player:setDuelWithNpc()
		end
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
					if pokemons[duelStatus] then
						selfSay(pokemons[duelStatus].name .. ", eu escolho voce!")
						npcPosition:getNextPosition(npc:getDirection())
						monster = Game.createMonster(pokemons[duelStatus].name, npcPosition, false, true, pokemons[duelStatus].level, 0)
						npcPosition:sendMagicEffect(balls.pokeball.effectRelease)
						monster:setMaster(npc)
						local health = monster:getTotalHealth() * 10
						monster:setMaxHealth(health)
						monster:setHealth(health)
						monster:changeSpeed(-monster:getSpeed() + monster:getTotalSpeed())
						player:increaseDuelWithNpcStatus()
					else
						selfSay("... Voce me surpreendeu ate, nao esperava que fosse derrotar todos os meus clones. Vamos ver como se sai contra meu pokemon mais forte.", cid)
						cleanArea(Position(Position(648, 413, 8), 4, 4))
						player:teleportTo(Position(646, 413, 8))
						Game.createMonster("Mewtwo", Position(651, 413, 8))
						npcHandler:releaseFocus(cid)
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
					selfSay("Voce e fraco.", cid)
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
