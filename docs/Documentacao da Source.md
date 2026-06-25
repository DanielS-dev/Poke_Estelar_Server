# Documentação da Source

Este documento descreve a organização geral da source do servidor. O objetivo é servir como mapa rápido para entender onde cada responsabilidade vive, quais pastas existem e qual é a função principal dos arquivos mais importantes.

Esta documentação não substitui a leitura do código. Ela resume a ideia geral de cada módulo para facilitar manutenção, refatoração e entrada de novos desenvolvedores no projeto.

## Visão Geral

| Área | Pasta | Responsabilidade |
|---|---|---|
| Aplicação | `src/app` | Inicialização do servidor, serviços e sinais do sistema. |
| Configuração | `src/config` | Leitura e acesso às configurações do servidor. |
| Core | `src/core` | Tipos base, constantes, scheduler, tarefas e estruturas compartilhadas. |
| Core Tools | `src/core/tools` | Funções auxiliares separadas por domínio. |
| Entidades | `src/entities` | Players, creatures, monsters, NPCs, guilds, parties e vocations. |
| Gameplay | `src/game` | Sistemas principais de jogo, combate, spells, raids, movement e commands. |
| IO | `src/io` | Leitura de arquivos em baixo nível. |
| Items | `src/items` | Itens, containers, mailbox, depot e atributos de item. |
| Network | `src/network` | Conexões, protocolos e mensagens de rede. |
| Persistence | `src/persistence` | Banco de dados, carregamento e salvamento persistente. |
| Scripting | `src/scripting` | Integração Lua, eventos, actions e talkactions. |
| Security | `src/security` | Banimentos, RSA e regras de segurança. |
| World | `src/world` | Mapa, tiles, houses, spawns, teleports e estruturas do mundo. |

## Dependências Entre Módulos

Esta visão ajuda a planejar refatorações sem quebrar consumidores indiretos. As setas indicam dependências frequentes ou contratos públicos importantes.

```text
app -> config, core, game, network, persistence, scripting, security, world
game -> core, entities, items, network, persistence, scripting, world
entities -> core, game/condition, items, scripting, world
world -> core, entities, game, items, persistence
network -> core, entities, game, items, scripting, world
persistence -> core, entities, items, world
scripting -> core, entities, game, items, network, persistence, world
items -> core, world
security -> core, persistence
```

Regras práticas:

- `game` é o orquestrador central e costuma conhecer vários módulos.
- `scripting` expõe contratos C++ para Lua; mudanças em nomes, assinaturas ou metatables podem quebrar scripts.
- `network` traduz estado interno para pacotes do cliente 10.98; mudanças devem ser compatíveis com o protocolo.
- `persistence` serializa estruturas de `entities`, `items` e `world`; alterações de schema ou atributos exigem migração.
- `core` e `core/tools` devem continuar genéricos, sem depender de domínios altos como `game` ou `network`.

## Arquivos Críticos

Use a marcação `CRÍTICO` para arquivos de alto impacto. Alterações nesses pontos exigem leitura dos consumidores, atualização de CMake/Visual Studio quando houver arquivos novos, revisão da documentação e compilação/teste local.

Arquivos críticos conhecidos:

- `src/game/game.hpp` e `src/game/game/*.cpp`: contrato e implementação do orquestrador principal do jogo.
- `src/network/protocolgame.hpp` e `src/network/protocolgame/*.cpp`: contrato do cliente/protocolo 10.98.
- `src/scripting/lua/luascript.hpp` e `src/scripting/lua/registry/luaGlobalFunctionsRegistry.cpp`: API C++ exposta ao Lua.
- `src/persistence/database.cpp/.hpp` e `src/persistence/login/iologindata.hpp`: acesso a banco, login, load/save de jogador.
- `src/entities/player.hpp`, `src/entities/creature.hpp` e `src/entities/monster.hpp`: contratos públicos das entidades centrais.
- `src/world/map.hpp`, `src/world/tile.hpp` e `src/world/cylinder.hpp`: contratos de mapa, tiles e movimentação de things.

## Estrutura de Pastas

### `src/app`

Responsável pelo bootstrap da aplicação, inicialização do servidor, controle de serviços e tratamento de sinais.

- `otserv.cpp`: fluxo principal de inicialização do servidor.
- `serviceManager.cpp`: gerenciamento dos serviços registrados.
- `servicePort.cpp`: abertura e controle de portas de serviço.
- `services.hpp`: declarações e tipos ligados aos serviços.
- `signals.cpp/.hpp`: tratamento de sinais do sistema operacional.

### `src/config`

Responsável por carregar e disponibilizar configurações globais do servidor.

- `configmanager.cpp/.hpp`: leitura, armazenamento e consulta das configurações definidas no arquivo de configuração.

### `src/core`

Contém estruturas fundamentais usadas por várias áreas da source.

