# Mapeamento da Pasta Data

Este documento mapeia a estrutura da pasta `data`, que concentra os arquivos de runtime do servidor: scripts Lua, XMLs de registro, mapa, itens, monstros, NPCs, raids e configuracoes de jogo.

O objetivo deste arquivo e servir como indice vivo da `data`. Cada subpasta deve ser analisada individualmente, descrevendo sua estrutura interna, os tipos de arquivos que aceita, a funcao de cada grupo de arquivos e como esse conteudo se comunica com a source C++ do servidor.

## Como Ler Este Documento

Use este documento em duas camadas:

- **Mapa geral**: visao rapida das pastas, volume de arquivos e responsabilidades.
- **Analise por subpasta**: detalhamento de cada modulo da `data`, incluindo estrutura, registradores, scripts, libs e ponte com a source.

Ao analisar uma subpasta, preencher sempre os mesmos campos:

```text
## data/<subpasta>

### Responsabilidade
O que essa pasta controla no servidor.

### Estrutura Interna
Arvore resumida das pastas e arquivos principais.

### Tipos de Arquivos
Quais formatos existem ali e para que servem.

### Arquivos Principais
XMLs registradores, libs, scripts centrais ou arquivos de dados importantes.

### Comunicacao com a Source
Quais classes/funcoes C++ carregam ou executam esses arquivos.

### Fluxo de Execucao
Como o servidor sai da source, passa pelo XML/lib/script e volta para a engine.

### Cuidados de Manutencao
Regras para adicionar, mover, renomear ou remover arquivos nessa pasta.
```

## Camadas da Pasta `data`

| Camada | Pastas | Papel |
|---|---|---|
| Bootstrap Lua | `global.lua`, `lib` | Inicializa funcoes globais, compatibilidade e helpers compartilhados por scripts. |
| Modulos XML-driven | `actions`, `chatchannels`, `creaturescripts`, `events`, `globalevents`, `movements`, `spells`, `talkactions`, `weapons` | Registram eventos/comandos por XML e executam scripts Lua. |
| Conteudo de entidades | `monster`, `npc`, `items` | Define monstros, NPCs e itens usados pelo jogo. |
| Mundo | `world`, `bkup_world` | Mapa, spawns, houses e backups. |
| Configuracoes globais | `XML` | Configuracoes estruturais como vocations, groups, commands, quests, mounts, outfits e stages. |
| Operacional/runtime | `logs`, `reports`, `migrations` | Saidas geradas por sistemas de jogo, reports e scripts de migracao. |

## Ponte Geral com a Source

| Area da `data` | Principal ponto na source | Funcao da source |
|---|---|---|
| `data/global.lua` | `src/scripting/scriptmanager.cpp` | Carrega o ambiente Lua global no startup. |
| `data/lib/*` | `data/lib/lib.lua` via `global.lua` | Organiza helpers Lua carregados antes dos sistemas scriptados. |
| Modulos XML-driven | `src/scripting/baseevents.cpp` | Monta caminhos `data/<modulo>/`, carrega XMLs e scripts. |
| `actions` | `src/scripting/actions/*.cpp` | Registra e executa actions por item/action/unique id. |
| `creaturescripts` | `src/scripting/creatureevent/*.cpp` | Registra eventos de criatura/player/monster. |
| `events` | `src/scripting/events/events.cpp` | Carrega scripts de eventos por entidade. |
| `globalevents` | `src/scripting/globalevent.hpp` e reloads em commands/signals | Executa eventos globais por startup, horario ou intervalo. |
| `talkactions` | `src/scripting/talkaction.cpp` | Registra comandos de fala. |
| `spells` | `src/game/spells/*.cpp` | Carrega spells XML, scripts e execucao de magias/moves. |
| `weapons` | `src/game/weapons/*.cpp` | Carrega armas XML e associa itens a comportamento de arma. |
| `movements` | `src/game/movement/*.cpp` | Registra eventos de movimento/tile/item. |
| `monster` | `src/entities/monsters/*.cpp` | Carrega catalogo `monsters.xml` e XMLs individuais de MonsterType. |
| `npc` | `src/entities/npc/*.cpp` | Carrega XML do NPC e script Lua associado. |
| `items` | `src/items/items/*.cpp`, `src/app/otserv.cpp` | Carrega `items.otb` e `items.xml`. |
| `world` | `src/game/game/gameMap.cpp`, `src/world/map/*.cpp` | Carrega o mapa OTBM, spawns e houses. |
| `XML/vocations.xml` | `src/entities/vocation.cpp` | Carrega vocations/classes. |
| `XML/groups.xml` | `src/entities/groups.cpp` | Carrega grupos e permissoes. |
| `XML/mounts.xml` | `src/entities/mounts.cpp` | Carrega mounts. |
| `XML/outfits.xml` | `src/entities/outfit.cpp` | Carrega outfits. |
| `XML/quests.xml` | `src/game/quests/questLoader.cpp` | Carrega quests/missions. |
| `XML/stages.xml` | `src/game/game/gameWorld.cpp` | Carrega stages de experiencia. |
| `XML/commands.xml` | `src/game/commands/commandLoader.cpp` | Carrega comandos internos da source. |
| `raids` | `src/game/raids/*.cpp` | Carrega `raids.xml` e arquivos individuais de raid. |
| `migrations` | `src/persistence/databasemanager.cpp` | Executa scripts de migracao por versao. |
| `logs`, `reports` | `src/game/commands/commandRules.cpp`, `src/game/game/gameReports.cpp` | Recebem arquivos gerados em runtime por comandos e reports de jogo. |

## Visao Geral

| Pasta | Arquivos | Lua | XML | Outros | Responsabilidade |
|---|---:|---:|---:|---:|---|
| `actions` | 86 | 85 | 1 | 0 | Acoes executadas ao usar itens, unique ids e action ids. |
| `bkup_world` | 5 | 0 | 2 | 3 | Backup de arquivos do mapa/world. |
| `chatchannels` | 8 | 7 | 1 | 0 | Canais de chat e scripts associados. |
| `creaturescripts` | 24 | 23 | 1 | 0 | Eventos ligados a players, monstros e criaturas. |
| `events` | 5 | 4 | 1 | 0 | Eventos globais de entidades via sistema moderno de events. |
| `globalevents` | 11 | 10 | 1 | 0 | Eventos globais por startup, intervalo, horario e record. |
| `items` | 2 | 0 | 1 | 1 | Definicao dos itens XML e arquivo OTB. |
| `lib` | 18 | 18 | 0 | 0 | Bibliotecas Lua globais carregadas pelo servidor. |
| `logs` | 1 | 0 | 0 | 1 | Pasta reservada para logs runtime. |
| `migrations` | 20 | 20 | 0 | 0 | Scripts Lua de migracao. |
| `monster` | 1048 | 0 | 1047 | 1 | Catalogo de monstros/Pokemon e XMLs individuais. |
| `movements` | 26 | 25 | 1 | 0 | Eventos de movimento, tiles, portas, agua, dive e afins. |
| `npc` | 129 | 65 | 64 | 0 | Definicoes XML e scripts Lua de NPCs. |
| `raids` | 17 | 0 | 17 | 0 | Registro e arquivos de raids. |
| `reports` | 1 | 0 | 0 | 1 | Pasta reservada para reports runtime. |
| `spells` | 793 | 792 | 1 | 0 | Spells, moves Pokemon, passivas e scripts de combate/suporte. |
| `talkactions` | 92 | 91 | 1 | 0 | Comandos de fala, comandos GM e comandos customizados. |
| `weapons` | 5 | 4 | 1 | 0 | Configuracao e scripts de armas/projeteis. |
| `world` | 6 | 0 | 2 | 4 | Mapa OTBM, spawns, houses, backups e utilitario de checagem. |
| `XML` | 7 | 0 | 7 | 0 | Configuracoes globais em XML: vocations, groups, commands, quests etc. |

Total aproximado no momento do mapeamento: 2307 arquivos, sendo 1149 `.xml`, 1145 `.lua`, 4 `.otbm`, 2 `.py`, 2 `.gitignore`, 1 `.zip`, 1 `.txt` e 1 `.otb`.

Observacao: `data/logs` e usada para logs gerados por sistemas de jogo, como comandos de GM. Os logs tecnicos do servidor gerados pelo logger central ficam, por padrao, em `/logs/server.log` na raiz do projeto. Consulte `docs/Sistema de Logger.md`.

## Fluxo de Carregamento Lua

O ponto de entrada global e `data/global.lua`, que carrega `data/lib/lib.lua`.

```text
data/global.lua
  -> data/lib/lib.lua
       -> data/lib/core/core.lua
       -> data/lib/compat/compat.lua
```

`global.lua` tambem define constantes, tabelas globais e helpers usados por varios scripts, como portas, money, datas, distancia e funcoes auxiliares de player/account.

## Padrao dos Modulos Scriptados

A maior parte dos modulos segue o padrao:

```text
data/<modulo>/<modulo>.xml
data/<modulo>/lib/*.lua
data/<modulo>/scripts/*.lua
```

O XML registra eventos, ids, nomes ou comandos. O servidor le esse XML e aponta para scripts dentro da pasta `scripts`. A pasta `lib`, quando existe, guarda helpers especificos daquele modulo.

Modulos nesse padrao:

- `actions`: `actions.xml`, `lib/actions.lua`, `scripts/*`.
- `chatchannels`: `chatchannels.xml`, `scripts/*`.
- `creaturescripts`: `creaturescripts.xml`, `lib/creaturescripts.lua`, `scripts/*`.
- `globalevents`: `globalevents.xml`, `lib/globalevents.lua`, `scripts/*`.
- `movements`: `movements.xml`, `lib/movements.lua`, `scripts/*`.
- `npc`: XMLs de NPC na raiz, `lib/npc.lua`, `lib/npcsystem/*`, `scripts/*`.
- `spells`: `spells.xml`, `lib/spells.lua`, `scripts/*`.
- `talkactions`: `talkactions.xml`, `lib/talkactions.lua`, `scripts/*`.
- `weapons`: `weapons.xml`, `lib/weapons.lua`, `scripts/*`.

