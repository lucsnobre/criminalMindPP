#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <memory>
#include <map>
#include "Suspeito.hpp"
#include "Pista.hpp"

class Engine {
private:
    // Sistema de tempo
    std::chrono::system_clock::time_point tempoInicio;
    std::chrono::minutes tempoLimite;
    std::chrono::minutes tempoRestante;
    
    // Sistema de casos
    struct Caso {
        std::string id;
        std::string titulo;
        std::string descricao;
        std::string vitima;
        std::string local;
        int dificuldade;
        std::vector<std::string> pistasRelevantes;
        std::string culpado;
    };
    
    std::vector<Caso> casos;
    Caso casoAtual;
    
    // Sistema de sons
    struct Som {
        std::string nome;
        std::string caminho;
        bool loop;
    };
    
    std::map<std::string, Som> sons;
    bool somAtivo;
    
    // Métodos privados
    void carregarCasos();
    void carregarSons();
    void tocarSom(const std::string& nome);
    void pararSom(const std::string& nome);
    void atualizarTempo();
    Caso gerarCasoAleatorio();
    std::vector<Pista> gerarPistasParaCaso(const Caso& caso);
    std::vector<Suspeito> gerarSuspeitosParaCaso(const Caso& caso);

public:
    Engine();
    ~Engine();
    
    // Métodos de tempo
    void iniciarTempo(std::chrono::minutes limite);
    std::chrono::minutes getTempoRestante() const;
    bool tempoAcabou() const;
    
    // Métodos de caso
    void iniciarNovoCaso();
    const Caso& getCasoAtual() const;
    std::vector<Pista> getPistasIniciais();
    std::vector<Suspeito> getSuspeitosIniciais();
    
    // Métodos de som
    void ativarSom(bool ativo);
    void tocarSomMenu();
    void tocarSomInvestigacao();
    void tocarSomInterrogatorio();
    void tocarSomDescoberta();
    void tocarSomAcusacao();
    
    // Métodos de utilidade
    int calcularDificuldade() const;
    std::string gerarDica() const;
    bool verificarAcusacao(const std::string& nomeSuspeito) const;
}; 