- `const.hpp`: constantes globais do servidor.
- `definitions.hpp`: definições gerais e configurações de compilação.
- `enums.hpp`: enumeradores compartilhados entre sistemas.
- `lockfree.hpp`: estruturas auxiliares para uso concorrente.
- `otpch.cpp/.hpp`: precompiled header usado pelo projeto.
- `position.cpp/.hpp`: representação e utilidades básicas de posição.
- `pugicast.hpp`: helpers para conversão de valores vindos de XML.
- `scheduler.cpp/.hpp`: agendamento de eventos futuros.
- `tasks.cpp/.hpp`: sistema de tarefas executadas pelo dispatcher.
- `thread_holder_base.hpp`: base para gerenciamento de threads.
- `waitlist.cpp/.hpp`: controle de fila de espera.
- `wildcardtree.cpp/.hpp`: estrutura auxiliar para busca por padrões.

### `src/core/tools`

Contém funções utilitárias divididas por responsabilidade. Novos helpers genéricos devem ser colocados aqui quando não pertencerem claramente a um domínio maior.

- `auths.cpp/.hpp`: funções de autenticação, SHA1 e token.
- `checksum.cpp/.hpp`: cálculo de checksum.
- `dateTools.cpp/.hpp`: formatação de datas.
- `fluidTools.cpp/.hpp`: conversão de fluidos entre servidor e cliente.
- `gameEnumTools.cpp/.hpp`: conversores de enums, nomes de combate, skills, weapons e atributos.
- `positionTools.cpp/.hpp`: helpers de direção e movimentação por posição.
- `random.cpp/.hpp`: geração de números aleatórios.
- `returnMessageTools.cpp/.hpp`: mensagens de retorno para códigos de erro do jogo.
- `stringsTools.cpp/.hpp`: helpers de strings, trim, lower/upper, split e conversões simples.
- `systemTools.hpp`: helpers inline de sistema, tempo e bits.
- `xmlErro.cpp/.hpp`: impressão detalhada de erros de XML.

### `src/entities`

Contém as entidades principais do servidor e seus comportamentos associados.

- `account.hpp`: estrutura de conta.
- `creature.hpp` [CRÍTICO]: contrato base para criaturas vivas; expõe identidade, posição, vida/mana, eventos, visão, movimento, combate e integração com `Tile`, `Game` e scripting.
- `creature/creature.cpp`: estado básico, visibilidade, skull e delays de caminhada.
- `creature/creatureThink.cpp`: ciclo de pensamento, ataque periódico e estado idle.
- `creature/creatureMovement.cpp`: caminhada, auto-walk, cache de mapa, duração de passos e luz.
- `creature/creatureEvents.cpp`: eventos de tile, movimentação, zona e registros de scripts.
- `creature/creatureDeath.cpp`: morte, corpse, experiência e histórico de ataques.
- `creature/creatureCombat.cpp`: vida, mana, dano, bloqueio de hits, follow/target e mapa de dano.
- `creature/creatureConditions.cpp`: condições, summons, imunidades, supressões e ticks de condição.
- `creature/creaturePathfinding.cpp`: busca de caminho, invisibilidade e `FrozenPathingConditionCall`.
- `groups.cpp/.hpp`: grupos de acesso e permissões.
- `guild.cpp/.hpp`: dados e regras de guild.
- `monster.hpp` [CRÍTICO]: contrato do comportamento individual de monstros; conecta AI, alvo, spawn, loot, spells, summons e regras herdadas de `Creature`.
- `monster/monster.cpp`: criação, construtor, lista global e visibilidade básica.
- `monster/monsterEvents.cpp`: eventos de criatura vistos pelo monstro.
- `monster/monsterTarget.cpp`: amigos, alvos, busca e seleção de target.
- `monster/monsterCombat.cpp`: bloqueio de dano e validação de alvos.
- `monster/monsterThink.cpp`: ciclo de think, ataques, defesa e yells.
- `monster/monsterMovement.cpp`: caminhada, push, dança, fuga e distância.
- `monster/monsterLifecycle.cpp`: morte, corpse, loot, convince/challenge e path params.
- `monsters.hpp`: contrato do catálogo global de monstros; expõe carregamento, busca e registro de `MonsterType`, loot, spells, flags e atributos usados por game, Lua e spawn.
- `monsters/monsters.cpp`: manager `Monsters`, carregamento principal, reload e busca de tipo.
- `monsters/monsterTypeLoader.cpp`: leitura do XML de cada `MonsterType`.
- `monsters/monsterSpellLoader.cpp`: parsing de spells, ataques, defesas e condições.
- `monsters/monsterTypeLoot.cpp`: criação de loot em runtime.
- `monsters/monsterLootLoader.cpp`: parsing de loot no XML.
- `mounts.cpp/.hpp`: carregamento e controle de mounts.
- `npc.hpp`: contrato público de NPCs; expõe foco, fala, shop, scripts Lua, handlers de eventos e integração com `Game` e `Creature`.
- `npc/npc.cpp`: núcleo do NPC, criação, reload, fala e estado básico.
- `npc/npcLoader.cpp`: carregamento XML de NPC.
- `npc/npcEvents.cpp`: eventos de criatura e think recebidos pelo NPC.
- `npc/npcMovement.cpp`: caminhada, foco e movimentação do NPC.
- `npc/npcShop.cpp`: trade, callbacks e janelas de shop.
- `npc/npcScriptInterface.cpp`: inicialização da interface Lua de NPC.
- `npc/npcLuaActions.cpp`: bindings Lua básicos de ação do NPC.
- `npc/npcLuaShop.cpp`: bindings Lua de shop e metatable `Npc`.
- `npc/npcEventsHandler.cpp`: execução dos callbacks de evento do script do NPC.
- `outfit.cpp/.hpp`: outfits disponíveis.
- `party.hpp`: contrato do sistema de party; expõe liderança, membros, convites, shared experience, mensagens e regras de corpse/loot.
- `party/party.cpp`: criação, disband e saída de membros.
- `party/partyMembership.cpp`: troca de liderança e entrada de jogadores.
- `party/partyInvitations.cpp`: convites, revogação e remoção de invites.
- `party/partyMessaging.cpp`: ícones, mensagens e loot broadcast da party.
- `party/partySharedExperience.cpp`: experiência compartilhada, vocations e ticks de participação.
- `party/partyCorpse.cpp`: regra de acesso ao corpse pelo grupo.
- `player.hpp` [CRÍTICO]: contrato público do jogador; concentra sessão, inventário, storage, skills, guild, party, combat, movement, containers, protocol e eventos Lua.
- `player/player.cpp`: construção, destruição, descrição e dados básicos do jogador.
- `player/playerStats.cpp`: vocation, skills, atributos, inventário equipado e cálculo de defesa/ataque.
- `player/playerContainers.cpp`: containers abertos, envio de itens de container e eventos de container.
- `player/playerStorageDepot.cpp`: storage, depot, depot locker, mail e corpse lookup.
- `player/playerVisibility.cpp`: visibilidade, ghost mode e walkthrough.
- `player/playerMessaging.cpp`: mensagens, ping, modal windows, canais privados e mute conditions.
- `player/playerEvents.cpp`: eventos de tile, criatura, zona e remoção/aparição.
- `player/playerShop.cpp`: shop, trade state e lista de venda.
- `player/playerMovement.cpp`: caminhada, tarefas de movimento, follow/chase, path params e luz.
- `player/playerThink.cpp`: ciclo de think, mute e message buffer.
- `player/playerProgression.cpp`: experiência, level, treino offline e janelas modais.
- `player/playerDeath.cpp`: morte, perda de experiência, blessings e corpse.
- `player/playerCombat.cpp`: vida, mana, bloqueio de dano, condições, imunidades e eventos de combate.
- `player/playerInventory.cpp`: regras de `Cylinder`, capacidade, query de itens, contagem e dinheiro.
- `player/playerSession.cpp`: IP, entrada/saída da lista, kick, logout e outfits.
- `player/playerSocial.cpp`: VIP, guild, party, skull, war, mounts e limites sociais.
- `vocation.cpp/.hpp`: vocations e suas configurações.

