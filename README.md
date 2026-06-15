# Poke Estelar Server

Servidor de Poketibia baseado em TFS, usando o servidor Poke Fans como base.

Este projeto sera usado para estudos de C++, OTServer, organizacao de source, build com Visual Studio e gerenciamento de dependencias com vcpkg.

## Objetivo

- Estudar a estrutura de um servidor TFS/Poketibia.
- Praticar manutencao e modernizacao de codigo C++.
- Entender integracao com banco de dados, scripts Lua e arquivos XML.
- Manter as dependencias fora da source usando vcpkg.

## Como executar

1. Clone o repositorio:

```powershell
git clone <url-do-repositorio>
cd Poke_Estelar_Server
```

2. Instale as dependencias com vcpkg:

```powershell
C:\vcpkg\vcpkg.exe install --triplet x64-windows
```

3. Abra a solution no Visual Studio:

```text
vc14/theforgottenserver.sln
```

4. Compile em `Release x64` ou `Debug x64`.

O executavel gerado sera `Poke_Estelar.exe`.

## Observacoes

- A pasta `vcpkg_installed/` nao deve ser enviada para o GitHub.
- Arquivos `.exe`, `.dll` e saidas de build tambem devem ficar fora do repositorio.
- As DLLs necessarias para execucao podem ser copiadas de `vcpkg_installed/x64-windows/bin` apos a instalacao das dependencias.

## Creditos

[@pota](https://tibiaking.com/profile/292369-pota/)

theforgottenserver

OTLand e Tibiaking

[Zayon Owatari](https://tibiaking.com/profile/113478-zayon-owatari/) (poke fans - https://tibiaking.com/topic/111519-1098-tfs12-pokefans-poketibia-com-level-system-boost-status-e-painel-de-moves-pokeadons/)
