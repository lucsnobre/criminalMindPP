#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Configuração inicial
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Configuração do terminal para cores ANSI
    #ifdef _WIN32
        system("color");
    #endif
    
    try {
        Game jogo;
        jogo.iniciar();
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mErro fatal: " << e.what() << "\033[0m\n";
        return 1;
    }
    
    return 0;
} 