### `src/game`

Contém os sistemas centrais de gameplay.

- `chat/chat.cpp/.hpp`: fachada e orquestração do sistema de chat.
- `chat/chatChannel.cpp/.hpp`: canais de chat, usuários, convites, eventos Lua e envio de mensagens.
- `chat/chatLoader.cpp/.hpp`: carregamento dos canais via XML e scripts.
- `chat/chatRules.cpp/.hpp`: regras de fala e normalização do tipo de mensagem por canal.
- `combat/combat.cpp/.hpp`: fachada e contrato do combate; define parâmetros, áreas, callbacks Lua, dano, mana, condições e execução contra criaturas/tiles.
- `combat/combatExecution.cpp`: execução de dano, mana, condições, dispel e efeitos em tiles.
- `combat/combatCallbacks.cpp/.hpp`: callbacks Lua de valor, tile e alvo.
- `combat/combatTypes.hpp`: parâmetros e tipos compartilhados do combate.
- `combat/areaCombat.cpp/.hpp`: áreas de combate e seleção de tiles.
- `combat/matrixArea.hpp`: matriz usada para montar áreas de combate.
- `combat/magicField.cpp/.hpp`: comportamento de magic fields ao pisar.
- `commands/command.cpp/.hpp`: representação de um comando individual.
- `commands/commandLoader.cpp/.hpp`: carregamento dos comandos via XML.
- `commands/commandRules.cpp/.hpp`: validação de permissão e log de execução dos comandos.
- `commands/commands.cpp/.hpp`: fachada dos comandos administrativos ou de servidor; expõe carregamento, permissões e dispatch de comandos.
- `condition/condition.cpp/.hpp`: contrato de conditions; expõe factory, serialização, ticks, atributos, dano periódico, velocidade, visual e cooldown.
- `condition/conditionAttributes.cpp`: modifiers de skills/stats e atributos temporários.
- `condition/conditionRegeneration.cpp`: regeneração de vida, mana e soul.
- `condition/conditionDamage.cpp`: condições de dano periódico e damage list.
- `condition/conditionSpeed.cpp`: haste, paralyze, sleep/silence e fórmula de speed.
- `condition/conditionVisual.cpp`: invisibilidade, outfit e light.
- `condition/conditionCooldown.cpp`: cooldown de spell, grupo e status simples.
- `game.hpp` [CRÍTICO]: contrato público do orquestrador do jogo; expõe operações de criaturas, players, itens, mapa, combate, chat, market, raids, world state e integração com quase todos os módulos.
- `game/game.cpp` [CRÍTICO]: construção, inicialização e agendamento base do jogo.
- `game/gameState.cpp`: estado do servidor, world type, save state, shutdown e cleanup.
- `game/gameMap.cpp`: carregamento de mapa, busca de cylinder/thing e posição interna.
- `game/gameLookup.cpp`: busca de criaturas, monstros, NPCs e jogadores por ID, nome, GUID e conta.
- `game/gameCreature.cpp`: criação, posicionamento, remoção e release de criaturas.
- `game/gameMovement.cpp` [CRÍTICO]: movimentação de criaturas e players no mapa; depende de `Map`, `Tile`, `Cylinder`, `Creature`, `Player` e eventos.
- `game/gameItems.cpp` [CRÍTICO]: movimentação, adição, remoção, transformação, teleport e dinheiro de itens; altera estado compartilhado de mapa/inventário.
- `game/gamePlayerActions.cpp`: ações gerais do jogador, ping, auto-walk, outfit, quest e mount.
- `game/gamePlayerChannels.cpp`: canais, private channel e comunicação de chat por canal.
- `game/gamePlayerItemActions.cpp`: uso de itens, containers, escrita, browse field e house window.
- `game/gamePlayerTrade.cpp`: trade entre jogadores e mensagens de erro de trade.
- `game/gamePlayerShop.cpp`: compra, venda, fechamento e consulta de shop.
- `game/gamePlayerLook.cpp`: look em tile, item, criatura e battle list.
- `game/gamePlayerCombat.cpp`: attack, follow, fight modes e cancelamento de combate.
- `game/gamePlayerVip.cpp`: adição, remoção e edição de VIP.
- `game/gamePlayerChat.cpp`: fala, comandos, spells, whisper, yell e NPC talk.
- `game/gameCreatureRuntime.cpp`: visão, fala interna, checks de criatura, velocidade, outfit e visibilidade.
- `game/gameCombat.cpp` [CRÍTICO]: bloqueio de hit, dano, mana, efeitos de combate e callbacks; impacta entidades, conditions, scripts e feedback visual.
- `game/gameEffects.cpp`: health update, magic effect e distance effect.
- `game/gameDecay.cpp`: decay de itens e buckets de decay.
- `game/gameLight.cpp`: luz global e atualização de ciclo dia/noite.
- `game/gameWorld.cpp`: broadcast, MOTD, records, premium, experience stages e atualizações visuais.
- `game/gameParty.cpp`: convites, entrada, liderança, saída e shared experience de party.
- `game/gameReports.cpp`: guild MOTD, kick, bug report e debug assert.
- `game/gameMarket.cpp`: market, ofertas, histórico, aceite/cancelamento e lista de itens.
- `game/gameModalCondition.cpp`: condições forçadas, treino offline e modal windows.
- `game/gameRegistry.cpp`: registro de players, NPCs, monstros, guilds, beds e unique items.
- `movement/movement.cpp/.hpp`: fachada e registro dos eventos de movement.
- `movement/movementEvent.cpp/.hpp`: evento individual de movement, ciclo de vida e dados de equip.
- `movement/movementEventConfig.cpp`: configuração XML, nome de evento Lua e resolução de funções nativas.
- `movement/movementEventHandlers.cpp`: callbacks nativos de field, equip e deequip.
- `movement/movementEventScript.cpp`: disparo e execução dos callbacks Lua.
- `movement/movementTypes.hpp`: enums e aliases compartilhados pelo módulo de movement.
- `quests/quest.cpp/.hpp`: entidade de quest, progresso geral e contagem de missões.
- `quests/questLoader.cpp/.hpp`: carregamento das quests e missões a partir do XML.
- `quests/questMission.cpp/.hpp`: entidade de missão, estado, descrição e conclusão.
- `quests/quests.cpp/.hpp`: fachada e coleção de quests disponíveis.
- `raids/raid.cpp/.hpp`: entidade de raid, fila de eventos e execução sequencial.
- `raids/raidEvent.cpp/.hpp`: eventos de raid, anúncios, spawns e scripts.
- `raids/raidLoader.cpp/.hpp`: carregamento das raids a partir dos XMLs.
- `raids/raids.cpp/.hpp`: fachada, agendamento e coleção de raids.
- `spells/spells.cpp/.hpp`: contrato do sistema de spells; expõe registro, lookup, carregamento XML, instant spells, rune spells e integração com Lua/combat.
- `spells/spell.cpp/.hpp`: base comum, custos e efeitos auxiliares.
- `spells/spellConfig.cpp`: configuração XML da base comum de spell.
- `spells/spellChecks.cpp`: validações comuns de cast, instant spell e rune spell.
- `spells/combatSpell.cpp/.hpp`: spell baseada em combate e execução Lua de combate.
- `spells/instantSpell.cpp/.hpp`: instant spells, fala, parâmetros e execução Lua.
- `spells/instantSpellHandlers.cpp`: funções nativas de instant spell, como house, exiva, summon, levitate e illusion.
- `spells/conjureSpell.cpp/.hpp`: spells de conjuração de itens.
- `spells/runeSpell.cpp/.hpp`: runes, uso por item e callbacks nativos.
- `weapons/weapon.cpp/.hpp`: base comum de armas, validações, consumo e execução de scripts.
- `weapons/weaponDistance.cpp/.hpp`: armas à distância, munições, chance de acerto e dano.
- `weapons/weaponMelee.cpp/.hpp`: armas corpo a corpo, skill e dano elemental.
- `weapons/weaponWand.cpp/.hpp`: wands/rods e dano mágico configurado por XML.
- `weapons/weapons.cpp/.hpp`: contrato do sistema de armas; expõe registro, carregamento XML, validações de uso e execução via combat/scripts.

