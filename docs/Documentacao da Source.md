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

- `chat.cpp/.hpp`: canais e regras de chat.
- `chatChannel.cpp/.hpp`: canais de chat, usuários, convites, eventos Lua e envio de mensagens.
- `chatLoader.cpp/.hpp`: carregamento dos canais via XML e scripts.
- `chatRules.cpp/.hpp`: regras de fala e normalização do tipo de mensagem por canal.
- `combat.cpp/.hpp`: combate, dano, áreas e condições de combate.
- `command.cpp/.hpp`: representação de um comando individual.
- `commandLoader.cpp/.hpp`: carregamento dos comandos via XML.
- `commandRules.cpp/.hpp`: validação de permissão e log de execução dos comandos.
- `commands.cpp/.hpp`: fachada e orquestração dos comandos administrativos ou de servidor.
- `condition.cpp/.hpp`: condições aplicadas em criaturas.
- `game.cpp/.hpp`: núcleo de coordenação da lógica do jogo.
- `movement.cpp/.hpp`: eventos e regras de movement.
- `quest.cpp/.hpp`: entidade de quest, progresso geral e contagem de missões.
- `questLoader.cpp/.hpp`: carregamento das quests e missões a partir do XML.
- `questMission.cpp/.hpp`: entidade de missão, estado, descrição e conclusão.
- `quests.cpp/.hpp`: fachada e coleção de quests disponíveis.
- `raids.cpp/.hpp`: raids, eventos de invasão e carregamento de raids.
- `spells.cpp/.hpp`: spells, runes e regras de conjuração.
- `weapons.cpp/.hpp`: armas, ataques e regras de weapon use.

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
- `protocolgame.cpp/.hpp`: protocolo principal de gameplay.
- `protocollogin.cpp/.hpp`: protocolo de login.
- `protocolold.cpp/.hpp`: suporte a protocolo antigo.
- `protocolstatus.cpp/.hpp`: protocolo de status do servidor.

### `src/persistence`

Contém acesso ao banco de dados e carregamento/salvamento persistente.

- `database.cpp/.hpp`: conexão e execução de queries.
- `databasemanager.cpp/.hpp`: gerenciamento de schema e tarefas administrativas de banco.
- `databasetasks.cpp/.hpp`: execução assíncrona de tarefas de banco.
- `ioguild.cpp/.hpp`: persistência de guilds.
- `iologindata.cpp/.hpp`: login, conta e dados iniciais do jogador.
- `iomap.cpp/.hpp`: carregamento do mapa.
- `iomapserialize.cpp/.hpp`: serialização de itens e estado do mapa.
- `iomarket.cpp/.hpp`: persistência do market.

### `src/scripting`

Contém a integração com Lua e os sistemas de eventos scriptáveis.

- `actions.cpp/.hpp`: actions usadas por itens e scripts.
- `baseevents.cpp/.hpp`: base para sistemas de eventos.
- `creatureevent.cpp/.hpp`: eventos ligados a criaturas.
- `events.cpp/.hpp`: eventos globais registrados via script.
- `globalevent.cpp/.hpp`: globalevents e eventos agendados.
- `luascript.cpp/.hpp`: interface principal entre C++ e Lua.
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
