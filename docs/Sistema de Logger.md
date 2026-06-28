# Sistema de Logger

Este documento descreve o sistema central de logs da source. O objetivo do logger e padronizar mensagens tecnicas do servidor, manter saida legivel no console e gravar um arquivo persistente para diagnostico depois que o processo fecha.

## Visao Geral

O logger central vive em:

```text
src/core/logger.hpp
src/core/logger.cpp
```

Ele e inicializado no inicio do `main`, em `src/app/otserv.cpp`, usando as configuracoes do `.env`. No encerramento normal do servidor, `Logger::shutdown()` drena a fila pendente e fecha o arquivo.

O logger atual foi implementado sem dependencia externa. Ele usa uma fila em memoria e uma thread dedicada para escrita, reduzindo o custo de I/O no fluxo principal do servidor.

## Saidas

O logger pode escrever em dois destinos:

- Console: util para desenvolvimento local e acompanhamento em tempo real.
- Arquivo: util para diagnostico persistente depois de crash, erro de startup ou fechamento do console.

Por padrao, os arquivos gerados sao separados por nivel:

```text
logs/info.log
logs/warn.log
logs/error.log
logs/fatal.log
```

Os arquivos `trace.log` e `debug.log` tambem podem ser gerados quando `LOG_FILE_LEVEL` permitir esses niveis. Se `LOG_SPLIT_BY_LEVEL` for desativado, o logger volta a usar um unico arquivo definido em `LOG_FILE`.

A pasta `/logs/` na raiz do projeto e ignorada pelo Git. Ela e diferente de `data/logs`, que continua sendo usada para logs de comandos de jogo.

Por padrao, o console mostra mensagens `info` em formato compacto, sem data/hora, sem arquivo:linha e sem o prefixo `[info]`. Avisos e erros continuam exibindo o nivel. Os arquivos continuam registrando as mensagens em formato completo para preservar historico de startup e diagnostico.

## Configuracao no `.env`

As variaveis abaixo controlam o comportamento do logger:

```env
LOG_LEVEL = "info"
LOG_CONSOLE_LEVEL = "info"
LOG_FILE_LEVEL = "info"
LOG_TO_CONSOLE = true
LOG_TO_FILE = true
LOG_SPLIT_BY_LEVEL = true
LOG_DIR = "logs"
LOG_FILE = "logs/server.log"
LOG_MAX_FILE_SIZE_MB = 10
LOG_MAX_FILES = 5
```

### Variaveis

| Variavel | Padrao | Descricao |
|---|---|---|
| `LOG_LEVEL` | `info` | Nivel global/fallback. Use `off` para desligar todos os destinos. |
| `LOG_CONSOLE_LEVEL` | `info` | Nivel minimo exibido no console. |
| `LOG_FILE_LEVEL` | `info` | Nivel minimo gravado no arquivo. |
| `LOG_TO_CONSOLE` | `true` | Habilita escrita no console. |
| `LOG_TO_FILE` | `true` | Habilita escrita em arquivo. |
| `LOG_SPLIT_BY_LEVEL` | `true` | Separa a escrita em arquivos por nivel (`info.log`, `warn.log`, `error.log`, `fatal.log`). |
| `LOG_DIR` | `logs` | Pasta usada quando `LOG_SPLIT_BY_LEVEL` esta habilitado. |
| `LOG_FILE` | `logs/server.log` | Caminho do arquivo unico quando `LOG_SPLIT_BY_LEVEL` esta desabilitado. |
| `LOG_MAX_FILE_SIZE_MB` | `10` | Tamanho maximo do arquivo antes da rotacao. |
| `LOG_MAX_FILES` | `5` | Quantidade maxima de arquivos rotacionados. |

## Niveis

Os niveis disponiveis sao:

| Nivel | Uso esperado |
|---|---|
| `trace` | Detalhe extremo, normalmente desligado. |
| `debug` | Diagnostico de desenvolvimento. |
| `info` | Fluxo normal do servidor. |
| `warn` | Problema recuperavel ou comportamento inesperado. |
| `error` | Falha real, mas o servidor pode continuar. |
| `fatal` | Falha critica que impede startup ou exige shutdown. |
| `off` | Desliga o logger. |

## Formato

Cada linha segue o formato:

```text
[YYYY-MM-DD HH:MM:SS.mmm] [level] [Category] Message (source.cpp:line)
```

Esse formato completo e usado nos arquivos de log. No console, a mensagem e exibida em formato compacto:

```text
[Category] Message
[warn] [Category] Message
[error] [Category] Message
```

