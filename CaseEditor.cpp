#include "CaseEditor.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>

CaseEditor::CaseEditor() : modoEdicao(false) {
    carregarCasos();
}

void CaseEditor::carregarCasos() {
    std::ifstream arquivo("data/casos.txt");
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de casos");
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        std::istringstream iss(linha);
        CasoEditavel caso;
        std::string campo;
        
        std::getline(iss, caso.id, '|');
        std::getline(iss, caso.titulo, '|');
        std::getline(iss, caso.descricao, '|');
        std::getline(iss, caso.vitima, '|');
        std::getline(iss, caso.local, '|');
        std::getline(iss, campo, '|');
        caso.dificuldade = std::stoi(campo);

        casos.push_back(caso);
    }
}

void CaseEditor::salvarCasos() {
    std::ofstream arquivo("data/casos.txt");
    if (arquivo.is_open()) {
        arquivo << "# Formato: ID|Título|Descrição|Vítima|Local|Dificuldade\n\n";
        for (const auto& caso : casos) {
            arquivo << caso.id << "|"
                   << caso.titulo << "|"
                   << caso.descricao << "|"
                   << caso.vitima << "|"
                   << caso.local << "|"
                   << caso.dificuldade << "\n";
        }
        arquivo.close();
    }
}

void CaseEditor::iniciar() {
    while (true) {
        std::cout << "\n\033[1;33m=== Editor de Casos ===\033[0m\n";
        std::cout << "1. Novo Caso\n";
        std::cout << "2. Editar Caso\n";
        std::cout << "3. Excluir Caso\n";
        std::cout << "4. Listar Casos\n";
        std::cout << "5. Exportar Caso\n";
        std::cout << "6. Importar Caso\n";
        std::cout << "7. Sair\n";
        std::cout << "Escolha uma opção: ";

        int opcao;
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1:
                novoCaso();
                break;
            case 2:
                listarCasos();
                std::cout << "Digite o ID do caso a editar: ";
                std::string id;
                std::getline(std::cin, id);
                editarCaso(id);
                break;
            case 3:
                listarCasos();
                std::cout << "Digite o ID do caso a excluir: ";
                std::getline(std::cin, id);
                excluirCaso(id);
                break;
            case 4:
                listarCasos();
                break;
            case 5:
                listarCasos();
                std::cout << "Digite o ID do caso a exportar: ";
                std::getline(std::cin, id);
                exportarCaso(id);
                break;
            case 6:
                std::cout << "Digite o nome do arquivo a importar: ";
                std::string arquivo;
                std::getline(std::cin, arquivo);
                importarCaso(arquivo);
                break;
            case 7:
                return;
            default:
                std::cout << "Opção inválida!\n";
        }
    }
}

void CaseEditor::novoCaso() {
    CasoEditavel caso;
    caso.id = "C" + std::to_string(casos.size() + 1);
    
    std::cout << "\n\033[1;32m=== Novo Caso ===\033[0m\n";
    
    std::cout << "Título: ";
    std::getline(std::cin, caso.titulo);
    
    std::cout << "Descrição: ";
    std::getline(std::cin, caso.descricao);
    
    std::cout << "Vítima: ";
    std::getline(std::cin, caso.vitima);
    
    std::cout << "Local: ";
    std::getline(std::cin, caso.local);
    
    std::cout << "Dificuldade (1-5): ";
    std::cin >> caso.dificuldade;
    std::cin.ignore();
    
    casoAtual = caso;
    modoEdicao = true;
    mostrarMenuEdicao();
    
    casos.push_back(caso);
    salvarCasos();
}

void CaseEditor::editarCaso(const std::string& id) {
    auto it = std::find_if(casos.begin(), casos.end(),
                          [&id](const CasoEditavel& c) { return c.id == id; });
    
    if (it != casos.end()) {
        casoAtual = *it;
        modoEdicao = true;
        mostrarMenuEdicao();
        *it = casoAtual;
        salvarCasos();
    } else {
        std::cout << "Caso não encontrado!\n";
    }
}

void CaseEditor::excluirCaso(const std::string& id) {
    auto it = std::find_if(casos.begin(), casos.end(),
                          [&id](const CasoEditavel& c) { return c.id == id; });
    
    if (it != casos.end()) {
        casos.erase(it);
        salvarCasos();
        std::cout << "Caso excluído com sucesso!\n";
    } else {
        std::cout << "Caso não encontrado!\n";
    }
}

void CaseEditor::listarCasos() {
    std::cout << "\n\033[1;35m=== Casos Disponíveis ===\033[0m\n";
    for (const auto& caso : casos) {
        std::cout << "ID: " << caso.id << "\n";
        std::cout << "Título: " << caso.titulo << "\n";
        std::cout << "Vítima: " << caso.vitima << "\n";
        std::cout << "Dificuldade: " << caso.dificuldade << "/5\n";
        std::cout << "-------------------\n";
    }
}

