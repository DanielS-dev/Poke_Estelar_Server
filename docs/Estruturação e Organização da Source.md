# Estruturação e Organização da Source

Este documento descreve a organização atual da source do servidor e registra as diretrizes usadas para manter o código mais legível, separado por responsabilidades e fácil de evoluir.

## Objetivos

1. Manter os arquivos separados por domínio e responsabilidade.
2. Reduzir acoplamento entre módulos da source.
3. Evitar implementação de regras de negócio em arquivos `.h` e `.hpp`.
4. Melhorar a legibilidade dos arquivos `.cpp`.
5. Fortalecer os logs de erro e facilitar diagnóstico de problemas.
6. Refatorar o código de forma gradual, sem alterar comportamento desnecessariamente.

## Estrutura Atual de Pastas

- `app/`: inicialização do servidor, ciclo principal e integração dos serviços centrais.
- `core/`: utilitários, tipos globais, scheduler, tarefas e estruturas compartilhadas.
- `config/`: carregamento e acesso às configurações do servidor.
- `game/`: regras e sistemas principais de gameplay.
- `entities/`: entidades vivas e sociais, como player, creature, monster, guild, party e vocations.
- `world/`: mapa, tiles, houses, spawns, teleports e estruturas do mundo.
- `items/`: itens, containers, mailbox, depot e estruturas relacionadas.
- `network/`: conexões, protocolos, mensagens e comunicação cliente-servidor.
- `persistence/`: banco de dados, carregamento e salvamento persistente.
- `scripting/`: Lua, eventos, actions, talkactions e integração com scripts.
- `security/`: banimentos, RSA e componentes ligados à segurança.
- `io/`: leitura de arquivos e loaders base.

Para o mapa detalhado de arquivos, contratos públicos, dependências entre módulos e arquivos críticos, consulte também `docs/Documentacao da Source.md`.

## Diretrizes

### Headers

Arquivos `.h` e `.hpp` devem priorizar declarações, tipos, constantes e interfaces públicas. Sempre que possível, a implementação deve ficar nos arquivos `.cpp`.

Evite colocar regras de negócio complexas em headers. Exceções aceitáveis incluem funções pequenas, `inline`, templates e código que precisa estar no header por exigência da linguagem.

Headers centrais podem funcionar como fachadas públicas quando isso preservar compatibilidade com os consumidores. Nesses casos, o header principal deve agregar headers menores e bem nomeados, mantendo o include antigo estável.

### Implementações

Arquivos `.cpp` devem concentrar a implementação real das classes e funções. Cada arquivo deve ter uma responsabilidade clara e evitar crescer com lógica de domínios diferentes.

Quando uma função começar a misturar gameplay, persistência, rede e validações externas, ela deve ser candidata a refatoração.

Quando um arquivo `.cpp` for dividido em vários arquivos menores, os novos arquivos devem ficar em uma subpasta própria do domínio refatorado. Isso evita poluir a pasta principal e deixa claro que aqueles arquivos pertencem ao mesmo grupo de responsabilidade.

### Logs

Logs devem ajudar a entender o erro sem poluir o fluxo normal do servidor. Mensagens de erro devem indicar o contexto mínimo necessário, como operação executada, entidade envolvida e motivo da falha quando disponível.

Evite mensagens genéricas demais, como `error` ou `failed`, sem contexto adicional.

### Refatorações

Refatorações devem ser pequenas, revisáveis e focadas. Ao mover código entre pastas ou arquivos, prefira preservar o comportamento atual antes de aplicar melhorias funcionais.

Mudanças estruturais devem ser feitas em etapas para facilitar testes, revisão e rollback.

Ao mover, criar ou remover arquivos, siga o Processo Padrão de Refatoração descrito abaixo. Ele é o checklist oficial para includes, consumidores, CMake, Visual Studio e documentação.

## Decisões Consolidadas

- Arquivos grandes devem ser divididos por responsabilidade, não apenas por tamanho.
- Quando um arquivo for separado em vários, deve ser criada uma subpasta para agrupar os novos arquivos.
- Headers públicos muito consumidos devem preservar o caminho antigo sempre que possível.
- Headers públicos críticos podem agregar headers auxiliares menores, como `player.hpp` incluindo `player/playerTypes.hpp`, para reduzir concentração sem quebrar consumidores.
- `luascript.hpp` permanece como fachada pública da interface Lua, agregando headers menores em `src/scripting/lua/luascript`.
- Bindings Lua de uma mesma classe ou domínio devem ficar agrupados em subpastas, como `src/scripting/lua/creature`.
- O registry da API Lua pode ser dividido em múltiplos `.cpp` por domínio, mantendo `luaGlobalFunctionsRegistry.cpp` como orquestrador central.
- A documentação da source deve ser atualizada junto com a refatoração, no mesmo ciclo de trabalho.
- Arquivos marcados como `CRÍTICO` na documentação principal exigem revisão mais cuidadosa dos consumidores antes de qualquer mudança.

## Processo Padrão de Refatoração

1. Entender a responsabilidade atual do arquivo.
2. Identificar consumidores, includes e registros associados.
3. Definir a nova divisão por responsabilidade.
4. Criar subpasta quando o arquivo for dividido em vários arquivos relacionados.
5. Mover declarações e implementações preservando comportamento.
6. Corrigir includes relativos e consumidores diretos.
7. Atualizar `src/CMakeLists.txt` quando novos `.cpp` entrarem no build.
8. Atualizar `vc14/theforgottenserver.vcxproj` com novos `.cpp` e `.hpp`.
9. Atualizar `docs/Documentacao da Source.md`.
10. Buscar referências antigas ao arquivo, caminho ou símbolo movido.
11. Compilar no Visual Studio.
12. Corrigir erros de contrato, visibilidade ou include revelados pela compilação.

## Planejamento

- [x] Separar os arquivos por pastas.
- [x] Definir que arquivos divididos em vários devem ficar agrupados em subpastas próprias.
- [x] Iniciar divisão de arquivos grandes por responsabilidade, como bindings de `Creature`.
- [x] Transformar `luascript.hpp` em fachada pública com headers internos menores.
- [x] Documentar dependências entre módulos e arquivos críticos na documentação principal.
- [ ] Continuar revisando arquivos `.cpp` grandes e dividir responsabilidades quando fizer sentido.
- [ ] Remover implementação desnecessária de regras de negócio em `.h` e `.hpp`, preservando templates, inline e fachadas públicas quando necessário.
- [ ] Padronizar e fortalecer logs de erro.
- [ ] Revisar dependências entre módulos para reduzir acoplamento em pontos críticos.
- [ ] Documentar novos padrões importantes conforme forem definidos.

## Observações

Este planejamento pode mudar conforme o projeto evoluir. A organização da source deve acompanhar as necessidades reais do servidor, sem criar abstrações antes de existir um problema claro para resolver.

Este documento define o processo e os padrões de organização. O documento `Documentacao da Source.md` deve continuar sendo o mapa detalhado da estrutura real da source.
