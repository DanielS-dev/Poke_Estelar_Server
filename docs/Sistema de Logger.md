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

Por padrao, o arquivo gerado e:

```text
logs/server.log
```

A pasta `/logs/` na raiz do projeto e ignorada pelo Git. Ela e diferente de `data/logs`, que continua sendo usada para logs de comandos de jogo.

## Configuracao no `.env`

As variaveis abaixo controlam o comportamento do logger:

```env
LOG_LEVEL = "info"
LOG_TO_CONSOLE = true
LOG_TO_FILE = true
LOG_FILE = "logs/server.log"
LOG_MAX_FILE_SIZE_MB = 10
LOG_MAX_FILES = 5
```

### Variaveis

| Variavel | Padrao | Descricao |
|---|---|---|
| `LOG_LEVEL` | `info` | Nivel minimo que sera registrado. |
| `LOG_TO_CONSOLE` | `true` | Habilita escrita no console. |
| `LOG_TO_FILE` | `true` | Habilita escrita em arquivo. |
| `LOG_FILE` | `logs/server.log` | Caminho do arquivo principal de log. |
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

Exemplo:

```text
[2026-06-26 09:12:44.031] [fatal] [Startup] Failed to connect to database. (src/app/otserv.cpp:40)
```

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

Ordem recomendada:

1. `src/persistence/database.cpp`
2. `src/scripting/lua/luaScriptInterface.cpp`
3. `src/core/tools/xmlErro.cpp`
4. `src/app/servicePort.cpp`
5. `src/network/connection.cpp`
6. Loaders de scripts, itens, monstros, raids e spells

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
