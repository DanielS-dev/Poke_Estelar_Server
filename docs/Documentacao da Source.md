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
- `creature.cpp/.hpp`: base para criaturas vivas no mundo.
- `groups.cpp/.hpp`: grupos de acesso e permissões.
- `guild.cpp/.hpp`: dados e regras de guild.
- `monster.cpp/.hpp`: comportamento individual de monstros.
- `monsters.cpp/.hpp`: carregamento e registro dos tipos de monstros.
- `mounts.cpp/.hpp`: carregamento e controle de mounts.
- `npc.cpp/.hpp`: comportamento e carregamento de NPCs.
- `outfit.cpp/.hpp`: outfits disponíveis.
- `party.cpp/.hpp`: sistema de party.
- `player.cpp/.hpp`: comportamento, estado e interações do jogador.
- `vocation.cpp/.hpp`: vocations e suas configurações.

### `src/game`

Contém os sistemas centrais de gameplay.

- `chat/chat.cpp/.hpp`: fachada e orquestração do sistema de chat.
- `chat/chatChannel.cpp/.hpp`: canais de chat, usuários, convites, eventos Lua e envio de mensagens.
- `chat/chatLoader.cpp/.hpp`: carregamento dos canais via XML e scripts.
- `chat/chatRules.cpp/.hpp`: regras de fala e normalização do tipo de mensagem por canal.
- `combat/combat.cpp/.hpp`: fachada, regras principais e configuração do combate.
- `combat/combatExecution.cpp`: execução de dano, mana, condições, dispel e efeitos em tiles.
- `combat/combatCallbacks.cpp/.hpp`: callbacks Lua de valor, tile e alvo.
- `combat/combatTypes.hpp`: parâmetros e tipos compartilhados do combate.
- `combat/areaCombat.cpp/.hpp`: áreas de combate e seleção de tiles.
- `combat/matrixArea.hpp`: matriz usada para montar áreas de combate.
- `combat/magicField.cpp/.hpp`: comportamento de magic fields ao pisar.
- `commands/command.cpp/.hpp`: representação de um comando individual.
- `commands/commandLoader.cpp/.hpp`: carregamento dos comandos via XML.
- `commands/commandRules.cpp/.hpp`: validação de permissão e log de execução dos comandos.
- `commands/commands.cpp/.hpp`: fachada e orquestração dos comandos administrativos ou de servidor.
- `condition/condition.cpp/.hpp`: fachada, base comum, factory e serialização geral de conditions.
- `condition/conditionAttributes.cpp`: modifiers de skills/stats e atributos temporários.
- `condition/conditionRegeneration.cpp`: regeneração de vida, mana e soul.
- `condition/conditionDamage.cpp`: condições de dano periódico e damage list.
- `condition/conditionSpeed.cpp`: haste, paralyze, sleep/silence e fórmula de speed.
- `condition/conditionVisual.cpp`: invisibilidade, outfit e light.
- `condition/conditionCooldown.cpp`: cooldown de spell, grupo e status simples.
- `game.cpp/.hpp`: núcleo de coordenação da lógica do jogo.
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
- `spells/spells.cpp/.hpp`: fachada e registro do sistema de spells.
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
- `weapons/weapons.cpp/.hpp`: fachada, registro e carregamento padrão das armas.

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
- `protocol.cpp/.hpp`: base comum dos protocolos.
- `protocolgame.hpp`: interface do protocolo principal de gameplay.
- `protocolgame/protocolgame.cpp`: lifecycle, login, conexão e dispatcher de pacotes.
- `protocolgame/protocolgameMap.cpp`: descrição de mapa, visibilidade e criaturas conhecidas.
- `protocolgame/protocolgameParse.cpp`: parsers dos pacotes recebidos do cliente.
- `protocolgame/protocolgameSend.cpp`: envios gerais, chat, status e canais.
- `protocolgame/protocolgameShopMarket.cpp`: shop, market e detalhes de ofertas.
- `protocolgame/protocolgameQuestTrade.cpp`: quest log, quest line e trade.
- `protocolgame/protocolgameWorld.cpp`: containers, inventário, tiles, world state e movement visual.
- `protocolgame/protocolgameHelpers.cpp`: helpers de serialização para criaturas, stats, outfit, luz e shop item.
- `protocollogin.cpp/.hpp`: protocolo de login.
- `protocolold.cpp/.hpp`: suporte a protocolo antigo.
- `protocolstatus.cpp/.hpp`: protocolo de status do servidor.

### `src/persistence`

Contém acesso ao banco de dados e carregamento/salvamento persistente.

- `database.cpp/.hpp`: conexão e execução de queries.
- `databasemanager.cpp/.hpp`: gerenciamento de schema e tarefas administrativas de banco.
- `databasetasks.cpp/.hpp`: execução assíncrona de tarefas de banco.
- `ioguild.cpp/.hpp`: persistência de guilds.
- `login/iologindata.hpp`: fachada dos dados de login, conta e jogador.
- `login/loginDataAccount.cpp`: persistência de contas e tipo de conta.
- `login/loginDataAuthentication.cpp`: autenticação do login server e gameworld.
- `login/loginDataPlayerLoad.cpp`: carregamento e preload dos dados do jogador.
- `login/loginDataItems.cpp`: serialização e desserialização de itens do jogador.
- `login/loginDataPlayerSave.cpp`: salvamento completo do jogador.
- `login/loginDataPlayerQueries.cpp`: consultas auxiliares de jogador, guid, nome, banco e house bid.
- `login/loginDataVip.cpp`: persistência da VIP list.
- `login/loginDataPremium.cpp`: ajustes de dias premium.
- `map/iomap.hpp`: fachada do carregamento de mapa OTBM.
- `map/iomap.cpp`: carregamento do mapa, tiles, towns e waypoints.
- `map/iomapserialize.hpp`: fachada da serialização persistente de mapa e houses.
- `map/mapHouseItems.cpp`: carregamento e salvamento dos itens de houses.
- `map/mapItemSerialization.cpp`: helpers para serializar/deserializar itens, containers e tiles.
- `map/mapHouseInfo.cpp`: carregamento e salvamento de informações e listas das houses.
- `map/otbmTypes.hpp`: enums e structs do formato OTBM.
- `market/iomarket.hpp`: fachada da persistência do market.
- `market/marketOffers.cpp`: consultas, criação, aceite e remoção de ofertas.
- `market/marketHistory.cpp`: histórico e movimentação de ofertas para histórico.
- `market/marketExpiration.cpp`: processamento de ofertas expiradas.
- `market/marketStatistics.cpp`: estatísticas de compra e venda do market.