Exemplo:

```text
[2026-06-26 09:12:44.031] [fatal] [Startup] Failed to connect to database. (src/app/otserv.cpp:40)
```

Com `LOG_SPLIT_BY_LEVEL = true`, cada mensagem vai para o arquivo do proprio nivel. Exemplo: `LOG_ERROR` grava em `logs/error.log`, enquanto `LOG_WARN` grava em `logs/warn.log`.

## Macros Disponiveis

As macros ficam em `src/core/logger.hpp`:

```cpp
LOG_TRACE("Category", "Message");
LOG_DEBUG("Category", "Message");
LOG_INFO("Category", "Message");
LOG_WARN("Category", "Message");
LOG_ERROR("Category", "Message");
LOG_FATAL("Category", "Message");
```

Elas registram automaticamente o arquivo e a linha de origem.

## Categorias Recomendadas

Use categorias curtas e consistentes:

```text
Startup
Config
Database
Lua
XML
Network
Game
Items
Monsters
Scripts
Commands
Security
```

## Quando Usar

Use o logger para mensagens tecnicas do servidor:

- Erros de startup.
- Falhas de banco de dados.
- Falhas de XML.
- Falhas de scripts Lua.
- Problemas de rede relevantes.
- Avisos operacionais que ajudam diagnostico.

Evite usar o logger para mensagens de gameplay destinadas ao jogador. Mensagens para player devem continuar usando os canais do jogo, como `sendTextMessage`.

## Migracao Gradual

Nao substitua todos os `std::cout` de uma vez. Migre por dominio, mantendo comportamento e contexto.

### Pontos Criticos Migrados

Os primeiros pontos criticos ja foram migrados para o logger central:

- `src/app/otserv.cpp`
- `src/config/configmanager.cpp`
- `src/persistence/database.cpp`
- `src/scripting/lua/luaScriptInterface.cpp`
- `src/core/tools/xmlErro.cpp`
- `src/app/servicePort.cpp`
- `src/network/connection.cpp`

Nesses arquivos, os logs tecnicos devem usar `LOG_INFO`, `LOG_WARN`, `LOG_ERROR` ou `LOG_FATAL`. O uso direto de `std::cout`/`std::cerr` para erro tecnico deve ser evitado.

Excecao atual: `badAllocationHandler()` em `src/app/otserv.cpp` usa `puts()` de forma intencional para evitar alocacao dinamica durante falha de memoria.

### Loaders Ja Migrados

As duas primeiras etapas da migracao de loaders ja foram concluidas:

1. Scripts, actions, creature events, globalevents, movements, spells, talkactions e weapons.
2. Itens, monstros, NPCs, raids, quests, mounts e outfits.

Os principais pontos agora usam o logger central para:

- falhas fatais de startup, como impossibilidade de carregar um subsystem inteiro;
- warnings de XML, Lua e duplicidade de registro;
- resumos agregados de carga, como quantidade de eventos, items, monstros, raids, quests, mounts e outfits carregados.

No caso dos NPCs, o logger foi ajustado para evitar poluicao do console com um `info` por NPC individual. O comportamento atual e:

- sucesso: um resumo agregado com a quantidade total de NPCs carregados a partir dos spawns;
- falha: erro especifico do NPC, XML ou script com contexto suficiente para diagnostico.

### Proximas Migracoes

Depois dos pontos criticos, a ordem recomendada e:

1. Sistemas de persistence/login que ainda imprimem erros no console.
2. Pontos de rede e protocolo que hoje fecham conexao silenciosamente, quando houver valor real de diagnostico.
3. Mensagens restantes de status normal que fizerem sentido como `LOG_INFO`.

Ao migrar uma mensagem, escolha o nivel correto e mantenha contexto suficiente para investigacao.

Exemplo:

```cpp
LOG_ERROR("Database", "Failed to execute query: " + query);
```

Para mensagens muito frequentes ou caras de montar, prefira verificar o nivel antes:

```cpp
if (Logger::getInstance().shouldLog(LogLevel::Debug)) {
	LOG_DEBUG("Network", "Packet received from " + ip);
}
```

## Cuidados

- Nao registre senhas, RSA privada, tokens ou dados sensiveis do `.env`.
- Evite logar queries gigantes em nivel `info`.
- Evite log por pacote de rede em nivel `info`.
- Use `warn`, `error` e `fatal` para mensagens acionaveis.
- Mantenha `data/logs` para logs de comandos de jogo e `/logs` para logs tecnicos do servidor.