## Principais Registradores XML

| Arquivo | Funcao |
|---|---|
| `data/actions/actions.xml` | Registra actions por `itemid`, `fromid/toid`, `actionid` e `uniqueid`. |
| `data/chatchannels/chatchannels.xml` | Registra canais e scripts de chat. |
| `data/creaturescripts/creaturescripts.xml` | Registra eventos como login, logout, death, postdeath, healthchange, move, extendedopcode e modalwindow. |
| `data/events/events.xml` | Registra scripts do sistema de events por entidade: player, party, monster e creature. |
| `data/globalevents/globalevents.xml` | Registra eventos de startup, record, horarios fixos e intervalos. |
| `data/items/items.xml` | Define atributos dos itens usados junto com `items.otb`. |
| `data/monster/monsters.xml` | Catalogo central que associa nome do monstro ao XML individual. |
| `data/movements/movements.xml` | Registra eventos de movimento por item/tile/action. |
| `data/raids/raids.xml` | Registra raids disponiveis. |
| `data/spells/spells.xml` | Registra spells e scripts de moves. |
| `data/talkactions/talkactions.xml` | Registra comandos por palavras/chaves de fala. |
| `data/weapons/weapons.xml` | Registra armas e scripts relacionados. |

## Configuracoes Globais em `data/XML`

| Arquivo | Responsabilidade |
|---|---|
| `commands.xml` | Comandos disponiveis e regras associadas. |
| `groups.xml` | Grupos de acesso/permissoes. |
| `mounts.xml` | Mounts disponiveis. |
| `outfits.xml` | Outfits disponiveis. |
| `quests.xml` | Registro de quests. |
| `stages.xml` | Stages de experiencia/level. |
| `vocations.xml` | Vocations/classes e seus atributos. |

## Conteudo de Mundo

| Arquivo | Funcao |
|---|---|
| `data/world/global_dash.otbm` | Mapa principal em formato OTBM. |
| `data/world/map-spawn.xml` | Spawns do mapa. |
| `data/world/map-house.xml` | Houses do mapa. |
| `data/world/backup.otbm` | Backup de mapa. |
| `data/world/global_dash.zip` | Arquivo compactado relacionado ao mapa. |
| `data/world/checkspawn.py` | Utilitario Python para checagem de spawn. |

`data/bkup_world` replica parte dessa estrutura como backup.

## Organizacao de Monstros

`data/monster/monsters.xml` e o catalogo central. Ele aponta para XMLs individuais separados por categoria:

| Categoria | Arquivos |
|---|---:|
| `.alola` | 10 |
| `.galarian` | 5 |
| `.hisuian` | 10 |
| `cloned` | 8 |
| `gen1` | 151 |
| `gen2` | 61 |
| `gen3` | 79 |
| `gen4` | 74 |
| `gen5` | 35 |
| `gen6` | 22 |
| `gen7` | 24 |
| `gen8` | 13 |
| `gen9` | 8 |
| `mega` | 42 |
| `shiny` | 493 |
| `utility` | 11 |

Observacao: as pastas `.alola`, `.galarian` e `.hisuian` usam ponto no inicio do nome. Em alguns sistemas ou editores isso pode fazer a pasta parecer oculta.

## Areas Mais Pesadas

- `monster`: maior volume de XMLs e catalogo de Pokemon/monstros.
- `spells`: maior volume de Lua, especialmente em `scripts/moves/*`, `scripts/passives/*`, `scripts/attack/*` e `scripts/support/*`.
- `npc`: mistura XMLs na raiz com scripts em `npc/scripts` e framework em `npc/lib/npcsystem`.
- `talkactions`: muitos comandos operacionais e sistemas customizados.
- `actions`: concentra uso de itens, quests e sistemas Pokemon como boost, catch, evolution, held, addon, dungeon e similares.

## Diretrizes de Manutencao

- Ao adicionar um script em modulo XML-driven, registrar tambem no XML correspondente.
- Ao alterar `data/global.lua` ou `data/lib/*`, revisar impacto amplo, porque esses arquivos alimentam muitos scripts.
- Ao adicionar monstro, criar XML individual e registrar em `data/monster/monsters.xml`.
- Ao mexer em mapa, conferir consistencia entre `.otbm`, `map-spawn.xml` e `map-house.xml`.
- Evitar deixar scripts novos soltos fora de `scripts/` ou helpers fora de `lib/`, salvo quando o modulo ja seguir outro padrao.
- Pastas runtime como `logs` e `reports` devem continuar reservadas para saidas geradas pelo servidor.

## Analise por Subpasta

As secoes abaixo devem ser preenchidas uma a uma conforme a auditoria avancar. A ordem recomendada e comecar pelos pontos de bootstrap e depois seguir para os modulos XML-driven, porque eles explicam o padrao que se repete no resto da `data`.

### Ordem Recomendada

1. `global.lua` e `lib`
2. `actions`
3. `creaturescripts`
4. `events`
5. `globalevents`
6. `movements`
7. `talkactions`
8. `spells`
9. `weapons`
10. `items`
11. `monster`
12. `npc`
13. `raids`
14. `world` e `bkup_world`
15. `XML`
16. `migrations`
17. `logs` e `reports`

## data/global.lua e data/lib

### Responsabilidade

Inicializar o ambiente Lua compartilhado. `data/global.lua` e carregado pela source no startup e chama `data/lib/lib.lua`, que por sua vez carrega as bibliotecas centrais e a camada de compatibilidade.

### Estrutura Interna