### `src/scripting`

Contém a integração com Lua e os sistemas de eventos scriptáveis.

- `actions/actions.hpp`: fachada das actions usadas por itens e scripts.
- `actions/actions.cpp`: manager, registro e lookup de actions.
- `actions/actionRules.cpp`: regras de alcance, floor, linha de visão e target.
- `actions/actionExecution.cpp`: fluxo de uso de item e execução de script.
- `actions/actionConfig.cpp`: configuração do Action e binding de função nativa.
- `actions/actionBuiltins.cpp`: funções nativas increase/decrease item id e market.
- `baseevents.cpp/.hpp`: base para sistemas de eventos.
- `creatureevent/creatureevent.hpp`: fachada dos eventos ligados a criaturas.
- `creatureevent/creatureEvents.cpp`: manager, registro, reload e disparo global de login/logout/advance.
- `creatureevent/creatureEventConfig.cpp`: configuração, tipo e metadados do evento.
- `creatureevent/creatureEventPlayer.cpp`: execuções de login, logout e advance.
- `creatureevent/creatureEventDeath.cpp`: execuções de death, post death, prepare death e kill.
- `creatureevent/creatureEventCombat.cpp`: execuções de health change e mana change.
- `creatureevent/creatureEventMisc.cpp`: execuções de think, modal, text edit, extended opcode e move.
- `events/events.hpp`: fachada dos eventos globais registrados via script.
- `events/events.cpp`: carregamento e registro dos eventos configurados.
- `events/eventsMonster.cpp`: callbacks de monster.
- `events/eventsCreature.cpp`: callbacks de creature.
- `events/eventsParty.cpp`: callbacks de party.
- `events/eventsPlayerLook.cpp`: callbacks de look do player.
- `events/eventsPlayerMove.cpp`: callbacks de movement, turn e trade do player.
- `events/eventsPlayerProgress.cpp`: callbacks de experiência e skill do player.
- `events/eventsPlayer.cpp`: callbacks de player que não pertencem aos grupos principais.
- `globalevent.cpp/.hpp`: globalevents e eventos agendados.
- `lua/luascript.hpp`: fachada da interface principal entre C++ e Lua.
- `lua/luaScriptEnvironment.cpp`: ambiente de script, UIDs temporários e resultados de banco.
- `lua/luaScriptInterface.cpp`: ciclo de vida, carregamento, chamadas e tratamento de erro Lua.
- `lua/luaScriptStack.cpp`: helpers de stack, push/get/pop, metatables e conversões.
- `lua/luaScriptRegistry.cpp`: registro de classes, métodos, tabelas e funções Lua.
- `lua/luaBindingsCore.cpp`: bindings utilitários, eventos agendados, bit/config e helpers gerais.
- `lua/luaBindingsDatabase.cpp`: bindings de database e result.
- `lua/luaBindingsGame.cpp`: bindings da classe Game.
- `lua/luaBindingsWorld.cpp`: bindings de variant, position, tile, town e house.
- `lua/luaBindingsNetwork.cpp`: bindings de network message e modal window.
- `lua/luaBindingsItem.cpp`: bindings de item, container, teleport e item type.
- `lua/luaBindingsCombatCondition.cpp`: bindings de combat, condition e área de combate.
- `lua/luaBindingsCreature.cpp`: bindings de creature.
- `lua/luaBindingsPlayer.cpp`: bindings de player.
- `lua/luaBindingsMonsterNpc.cpp`: bindings de monster, monster type e npc.
- `lua/luaBindingsSocial.cpp`: bindings de guild, group, vocation e party.
- `lua/luaBindingsLegacy.cpp`: bindings legados que ficaram fora dos grupos principais.
- `lua/luaEnvironment.cpp`: gerenciamento do LuaEnvironment global.
- `scriptmanager.cpp/.hpp`: carregamento e gerenciamento de scripts.
- `talkaction.cpp/.hpp`: talkactions e comandos por fala.

### `src/security`

Contém componentes ligados à segurança.

- `ban.cpp/.hpp`: regras e consultas de banimento.
- `rsa.cpp/.hpp`: suporte a RSA.

### `src/world`

Contém estruturas físicas e lógicas do mundo.

- `bed.cpp/.hpp`: camas e regras associadas.
- `cylinder.cpp/.hpp`: base para objetos que podem conter coisas.
- `house.cpp/.hpp`: casas e seus dados.
- `housetile.cpp/.hpp`: tiles associados a casas.
- `map.cpp/.hpp`: mapa, carregamento e consultas espaciais.
- `spawn.cpp/.hpp`: spawns de criaturas.
- `teleport.cpp/.hpp`: teleports.
- `thing.cpp/.hpp`: base comum para entidades posicionáveis.
- `tile.cpp/.hpp`: tiles, flags, itens e criaturas no mapa.
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
