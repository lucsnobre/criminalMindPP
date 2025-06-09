#pragma once

#include <string>
#include <vector>

class Pista {
private:
    std::string descricao;
    int relevancia;
    std::string suspeitoRelacionado;
    bool foiColetada;
    std::string localEncontrado;

public:
    Pista(const std::string& descricao, int relevancia,
          const std::string& suspeitoRelacionado = "",
          const std::string& localEncontrado = "");

    // Getters
    std::string getDescricao() const { return descricao; }
    int getRelevancia() const { return relevancia; }
    std::string getSuspeitoRelacionado() const { return suspeitoRelacionado; }
    bool getFoiColetada() const { return foiColetada; }
    std::string getLocalEncontrado() const { return localEncontrado; }

    // Setters
    void setFoiColetada(bool coletada) { foiColetada = coletada; }
    void setRelevancia(int novaRelevancia) { relevancia = novaRelevancia; }

    // Métodos
    void mostrarPista() const;
    bool relacionadaAoSuspeito(const std::string& nomeSuspeito) const;
    void atualizarRelevancia(int novaRelevancia);
}; 