void CaseEditor::mostrarMenuEdicao() {
    while (modoEdicao) {
        std::cout << "\n\033[1;36m=== Editando Caso: " << casoAtual.titulo << " ===\033[0m\n";
        std::cout << "1. Editar Título\n";
        std::cout << "2. Editar Descrição\n";
        std::cout << "3. Editar Vítima\n";
        std::cout << "4. Editar Local\n";
        std::cout << "5. Editar Dificuldade\n";
        std::cout << "6. Editar Pistas\n";
        std::cout << "7. Editar Suspeitos\n";
        std::cout << "8. Definir Culpado\n";
        std::cout << "9. Validar Caso\n";
        std::cout << "0. Salvar e Sair\n";
        std::cout << "Escolha uma opção: ";

        int opcao;
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1: editarTitulo(); break;
            case 2: editarDescricao(); break;
            case 3: editarVitima(); break;
            case 4: editarLocal(); break;
            case 5: editarDificuldade(); break;
            case 6: editarPistas(); break;
            case 7: editarSuspeitos(); break;
            case 8: definirCulpado(); break;
            case 9: validarCaso(); break;
            case 0:
                modoEdicao = false;
                break;
            default:
                std::cout << "Opção inválida!\n";
        }
    }
}

void CaseEditor::editarTitulo() {
    std::cout << "Novo título: ";
    std::getline(std::cin, casoAtual.titulo);
}

void CaseEditor::editarDescricao() {
    std::cout << "Nova descrição: ";
    std::getline(std::cin, casoAtual.descricao);
}

void CaseEditor::editarVitima() {
    std::cout << "Nova vítima: ";
    std::getline(std::cin, casoAtual.vitima);
}

void CaseEditor::editarLocal() {
    std::cout << "Novo local: ";
    std::getline(std::cin, casoAtual.local);
}

void CaseEditor::editarDificuldade() {
    std::cout << "Nova dificuldade (1-5): ";
    std::cin >> casoAtual.dificuldade;
    std::cin.ignore();
}

void CaseEditor::editarPistas() {
    std::cout << "\n=== Pistas Atuais ===\n";
    for (size_t i = 0; i < casoAtual.pistas.size(); ++i) {
        std::cout << i + 1 << ". " << casoAtual.pistas[i] << "\n";
    }
    
    std::cout << "\n1. Adicionar Pista\n";
    std::cout << "2. Remover Pista\n";
    std::cout << "3. Voltar\n";
    std::cout << "Escolha uma opção: ";
    
    int opcao;
    std::cin >> opcao;
    std::cin.ignore();
    
    if (opcao == 1) {
        std::cout << "Nova pista: ";
        std::string pista;
        std::getline(std::cin, pista);
        casoAtual.pistas.push_back(pista);
    } else if (opcao == 2) {
        std::cout << "Índice da pista a remover: ";
        size_t indice;
        std::cin >> indice;
        std::cin.ignore();
        
        if (indice > 0 && indice <= casoAtual.pistas.size()) {
            casoAtual.pistas.erase(casoAtual.pistas.begin() + indice - 1);
        }
    }
}

void CaseEditor::editarSuspeitos() {
    std::cout << "\n=== Suspeitos Atuais ===\n";
    for (size_t i = 0; i < casoAtual.suspeitos.size(); ++i) {
        std::cout << i + 1 << ". " << casoAtual.suspeitos[i] << "\n";
    }
    
    std::cout << "\n1. Adicionar Suspeito\n";
    std::cout << "2. Remover Suspeito\n";
    std::cout << "3. Voltar\n";
    std::cout << "Escolha uma opção: ";
    
    int opcao;
    std::cin >> opcao;
    std::cin.ignore();
    
    if (opcao == 1) {
        std::cout << "Novo suspeito: ";
        std::string suspeito;
        std::getline(std::cin, suspeito);
        casoAtual.suspeitos.push_back(suspeito);
    } else if (opcao == 2) {
        std::cout << "Índice do suspeito a remover: ";
        size_t indice;
        std::cin >> indice;
        std::cin.ignore();
        
        if (indice > 0 && indice <= casoAtual.suspeitos.size()) {
            casoAtual.suspeitos.erase(casoAtual.suspeitos.begin() + indice - 1);
        }
    }
}

