#include "Game.hpp"
#include "Achievement.hpp"
#include "CaseEditor.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>

int main() {
    try {
        // Configurar cores do terminal
        utils::configurarCores();
        
        // Criar instâncias das classes principais
        auto game = std::make_unique<Game>();
        auto achievements = std::make_unique<Achievement>();
        auto editor = std::make_unique<CaseEditor>();
        
        while (true) {
            std::cout << "\n\033[1;33m=== CriminalMind++ ===\033[0m\n";
            std::cout << "1. Iniciar Jogo\n";
            std::cout << "2. Editor de Casos\n";
            std::cout << "3. Conquistas\n";
            std::cout << "4. Sair\n";
            std::cout << "Escolha uma opção: ";
            
            int opcao;
            std::cin >> opcao;
            std::cin.ignore();
            
            switch (opcao) {
                case 1:
                    game->iniciar();
                    break;
                case 2:
                    editor->iniciar();
                    break;
                case 3:
                    achievements->mostrarConquistas();
                    break;
                case 4:
                    return 0;
                default:
                    std::cout << "Opção inválida!\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "\n\033[1;31mErro: " << e.what() << "\033[0m\n";
        return 1;
    }
    
    return 0;
} 