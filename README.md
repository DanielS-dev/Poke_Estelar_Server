# Poke Estelar Server

Servidor Poketibia/OTServer em C++ baseado em The Forgotten Server (TFS) 1.2, usando o projeto Poke Fans como base inicial e cliente/protocolo 10.98.

Este repositório é usado para estudo e evolução de uma source de servidor: organização de código C++, refatoração por responsabilidades, integração com Lua/XML, banco de dados e build no Windows com Visual Studio e vcpkg.

## Sobre o Projeto

O Poke Estelar Server é uma source de servidor Poketibia derivada de uma base TFS 1.2/Poke Fans, com suporte ao cliente/protocolo 10.98. O objetivo principal é estudar, manter e modernizar a estrutura do servidor sem misturar dependências externas com o código-fonte.

Principais áreas de estudo:

- Estrutura de um servidor TFS/Poketibia.
- Manutenção e modernização de código C++.
- Integração com scripts Lua e arquivos XML.
- Persistência com banco de dados MySQL/MariaDB.
- Organização da source por domínios e responsabilidades.
- Gerenciamento de dependências com vcpkg.

## Requisitos

- Windows x64.
- Visual Studio com toolset `v143`.
- Windows SDK `10.0`.
- vcpkg instalado e acessível em `C:\vcpkg`.
- MySQL ou MariaDB compatível com a base de dados do projeto.

Dependências gerenciadas pelo `vcpkg.json`:

- Boost: `asio`, `lexical-cast`, `lockfree`, `range`, `system`.
- `libmysql`
- `luajit`
- `mpir`
- `pugixml`

## Como Compilar

1. Clone o repositório:

```powershell
git clone <url-do-repositorio>
cd Poke_Estelar_Server
```

2. Instale as dependências com vcpkg:

```powershell
C:\vcpkg\vcpkg.exe install --triplet x64-windows
```

3. Abra a solution no Visual Studio:

```text
vc14/theforgottenserver.sln
```

4. Compile em `Release x64` ou `Debug x64`.

O executável gerado será `Poke_Estelar.exe`.

## Como Configurar e Executar

1. Configure o banco de dados em `config.lua`:

```lua
mysqlHost = "127.0.0.1"
mysqlUser = "root"
mysqlPass = ""
mysqlDatabase = "pokeestelar"
mysqlPort = 3306
```

2. Importe a estrutura do banco de dados:

```text
schema.sql
```

3. Se necessário, importe também os dados do projeto:

```text
pokeestelar - dados.sql
```

4. Confira as principais configurações em `config.lua`, como IP, portas, nome do mapa e nome do servidor.

5. Copie as DLLs necessárias para a pasta do executável. Elas podem ser obtidas em:

```text
vcpkg_installed/x64-windows/bin
```

6. Execute o servidor:

```text
Poke_Estelar.exe
```

## Estrutura do Repositório

- `src/`: código-fonte C++ do servidor.
- `data/`: arquivos de dados, scripts, mapas e configurações usadas pelo servidor.
- `docs/`: documentação interna da source e da organização do projeto.
- `cmake/`: módulos auxiliares do CMake.
- `vc14/`: solution e projeto do Visual Studio.
- `vcpkg.json`: manifesto das dependências externas.
- `config.lua`: configuração principal de execução do servidor.
- `schema.sql`: estrutura inicial do banco de dados.
- `pokeestelar - dados.sql`: dados adicionais do projeto.

## Observações

- A pasta `vcpkg_installed/` não deve ser enviada para o GitHub.
- Arquivos `.exe`, `.dll` e saídas de build também devem ficar fora do repositório.
- As DLLs necessárias para execução podem ser copiadas de `vcpkg_installed/x64-windows/bin` após a instalação das dependências.

## Créditos

| Nome/Projeto | Papel | Link |
| --- | --- | --- |
| The Forgotten Server | Base OTServer/TFS usada como referência do projeto. | https://github.com/otland/forgottenserver |
| Poke Fans | Base Poketibia usada como ponto de partida. | https://tibiaking.com/topic/111519-1098-tfs12-pokefans-poketibia-com-level-system-boost-status-e-painel-de-moves-pokeadons/ |
| Zayon Owatari | Publicação e créditos relacionados à base Poke Fans. | https://tibiaking.com/profile/113478-zayon-owatari/ |
| pota | Contribuições e referências na comunidade. | https://tibiaking.com/profile/292369-pota/ |
| OTLand | Comunidade e ecossistema TFS/OTServer. | https://otland.net/ |
| Tibiaking | Comunidade e publicações relacionadas a OTServer/Poketibia. | https://tibiaking.com/ |
