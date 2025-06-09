#include "Engine.hpp"
#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono>

Engine::Engine() : somAtivo(false) {
    carregarCasos();
    carregarSons();
}

Engine::~Engine() {
    // Limpar recursos de áudio se necessário
}

void Engine::carregarCasos() {
    std::ifstream arquivo("data/casos.txt");
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de casos");
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        std::istringstream iss(linha);
        Caso caso;
        std::string campo;
        
        std::getline(iss, caso.id, '|');
        std::getline(iss, caso.titulo, '|');
        std::getline(iss, caso.descricao, '|');
        std::getline(iss, caso.vitima, '|');
        std::getline(iss, caso.local, '|');
        std::getline(iss, campo, '|');
        caso.dificuldade = std::stoi(campo);

        casos.push_back(caso);
    }
}

void Engine::carregarSons() {
    // Configuração dos sons do jogo
    sons["menu"] = {"Menu", "sounds/menu.wav", true};
    sons["investigacao"] = {"Investigação", "sounds/investigacao.wav", true};
    sons["interrogatorio"] = {"Interrogatório", "sounds/interrogatorio.wav", true};
    sons["descoberta"] = {"Descoberta", "sounds/descoberta.wav", false};
    sons["acusacao"] = {"Acusação", "sounds/acusacao.wav", false};
}

void Engine::tocarSom(const std::string& nome) {
    if (!somAtivo) return;
    
    auto it = sons.find(nome);
    if (it != sons.end()) {
        // Implementar reprodução de som aqui
        // Por enquanto, apenas simula o som
        std::cout << "\n[Reproduzindo: " << it->second.nome << "]\n";
    }
}

void Engine::pararSom(const std::string& nome) {
    auto it = sons.find(nome);
    if (it != sons.end()) {
        // Implementar parada de som aqui
        std::cout << "\n[Parando: " << it->second.nome << "]\n";
    }
}

void Engine::iniciarTempo(std::chrono::minutes limite) {
    tempoInicio = std::chrono::system_clock::now();
    tempoLimite = limite;
    tempoRestante = limite;
}

void Engine::atualizarTempo() {
    auto agora = std::chrono::system_clock::now();
    auto decorrido = std::chrono::duration_cast<std::chrono::minutes>(agora - tempoInicio);
    tempoRestante = tempoLimite - decorrido;
}

std::chrono::minutes Engine::getTempoRestante() const {
    return tempoRestante;
}

bool Engine::tempoAcabou() const {
    return tempoRestante <= std::chrono::minutes(0);
}

void Engine::iniciarNovoCaso() {
    casoAtual = gerarCasoAleatorio();
    tocarSom("investigacao");
}

const Engine::Caso& Engine::getCasoAtual() const {
    return casoAtual;
}

Engine::Caso Engine::gerarCasoAleatorio() {
    if (casos.empty()) {
        throw std::runtime_error("Não há casos disponíveis");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, casos.size() - 1);
    
    return casos[dis(gen)];
}

std::vector<Pista> Engine::getPistasIniciais() {
    return gerarPistasParaCaso(casoAtual);
}

std::vector<Suspeito> Engine::getSuspeitosIniciais() {
    return gerarSuspeitosParaCaso(casoAtual);
}

std::vector<Pista> Engine::gerarPistasParaCaso(const Caso& caso) {
    std::vector<Pista> pistas;
    std::ifstream arquivo("data/pistas_base.txt");
    
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de pistas");
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        std::istringstream iss(linha);
        std::string descricao, relevancia, local, tipo, relacionado;
        
        std::getline(iss, descricao, '|');
        std::getline(iss, relevancia, '|');
        std::getline(iss, local, '|');
        std::getline(iss, tipo, '|');
        std::getline(iss, relacionado, '|');

        // Adiciona a pista com 70% de chance
        if (utils::numeroAleatorio(1, 100) <= 70) {
            pistas.emplace_back(descricao, std::stoi(relevancia), relacionado, local);
        }
    }

    return pistas;
}

std::vector<Suspeito> Engine::gerarSuspeitosParaCaso(const Caso& caso) {
    std::vector<Suspeito> suspeitos;
    std::ifstream arquivo("data/suspeitos_base.txt");
    
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de suspeitos");
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        std::istringstream iss(linha);
        std::string nome, idade, profissao, personalidade, historico;
        
        std::getline(iss, nome, '|');
        std::getline(iss, idade, '|');
        std::getline(iss, profissao, '|');
        std::getline(iss, personalidade, '|');
        std::getline(iss, historico, '|');

        // Adiciona o suspeito com 60% de chance
        if (utils::numeroAleatorio(1, 100) <= 60) {
            bool eCulpado = (nome == caso.culpado);
            suspeitos.emplace_back(nome, std::stoi(idade), profissao, historico, eCulpado);
        }
    }

    return suspeitos;
}

void Engine::ativarSom(bool ativo) {
    somAtivo = ativo;
}

void Engine::tocarSomMenu() {
    tocarSom("menu");
}

void Engine::tocarSomInvestigacao() {
    tocarSom("investigacao");
}

void Engine::tocarSomInterrogatorio() {
    tocarSom("interrogatorio");
}

void Engine::tocarSomDescoberta() {
    tocarSom("descoberta");
}

void Engine::tocarSomAcusacao() {
    tocarSom("acusacao");
}

int Engine::calcularDificuldade() const {
    return casoAtual.dificuldade;
}

std::string Engine::gerarDica() const {
    // Implementar lógica de dicas baseada no caso atual
    return "Dica: " + casoAtual.descricao;
}

bool Engine::verificarAcusacao(const std::string& nomeSuspeito) const {
    return nomeSuspeito == casoAtual.culpado;
} 