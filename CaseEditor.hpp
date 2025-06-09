#pragma once

#include <string>
#include <vector>
#include <map>
#include "Engine.hpp"

class CaseEditor {
private:
    struct CasoEditavel {
        std::string id;
        std::string titulo;
        std::string descricao;
        std::string vitima;
        std::string local;
        int dificuldade;
        std::vector<std::string> pistas;
        std::string culpado;
        std::vector<std::string> suspeitos;
    };

    std::vector<CasoEditavel> casos;
    CasoEditavel casoAtual;
    bool modoEdicao;

    // Métodos privados
    void carregarCasos();
    void salvarCasos();
    void mostrarMenuEdicao();
    void editarTitulo();
    void editarDescricao();
    void editarVitima();
    void editarLocal();
    void editarDificuldade();
    void editarPistas();
    void editarSuspeitos();
    void definirCulpado();
    void validarCaso();

public:
    CaseEditor();
    
    // Métodos principais
    void iniciar();
    void novoCaso();
    void editarCaso(const std::string& id);
    void excluirCaso(const std::string& id);
    void listarCasos();
    void exportarCaso(const std::string& id);
    void importarCaso(const std::string& arquivo);
    
    // Getters
    bool getModoEdicao() const { return modoEdicao; }
    const CasoEditavel& getCasoAtual() const { return casoAtual; }
    
    // Setters
    void setModoEdicao(bool modo) { modoEdicao = modo; }
}; 