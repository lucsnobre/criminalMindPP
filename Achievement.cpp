#include "Achievement.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Achievement::Achievement() : pontosTotais(0) {
    inicializarConquistas();
}

void Achievement::inicializarConquistas() {
    // Conquistas básicas
    conquistas["primeiro_caso"] = {
        "primeiro_caso",
        "Primeiro Caso",
        "Resolva seu primeiro caso",
        false,
        std::chrono::system_clock::now(),
        100
    };

    conquistas["detetive_perfeito"] = {
        "detetive_perfeito",
        "Detetive Perfeito",
        "Resolva um caso sem cometer erros",
        false,
        std::chrono::system_clock::now(),
        500
    };

    conquistas["velocista"] = {
        "velocista",
        "Velocista",
        "Resolva um caso em menos de 10 minutos",
        false,
        std::chrono::system_clock::now(),
        300
    };

    conquistas["interrogador"] = {
        "interrogador",
        "Interrogador",
        "Faça 10 interrogatórios em um único caso",
        false,
        std::chrono::system_clock::now(),
        200
    };

    conquistas["colecionador"] = {
        "colecionador",
        "Colecionador",
        "Colete todas as pistas em um caso",
        false,
        std::chrono::system_clock::now(),
        400
    };
}

bool Achievement::isDesbloqueada(const std::string& id) const {
    auto it = conquistas.find(id);
    return it != conquistas.end() && it->second.desbloqueada;
}

std::vector<Achievement::Conquista> Achievement::getConquistas() const {
    std::vector<Conquista> resultado;
    for (const auto& pair : conquistas) {
        resultado.push_back(pair.second);
    }
    return resultado;
}

void Achievement::desbloquear(const std::string& id) {
    auto it = conquistas.find(id);
    if (it != conquistas.end() && !it->second.desbloqueada) {
        it->second.desbloqueada = true;
        it->second.dataDesbloqueio = std::chrono::system_clock::now();
        pontosTotais += it->second.pontos;
        
        std::cout << "\n\033[1;32m=== Nova Conquista Desbloqueada! ===\033[0m\n";
        std::cout << "Título: " << it->second.titulo << "\n";
        std::cout << "Descrição: " << it->second.descricao << "\n";
        std::cout << "Pontos: +" << it->second.pontos << "\n";
        std::cout << "==============================\n";
        
        salvarProgresso();
    }
}

void Achievement::verificarConquistas(int casosResolvidos, int reputacao, int tempoTotal) {
    if (casosResolvidos == 1) {
        verificarPrimeiroCaso();
    }
    
    if (reputacao >= 100) {
        verificarDetetivePerfeito();
    }
    
    if (tempoTotal < 10) {
        verificarVelocista();
    }
}

void Achievement::verificarPrimeiroCaso() {
    if (!isDesbloqueada("primeiro_caso")) {
        desbloquear("primeiro_caso");
    }
}

void Achievement::verificarDetetivePerfeito() {
    if (!isDesbloqueada("detetive_perfeito")) {
        desbloquear("detetive_perfeito");
    }
}

void Achievement::verificarVelocista() {
    if (!isDesbloqueada("velocista")) {
        desbloquear("velocista");
    }
}

void Achievement::verificarInterrogador() {
    if (!isDesbloqueada("interrogador")) {
        desbloquear("interrogador");
    }
}

void Achievement::verificarColecionador() {
    if (!isDesbloqueada("colecionador")) {
        desbloquear("colecionador");
    }
}

void Achievement::mostrarConquistas() const {
    std::cout << "\n\033[1;33m=== Conquistas ===\033[0m\n";
    std::cout << "Pontos totais: " << pontosTotais << "\n\n";
    
    for (const auto& pair : conquistas) {
        const auto& conquista = pair.second;
        std::cout << "Título: " << conquista.titulo << "\n";
        std::cout << "Descrição: " << conquista.descricao << "\n";
        std::cout << "Status: " << (conquista.desbloqueada ? "Desbloqueada" : "Bloqueada") << "\n";
        if (conquista.desbloqueada) {
            auto time = std::chrono::system_clock::to_time_t(conquista.dataDesbloqueio);
            std::cout << "Desbloqueada em: " << std::ctime(&time);
        }
        std::cout << "Pontos: " << conquista.pontos << "\n";
        std::cout << "-------------------\n";
    }
}

void Achievement::salvarProgresso() {
    std::ofstream arquivo("achievements.txt");
    if (arquivo.is_open()) {
        arquivo << pontosTotais << "\n";
        for (const auto& pair : conquistas) {
            const auto& conquista = pair.second;
            arquivo << conquista.id << "|"
                   << conquista.desbloqueada << "|"
                   << std::chrono::system_clock::to_time_t(conquista.dataDesbloqueio) << "\n";
        }
        arquivo.close();
    }
}

void Achievement::carregarProgresso() {
    std::ifstream arquivo("achievements.txt");
    if (arquivo.is_open()) {
        arquivo >> pontosTotais;
        arquivo.ignore();
        
        std::string linha;
        while (std::getline(arquivo, linha)) {
            std::istringstream iss(linha);
            std::string id, desbloqueada, timestamp;
            
            std::getline(iss, id, '|');
            std::getline(iss, desbloqueada, '|');
            std::getline(iss, timestamp);
            
            auto it = conquistas.find(id);
            if (it != conquistas.end()) {
                it->second.desbloqueada = (desbloqueada == "1");
                it->second.dataDesbloqueio = std::chrono::system_clock::from_time_t(std::stoll(timestamp));
            }
        }
        arquivo.close();
    }
} 