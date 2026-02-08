# UnauthScout C++

**UnauthScout** é uma ferramenta OSINT (Open Source Intelligence) para reconhecimento passivo de usuários e repositórios em plataformas de controle de versão (GitHub e GitLab). Projetada para desenvolvedores, pesquisadores de segurança e profissionais de inteligência, oferece coleta, normalização e relatório de dados públicos de forma modular e eficiente.

---

## Recursos
- Busca e normaliza dados de usuários e repositórios do GitHub e GitLab.
- Saída em formato JSON para integração com outras ferramentas.
- Relatórios detalhados e sumários de inteligência.
- Suporte a flags para controle de saída (`--raw`, `--pretty`, `--save`).
- Arquitetura modular para fácil extensão.

## Requisitos
Instale as dependências necessárias em sistemas baseados em Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install -y g++ cmake libcurl4-openssl-dev
```

Para a biblioteca `nlohmann/json` (header-only):

```bash
mkdir -p include/nlohmann
wget https://raw.githubusercontent.com/nlohmann/json/v3.11.2/single_include/nlohmann/json.hpp -O include/nlohmann/json.hpp
```

## Compilação

1. Crie e acesse o diretório de build:

```bash
mkdir -p build && cd build
```

2. Configure o projeto com CMake:

```bash
cmake ..
```

3. Compile:

```bash
make
```

## Uso

### Buscar dados de um usuário:

```bash
./unauthscout torvalds
```

### Salvar resposta em JSON:

```bash
./unauthscout torvalds --save
```

Gera arquivos no formato `output/torvalds_YYYY-MM-DD.json`.

### Modo raw (dados brutos):

```bash
./unauthscout torvalds --raw
```

### Sumário de inteligência:

```bash
./unauthscout torvalds --repos --summarize
```

### Ajuda:

```bash
./unauthscout --help
```

## Exemplo de Saída

Arquivos de exemplo estão disponíveis em `output/`:
- [torvalds_2026-02-07.json](output/torvalds_2026-02-07.json) (dados de usuário)
- [torvalds_repos_2026-02-07.json](output/torvalds_repos_2026-02-07.json) (dados de repositórios)

## Solução de Problemas

### Erros de compilação
- Verifique se todos os arquivos `.cpp` estão listados no `CMakeLists.txt`.
- Garanta que `target_include_directories` seja chamado após `add_executable`.
- Recompile do zero se houver alterações em headers:

```bash
rm -rf build && mkdir build && cd build
cmake ..
make
```

### Dependências ausentes
- Confirme a instalação do `libcurl4-openssl-dev`.
- Verifique a presença do arquivo `include/nlohmann/json.hpp`.

---

## Contribuição
Pull requests são bem-vindos. Para grandes mudanças, abra uma issue primeiro para discutir o que você gostaria de alterar.
