#include "../include/Solutii.h"

Solutii::Solutii(const std::vector<std::string>& solutii) : cuvinte(solutii) {}

bool Solutii::esteSolutie(const std::string& incercare) const {
    for (const auto& sol : cuvinte) {
        if (sol == incercare) {
            return true;
        }
    }
    return false;
}

int Solutii::getNumarSolutii() const {
    return cuvinte.size();
}

const std::vector<std::string>& Solutii::getToateSolutiile() const {
    return cuvinte;
}