#include "Suspeito.hpp"
#include <iostream>
#include <random>
#include <algorithm>

Suspeito::Suspeito(const std::string& nome, int idade, const std::string& relacao,
                   const std::string& historico, bool eCulpado)
    : nome(nome), idade(idade), relacaoComVitima(relacao),
      historico(historico), nivelNervosismo(0), eCulpado(eCulpado),
      falaVerdade(!eCulpado) {
    
    // Inicializa respostas possíveis
    respostasPossiveis = {
        "Não tenho certeza...",
        "Não me lembro exatamente...",
        "Posso estar errado, mas...",
        "Sim, tenho certeza disso.",
        "Não, absolutamente não."
    };
}

std::string Suspeito::responderPergunta(const std::string& pergunta) {
    if (decidirSeMente()) {
        return mentir() ? "Não sei nada sobre isso." : "Sim, posso confirmar isso.";
    }
    
    // Lógica básica de resposta baseada no perfil
    if (pergunta.find("onde") != std::string::npos) {
        return "Estava em casa naquele momento.";
    } else if (pergunta.find("quando") != std::string::npos) {
        return "Não me lembro exatamente do horário.";
    }
    
    // Resposta aleatória das possíveis
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, respostasPossiveis.size() - 1);
    return respostasPossiveis[dis(gen)];
}

bool Suspeito::mentir() const {
    if (!eCulpado) return false;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    // Culpados têm 70% de chance de mentir
    return dis(gen) < 0.7;
}

std::string Suspeito::entregarOutro(const std::vector<Suspeito>& outrosSuspeitos) {
    if (outrosSuspeitos.empty()) return "Não tenho ninguém para acusar.";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, outrosSuspeitos.size() - 1);
    
    const Suspeito& outro = outrosSuspeitos[dis(gen)];
    return "Acho que " + outro.getNome() + " pode estar envolvido...";
}

void Suspeito::mostrarPerfil() const {
    std::cout << "\n=== Perfil do Suspeito ===\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Idade: " << idade << "\n";
    std::cout << "Relação com a vítima: " << relacaoComVitima << "\n";
    std::cout << "Histórico: " << historico << "\n";
    std::cout << "Nível de nervosismo: " << nivelNervosismo << "\n";
    std::cout << "========================\n";
}

void Suspeito::aumentarNervosismo(int valor) {
    nivelNervosismo = std::min(100, nivelNervosismo + valor);
}

void Suspeito::diminuirNervosismo(int valor) {
    nivelNervosismo = std::max(0, nivelNervosismo - valor);
}

bool Suspeito::decidirSeMente() const {
    if (!eCulpado) return false;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    // Chance de mentir aumenta com o nervosismo
    double chanceMentir = 0.3 + (nivelNervosismo / 200.0);
    return dis(gen) < chanceMentir;
} 