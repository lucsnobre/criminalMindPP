# CriminalMind++

Bem-vindo ao CriminalMind++, um jogo de simulação de investigação policial em texto desenvolvido em C++ moderno. Aqui você poderá viver a experiência de ser um detetive, resolvendo casos intrigantes e desvendando mistérios.

## O que você encontrará aqui

- Histórias envolventes com casos únicos para investigar
- Personagens interessantes para interagir e interrogar
- Um sistema de pistas e evidências para coletar e analisar
- Sistema de reputação que afeta suas interações
- Gerenciamento de tempo para dar mais emoção às investigações
- Trilha sonora e efeitos sonoros para imersão
- Sistema de conquistas para registrar seus feitos
- Ferramenta para criar seus próprios casos
- Interface colorida e intuitiva
- Sistema de salvamento para continuar suas investigações depois

## O que você precisa para começar

- Um compilador C++ que suporte C++17 ou versão mais recente
- CMake versão 3.10 ou superior
- Um terminal que suporte cores ANSI

## Como começar a jogar

1. Primeiro, vamos preparar o ambiente. Abra seu terminal e execute:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

2. Agora é só executar o jogo:
```bash
./CriminalMindPP
```

## Como o projeto está organizado

```
CriminalMind++/
├── data/                  # Arquivos de dados do jogo
│   ├── casos.txt         # Casos predefinidos
│   ├── suspeitos_base.txt # Perfis de suspeitos
│   └── pistas_base.txt   # Pistas disponíveis
├── sounds/               # Arquivos de áudio
│   ├── menu.wav         # Música do menu
│   ├── investigacao.wav # Música de investigação
│   ├── interrogatorio.wav # Música de interrogatório
│   ├── descoberta.wav   # Som de descoberta
│   └── acusacao.wav     # Som de acusação
├── casos_exportados/     # Casos criados por você
├── src/                  # Código fonte
│   ├── Game.hpp         # Gerenciamento do jogo
│   ├── Game.cpp
│   ├── Suspeito.hpp     # Sistema de suspeitos
│   ├── Suspeito.cpp
│   ├── Pista.hpp        # Sistema de pistas
│   ├── Pista.cpp
│   ├── Engine.hpp       # Motor do jogo
│   ├── Engine.cpp
│   ├── Achievement.hpp  # Sistema de conquistas
│   ├── Achievement.cpp
│   ├── CaseEditor.hpp   # Editor de casos
│   ├── CaseEditor.cpp
│   └── utils.hpp        # Funções utilitárias
├── main.cpp             # Ponto de entrada
├── CMakeLists.txt       # Configuração de build
└── README.md            # Este arquivo
```

## Recursos que você vai encontrar

### Sistema de Conquistas
- Desbloqueie conquistas ao completar objetivos específicos
- Ganhe pontos por cada conquista desbloqueada
- Conquistas incluem:
  - Primeiro Caso: Complete seu primeiro caso
  - Detetive Perfeito: Resolva um caso sem erros
  - Velocista: Resolva um caso antes do tempo
  - Interrogador: Extraia informações importantes de suspeitos
  - Colecionador: Colete todas as pistas de um caso

### Editor de Casos
- Crie suas próprias histórias de investigação
- Edite casos existentes
- Exporte e importe seus casos
- Validação automática para garantir que seu caso é jogável
- Interface amigável para edição

### Sistema de Tempo
- Cada caso tem seu próprio limite de tempo
- O tempo passa conforme você toma ações
- Cuidado com as penalidades por exceder o tempo
- Ganhe bônus por resolver casos rapidamente

### Sistema de Som
- Músicas que mudam conforme o contexto
- Efeitos sonoros para cada ação
- Músicas em loop para manter a atmosfera
- Ajuste o volume como preferir

## Como jogar

1. Ao iniciar o jogo, você terá três opções:
   - Começar uma nova investigação
   - Criar ou editar casos
   - Ver suas conquistas

2. Durante o jogo, você poderá:
   - Explorar a cena do crime
   - Conversar com suspeitos
   - Analisar pistas coletadas
   - Fazer acusações
   - Salvar seu progresso

3. Lembre-se:
   - Gerencie bem seu tempo
   - Mantenha sua reputação alta
   - Colete todas as pistas possíveis
   - Escolha suas palavras com cuidado

## Quer contribuir?

Adoraríamos ter sua ajuda! Para contribuir:

1. Faça um fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/nova-feature`)
3. Commit suas mudanças (`git commit -am 'Adiciona nova feature'`)
4. Push para a branch (`git push origin feature/nova-feature`)
5. Crie um Pull Request

## Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo LICENSE para detalhes.

## Créditos

CriminalMind++ foi desenvolvido como um projeto de demonstração de C++ moderno e boas práticas de programação. Esperamos que você se divirta tanto jogando quanto nós nos divertimos desenvolvendo!