void CaseEditor::definirCulpado() {
    std::cout << "\n=== Suspeitos Disponíveis ===\n";
    for (size_t i = 0; i < casoAtual.suspeitos.size(); ++i) {
        std::cout << i + 1 << ". " << casoAtual.suspeitos[i] << "\n";
    }
    
    std::cout << "Escolha o culpado (número): ";
    size_t escolha;
    std::cin >> escolha;
    std::cin.ignore();
    
    if (escolha > 0 && escolha <= casoAtual.suspeitos.size()) {
        casoAtual.culpado = casoAtual.suspeitos[escolha - 1];
    }
}

void CaseEditor::validarCaso() {
    bool valido = true;
    std::string mensagem;
    
    if (casoAtual.titulo.empty()) {
        valido = false;
        mensagem += "Título não pode estar vazio\n";
    }
    
    if (casoAtual.descricao.empty()) {
        valido = false;
        mensagem += "Descrição não pode estar vazia\n";
    }
    
    if (casoAtual.vitima.empty()) {
        valido = false;
        mensagem += "Vítima não pode estar vazia\n";
    }
    
    if (casoAtual.local.empty()) {
        valido = false;
        mensagem += "Local não pode estar vazio\n";
    }
    
    if (casoAtual.dificuldade < 1 || casoAtual.dificuldade > 5) {
        valido = false;
        mensagem += "Dificuldade deve estar entre 1 e 5\n";
    }
    
    if (casoAtual.pistas.empty()) {
        valido = false;
        mensagem += "Caso deve ter pelo menos uma pista\n";
    }
    
    if (casoAtual.suspeitos.empty()) {
        valido = false;
        mensagem += "Caso deve ter pelo menos um suspeito\n";
    }
    
    if (casoAtual.culpado.empty()) {
        valido = false;
        mensagem += "Culpado deve ser definido\n";
    }
    
    if (valido) {
        std::cout << "\n\033[1;32mCaso válido!\033[0m\n";
    } else {
        std::cout << "\n\033[1;31mCaso inválido:\033[0m\n" << mensagem;
    }
}

void CaseEditor::exportarCaso(const std::string& id) {
    auto it = std::find_if(casos.begin(), casos.end(),
                          [&id](const CasoEditavel& c) { return c.id == id; });
    
    if (it != casos.end()) {
        std::string nomeArquivo = "casos_exportados/" + id + ".txt";
        std::ofstream arquivo(nomeArquivo);
        
        if (arquivo.is_open()) {
            arquivo << "ID: " << it->id << "\n";
            arquivo << "Título: " << it->titulo << "\n";
            arquivo << "Descrição: " << it->descricao << "\n";
            arquivo << "Vítima: " << it->vitima << "\n";
            arquivo << "Local: " << it->local << "\n";
            arquivo << "Dificuldade: " << it->dificuldade << "\n";
            arquivo << "\nPistas:\n";
            for (const auto& pista : it->pistas) {
                arquivo << "- " << pista << "\n";
            }
            arquivo << "\nSuspeitos:\n";
            for (const auto& suspeito : it->suspeitos) {
                arquivo << "- " << suspeito << "\n";
            }
            arquivo << "\nCulpado: " << it->culpado << "\n";
            
            arquivo.close();
            std::cout << "Caso exportado com sucesso para " << nomeArquivo << "\n";
        }
    } else {
        std::cout << "Caso não encontrado!\n";
    }
}

void CaseEditor::importarCaso(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cout << "Não foi possível abrir o arquivo!\n";
        return;
    }

    CasoEditavel caso;
    std::string linha;
    
    while (std::getline(file, linha)) {
        if (linha.empty()) continue;
        
        if (linha.find("ID: ") == 0) {
            caso.id = linha.substr(4);
        } else if (linha.find("Título: ") == 0) {
            caso.titulo = linha.substr(8);
        } else if (linha.find("Descrição: ") == 0) {
            caso.descricao = linha.substr(11);
        } else if (linha.find("Vítima: ") == 0) {
            caso.vitima = linha.substr(8);
        } else if (linha.find("Local: ") == 0) {
            caso.local = linha.substr(7);
        } else if (linha.find("Dificuldade: ") == 0) {
            caso.dificuldade = std::stoi(linha.substr(12));
        } else if (linha == "Pistas:") {
            while (std::getline(file, linha) && !linha.empty()) {
                if (linha[0] == '-') {
                    caso.pistas.push_back(linha.substr(2));
                }
            }
        } else if (linha == "Suspeitos:") {
            while (std::getline(file, linha) && !linha.empty()) {
                if (linha[0] == '-') {
                    caso.suspeitos.push_back(linha.substr(2));
                }
            }
        } else if (linha.find("Culpado: ") == 0) {
            caso.culpado = linha.substr(9);
        }
    }
    
    casos.push_back(caso);
    salvarCasos();
    std::cout << "Caso importado com sucesso!\n";
} 