### `src/io`

Contém componentes de leitura de arquivos usados por outras áreas.

- `fileloader.cpp/.hpp`: carregamento de arquivos em formato próprio do servidor.

### `src/items`

Contém o sistema de itens e containers.

- `container.cpp/.hpp`: comportamento base de containers.
- `depotchest.cpp/.hpp`: depot chest e regras de limite.
- `depotlocker.cpp/.hpp`: locker de depot.
- `inbox.cpp/.hpp`: inbox do jogador.
- `item.cpp/.hpp`: comportamento principal de um item.
- `itemloader.hpp`: estruturas auxiliares para carregar itens.
- `items.cpp/.hpp`: registro, carregamento e configuração de tipos de itens.
- `mailbox.cpp/.hpp`: mailbox e envio de correspondências.
- `trashholder.cpp/.hpp`: lixeira e descarte de itens.

### `src/network`

Contém conexões, protocolos e mensagens trocadas entre cliente e servidor.

- `connection.cpp/.hpp`: conexão de rede e controle de pacotes.
- `networkmessage.cpp/.hpp`: leitura e escrita de mensagens de rede.
- `outputmessage.cpp/.hpp`: mensagens de saída.
- `protocol.cpp/.hpp`: contrato base dos protocolos; controla ciclo de conexão, mensagens, timeout e hooks comuns.
- `protocolgame.hpp` [CRÍTICO]: contrato do protocolo principal de gameplay para cliente 10.98; expõe parse/send, estado da sessão, mapa conhecido, containers, shop, trade e callbacks de jogo.
- `protocolgame/protocolgame.cpp` [CRÍTICO]: lifecycle, login, conexão e dispatcher de pacotes.
- `protocolgame/protocolgameMap.cpp` [CRÍTICO]: descrição de mapa, visibilidade e criaturas conhecidas.
- `protocolgame/protocolgameParse.cpp` [CRÍTICO]: parsers dos pacotes recebidos do cliente 10.98.
- `protocolgame/protocolgameSend.cpp` [CRÍTICO]: envios gerais, chat, status e canais.
- `protocolgame/protocolgameShopMarket.cpp`: shop, market e detalhes de ofertas.
- `protocolgame/protocolgameQuestTrade.cpp`: quest log, quest line e trade.
- `protocolgame/protocolgameWorld.cpp`: containers, inventário, tiles, world state e movement visual.
- `protocolgame/protocolgameHelpers.cpp`: helpers de serialização para criaturas, stats, outfit, luz e shop item.
- `protocollogin.cpp/.hpp` [CRÍTICO]: protocolo de login; depende de autenticação, banco, conta/personagens e compatibilidade com cliente.
- `protocolold.cpp/.hpp`: suporte a protocolo antigo.
- `protocolstatus.cpp/.hpp`: protocolo de status do servidor.

