#pragma once

#include <string>
#include <vector>
#include <random>

class Suspeito {
private:
    std::string nome;
    int idade;
    std::string relacaoComVitima;
    std::string historico;
    int nivelNervosismo;
    bool eCulpado;
    bool falaVerdade;
    std::vector<std::string> respostasPossiveis;

public:
    Suspeito(const std::string& nome, int idade, const std::string& relacao,
             const std::string& historico, bool eCulpado = false);

    // Getters
    std::string getNome() const { return nome; }
    int getIdade() const { return idade; }
    std::string getRelacaoComVitima() const { return relacaoComVitima; }
    bool getECulpado() const { return eCulpado; }

    // Métodos principais
    std::string responderPergunta(const std::string& pergunta);
    bool mentir() const;
    std::string entregarOutro(const std::vector<Suspeito>& outrosSuspeitos);
    void mostrarPerfil() const;
    
    // Métodos auxiliares
    void aumentarNervosismo(int valor);
    void diminuirNervosismo(int valor);
    bool decidirSeMente() const;
}; 