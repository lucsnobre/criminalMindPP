#include "Pista.hpp"
#include <iostream>

Pista::Pista(const std::string& descricao, int relevancia,
             const std::string& suspeitoRelacionado,
             const std::string& localEncontrado)
    : descricao(descricao), relevancia(relevancia),
      suspeitoRelacionado(suspeitoRelacionado),
      localEncontrado(localEncontrado), foiColetada(false) {}

void Pista::mostrarPista() const {
    std::cout << "\n=== Pista ===\n";
    std::cout << "Descrição: " << descricao << "\n";
    std::cout << "Relevância: " << relevancia << "/10\n";
    if (!suspeitoRelacionado.empty()) {
        std::cout << "Relacionada a: " << suspeitoRelacionado << "\n";
    }
    if (!localEncontrado.empty()) {
        std::cout << "Local encontrado: " << localEncontrado << "\n";
    }
    std::cout << "Status: " << (foiColetada ? "Coletada" : "Não coletada") << "\n";
    std::cout << "============\n";
}

bool Pista::relacionadaAoSuspeito(const std::string& nomeSuspeito) const {
    return suspeitoRelacionado == nomeSuspeito;
}

void Pista::atualizarRelevancia(int novaRelevancia) {
    relevancia = std::max(0, std::min(10, novaRelevancia));
} 