```text
data/global.lua
data/lib/lib.lua
data/lib/core/*.lua
data/lib/compat/compat.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.lua` | Define helpers globais, constantes, wrappers de API, compatibilidade e funcoes reutilizadas pelos scripts. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `data/global.lua` | Ponto de entrada Lua global; carrega `data/lib/lib.lua` e define tabelas/funcoes globais. |
| `data/lib/lib.lua` | Agregador das libs globais. |
| `data/lib/core/core.lua` | Entrada das libs core Lua. |
| `data/lib/compat/compat.lua` | Compatibilidade com API Lua antiga. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/scriptmanager.cpp` | Chama `g_luaEnvironment.loadFile("data/global.lua")` no carregamento dos sistemas de script. |
| `src/app/signals.cpp` e `src/game/commands/commands.cpp` | Permitem reload de `global.lua`. |
| `src/scripting/lua/*` | Expoe classes/funcoes C++ para uso das libs e scripts Lua. |

### Fluxo de Execucao

```text
ScriptingManager
  -> loadFile("data/global.lua")
     -> dofile("data/lib/lib.lua")
        -> dofile("data/lib/core/core.lua")
        -> dofile("data/lib/compat/compat.lua")
```

### Cuidados de Manutencao

- Mudancas em `global.lua` e `data/lib` tem alto impacto, porque afetam quase todos os scripts.
- Evitar dependencias circulares entre libs.
- Helpers muito especificos de um modulo devem ficar em `data/<modulo>/lib`, nao na lib global.

## data/actions

### Responsabilidade

Registrar e executar acoes disparadas pelo uso de itens, action ids, unique ids e intervalos de item ids.

### Estrutura Interna

```text
data/actions/actions.xml
data/actions/lib/actions.lua
data/actions/scripts/other/*.lua
data/actions/scripts/poke/*.lua
data/actions/scripts/quests/*.lua
data/actions/scripts/raid/*.lua
data/actions/scripts/tools/*.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra quais ids disparam quais scripts. |
| `.lua` | Implementa a logica executada quando a action e acionada. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `data/actions/actions.xml` | Registrador central de actions. |
| `data/actions/lib/actions.lua` | Helpers especificos de actions. |
| `data/actions/scripts/poke/*` | Sistemas Pokemon acionados por itens, como catch, evolution, held, boost, addon e dungeon. |
| `data/actions/scripts/quests/*` | Actions ligadas a quests. |
| `data/actions/scripts/tools/*` | Ferramentas como rope, shovel, pick, fishing e similares. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/actions/actions.cpp` | Sistema principal de actions. |
| `src/scripting/actions/actionConfig.cpp` | Leitura/configuracao das actions registradas. |
| `src/scripting/actions/actionExecution.cpp` | Execucao da action e chamada do script Lua. |
| `src/scripting/baseevents.cpp` | Fornece o padrao de carregamento `data/actions/`. |

### Fluxo de Execucao

```text
Player usa item
  -> Game/Actions na source
     -> procura registro em actions.xml
        -> carrega/executa data/actions/scripts/<script>.lua
           -> script chama API Lua exposta pela source
```

### Cuidados de Manutencao

- Todo script novo deve ser registrado em `actions.xml`.
- Ao renomear script, atualizar o atributo `script`.
- Evitar misturar sistemas diferentes no mesmo script quando houver subpasta clara (`poke`, `quests`, `tools`, `other`).

## data/bkup_world

### Responsabilidade

Guardar uma copia operacional dos arquivos principais de mundo. Esta pasta nao e carregada diretamente pelo servidor no fluxo normal; ela serve como backup/manual fallback para mapa, houses, spawns e utilitario de checagem.

### Estrutura Interna

```text
data/bkup_world/backup.otbm
data/bkup_world/global_dash.otbm
data/bkup_world/map-house.xml
data/bkup_world/map-spawn.xml
data/bkup_world/checkspawn.py
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.otbm` | Arquivo binario de mapa usado pelo servidor/map editor. |
| `.xml` | Dados auxiliares do mundo, como houses e spawns. |
| `.py` | Script utilitario para verificacao de spawn. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `global_dash.otbm` | Copia do mapa principal. |
| `backup.otbm` | Backup adicional de mapa. |
| `map-spawn.xml` | Copia dos spawns do mapa. |
| `map-house.xml` | Copia das houses do mapa. |
| `checkspawn.py` | Utilitario Python para auditoria/checagem de spawns. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/game/game/gameMap.cpp` | O fluxo normal carrega mapa a partir de `data/world/<nome>.otbm`, nao de `data/bkup_world`. |
| `src/world/map/*.cpp` | Processa mapa, spawns e houses quando os arquivos ativos estao em `data/world`. |

### Fluxo de Execucao

```text
Fluxo normal:
source
  -> data/world/global_dash.otbm
  -> data/world/map-spawn.xml
  -> data/world/map-house.xml

Fluxo de backup:
operador/desenvolvedor
  -> copia arquivo de data/bkup_world para data/world
  -> servidor passa a carregar a copia restaurada no proximo load/restart
```

### Cuidados de Manutencao

- Nao assumir que alteracoes em `data/bkup_world` entram no servidor automaticamente.
- Ao atualizar o mapa oficial em `data/world`, avaliar se o backup precisa ser sincronizado.
- Evitar versionar backups temporarios grandes fora dessa pasta para nao confundir qual mapa e o ativo.
- Antes de restaurar backup, conferir compatibilidade entre `.otbm`, `map-spawn.xml` e `map-house.xml`.

## data/chatchannels

### Responsabilidade

Registrar canais normais de chat e associar scripts Lua opcionais para validar entrada, saida e fala dos jogadores.

### Estrutura Interna

```text
data/chatchannels/chatchannels.xml
data/chatchannels/scripts/advertising-rook.lua
data/chatchannels/scripts/advertising.lua
data/chatchannels/scripts/englishchat.lua
data/chatchannels/scripts/gamemaster.lua
data/chatchannels/scripts/help.lua
data/chatchannels/scripts/tutor.lua
data/chatchannels/scripts/worldchat.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra canais por id, nome, visibilidade publica e script. |
| `.lua` | Implementa callbacks do canal, como `onSpeak`, `canJoin`, `onJoin` e `onLeave`. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `chatchannels.xml` | Registrador central dos canais normais. |
| `scripts/worldchat.lua` | Regras de fala do World Chat. |
| `scripts/help.lua` | Regras e orientacoes do canal Help. |
| `scripts/tutor.lua` | Regras do canal Tutor. |
| `scripts/gamemaster.lua` | Regras do canal Gamemaster. |
| `scripts/advertising-rook.lua` | Regras do canal Trade registrado atualmente no XML. |
| `scripts/advertising.lua` e `scripts/englishchat.lua` | Scripts existentes, mas nao registrados no XML atual. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/game/chat/chatLoader.cpp` | Carrega `data/chatchannels/chatchannels.xml` e os scripts em `data/chatchannels/scripts/`. |
| `src/game/chat/chat.cpp` | Controla criacao, busca, entrada, saida e fala nos canais. |
| `src/game/chat/chatChannel.cpp` | Executa callbacks Lua `canJoin`, `onJoin`, `onLeave` e `onSpeak`. |
| `src/game/chat/chatRules.cpp` | Normaliza tipos de fala para alguns canais especiais. |

### Fluxo de Execucao

```text
Startup/reload de chat
  -> ChatLoader le chatchannels.xml
     -> para cada <channel>, cria ChatChannel
     -> se houver script, carrega data/chatchannels/scripts/<script>
        -> registra callbacks Lua encontrados

Jogador fala no canal
  -> Chat::talkToChannel
     -> ChatChannel::executeOnSpeakEvent
        -> onSpeak(player, type, message)
     -> ChatChannel::talk envia mensagem aos usuarios
```

### Cuidados de Manutencao

- Todo canal novo deve ter `id` unico em `chatchannels.xml`.
- Se o canal usar script, o arquivo deve existir em `data/chatchannels/scripts`.
- Scripts podem retornar `false` para bloquear ou um novo `type` para alterar a classe da fala.
- Arquivos Lua sem registro no XML nao sao carregados pelo fluxo normal do chat.

## data/creaturescripts

### Responsabilidade

Registrar eventos ligados a players, criaturas e monstros. E um dos pontos mais sensiveis da `data`, porque intercepta login/logout, morte, loot, health change, movement, modal window e extended opcodes.

### Estrutura Interna

```text
data/creaturescripts/creaturescripts.xml
data/creaturescripts/lib/creaturescripts.lua
data/creaturescripts/scripts/*.lua
data/creaturescripts/bkup.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra eventos por `type`, `name` e `script`. |
| `.lua` | Implementa callbacks como `onLogin`, `onLogout`, `onDeath`, `onPostDeath`, `onHealthChange`, `onMove`, `onModalWindow` e `onExtendedOpcode`. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `creaturescripts.xml` | Registrador central dos creature events. |
| `lib/creaturescripts.lua` | Lib especifica do modulo, carregada antes dos scripts pelo `BaseEvents`. Atualmente e pequena. |
| `scripts/login.lua` | Inicializacao do player no login, registro de eventos, questlog, estados Pokemon e correcoes de estado. |
| `scripts/logout.lua` | Tratamento de saida do player. |
| `scripts/playerdeath.lua` | Regras de morte do player. |
| `scripts/corpselevel.lua` e `scripts/corpseloot.lua` | Regras de corpse e loot pos-morte. |
| `scripts/monsterdeath.lua` | Regras de morte de monstros. |
| `scripts/monsterhealthchange.lua` | Regras de dano, resistencias, imunidades e tipos Pokemon em health change. |
| `scripts/extendedopcode.lua` | Entrada de opcodes estendidos do client. |
| `scripts/flyevent.lua`, `scripts/walkevent.lua`, `scripts/removesummon.lua` | Eventos de movimento/estado. |
| `bkup.lua` e `scripts/bkup corpseloot.lua` | Backups internos de scripts; nao sao carregados pelo XML atual. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/baseevents.cpp` | Carrega `data/creaturescripts/lib/creaturescripts.lua`, `creaturescripts.xml` e scripts registrados. |
| `src/scripting/creatureevent/creatureEventManager.cpp` | Gerencia registro e disparo dos eventos. |
| `src/scripting/creatureevent/creatureEventConfig.cpp` | Converte `type` do XML para enum C++ e define o nome do callback Lua esperado. |
| `src/scripting/creatureevent/creatureEventPlayer.cpp` | Executa callbacks de login/logout. |
| `src/scripting/creatureevent/creatureEventDeath.cpp` | Executa callbacks de death/postdeath. |
| `src/scripting/creatureevent/creatureEventCombat.cpp` | Executa callbacks de health/manachange. |
| `src/scripting/creatureevent/creatureEventMisc.cpp` | Executa modalwindow, extendedopcode e move. |
| `src/entities/monster/monster.cpp` | Registra creature events declarados por monstros. |
| `src/scripting/lua/player/*` | Expoe APIs Lua como `player:registerEvent(...)`. |

### Fluxo de Execucao

```text
Startup/reload de creaturescripts
  -> BaseEvents usa getScriptBaseName() = "creaturescripts"
  -> carrega data/creaturescripts/lib/creaturescripts.lua
  -> le data/creaturescripts/creaturescripts.xml
  -> para cada <event>, configura tipo/nome/script
  -> valida callback esperado no Lua
  -> registra CreatureEvent por nome

Durante o jogo
  -> source detecta evento de player/creature/monster
  -> CreatureEvents procura eventos registrados do tipo correto
  -> CreatureEvent executa callback Lua correspondente
```

Exemplo importante:

```text
login.lua
  -> onLogin(player)
  -> player:registerEvent("PlayerDeath")
  -> player:registerEvent("DropLoot")
  -> player:registerEvent("MonsterHealthChange")
  -> player:registerEvent("WalkEvent")
```

### Cuidados de Manutencao

- O atributo `type` do XML precisa existir em `CreatureEvent::configureEvent`.
- O script deve declarar o callback esperado pelo tipo, por exemplo `onLogin` para `type="login"` e `onHealthChange` para `type="healthchange"`.
- Eventos usados via `player:registerEvent("Nome")` precisam existir com o mesmo `name` em `creaturescripts.xml`.
- Scripts de login e healthchange tem alto impacto e devem ser alterados com muita cautela.
- Arquivos de backup dentro da pasta nao sao carregados se nao estiverem registrados no XML.

## data/events

### Responsabilidade

Registrar hooks Lua por classe/metodo para entidades centrais do jogo. Diferente de `creaturescripts`, que registra eventos nomeados por XML e pode ser associado via `registerEvent`, esta pasta trabalha com metodos Lua ligados as metatables `Creature`, `Party`, `Player` e `Monster`.

### Estrutura Interna

```text
data/events/events.xml
data/events/scripts/creature.lua
data/events/scripts/monster.lua
data/events/scripts/party.lua
data/events/scripts/player.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Habilita/desabilita metodos por classe e nome do callback. |
| `.lua` | Implementa metodos no formato `Classe:metodo(...)`, como `Player:onLook(...)` e `Monster:onSpawn(...)`. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `events.xml` | Registrador central dos hooks por classe/metodo. |
| `scripts/player.lua` | Hooks de player: look, move item, trade, turn, gain experience, skill tries e outros. |
| `scripts/monster.lua` | Hook de spawn de monstros; ajusta vida, formas especiais, bosses, mega/tera e lendarios. |
| `scripts/creature.lua` | Hooks gerais de criaturas, como outfit e combate. |
| `scripts/party.lua` | Hooks de party; atualmente os metodos de party estao desabilitados no XML. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/events/events.cpp` | Carrega `data/events/events.xml`, carrega `data/events/scripts/<classe>.lua` e guarda IDs dos metodos habilitados. |
| `src/scripting/events/eventsPlayer*.cpp` | Executa hooks de `Player`. |
| `src/scripting/events/eventsCreature*.cpp` | Executa hooks de `Creature`. |
| `src/scripting/events/eventsMonster.cpp` | Executa hooks de `Monster`. |
| `src/scripting/events/eventsParty.cpp` | Executa hooks de `Party`. |
| `src/game/*`, `src/entities/*` | Chamam `g_events` nos pontos de gameplay correspondentes. |

### Fluxo de Execucao

```text
Startup/reload de events
  -> Events::load le data/events/events.xml
  -> para cada classe habilitada, carrega data/events/scripts/<classe>.lua
  -> busca o metodo na metatable Lua
  -> salva o id do callback em EventsInfo

Durante o jogo
  -> source chama g_events->event<Class><Method>(...)
  -> Events empilha userdata/metatable C++
  -> executa Classe:metodo(...) no Lua
```

Exemplo:

```text
Player olha item/criatura
  -> source chama eventPlayerOnLook
  -> Player:onLook(thing, position, distance)
  -> script monta descricao customizada Pokemon/item/player
```

### Cuidados de Manutencao

- O `class` e o `method` no XML precisam bater exatamente com os nomes esperados em `Events::load`.
- O arquivo Lua carregado e definido pelo nome da classe em minusculo: `Player` -> `player.lua`.
- Se `enabled="0"`, o metodo nao e carregado nem executado.
- `player.lua` e `monster.lua` sao pontos de alto impacto, pois alteram descricao, movimentacao, trade, experiencia e spawn.
- Eventos daqui nao usam `player:registerEvent`; isso pertence a `creaturescripts`.

## data/globalevents

### Responsabilidade

Registrar eventos globais executados no startup, por record, por horario fixo ou por intervalo. Sao usados para rotinas operacionais e sistemas globais, como server save, broadcast, save periodico, record, shiny collector e inicializacao do servidor.

### Estrutura Interna

```text
data/globalevents/globalevents.xml
data/globalevents/lib/globalevents.lua
data/globalevents/scripts/broadcast.lua
data/globalevents/scripts/globalsave.lua
data/globalevents/scripts/kingoftheforest.lua
data/globalevents/scripts/pokepark.lua
data/globalevents/scripts/record.lua
data/globalevents/scripts/serversave.lua
data/globalevents/scripts/shinycollector.lua
data/globalevents/scripts/soccerevent.lua
data/globalevents/scripts/startup.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra eventos globais por `type`, `time` ou `interval`. |
| `.lua` | Implementa callbacks globais, como `onStartup`, `onRecord`, `onTime` e `onThink`. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `globalevents.xml` | Registrador central dos eventos globais. |
| `lib/globalevents.lua` | Lib especifica do modulo, carregada pelo `BaseEvents`; atualmente vazia. |
| `scripts/startup.lua` | Rotinas de startup: limpeza de tabelas, bans expiridos, auctions, spawn inicial e reset semanal. |
| `scripts/serversave.lua` | Rotina agendada de server save as 06:00. |
| `scripts/shinycollector.lua` | Evento horario do Shiny Collector. |
| `scripts/broadcast.lua` | Broadcast periodico por intervalo. |
| `scripts/globalsave.lua` | Save global periodico por intervalo. |
| `scripts/record.lua` | Evento de record de jogadores online. |
| `scripts/kingoftheforest.lua`, `pokepark.lua`, `soccerevent.lua` | Scripts existentes, mas nem todos estao ativos no XML atual. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/baseevents.cpp` | Carrega `data/globalevents/lib/globalevents.lua`, `globalevents.xml` e scripts registrados. |
| `src/scripting/globalevent.cpp` | Configura tipos, horarios, intervalos, scheduler e execucao dos callbacks. |
| `src/scripting/globalevent.hpp` | Define `getScriptBaseName() = "globalevents"`. |
| `src/core/scheduler.*` | Agenda eventos de intervalo e horario. |
| `src/app/signals.cpp` e `src/game/commands/commands.cpp` | Permitem reload de globalevents. |

### Fluxo de Execucao

```text
Startup/reload de globalevents
  -> BaseEvents usa getScriptBaseName() = "globalevents"
  -> carrega lib/globalevents.lua
  -> le globalevents.xml
  -> GlobalEvent::configureEvent interpreta:
       type="startup" / type="record"
       time="HH:MM:SS"
       interval="milliseconds"
  -> registra em serverMap, timerMap ou thinkMap

Execucao
  -> startup/record sao chamados por tipo
  -> time roda pelo timer diario
  -> interval roda pelo scheduler recorrente
```

### Cuidados de Manutencao

- `name` deve ser unico; duplicados sao rejeitados com warning.
- Eventos com `time` usam horario diario; se o horario ja passou, ficam para o proximo dia.
- Eventos com `interval` usam milissegundos.
- Scripts de startup podem tocar banco, spawns e estado global; revisar com cautela.
- Comentarios no XML desativam eventos mesmo que o script exista.

## data/items

### Responsabilidade

Definir o catalogo de itens do servidor. `items.otb` fornece a base binaria dos tipos de item, enquanto `items.xml` complementa nomes, atributos, slots, descricoes, transformacoes, decays, containers, corpos, armas, runas e propriedades usadas pela engine e pelos scripts.

### Estrutura Interna

```text
data/items/items.otb
data/items/items.xml
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.otb` | Base binaria de tipos de item, carregada antes do XML. |
| `.xml` | Complementa e sobrescreve atributos dos itens por `id` ou intervalo `fromid/toid`. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `items.otb` | Catalogo base de ids e propriedades binaria dos itens. |
| `items.xml` | Catalogo textual de atributos, nomes e configuracoes especificas. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/app/otserv.cpp` | No boot, carrega `data/items/items.otb` e depois `data/items/items.xml` antes dos sistemas de script. |
| `src/items/items/itemsCore.cpp` | Controla reload de itens e recarrega movements/weapons depois do reload. |
| `src/items/items/itemsXmlLoader.cpp` | Faz parse de `items.xml` e popula `ItemType`. |
| `src/items/item/*` | Usa `ItemType` para comportamento, descricao, serializacao, decay e atributos. |
| `src/game/movement/*` e `src/game/weapons/*` | Dependem dos dados de item para movement events e armas. |
| `src/scripting/lua/item/*` | Expoe `Item` e `ItemType` para Lua. |

### Fluxo de Execucao

```text
Boot do servidor
  -> Item::items.loadFromOtb("data/items/items.otb")
  -> Item::items.loadFromXml()
     -> le data/items/items.xml
     -> para cada <item id="..."> ou <item fromid="..." toid="...">
     -> parseItemNode atualiza ItemType

Runtime
  -> source e scripts consultam ItemType/Item
  -> actions, movements, weapons, containers e descricoes usam os atributos carregados
```

### Cuidados de Manutencao

- `items.otb` e `items.xml` precisam estar consistentes; id inexistente no OTB pode nao produzir efeito util no XML.
- Ao alterar slots customizados como `order` e `info`, conferir tambem a source de inventario/equipamento.
- Mudancas de `decayTo`, `duration`, `transformEquipTo`, `transformDeEquipTo` e `containerSize` podem afetar gameplay e persistencia.
- Atributos usados por scripts devem manter nomes estaveis para nao quebrar actions/movements/spells.
- Como itens carregam antes dos scripts, erro em `items.otb` ou `items.xml` pode impedir o servidor de subir.

## data/lib

### Responsabilidade

Fornecer a base Lua compartilhada por praticamente todos os scripts da `data`. Esta pasta contem helpers globais, extensoes de metatables, wrappers para a API C++ e uma camada grande de compatibilidade com a API antiga.

### Estrutura Interna

```text
data/lib/lib.lua
data/lib/core/constants.lua
data/lib/core/container.lua
data/lib/core/core.lua
data/lib/core/creature.lua
data/lib/core/game.lua
data/lib/core/item.lua
data/lib/core/itemtype.lua
data/lib/core/item_attributes.lua
data/lib/core/lib.lua
data/lib/core/newfunctions.lua
data/lib/core/player.lua
data/lib/core/position.lua
data/lib/core/string.lua
data/lib/core/tables.lua
data/lib/core/teleport.lua
data/lib/core/tile.lua
data/lib/compat/compat.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.lua` | Bibliotecas globais, helpers de metatable, funcoes utilitarias, aliases e compatibilidade com scripts antigos. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `lib.lua` | Agregador principal chamado por `data/global.lua`. |
| `core/core.lua` | Agregador das libs core. |
| `core/newfunctions.lua` | Maior arquivo da lib; concentra muitas funcoes customizadas do projeto. |
| `compat/compat.lua` | Camada de compatibilidade com API antiga, incluindo aliases `do*`, `get*`, constantes antigas e ajustes de metatable. |
| `core/player.lua`, `core/creature.lua`, `core/item.lua`, `core/game.lua` | Extensoes Lua para classes expostas pela source. |
| `core/item_attributes.lua` | Helpers/constantes de atributos customizados de item. |
| `core/tables.lua` | Tabelas compartilhadas usadas por sistemas Lua. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/scriptmanager.cpp` | Carrega `data/global.lua`, que chama `data/lib/lib.lua`. |
| `src/scripting/lua/*` | Expoe classes, metatables e funcoes C++ consumidas pelas libs. |
| `src/scripting/lua/registry/*` | Registra globais/metodos que `compat.lua` e `core/*.lua` usam. |
| Todos os modulos Lua | Herdam o ambiente preparado por `global.lua` e `data/lib`. |

### Fluxo de Execucao

```text
ScriptingManager
  -> data/global.lua
     -> data/lib/lib.lua
        -> data/lib/core/core.lua
           -> constants/container/creature/game/item/itemtype/player/position/teleport/tile
           -> item_attributes/newfunctions/string
        -> data/lib/compat/compat.lua
```

### Cuidados de Manutencao

- Alteracoes aqui sao de alto impacto, pois afetam scripts de actions, movements, spells, NPCs, events e creaturescripts.
- Evitar adicionar regra de negocio muito especifica na lib global; preferir `data/<modulo>/lib` quando o helper for local.
- `compat.lua` altera metatables e cria aliases antigos; remover funcoes pode quebrar scripts legados.
- `core/newfunctions.lua` e grande e deve ser analisado com cuidado antes de refatorar.
- `core/lib.lua` esta vazio; antes de remover, confirmar se algum fluxo externo depende do arquivo existir.

## data/logs

### Responsabilidade

Reservar uma pasta para logs gerados em runtime pelo servidor. O repositorio mantem apenas `.gitignore`, permitindo que os arquivos de log locais nao subam para o Git.

### Estrutura Interna

```text
data/logs/.gitignore
data/logs/<player> commands.log  (gerado em runtime)
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.gitignore` | Mantem a pasta versionada, mas ignora logs gerados. |
| `.log` ou `.txt` runtime | Saidas locais geradas pelo servidor, conforme funcionalidades especificas. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `.gitignore` | Ignora tudo na pasta, exceto ele mesmo. |
| `<player> commands.log` | Arquivo produzido pela source ao registrar comandos de jogadores. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/game/commands/commandRules.cpp` | Escreve logs em `data/logs/<nome> commands.log`. |

### Fluxo de Execucao

```text
Jogador executa comando logavel
  -> commandRules.cpp monta caminho data/logs/<player> commands.log
  -> servidor escreve/append no arquivo local
  -> .gitignore impede versionamento desses logs
```

### Cuidados de Manutencao

- Nao versionar logs reais de jogadores.
- Se adicionar novos logs runtime, manter padrao de nome claro e evitar sobrescrever arquivos de outros sistemas.
- Garantir que a pasta exista no deploy; o `.gitignore` ajuda a manter a pasta no repositorio.

## data/migrations

### Responsabilidade

Guardar scripts Lua de migracao de banco de dados. Eles sao executados no startup pelo `DatabaseManager`, em ordem numerica de versao, para atualizar o schema e dados persistentes.

### Estrutura Interna

```text
data/migrations/0.lua
data/migrations/1.lua
...
data/migrations/19.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.lua` | Script de migracao com funcao `onUpdateDatabase()`. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `0.lua` a `18.lua` | Migracoes reais aplicadas sequencialmente conforme `db_version`. |
| `19.lua` | Script sentinela atual; retorna `false` para parar o processo de migracao. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/app/otserv.cpp` | Chama `DatabaseManager::updateDatabase()` durante o boot. |
| `src/persistence/databasemanager.cpp` | Cria estado Lua isolado, registra `db`/`result`, executa `data/migrations/<versao>.lua` e chama `onUpdateDatabase()`. |
| `src/scripting/lua/luascript.hpp` | Fornece bindings Lua de `db`, `result` e bit ops usados nas migrations. |

### Fluxo de Execucao

```text
Boot do servidor
  -> DatabaseManager::updateDatabase()
     -> le db_version em server_config
     -> carrega data/migrations/<db_version>.lua
     -> chama onUpdateDatabase()
        -> se retornar true:
             incrementa db_version
             tenta a proxima migration
        -> se retornar false ou erro:
             para o processo
```

### Cuidados de Manutencao

- Cada migration deve declarar `function onUpdateDatabase()` e retornar `true` quando aplicada com sucesso.
- O numero do arquivo precisa corresponder ao `db_version` esperado.
- O ultimo arquivo pode funcionar como sentinela retornando `false` para encerrar o loop.
- Migrations devem ser idempotentes quando possivel ou validar estado antes de alterar tabelas.
- Erros aqui podem impedir o servidor de subir corretamente ou deixar o banco em estado parcial.
- Evitar usar APIs de gameplay nas migrations; o ambiente Lua registrado aqui e focado em `db`, `result` e libs basicas.

## data/monster

### Responsabilidade

Definir o catalogo de monstros/Pokemon do servidor. A pasta contem um registrador central (`monsters.xml`) e XMLs individuais com status, tipos, flags, moves, ataques, evolucoes, loot, vozes e eventos de cada criatura.

### Estrutura Interna

```text
data/monster/monsters.xml
data/monster/monster list.txt
data/monster/.alola/*.xml
data/monster/.galarian/*.xml
data/monster/.hisuian/*.xml
data/monster/cloned/*.xml
data/monster/gen1/*.xml
data/monster/gen2/*.xml
data/monster/gen3/*.xml
data/monster/gen4/*.xml
data/monster/gen5/*.xml
data/monster/gen6/*.xml
data/monster/gen7/*.xml
data/monster/gen8/*.xml
data/monster/gen9/*.xml
data/monster/mega/*.xml
data/monster/shiny/*.xml
data/monster/utility/*.xml
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Define catalogo central e cada MonsterType individual. |
| `.txt` | Lista auxiliar/manual de monstros. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `monsters.xml` | Catalogo central que associa `name` a `file`. |
| `monster list.txt` | Lista auxiliar de referencia. |
| `gen*/<pokemon>.xml` | Pokemon por geracao. |
| `shiny/*.xml` | Variantes shiny. |
| `mega/*.xml` | Mega evolucoes. |
| `.alola`, `.galarian`, `.hisuian` | Formas regionais; usam ponto no inicio do nome da pasta. |
| `utility/*.xml` | Criaturas utilitarias, como turrets e objetos especiais. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/app/otserv.cpp` | Chama `g_monsters.loadFromXml()` durante o boot. |
| `src/entities/monsters/monsters.cpp` | Carrega `data/monster/monsters.xml`, percorre cada entrada e chama `loadMonster`. |
| `src/entities/monsters/monsterTypeLoader.cpp` | Faz parse do XML individual de cada monstro. |
| `src/entities/monsters/monsterSpellLoader.cpp` | Carrega attacks, defenses, spells e moves declarados no XML. |
| `src/entities/monsters/monsterLootLoader.cpp` | Faz parse da lista de loot. |
| `src/entities/monsters/monsterTypeLoot.cpp` | Gera loot em runtime a partir do MonsterType. |
| `src/entities/monster/*.cpp` | Usa `MonsterType` para comportamento individual do monstro em runtime. |
| `src/scripting/creatureevent/*` | Executa eventos declarados dentro da tag `<script>` do monstro. |

### Fluxo de Execucao

```text
Boot/reload de monstros
  -> g_monsters.loadFromXml()
     -> le data/monster/monsters.xml
     -> para cada <monster name="..." file="...">
        -> carrega data/monster/<file>
        -> MonsterTypeLoader popula MonsterType
        -> MonsterSpellLoader carrega moves/attacks/defenses
        -> MonsterLootLoader carrega loot
        -> registra creature events declarados em <script>

Runtime
  -> Game/Spawn cria Monster pelo nome
  -> Monster usa MonsterType carregado
  -> events Lua de creaturescripts podem interceptar dano, corpse, loot e death
```

### Cuidados de Manutencao

- Todo XML individual novo deve ser registrado em `monsters.xml`.
- O `name` do registrador e o `name` dentro do XML individual devem ser mantidos consistentes.
- As pastas com ponto (`.alola`, `.galarian`, `.hisuian`) podem aparecer ocultas em alguns editores.
- Alterar `race`, `race2`, flags, corpse, moves ou loot afeta gameplay, balanceamento e scripts como catch/loot/dano.
- Eventos declarados em `<script><event name="..."/></script>` precisam existir em `data/creaturescripts/creaturescripts.xml`.
- Se usar atributo `script` no XML do monstro, a source tenta carregar em `data/monster/scripts/<script>`.

## data/movements

### Responsabilidade

Registrar eventos disparados por movimento, tiles, itens, equipamentos e alteracoes de item em tile. Controla portas, quest doors, level doors, traps, surf/swimming, dive, drowning, citizen teleports, tiles especiais, equip/deequip e sistemas customizados.

### Estrutura Interna

```text
data/movements/movements.xml
data/movements/lib/movements.lua
data/movements/scripts/*.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra `movevent` por evento, item id, action id, unique id, posicao ou intervalo. |
| `.lua` | Implementa callbacks `onStepIn`, `onStepOut`, `onEquip`, `onDeEquip`, `onAddItem` e `onRemoveItem`. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `movements.xml` | Registrador central dos move events. |
| `lib/movements.lua` | Lib especifica do modulo; atualmente vazia/placeholder. |
| `scripts/swimming.lua` | Entrada/saida de surf e controle de outfit/velocidade. |
| `scripts/dive.lua` e `scripts/drowning.lua` | Regras de dive e dano/estado em agua. |
| `scripts/opendoor.lua`, `closingdoor.lua`, `quest_door.lua`, `level_door.lua` | Portas e restricoes de acesso. |
| `scripts/pokeball.lua` | Equip/deequip de pokeball/slot. |
| `scripts/train.lua`, `trap.lua`, `tiles.lua`, `citizen.lua` | Tiles de treino, armadilhas, depot/level/citizen e comportamento de tile. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/baseevents.cpp` | Carrega `data/movements/lib/movements.lua`, `movements.xml` e scripts registrados. |
| `src/game/movement/movement.cpp` | Registra eventos por item, action id, unique id e posicao. |
| `src/game/movement/movementEventConfig.cpp` | Interpreta `event`, `slot`, level, maglevel, premium, vocation e callbacks esperados. |
| `src/game/movement/movementEventHandlers.cpp` | Executa callbacks Lua e funcoes built-in. |
| `src/items/items/itemsCore.cpp` | Ao recarregar itens, tambem recarrega movements. |
| `src/entities/player/playerInventory.cpp` | Consulta move events ao equipar itens. |

### Fluxo de Execucao

```text
Startup/reload de movements
  -> BaseEvents usa getScriptBaseName() = "movements"
  -> carrega lib/movements.lua
  -> le movements.xml
  -> para cada <movevent>, configura tipo e destino:
       itemid/fromid, actionid/fromaid, uniqueid/fromuid, pos
  -> carrega script Lua ou funcao built-in

Runtime
  -> jogador pisa/sai/equipa/adiciona/remove item
  -> source procura MoveEvent nos mapas registrados
  -> executa onStepIn/onStepOut/onEquip/onDeEquip/onAddItem/onRemoveItem
```

### Cuidados de Manutencao

- O atributo `event` precisa ser um dos aceitos pela source: `StepIn`, `StepOut`, `Equip`, `DeEquip`, `AddItem`, `RemoveItem`.
- Registros com `script` exigem arquivo em `data/movements/scripts`.
- Registros com `function` chamam handlers built-in da source, como `onStepInField`, `onEquipItem` e `onDeEquipItem`.
- Em `Equip`/`DeEquip`, o atributo `slot` precisa bater com slots aceitos pela source, incluindo customizados `order` e `info`.
- `movements.xml` e grande; preferir manter blocos comentados por dominio para evitar duplicidade e conflito de ids.

## data/npc

### Responsabilidade

Definir NPCs, seus XMLs, scripts Lua e framework de conversacao/shop. Cada NPC costuma ter um XML na raiz apontando para um script em `scripts/`, enquanto `lib/npc.lua` carrega o sistema compartilhado de NPC.

### Estrutura Interna

```text
data/npc/<Npc Name>.xml
data/npc/scripts/*.lua
data/npc/lib/npc.lua
data/npc/lib/npcsystem/npcsystem.lua
data/npc/lib/npcsystem/npchandler.lua
data/npc/lib/npcsystem/modules.lua
data/npc/lib/npcsystem/keywordhandler.lua
data/npc/lib/npcsystem/customModules.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Define nome, script, look, health, walk interval/radius, parametros e propriedades do NPC. |
| `.lua` | Implementa callbacks e comportamento de conversa, shop, quests, heal, trade e sistemas customizados. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `lib/npc.lua` | Lib principal de NPC; carrega `npcsystem` e helpers de compra/venda/fala. |
| `lib/npcsystem/npcsystem.lua` | Entrada do sistema avancado de NPC. |
| `lib/npcsystem/npchandler.lua` | Gerencia foco, mensagens, callbacks e fluxo de conversa. |
| `lib/npcsystem/modules.lua` | Modulos reutilizaveis do sistema de NPC. |
| `lib/npcsystem/customModules.lua` | Modulos customizados do projeto. |
| `scripts/healer.lua` | Exemplo de NPC healer usado por `Nurse.xml`. |
| `scripts/default.lua` | Script padrao simples para NPCs genericos. |
| XMLs na raiz | Cada arquivo define um NPC carregavel pelo nome. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/entities/npc/npc.cpp` | Cria NPC por nome e monta caminho `data/npc/<name>.xml`; carrega `data/npc/lib/npc.lua`. |
| `src/entities/npc/npcLoader.cpp` | Faz parse do XML de NPC: atributos, look, health, parametros e script. |
| `src/entities/npc/npcEventsHandler.cpp` | Carrega `data/npc/scripts/<script>` e executa callbacks. |
| `src/entities/npc/npcLuaActions.cpp` e `npcLuaShop.cpp` | Expoem funcoes/metodos Lua especificos de NPC. |
| `src/entities/npc/npcShop.cpp` | Integra shop do NPC com o jogo. |
| `src/game/game/*` e mapa/spawn | Criam/posicionam NPCs pelo nome definido no XML/mapa. |

### Fluxo de Execucao

```text
Criacao de NPC
  -> Npc::createNpc(name)
     -> filename = data/npc/<name>.xml
     -> carrega data/npc/lib/npc.lua uma vez
     -> Npc::loadFromXml()
        -> le atributos do XML
        -> carrega data/npc/scripts/<script>
        -> registra callbacks:
             onCreatureAppear
             onCreatureDisappear
             onCreatureMove
             onCreatureSay
             onThink

Runtime
  -> jogador aparece/fala/sai/perto do NPC
  -> NpcEventsHandler chama callback Lua
  -> npcHandler/KeywordHandler/module processam conversa e respostas
```

### Cuidados de Manutencao

- O nome usado para criar/spawnar NPC precisa corresponder ao XML `data/npc/<name>.xml`.
- O atributo `script` do XML aponta para `data/npc/scripts/<script>`.
- Scripts com `NpcHandler` devem declarar os callbacks padrao (`onCreatureAppear`, `onCreatureDisappear`, `onCreatureSay`, `onThink`).
- Alteracoes em `lib/npcsystem` afetam muitos NPCs ao mesmo tempo.
- Manter consistencia entre maiusculas/minusculas de nomes de arquivo, especialmente para deploy em sistemas case-sensitive.
- NPCs com shop, quest ou sistemas Pokemon devem ser testados no fluxo de fala real, nao apenas por parse do XML.

## data/raids

### Responsabilidade

Definir raids/eventos temporizados do servidor. A pasta contem um registrador central (`raids.xml`) e arquivos XML individuais que descrevem a sequencia de eventos da raid, como anuncios, spawns em area, spawns pontuais e scripts customizados.

### Estrutura Interna

```text
data/raids/raids.xml
data/raids/poke/*.xml
```

Observacao: a source tambem suporta `data/raids/scripts/*.lua` para eventos `<script>`, mas essa pasta nao existe no estado atual do projeto.

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra raids e define eventos temporizados de cada raid. |
| `.lua` | Suportado pela source para eventos de raid com callback `onRaid`, caso a pasta `scripts` seja criada. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `raids.xml` | Registrador central com `<raid name="..." file="..." interval2="..." margin="..." />`. |
| `poke/rattata.xml` | Exemplo de raid com anuncios e areaspawn em Saffron. |
| `poke/aquatica.xml`, `raikou.xml`, `christmas.xml` | Exemplos de raids tematicas/eventos especiais. |
| `poke/arena*.xml` | Raids de arena/lendarios. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/game/game/gameState.cpp` | Carrega `g_game.raids.loadFromXml()` no boot/reload de estado. |
| `src/game/raids/raidLoader.cpp` | Le `data/raids/raids.xml`, valida `name`, `file`, `interval2`, `margin` e `repeat`. |
| `src/game/raids/raid.cpp` | Carrega o XML individual e agenda os eventos da raid. |
| `src/game/raids/raidEvent.cpp` | Implementa `announce`, `singlespawn`, `areaspawn` e `script`. |
| `src/scripting/lua/luaBindingsGame.cpp` | Expoe `Game.startRaid(raidName)` para Lua. |
| `src/scripting/lua/registry/luaGlobalFunctionsRegistryGameWorld.cpp` | Registra `Game.startRaid` no ambiente Lua. |

### Fluxo de Execucao

```text
Startup/reload
  -> g_game.raids.loadFromXml()
     -> RaidLoader le data/raids/raids.xml
     -> para cada <raid> ativo:
        -> carrega data/raids/<file>
        -> cria eventos announce/singlespawn/areaspawn/script
        -> ordena eventos por delay

Runtime
  -> sistema automatico ou Game.startRaid(nome)
  -> Raid::startRaid agenda o primeiro evento
  -> scheduler executa cada evento pelo delay relativo
  -> announce envia broadcast
  -> spawn cria Monster e posiciona no mapa
```

### Cuidados de Manutencao

- No estado atual, todos os registros em `raids.xml` estao comentados; os XMLs individuais existem, mas nao rodam automaticamente se nao forem ativados.
- `interval2` e convertido para segundos na source; valor zero ou ausente invalida a raid.
- `margin` e convertido para milissegundos e controla a janela aleatoria de execucao.
- Monstros usados em `singlespawn` e `areaspawn` precisam existir em `data/monster`.
- Coordenadas precisam apontar para areas validas, livres e coerentes com protecao/colisao do mapa.
- Eventos `<script>` exigem arquivo em `data/raids/scripts` e callback `onRaid`.

## data/reports

### Responsabilidade

Armazenar reports gerados em runtime por jogadores autorizados. Diferente das pastas de configuracao, `reports` e uma pasta operacional: os arquivos sao criados pelo servidor durante execucao e nao devem ser versionados.

### Estrutura Interna

```text
data/reports/.gitignore
data/reports/<Player Name> report.txt   (gerado em runtime)
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.gitignore` | Mantem a pasta no repositorio e ignora reports gerados. |
| `.txt` | Arquivos de report por jogador, criados pela source em runtime. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `.gitignore` | Ignora tudo dentro de `data/reports`, exceto o proprio `.gitignore`. |
| `<Player Name> report.txt` | Arquivo append-only com reports daquele jogador. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/network/protocolgame/protocolgame.cpp` | Direciona pacote `0xE6` para parse de bug report. |
| `src/network/protocolgame/protocolgameParse.cpp` | Le mensagem, posicao e categoria do report recebido do client. |
| `src/game/game/gameReports.cpp` | Implementa `Game::playerReportBug` e escreve em `data/reports/<player> report.txt`. |
| `src/core/enums.hpp` | Define categorias como `BUG_CATEGORY_MAP`. |

### Fluxo de Execucao

```text
Client envia bug report
  -> ProtocolGame::parseBugReport()
     -> agenda Game::playerReportBug(playerId, message, position, category)
        -> valida player e account type
        -> abre data/reports/<player> report.txt em append
        -> escreve nome, posicao e comentario
        -> confirma envio ao jogador
```

### Cuidados de Manutencao

- Reports gerados nao sobem para o Git por causa do `.gitignore`.
- Apenas contas acima de `ACCOUNT_TYPE_NORMAL` conseguem gerar report pela implementacao atual.
- O nome do arquivo usa o nome do player; nomes incomuns podem afetar organizacao/compatibilidade no filesystem.
- A escrita usa append em arquivo texto, entao a pasta precisa existir e ter permissao de escrita no ambiente de producao.
- O conteudo pode conter dados operacionais do mapa/player; tratar como arquivo de administracao, nao como configuracao.

## data/spells

### Responsabilidade

Registrar e implementar magias, moves, runas, conjures, spells de monstros e passivas. E uma das pastas mais pesadas de script Lua: `spells.xml` faz o registro central e os arquivos em `scripts/` implementam `onCastSpell`.

### Estrutura Interna

```text
data/spells/spells.xml
data/spells/lib/spells.lua
data/spells/scripts/attack/*.lua
data/spells/scripts/custom/*.lua
data/spells/scripts/healing/*.lua
data/spells/scripts/monster/*.lua
data/spells/scripts/moves/**/*.lua
data/spells/scripts/party/*.lua
data/spells/scripts/passives/*.lua
data/spells/scripts/support/*.lua
data/spells/scripts/test/*.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra `<instant>`, `<rune>` e `<conjure>` com palavras, custos, cooldowns, flags e script/function. |
| `.lua` | Implementa `onCastSpell(creature, variant)` ou variantes com `isHotkey`. |

### Arquivos Principais

| Arquivo/Pasta | Funcao |
|---|---|
| `spells.xml` | Registrador central com 678 entradas entre instant/rune/conjure. |
| `lib/spells.lua` | Lib compartilhada de areas/constantes usadas por scripts de spell. |
| `scripts/moves` | Maior grupo de scripts, com moves Pokemon separados por tipo. |
| `scripts/attack` | Magias ofensivas gerais. |
| `scripts/healing` | Cura e remocao de condicoes. |
| `scripts/support` | Runas e suporte utilitario. |
| `scripts/monster` | Spells usadas por monstros via `words="###..."`. |
| `scripts/passives` | Efeitos passivos por tipo. |
| `scripts/custom`, `party`, `test` | Scripts especiais, party e testes. |

### Distribuicao Atual de Scripts Lua

| Pasta | Quantidade |
|---|---:|
| `attack` | 74 |
| `custom` | 5 |
| `healing` | 22 |
| `monster` | 49 |
| `moves` | 601 |
| `party` | 4 |
| `passives` | 13 |
| `support` | 22 |
| `test` | 1 |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/scriptmanager.cpp` | Cria `g_spells` e chama `g_spells->loadFromXml()`. |
| `src/scripting/baseevents.cpp` | Carrega `data/spells/lib/spells.lua`, `spells.xml` e scripts/function registrados. |
| `src/game/spells/spells.cpp` | Define `getScriptBaseName() = "spells"`, cria eventos `rune`, `instant`, `conjure` e registra mapas de spells. |
| `src/game/spells/instantSpell.cpp` | Executa instant spells, parseia `words`, target/direction/param e chama `onCastSpell`. |
| `src/game/spells/runeSpell.cpp` | Executa runas por item id e integra com actions/use. |
| `src/game/spells/conjureSpell.cpp` | Implementa conjure de item/runa. |
| `src/game/spells/spellChecks.cpp` | Valida level, mana, cooldown, premium, vocacao, target e learn. |
| `src/scripting/talkaction.cpp` | Encaminha fala do jogador para `playerSaySpell`. |
| `src/entities/monsters/monsterSpellLoader.cpp` | Carrega spells de monstros e scripts em `data/spells/scripts`. |
| `src/items/item/itemDescription.cpp` | Usa dados de rune spell para descricao de itens. |
| `src/persistence/login/*` | Carrega/salva lista de instant spells aprendidas. |

### Fluxo de Execucao

```text
Startup/reload
  -> g_spells->loadFromXml()
     -> BaseEvents carrega data/spells/lib/spells.lua
     -> le data/spells/spells.xml
     -> para cada <instant>, <rune> ou <conjure>:
        -> configura Spell/TalkAction/Action
        -> carrega script Lua ou function built-in
        -> registra por words ou rune item id

Jogador usa spell por fala
  -> TalkActions::playerSaySpell()
  -> Spells::playerSaySpell()
  -> InstantSpell::playerCastInstant()
  -> valida checks e executa onCastSpell

Jogador usa rune
  -> Actions encontra RuneSpell pelo item id
  -> RuneSpell::executeUse()
  -> valida checks e executa script/function

Monstro usa spell
  -> MonsterSpellLoader associa spell ao MonsterType
  -> MonsterThink escolhe spell em combate
  -> CombatSpell/InstantSpell executa efeito
```

### Cuidados de Manutencao

- `script` em `spells.xml` aponta para `data/spells/scripts/<script>`.
- Registros sem `script` precisam usar `function` reconhecida pela source.
- `words` deve ser unico para instant spells; duplicidade gera warning em `Spells::registerEvent`.
- Runas sao registradas por `id`; duplicidade de id tambem gera warning.
- `needlearn`, `lvl`, `mana`, `cooldown`, `groupcooldown`, `range`, `needtarget`, `direction` e `blockwalls` mudam diretamente gameplay e UX.
- Moves Pokemon usam muitos nomes com espacos no caminho; cuidar ao renomear arquivos/scripts.
- Scripts de spell devem expor `onCastSpell`; se o callback nao existir, `Event::checkScript` falha no carregamento.

## data/talkactions

### Responsabilidade

Registrar comandos executados por fala do jogador. A pasta concentra comandos administrativos (`/ban`, `/goto`, `/i`, `/m`), comandos de jogador (`!online`, `!catch`, `!autoloot`) e comandos customizados do servidor Pokemon (`#tmsystem`, `#storebuy`, `#rodsystem`, moves `m1` a `m12`).

### Estrutura Interna

```text
data/talkactions/talkactions.xml
data/talkactions/lib/talkactions.lua
data/talkactions/scripts/*.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra comandos `<talkaction>` com `words`, `separator` e `script`. |
| `.lua` | Implementa callback `onSay(player, words, param, type)`. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `talkactions.xml` | Registrador central; possui 104 comandos ativos no estado atual. |
| `lib/talkactions.lua` | Lib do modulo; atualmente placeholder (`-- Nothing --`). |
| `scripts/#tmsystem.lua` | Sistema grande de TM; arquivo mais pesado da pasta. |
| `scripts/summonspells.lua` | Integra comandos `m1` a `m12` com moves do summon. |
| `scripts/#storebuy.lua` | Compra/entrega via store. |
| `scripts/create_item.lua`, `place_monster.lua`, `place_npc.lua` | Comandos administrativos de criacao/spawn. |
| `scripts/teleport_*.lua`, `fly.lua` | Movimentacao/teleporte por comando. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/scriptmanager.cpp` | Cria `g_talkActions` e chama `loadFromXml()`. |
| `src/scripting/baseevents.cpp` | Carrega `data/talkactions/lib/talkactions.lua`, `talkactions.xml` e scripts. |
| `src/scripting/talkaction.cpp` | Registra comandos, parseia `words`/`separator` e executa `onSay`. |
| `src/game/game/gamePlayerChat.cpp` | Encaminha falas do jogador para talkactions/spells/chat. |
| `src/entities/player/*` | Muitas funcoes Lua usadas pelos scripts alteram estado do player, summon, itens e storages. |

### Fluxo de Execucao

```text
Startup/reload
  -> g_talkActions->loadFromXml()
     -> BaseEvents carrega lib/talkactions.lua
     -> le talkactions.xml
     -> cada <talkaction> cria TalkAction
     -> carrega data/talkactions/scripts/<script>

Runtime
  -> jogador fala uma mensagem
  -> Game/Protocol encaminha para TalkActions::playerSaySpell()
  -> compara prefixo com words
  -> extrai param usando separator
  -> executa onSay(player, words, param, type)
```

### Cuidados de Manutencao

- `words` funciona como prefixo; comandos parecidos podem conflitar se a ordem/parametros nao forem pensados.
- `separator=" "` e comum para comandos com parametros; sem separator, o script recebe parametro apenas se a fala casar com a regra da source.
- Scripts devem declarar `function onSay(player, words, param, type)`.
- Comandos administrativos devem validar permissao/grupo dentro do script quando necessario.
- Arquivos com `#` e `!` no nome exigem cuidado ao manipular por shell ou ferramentas externas.
- Sistemas grandes como `#tmsystem.lua` merecem testes funcionais antes de qualquer reorganizacao.

## data/weapons

### Responsabilidade

Registrar comportamento e restricoes de armas. A pasta define armas melee, distance e wand/rod, incluindo level minimo, mana, vocacao, dano elemental, break chance, scripts customizados e acoes como remover carga.

### Estrutura Interna

```text
data/weapons/weapons.xml
data/weapons/lib/weapons.lua
data/weapons/scripts/burst_arrow.lua
data/weapons/scripts/poison_arrow.lua
data/weapons/scripts/viper_star.lua
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Registra `<melee>`, `<distance>` e `<wand>` por item id. |
| `.lua` | Implementa `onUseWeapon(player, variant)` para armas scriptadas. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `weapons.xml` | Registrador central; possui 293 entradas de arma no estado atual. |
| `lib/weapons.lua` | Lib do modulo; atualmente vazia. |
| `scripts/burst_arrow.lua` | Comportamento customizado de flecha explosiva. |
| `scripts/poison_arrow.lua` | Comportamento customizado de flecha venenosa. |
| `scripts/viper_star.lua` | Comportamento customizado de estrela/arremesso. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/scripting/scriptmanager.cpp` | Cria `g_weapons` e chama `loadFromXml()`. |
| `src/scripting/baseevents.cpp` | Carrega `data/weapons/lib/weapons.lua`, `weapons.xml` e scripts. |
| `src/game/weapons/weapons.cpp` | Define `getScriptBaseName() = "weapons"`, cria `WeaponMelee`, `WeaponDistance` e `WeaponWand`. |
| `src/game/weapons/weapon.cpp` | Parseia requisitos, vocacoes, action, enabled, unproperly e executa `onUseWeapon`. |
| `src/game/weapons/weaponMelee.cpp` | Calcula dano melee e skill correspondente. |
| `src/game/weapons/weaponDistance.cpp` | Calcula distancia, ammo, hit chance e dano ranged. |
| `src/game/weapons/weaponWand.cpp` | Configura `min`, `max` e tipo elemental de wand/rod. |
| `src/entities/player/playerCombat.cpp` | Usa `g_weapons` no combate do jogador. |
| `src/items/items/itemsCore.cpp` | Recarrega weapons quando itens sao recarregados. |

### Fluxo de Execucao

```text
Startup/reload
  -> g_weapons->loadFromXml()
     -> BaseEvents carrega lib/weapons.lua
     -> le weapons.xml
     -> cria WeaponMelee/WeaponDistance/WeaponWand
     -> configura requisitos, vocacao e comportamento
     -> registra por item id
     -> loadDefaults cobre armas do items.xml/otb nao registradas explicitamente

Runtime
  -> player ataca com item equipado
  -> Player/Combat consulta g_weapons->getWeapon(item)
  -> Weapon valida level, mana, soul, premium, vocacao e range
  -> executa dano padrao ou script onUseWeapon
  -> aplica efeitos/consumo/action da arma
```

### Cuidados de Manutencao

- O `id` precisa existir em `data/items/items.xml` e `items.otb`.
- Duplicidade de `id` em `weapons.xml` gera warning e o registro duplicado nao entra.
- `unproperly="1"` permite usar sem requisito com penalidade; sem isso o uso pode ser bloqueado.
- `vocation` altera descricao do item e validacao de uso.
- `script` aponta para `data/weapons/scripts/<script>` e exige callback `onUseWeapon`.
- Alterar `min`, `max`, `type`, `level`, `mana` ou `breakchance` mexe diretamente no balanceamento de combate.

## data/world

### Responsabilidade

Armazenar o mapa principal do servidor e seus arquivos auxiliares de mundo. A pasta contem o OTBM carregado no boot, XML de spawns, XML de houses, backup/zip do mapa e uma ferramenta auxiliar de verificacao de spawn.

### Estrutura Interna

```text
data/world/global_dash.otbm
data/world/backup.otbm
data/world/global_dash.zip
data/world/map-spawn.xml
data/world/map-house.xml
data/world/checkspawn.py
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.otbm` | Mapa binario carregado pela engine. |
| `.xml` | Spawns e houses associados ao mapa. |
| `.zip` | Arquivo compactado/backup do mapa. |
| `.py` | Script auxiliar local para checagem de spawn. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `global_dash.otbm` | Mapa principal, usado por `mapName = "global_dash"` em `config.lua`. |
| `backup.otbm` | Backup local de mapa. |
| `global_dash.zip` | Versao compactada do mapa. |
| `map-spawn.xml` | Define pontos de spawn, raio, monster/npc e `spawntime`. |
| `map-house.xml` | Define casas: `houseid`, nome, entrada, rent, town e size. |
| `checkspawn.py` | Utilitario auxiliar para inspecao/validacao de spawns. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `config.lua` | Define `mapName = "global_dash"`. |
| `src/app/otserv.cpp` | Durante o boot chama `g_game.loadMainMap(mapName)`. |
| `src/game/game/gameMap.cpp` | Monta caminho `data/world/<mapName>.otbm` para o mapa principal. |
| `src/world/map/map.cpp` | Chama `IOMap::loadMap`, depois `IOMap::loadSpawns` e `IOMap::loadHouses`. |
| `src/persistence/map/iomap.cpp` | Le OTBM e extrai tiles, itens, atributos, spawnfile e housefile quando definidos. |
| `src/persistence/map/iomap.hpp` | Se o OTBM nao informar arquivos, tenta `<mapName>-spawn.xml` e `<mapName>-house.xml`. |
| `src/world/spawn/spawns.cpp` | Carrega o XML de spawns e cria regras de respawn. |
| `src/world/house.cpp` e persistencia de map/house | Carrega houses e itens/dados persistidos de casas. |
| `src/scripting/lua/luaBindingsGame.cpp` | Expoe `Game.loadMap(path)` para carregar mapa adicional por Lua. |

### Fluxo de Execucao

```text
Boot do servidor
  -> config.lua define mapName
  -> g_game.loadMainMap(mapName)
     -> map.loadMap(data/world/<mapName>.otbm, loadHouses=true)
        -> IOMap::loadMap carrega OTBM
        -> IOMap::loadSpawns carrega spawn XML
        -> IOMap::loadHouses carrega house XML
        -> IOMapSerialize carrega info/itens persistidos de houses

Runtime
  -> mapa fornece tiles, towns, teleports, houses, spawns e itens estaticos
  -> spawns criam monstros/NPCs a partir dos nomes registrados em data/monster e data/npc
```

### Cuidados de Manutencao

- `config.lua` aponta para `global_dash`, entao o boot espera `data/world/global_dash.otbm`.
- O OTBM pode carregar nomes de spawn/house internamente; se nao carregar, a source tenta nomes derivados de `mapName`.
- No estado atual existem `map-spawn.xml` e `map-house.xml`; confirmar no editor de mapa/OTBM se esses nomes estao referenciados corretamente.
- Spawns dependem de nomes validos em `data/monster` e, quando aplicavel, `data/npc`.
- Alterar house ids ou entry positions pode afetar dados persistidos de houses no banco.
- Arquivos `.otbm` e `.zip` sao grandes; evitar edicoes manuais e preferir ferramenta/editor proprio de mapa.

## data/XML

### Responsabilidade

Centralizar configuracoes estruturais do servidor em XML. Diferente dos modulos XML-driven que apontam para scripts Lua, esta pasta alimenta sistemas internos da source: vocations, grupos/permissoes, comandos nativos, outfits, mounts, quests e stages de experiencia.

### Estrutura Interna

```text
data/XML/commands.xml
data/XML/groups.xml
data/XML/mounts.xml
data/XML/outfits.xml
data/XML/quests.xml
data/XML/stages.xml
data/XML/vocations.xml
```

### Tipos de Arquivos

| Tipo | Funcao |
|---|---|
| `.xml` | Arquivos de configuracao carregados diretamente por classes C++ especificas. |

### Arquivos Principais

| Arquivo | Funcao |
|---|---|
| `commands.xml` | Define permissao/log de comandos nativos como `/reload`, `/raid` e `!sellhouse`. |
| `groups.xml` | Define grupos (`player`, `gamemaster`, `god`), flags, access, depot e VIP limit. |
| `mounts.xml` | Define mounts por `id`, `clientid`, `name`, `speed` e `premium`; no estado atual ha muitas mounts comentadas e uma ativa (`Flamesteed`). |
| `outfits.xml` | Define outfits por sexo/tipo, `looktype`, nome, premium, unlocked e enabled; possui 118 outfits ativas no estado atual. |
| `quests.xml` | Define quest log por storage, missoes e estados de missao; possui 40 quests no estado atual. |
| `stages.xml` | Define stages de experiencia por faixa de level; atualmente `enabled="0"`. |
| `vocations.xml` | Define vocations/classes, client id, ganho de HP/mana, speed, attack speed, formulas e skill multipliers. |

### Comunicacao com a Source

| Source | Relacao |
|---|---|
| `src/app/otserv.cpp` | Carrega vocations e outfits durante o boot principal. |
| `src/entities/vocation.cpp` | Le `data/XML/vocations.xml` e popula `g_vocations`. |
| `src/entities/groups.cpp` | Le `data/XML/groups.xml` e popula grupos/permissoes. |
| `src/entities/mounts.cpp` | Le `data/XML/mounts.xml` e popula a lista de mounts. |
| `src/entities/outfit.cpp` | Le `data/XML/outfits.xml` e popula outfits por sexo/tipo. |
| `src/game/quests/questLoader.cpp` | Le `data/XML/quests.xml` e cria quests, missions e descriptions. |
| `src/game/game/gameWorld.cpp` | Le `data/XML/stages.xml` em `Game::loadExperienceStages`. |
| `src/game/commands/commandLoader.cpp` | Le `data/XML/commands.xml` e aplica group, account type e log aos comandos nativos. |
| `src/game/game/gameState.cpp` | Carrega commands, quests e mounts na inicializacao de estado do jogo. |

### Fluxo de Execucao

```text
Boot principal
  -> g_vocations.loadFromXml()
     -> data/XML/vocations.xml
  -> Outfits::getInstance()->loadFromXml()
     -> data/XML/outfits.xml

Inicializacao do game state
  -> commands.loadFromXml()
     -> data/XML/commands.xml
  -> loadExperienceStages()
     -> data/XML/stages.xml
  -> quests.loadFromXml()
     -> data/XML/quests.xml
  -> mounts.loadFromXml()
     -> data/XML/mounts.xml

Login/runtime
  -> groups definem permissoes do player
  -> vocations influenciam stats/combat/skills
  -> outfits/mounts aparecem para client/player
  -> quests leem storages para montar quest log
  -> stages alteram multiplicador de experiencia se enabled=1
```

### Cuidados de Manutencao

- `commands.xml` so configura comandos que ja existem no `commandMap` da source; comando desconhecido gera warning e e ignorado.
- `groups.xml` usa flags numericas grandes; alterar sem mapear os bits pode abrir ou bloquear permissoes criticas.
- `mounts.xml` tem muitas entradas comentadas; ativar uma mount exige validar `clientid`, velocidade, premium e compatibilidade com o client.
- `outfits.xml` ignora entradas com `enabled="no"` e valida `type`; `looktype` precisa existir no client.
- `quests.xml` depende de storages; reutilizar storage sem planejamento pode misturar progresso de quests diferentes.
- `stages.xml` so altera experiencia quando `<config enabled="1" />`; com `enabled="0"`, a source usa `rateExp` do `config.lua`.
- `vocations.xml` afeta combate, velocidade, mana/HP, skill rate e descricoes de classe; mudancas devem ser testadas em login, level up e combate.

## Secoes Pendentes

As proximas secoes devem seguir o mesmo modelo usado em `data/global.lua e data/lib` e `data/actions`.

```text
## data/<subpasta>

### Responsabilidade
### Estrutura Interna
### Tipos de Arquivos
### Arquivos Principais
### Comunicacao com a Source
### Fluxo de Execucao
### Cuidados de Manutencao
```
