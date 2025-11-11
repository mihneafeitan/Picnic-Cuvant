#pragma once
#include "Litere.h"
#include "Solutii.h"
#include <vector>
#include <string>


class Nivel {
private:
    int nrNivel;
    Solutii solutii;
    Litere litereDisponibile;

public:
    Nivel(int nr, const std::vector<std::string>& cuvinte);

    bool esteSolutie(const std::string& incercare) const;
    int getNumarSolutii() const;
    int getNrNivel() const;

    const std::vector<std::string>& getNivelSolutii() const;

    friend std::ostream& operator<<(std::ostream& os, const Nivel& n);
};