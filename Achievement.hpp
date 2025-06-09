#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>

class Achievement {
private:
    struct Conquista {
        std::string id;
        std::string titulo;
        std::string descricao;
        bool desbloqueada;
        std::chrono::system_clock::time_point dataDesbloqueio;
        int pontos;
    };

    std::map<std::string, Conquista> conquistas;
    int pontosTotais;

    // Conquistas predefinidas
    void inicializarConquistas();

public:
    Achievement();
    
    // Getters
    bool isDesbloqueada(const std::string& id) const;
    int getPontosTotais() const { return pontosTotais; }
    std::vector<Conquista> getConquistas() const;
    
    // Métodos principais
    void desbloquear(const std::string& id);
    void verificarConquistas(int casosResolvidos, int reputacao, int tempoTotal);
    void mostrarConquistas() const;
    void salvarProgresso();
    void carregarProgresso();
    
    // Conquistas específicas
    void verificarPrimeiroCaso();
    void verificarDetetivePerfeito();
    void verificarVelocista();
    void verificarInterrogador();
    void verificarColecionador();
}; 