### `src/persistence`

Contém acesso ao banco de dados e carregamento/salvamento persistente.

- `database.cpp/.hpp` [CRÍTICO]: contrato de conexão e execução de queries; impacta login, saves, market, guilds e tarefas assíncronas.
- `databasemanager.cpp/.hpp`: gerenciamento de schema e tarefas administrativas de banco.
- `databasetasks.cpp/.hpp` [CRÍTICO]: execução assíncrona de tarefas de banco; mudanças podem afetar ordem, concorrência e lifetime de queries.
- `ioguild.cpp/.hpp`: persistência de guilds.
- `login/iologindata.hpp` [CRÍTICO]: contrato de login/load/save de contas e jogadores; expõe autenticação, preload, inventário, storage, premium, VIP e persistência de player.
- `login/loginDataAccount.cpp`: persistência de contas e tipo de conta.
- `login/loginDataAuthentication.cpp`: autenticação do login server e gameworld.
- `login/loginDataPlayerLoad.cpp` [CRÍTICO]: carregamento e preload dos dados do jogador.
- `login/loginDataItems.cpp` [CRÍTICO]: serialização e desserialização de itens do jogador.
- `login/loginDataPlayerSave.cpp` [CRÍTICO]: salvamento completo do jogador.
- `login/loginDataPlayerQueries.cpp`: consultas auxiliares de jogador, guid, nome, banco e house bid.
- `login/loginDataVip.cpp`: persistência da VIP list.
- `login/loginDataPremium.cpp`: ajustes de dias premium.
- `map/iomap.hpp`: contrato do carregamento de mapa OTBM; expõe leitura de tiles, towns, waypoints e atributos persistentes do mapa.
- `map/iomap.cpp`: carregamento do mapa, tiles, towns e waypoints.
- `map/iomapserialize.hpp` [CRÍTICO]: contrato da serialização persistente de mapa e houses; impacta itens de houses, containers e atributos salvos.
- `map/mapHouseItems.cpp`: carregamento e salvamento dos itens de houses.
- `map/mapItemSerialization.cpp` [CRÍTICO]: helpers para serializar/deserializar itens, containers e tiles.
- `map/mapHouseInfo.cpp`: carregamento e salvamento de informações e listas das houses.
- `map/otbmTypes.hpp`: enums e structs do formato OTBM.
- `market/iomarket.hpp`: fachada da persistência do market.
- `market/marketOffers.cpp`: consultas, criação, aceite e remoção de ofertas.
- `market/marketHistory.cpp`: histórico e movimentação de ofertas para histórico.
- `market/marketExpiration.cpp`: processamento de ofertas expiradas.
- `market/marketStatistics.cpp`: estatísticas de compra e venda do market.

