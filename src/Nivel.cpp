#include "../include/Nivel.h"
#include <iostream>

Nivel::Nivel(int nr, const std::vector<std::string>& cuvinte)
    : nrNivel(nr), solutii(cuvinte) {
    for (const auto& cuv : cuvinte) {
        litereDisponibile.adaugaLitereDinCuvant(cuv);
    }
}

bool Nivel::esteSolutie(const std::string& incercare) const {
    return solutii.esteSolutie(incercare);
}

int Nivel::getNumarSolutii() const {
    return solutii.getNumarSolutii();
}

int Nivel::getNrNivel() const {
    return nrNivel;
}

const std::vector<std::string>& Nivel::getNivelSolutii() const {
    return solutii.getToateSolutiile();
}

std::ostream& operator<<(std::ostream& os, const Nivel& n) {
    os << "\nNivelul " << n.nrNivel << "\n";
    os << "Litere Disponibile: " << n.litereDisponibile << "\n";
    return os;
}