#include "Game.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>

Game::Game() : jogoEmAndamento(false), reputacao(50) {}

Game::~Game() {
    if (jogoEmAndamento) {
        salvarProgresso();
    }
}

void Game::iniciar() {
    std::cout << "\033[1;36m=== CriminalMind++ ===\033[0m\n\n";
    std::cout << "Bem-vindo ao simulador de investigação policial!\n";
    std::cout << "Por favor, digite seu nome, detetive: ";
    std::getline(std::cin, nomeDetetive);
    
    mostrarMenu();
}

void Game::mostrarMenu() {
    while (true) {
        std::cout << "\n\033[1;33m=== Menu Principal ===\033[0m\n";
        std::cout << "1. Novo Caso\n";
        std::cout << "2. Continuar\n";
        std::cout << "3. Estatísticas\n";
        std::cout << "4. Sair\n";
        std::cout << "Escolha uma opção: ";

        int opcao;
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1:
                gerarNovoCaso();
                executar();
                break;
            case 2:
                carregarProgresso();
                executar();
                break;
            case 3:
                mostrarEstatisticas();
                break;
            case 4:
                finalizar();
                return;
            default:
                std::cout << "Opção inválida!\n";
        }
    }
}

void Game::gerarNovoCaso() {
    // Limpa dados anteriores
    suspeitos.clear();
    pistas.clear();
    
    // Gera suspeitos iniciais
    suspeitos.emplace_back("João Silva", 35, "Vizinho", "Histórico limpo", false);
    suspeitos.emplace_back("Maria Santos", 28, "Ex-namorada", "Histórico de agressão", true);
    suspeitos.emplace_back("Pedro Oliveira", 45, "Colega de trabalho", "Histórico limpo", false);
    
    // Gera pistas iniciais
    pistas.emplace_back("Pegadas na cena do crime", 7, "Maria Santos", "Sala de estar");
    pistas.emplace_back("Carteira da vítima", 5, "", "Bolso do casaco");
    pistas.emplace_back("Mensagem ameaçadora", 8, "Maria Santos", "Celular da vítima");
    
    jogoEmAndamento = true;
    casoAtual = "Caso #" + std::to_string(rand() % 1000);
}

void Game::executar() {
    while (jogoEmAndamento) {
        std::cout << "\n\033[1;32m=== Ações Disponíveis ===\033[0m\n";
        std::cout << "1. Investigar Cena\n";
        std::cout << "2. Interrogar Suspeitos\n";
        std::cout << "3. Analisar Pistas\n";
        std::cout << "4. Fazer Acusação\n";
        std::cout << "5. Salvar e Sair\n";
        std::cout << "Escolha uma ação: ";

        int acao;
        std::cin >> acao;
        std::cin.ignore();

        switch (acao) {
            case 1:
                investigarCena();
                break;
            case 2:
                interrogarSuspeitos();
                break;
            case 3:
                analisarPistas();
                break;
            case 4:
                fazerAcusacao();
                break;
            case 5:
                salvarProgresso();
                jogoEmAndamento = false;
                break;
            default:
                std::cout << "Ação inválida!\n";
        }
    }
}

void Game::investigarCena() {
    std::cout << "\n\033[1;35mInvestigando a cena do crime...\033[0m\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    for (auto& pista : pistas) {
        if (!pista.getFoiColetada()) {
            pista.mostrarPista();
            std::cout << "Coletar esta pista? (s/n): ";
            char resposta;
            std::cin >> resposta;
            if (resposta == 's' || resposta == 'S') {
                pista.setFoiColetada(true);
            }
        }
    }
}

void Game::interrogarSuspeitos() {
    std::cout << "\n\033[1;35mSelecionando suspeito para interrogatório...\033[0m\n";
    
    for (size_t i = 0; i < suspeitos.size(); ++i) {
        std::cout << i + 1 << ". " << suspeitos[i].getNome() << "\n";
    }
    
    std::cout << "Escolha um suspeito (número): ";
    int escolha;
    std::cin >> escolha;
    std::cin.ignore();
    
    if (escolha > 0 && escolha <= static_cast<int>(suspeitos.size())) {
        Suspeito& suspeito = suspeitos[escolha - 1];
        suspeito.mostrarPerfil();
        
        std::cout << "\nDigite sua pergunta: ";
        std::string pergunta;
        std::getline(std::cin, pergunta);
        
        std::cout << "\nResposta: " << suspeito.responderPergunta(pergunta) << "\n";
    }
}

void Game::analisarPistas() {
    std::cout << "\n\033[1;35m=== Pistas Coletadas ===\033[0m\n";
    for (const auto& pista : pistas) {
        if (pista.getFoiColetada()) {
            pista.mostrarPista();
        }
    }
}

void Game::fazerAcusacao() {
    std::cout << "\n\033[1;31m=== Fazer Acusação ===\033[0m\n";
    for (size_t i = 0; i < suspeitos.size(); ++i) {
        std::cout << i + 1 << ". " << suspeitos[i].getNome() << "\n";
    }
    
    std::cout << "Quem você acusa? (número): ";
    int acusacao;
    std::cin >> acusacao;
    
    if (acusacao > 0 && acusacao <= static_cast<int>(suspeitos.size())) {
        const Suspeito& acusado = suspeitos[acusacao - 1];
        if (acusado.getECulpado()) {
            std::cout << "\n\033[1;32mParabéns! Você acertou!\033[0m\n";
            reputacao += 10;
        } else {
            std::cout << "\n\033[1;31mErrado! O verdadeiro culpado continua solto...\033[0m\n";
            reputacao -= 5;
        }
        jogoEmAndamento = false;
    }
}

void Game::salvarProgresso() {
    std::ofstream arquivo("savegame.txt");
    if (arquivo.is_open()) {
        arquivo << nomeDetetive << "\n";
        arquivo << reputacao << "\n";
        arquivo << casoAtual << "\n";
        arquivo << jogoEmAndamento << "\n";
        arquivo.close();
    }
}

void Game::carregarProgresso() {
    std::ifstream arquivo("savegame.txt");
    if (arquivo.is_open()) {
        std::getline(arquivo, nomeDetetive);
        arquivo >> reputacao;
        arquivo.ignore();
        std::getline(arquivo, casoAtual);
        arquivo >> jogoEmAndamento;
        arquivo.close();
    }
}

void Game::mostrarEstatisticas() {
    std::cout << "\n\033[1;33m=== Estatísticas do Detetive ===\033[0m\n";
    std::cout << "Nome: " << nomeDetetive << "\n";
    std::cout << "Reputação: " << reputacao << "\n";
    std::cout << "Casos resolvidos: " << (reputacao - 50) / 10 << "\n";
}

void Game::pausar() {
    salvarProgresso();
    jogoEmAndamento = false;
}

void Game::continuar() {
    carregarProgresso();
    jogoEmAndamento = true;
}

void Game::finalizar() {
    if (jogoEmAndamento) {
        salvarProgresso();
    }
    std::cout << "\n\033[1;36mObrigado por jogar CriminalMind++!\033[0m\n";
} 