### `src/scripting`

Contém a integração com Lua e os sistemas de eventos scriptáveis.

- `actions/actions.hpp`: contrato das actions usadas por itens e scripts; expõe registro, lookup e execução por item/action id.
- `actions/actions.cpp`: manager, registro e lookup de actions.
- `actions/actionRules.cpp`: regras de alcance, floor, linha de visão e target.
- `actions/actionExecution.cpp`: fluxo de uso de item e execução de script.
- `actions/actionConfig.cpp`: configuração do Action e binding de função nativa.
- `actions/actionBuiltins.cpp`: funções nativas increase/decrease item id e market.
- `baseevents.cpp/.hpp`: contrato base para sistemas de eventos; centraliza carregamento XML, script id e ligação com Lua.
- `creatureevent/creatureevent.hpp`: contrato dos eventos ligados a criaturas; expõe tipos, registro e callbacks usados por player, monster, NPC e scripts.
- `creatureevent/creatureEventManager.cpp`: manager, registro, reload e disparo global de login/logout/advance.
- `creatureevent/creatureEventConfig.cpp`: configuração, tipo e metadados do evento.
- `creatureevent/creatureEventPlayer.cpp`: execuções de login, logout e advance.
- `creatureevent/creatureEventDeath.cpp`: execuções de death, post death, prepare death e kill.
- `creatureevent/creatureEventCombat.cpp`: execuções de health change e mana change.
- `creatureevent/creatureEventMisc.cpp`: execuções de think, modal, text edit, extended opcode e move.
- `events/events.hpp`: contrato dos eventos globais registrados via script; expõe callbacks de player, creature, monster e party.
- `events/events.cpp`: carregamento e registro dos eventos configurados.
- `events/eventsMonster.cpp`: callbacks de monster.
- `events/eventsCreature.cpp`: callbacks de creature.
- `events/eventsParty.cpp`: callbacks de party.
- `events/eventsPlayerLook.cpp`: callbacks de look do player.
- `events/eventsPlayerMove.cpp`: callbacks de movement, turn e trade do player.
- `events/eventsPlayerProgress.cpp`: callbacks de experiência e skill do player.
- `events/eventsPlayer.cpp`: callbacks de player que não pertencem aos grupos principais.
- `globalevent.cpp/.hpp`: globalevents e eventos agendados.
- `lua/luascript.hpp` [CRÍTICO]: fachada pública da interface principal entre C++ e Lua; agrega os headers menores de `lua/luascript` e define contratos de stack, userdata, metatables, ambiente, eventos e bindings.
- `lua/luascript/luaScriptTypes.hpp`: forward declarations, enums e estruturas compartilhadas pelo scripting Lua.
- `lua/luascript/scriptEnvironment.hpp`: declaração do `ScriptEnvironment`, UIDs locais, itens temporários, NPC atual e resultados de banco.
- `lua/luascript/luaScriptInterfacePublic.hpp`: API pública de `LuaScriptInterface`, helpers de stack, userdata, metatables, getters e pushers.
- `lua/luascript/luaScriptInterfaceCore.hpp`: ciclo protegido da interface, registro de classes/tabelas/métodos e helpers centrais.
- `lua/luascript/luaScriptInterfaceLegacy.hpp`: declarações de funções globais legadas e utilitárias expostas ao Lua.
- `lua/luascript/luaScriptInterfaceGameWorld.hpp`: declarações de bindings de `Game`, `Variant`, `Position`, `Tile`, `NetworkMessage` e `ModalWindow`.
- `lua/luascript/luaScriptInterfaceItemCreature.hpp`: declarações de bindings de `Item`, `Container`, `Teleport` e `Creature`.
- `lua/luascript/luaScriptInterfacePlayerMonsterNpc.hpp`: declarações de bindings de `Player`, `Monster` e `Npc`.
- `lua/luascript/luaScriptInterfaceSocialCombat.hpp`: declarações de bindings de guild, group, vocation, town, house, item type, combat, condition e monster type.
- `lua/luascript/luaScriptInterfaceParty.hpp`: declarações de bindings de `Party`.
- `lua/luascript/luaScriptInterfacePrivate.hpp`: estado protegido da interface Lua, cache de arquivos e ambiente de scripts.
- `lua/luascript/luaEnvironment.hpp`: declaração de `LuaEnvironment`, timers, mapas de combat/area e interface de teste.
- `lua/luaScriptEnvironment.cpp`: ambiente de script, UIDs temporários e resultados de banco.
- `lua/luaScriptInterface.cpp`: ciclo de vida, carregamento, chamadas e tratamento de erro Lua.
- `lua/luaScriptStack.cpp`: helpers de stack, push/get/pop, metatables e conversões.
- `lua/registry/luaGlobalFunctionsRegistry.cpp` [CRÍTICO]: registro das funções globais, enums, classes e métodos expostos ao Lua; mudanças aqui podem quebrar scripts sem alterar código C++ consumidor.
- `lua/registry/luaRegistryHelpers.cpp`: helpers para registrar classes, tabelas, métodos, metatables e variáveis globais.
- `lua/luaBindingsCore.cpp`: bindings utilitários, eventos agendados, bit/config e helpers gerais.
- `lua/luaBindingsDatabase.cpp` [CRÍTICO]: bindings de database e result expostos aos scripts.
- `lua/luaBindingsGame.cpp` [CRÍTICO]: bindings da classe Game expostos aos scripts.
- `lua/world/luaVariant.cpp`: bindings de `Variant`.
- `lua/world/luaPosition.cpp`: bindings de `Position`, distância, visão e efeitos.
- `lua/world/luaTile.cpp`: bindings de `Tile`, itens, criaturas, flags, propriedades e house lookup.
- `lua/world/luaTown.cpp`: bindings de `Town`, nome, ID e templo.
- `lua/world/luaHouse.cpp`: bindings de `House`, owner, beds, doors, tiles e access lists.
- `lua/luaBindingsNetwork.cpp`: bindings de network message e modal window.
- `lua/item/luaItemLegacy.cpp`: funções globais legadas de criação, UID, depot e manipulação básica de itens.
- `lua/item/luaItem.cpp`: bindings da classe `Item`, atributos, clone, split, move, transform, decay e descrição.
- `lua/item/luaContainer.cpp`: bindings de `Container`, capacidade, slots, itens internos e adição de itens.
- `lua/item/luaTeleport.cpp`: bindings de `Teleport` e destino.
- `lua/item/luaItemType.cpp`: bindings de `ItemType`, flags, propriedades, atributos de combate e transformações.
- `lua/combat_condition/luaCombatLegacy.cpp`: funções globais legadas de área, alvo, dispel, outfit, movimento, luz e condição.
- `lua/combat_condition/luaCombatObject.cpp`: bindings do objeto `Combat`, parâmetros, fórmula, área, condição, callback, origem e execução.
- `lua/combat_condition/luaCondition.cpp`: bindings de `Condition`, ticks, parâmetros, fórmula, outfit, danos e imunidades de `MonsterType`.
- `lua/creature/luaCreatureCore.cpp`: criação, eventos, validações básicas, visão, parent, ID e nome de `Creature`.
- `lua/creature/luaCreatureRelations.cpp`: bindings de relações entre criaturas, como target, follow e master.
- `lua/creature/luaCreatureAttributes.cpp`: bindings de atributos de `Creature`, incluindo luz, velocidade, drop loot, vida, mana, skull e outfit.
- `lua/creature/luaCreatureMovement.cpp`: bindings de posição, tile, direção, teleport, pathfinding, movimento e walk delay.
- `lua/creature/luaCreatureActions.cpp`: ações diretas de `Creature`, como remove e say.
- `lua/creature/luaCreatureCollections.cpp`: coleções expostas ao Lua, como damage map e summons.
- `lua/player/luaPlayerCore.cpp`: criação, validação e dados básicos de `Player`.
- `lua/player/luaPlayerStats.cpp`: capacity, experiência, level, mana, skills, stamina, soul e banco.
- `lua/player/luaPlayerInventory.cpp`: itens, depot, inbox, dinheiro, slots e containers abertos.
- `lua/player/luaPlayerIdentity.cpp`: vocation, sexo e town.
- `lua/player/luaPlayerSocial.cpp`: guild, group e party.
- `lua/player/luaPlayerStorage.cpp`: storage values de player.
- `lua/player/luaPlayerMessaging.cpp`: text dialog, mensagens, canais e private messages.
- `lua/player/luaPlayerAppearance.cpp`: outfits, addons, janela de outfit e mounts.
- `lua/player/luaPlayerProgression.cpp`: premium, blessings e spells aprendidas.
- `lua/player/luaPlayerUtilities.cpp`: tutorial, map mark, save, FYI, PZ lock, client, house e ghost mode.
- `lua/monster_npc/luaMonster.cpp`: bindings da classe `Monster`, alvos, amigos, spawn, idle e experiência.
- `lua/monster_npc/luaNpc.cpp`: bindings da classe `Npc`, master position e speech bubble.
- `lua/monster_npc/luaMonsterTypeCore.cpp`: bindings centrais de `MonsterType`, flags, nomes, stats básicos e propriedades.
- `lua/monster_npc/luaMonsterTypeLists.cpp`: bindings de listas de ataques, moves, defesas, elementos, vozes, loot, summons e evoluções.
- `lua/monster_npc/luaMonsterTypeStats.cpp`: bindings de atributos finais de `MonsterType`, outfit, race, levels, corpse, mana, velocidade e target.
- `lua/luaBindingsSocial.cpp`: bindings de guild, group, vocation e party.
- `lua/luaBindingsLegacy.cpp`: bindings legados que ficaram fora dos grupos principais.
- `lua/luaEnvironment.cpp`: gerenciamento do LuaEnvironment global.
- `scriptmanager.cpp/.hpp`: contrato de carregamento e gerenciamento de scripts.
- `talkaction.cpp/.hpp`: contrato de talkactions e comandos por fala; expõe registro, permissões e execução Lua.

