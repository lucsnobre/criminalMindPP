#pragma once

#include "Suspeito.hpp"
#include "Pista.hpp"
#include "Engine.hpp"
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <chrono>

class Game {
private:
    std::vector<Suspeito> suspeitos;
    std::vector<Pista> pistas;
    std::string casoAtual;
    bool jogoEmAndamento;
    int reputacao;
    std::string nomeDetetive;
    std::unique_ptr<Engine> engine;
    
    // Métodos privados
    void carregarCaso();
    void gerarNovoCaso();
    void salvarProgresso();
    void carregarProgresso();
    void mostrarMenu();
    void investigarCena();
    void interrogarSuspeitos();
    void analisarPistas();
    void fazerAcusacao();
    void mostrarEstatisticas();
    void mostrarTempoRestante();
    void atualizarTempo();
    void mostrarDica();

public:
    Game();
    ~Game();

    // Métodos principais
    void iniciar();
    void executar();
    void pausar();
    void continuar();
    void finalizar();

    // Getters
    bool getJogoEmAndamento() const { return jogoEmAndamento; }
    int getReputacao() const { return reputacao; }
    std::string getNomeDetetive() const { return nomeDetetive; }

    // Setters
    void setNomeDetetive(const std::string& nome) { nomeDetetive = nome; }
}; 