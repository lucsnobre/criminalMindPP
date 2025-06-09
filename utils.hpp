#pragma once

#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <iostream>

namespace utils {

// Função para simular digitação
inline void simularDigitacao(const std::string& texto, int velocidade = 50) {
    for (char c : texto) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(velocidade));
    }
    std::cout << std::endl;
}

// Função para limpar a tela do terminal
inline void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para gerar número aleatório em um intervalo
inline int numeroAleatorio(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Função para mostrar uma barra de progresso
inline void mostrarBarraProgresso(int duracao = 3) {
    const int largura = 50;
    for (int i = 0; i <= largura; ++i) {
        std::cout << "\r\033[1;36m[";
        for (int j = 0; j < largura; ++j) {
            if (j < i) std::cout << "=";
            else std::cout << " ";
        }
        std::cout << "] " << (i * 100 / largura) << "%\033[0m" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(duracao * 1000 / largura));
    }
    std::cout << std::endl;
}

// Função para formatar texto com cores
inline std::string colorirTexto(const std::string& texto, const std::string& cor) {
    return "\033[" + cor + "m" + texto + "\033[0m";
}

// Função para verificar se uma string contém outra (case insensitive)
inline bool contemString(const std::string& texto, const std::string& busca) {
    std::string textoLower = texto;
    std::string buscaLower = busca;
    
    std::transform(textoLower.begin(), textoLower.end(), textoLower.begin(), ::tolower);
    std::transform(buscaLower.begin(), buscaLower.end(), buscaLower.begin(), ::tolower);
    
    return textoLower.find(buscaLower) != std::string::npos;
}

// Função para dividir uma string em tokens
inline std::vector<std::string> dividirString(const std::string& texto, char delimitador = ' ') {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(texto);
    
    while (std::getline(tokenStream, token, delimitador)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

} // namespace utils 