### `src/security`

Contém componentes ligados à segurança.

- `ban.cpp/.hpp`: regras e consultas de banimento.
- `rsa.cpp/.hpp`: suporte a RSA.

### `src/world`

Contém estruturas físicas e lógicas do mundo.

- `bed.cpp/.hpp`: camas e regras associadas.
- `cylinder.cpp/.hpp` [CRÍTICO]: contrato base para objetos que contêm ou recebem `Thing`; usado por tiles, containers, players e movimentação.
- `house.hpp`: contrato de casas, portas, listas de acesso e gerenciador de casas; expõe owner, permissões, tiles, beds e transferência.
- `house/house.cpp`: dados principais da casa, dono, tiles, portas, camas e permissões gerais.
- `house/houseAccess.cpp`: listas de acesso, convidados, subdonos e expressões de permissão.
- `house/houseDoor.cpp`: portas de casas, leitura de atributos e acesso por porta.
- `house/houseTransfer.cpp`: transferência de casas e envio de itens ao depot/inbox.
- `house/houses.cpp`: gerenciador de casas, carregamento XML e cobrança de aluguel.
- `housetile.cpp/.hpp`: tiles associados a casas.
- `map.hpp` [CRÍTICO]: contrato do mapa; expõe quadtree, pathfinding, spectators, tiles, criaturas, queries espaciais e operações usadas por game/network/world.
- `map/map.cpp`: carregamento e salvamento do mapa.
- `map/mapStorage.cpp`: leitura e escrita de tiles na estrutura espacial.
- `map/mapCreature.cpp` [CRÍTICO]: posicionamento e movimentação de criaturas no mapa.
- `map/mapSpectators.cpp` [CRÍTICO]: busca e cache de espectadores usados por visão, fala, efeitos e protocolo.
- `map/mapSight.cpp`: linha de visão e alcance de arremesso.
- `map/mapPathfinding.cpp` [CRÍTICO]: busca de caminho em alto nível.
- `map/mapAStar.cpp`: nós e custos do algoritmo A*.
- `map/mapQTree.cpp`: floors, quadtree e folhas do mapa.
- `map/mapMaintenance.cpp`: limpeza de itens do mapa.
- `spawn.hpp`: contrato de spawns de criaturas e NPCs; expõe carregamento, agendamento e lifecycle de respawn.
- `spawn/spawns.cpp`: carregamento XML e ciclo do gerenciador `Spawns`.
- `spawn/spawn.cpp`: núcleo do spawn, registro e remoção de monstros.
- `spawn/spawnMonster.cpp`: criação e posicionamento de monstros.
- `spawn/spawnScheduler.cpp`: agendamento, checagem e limpeza de respawns.
- `teleport.cpp/.hpp`: teleports.
- `thing.cpp/.hpp`: contrato base para entidades posicionáveis; raiz comum de itens, criaturas e outras things.
- `tile.hpp` [CRÍTICO]: contrato de tiles; expõe flags, itens, criaturas, stackpos, queries, notificações e regras de add/remove.
- `tile/tile.cpp`: definições base e tile nulo.
- `tile/tileFlags.cpp`: flags, propriedades e bloqueios do tile.
- `tile/tileLookup.cpp`: consultas de itens, criaturas, stackpos e item de uso.
- `tile/tileNotifications.cpp`: notificações de adição, atualização, remoção e eventos de movimento.
- `tile/tileQueries.cpp` [CRÍTICO]: regras de adição, remoção e destino.
- `tile/tileThingManagement.cpp` [CRÍTICO]: adição, atualização, substituição e remoção de things.
- `town.hpp`: representação de cidades.

## Convenções de Manutenção

- Headers `.hpp` devem declarar interfaces, tipos e funções públicas.
- Arquivos `.cpp` devem concentrar a implementação.
- Evite depender de includes indiretos. O arquivo deve incluir diretamente o header da função que usa.
- Helpers genéricos devem ficar em `src/core/tools`, separados por responsabilidade.
- Código de domínio deve ficar perto do sistema que representa.
- Ao mover arquivos, atualize também `src/CMakeLists.txt` e `vc14/theforgottenserver.vcxproj`.

## Fluxo Sugerido Para Refatorações

1. Criar o novo `.hpp/.cpp`.
2. Mover declarações e implementações.
3. Corrigir os includes dos consumidores.
4. Atualizar `src/CMakeLists.txt`.
5. Atualizar `vc14/theforgottenserver.vcxproj`.
6. Buscar referências antigas ao arquivo ou função movida.
7. Compilar e testar no ambiente local.

## Observações

Esta documentação deve acompanhar a evolução da source. Quando uma pasta nova for criada, um arquivo for movido ou uma responsabilidade mudar de lugar, este documento deve ser atualizado para continuar servindo como mapa confiável do projeto.
