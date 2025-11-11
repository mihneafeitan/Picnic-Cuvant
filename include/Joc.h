#pragma once
#include "Jucator.h"
#include "Nivel.h"
#include <vector>
#include <string>

class Joc {
private:
    std::vector<Nivel> toateNivelele;
    Jucator jucator;
    bool jucatorAreProgres;

    // Functii helper private
    void incarcaNivele(const std::string& numeFisier);
    void afiseazaMeniu() const;

    // Returneaza 'true' daca jucatorul a tastat 'exit', 'false' daca a completat nivelul
    bool joacaUnNivel();

    // Functia noua care va rula nivelele intr-o bucla
    void ruleazaSesiuneDeJoc();

    void afiseazaProgresNivelCurent() const;

public:
    explicit Joc(const std::string& fisierNivele);
    void ruleaza(); // Functia principala a jocului
};