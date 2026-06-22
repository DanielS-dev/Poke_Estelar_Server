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

## Diretrizes

### Headers

Arquivos `.h` e `.hpp` devem priorizar declarações, tipos, constantes e interfaces públicas. Sempre que possível, a implementação deve ficar nos arquivos `.cpp`.

Evite colocar regras de negócio complexas em headers. Exceções aceitáveis incluem funções pequenas, `inline`, templates e código que precisa estar no header por exigência da linguagem.

### Implementações

Arquivos `.cpp` devem concentrar a implementação real das classes e funções. Cada arquivo deve ter uma responsabilidade clara e evitar crescer com lógica de domínios diferentes.

Quando uma função começar a misturar gameplay, persistência, rede e validações externas, ela deve ser candidata a refatoração.

### Logs

Logs devem ajudar a entender o erro sem poluir o fluxo normal do servidor. Mensagens de erro devem indicar o contexto mínimo necessário, como operação executada, entidade envolvida e motivo da falha quando disponível.

Evite mensagens genéricas demais, como `error` ou `failed`, sem contexto adicional.

### Refatorações

Refatorações devem ser pequenas, revisáveis e focadas. Ao mover código entre pastas ou arquivos, prefira preservar o comportamento atual antes de aplicar melhorias funcionais.

Mudanças estruturais devem ser feitas em etapas para facilitar testes, revisão e rollback.

## Planejamento

- [x] Separar os arquivos por pastas.
- [ ] Revisar arquivos `.cpp` grandes e dividir responsabilidades quando fizer sentido.
- [ ] Remover implementação desnecessária de regras de negócio em `.h` e `.hpp`.
- [ ] Padronizar e fortalecer logs de erro.
- [ ] Revisar dependências entre módulos para reduzir acoplamento.
- [ ] Documentar padrões importantes conforme forem definidos.

## Observações

Este planejamento pode mudar conforme o projeto evoluir. A organização da source deve acompanhar as necessidades reais do servidor, sem criar abstrações antes de existir um problema claro para resolver.
