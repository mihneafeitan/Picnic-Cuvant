#pragma once
#include <string>
#include <iostream>

class Statistici {
private:
    std::string numeFisierJucator;
    int cuvinteCorecteTotal;
    int niveleCompletateTotal;
    int greseliTotal;

public:
    // Folosim 'explicit' pentru a trece bifa cppcheck
    explicit Statistici();

    // Functii pentru logica
    void incarca(const std::string& numeJucator);
    void salveaza() const;
    void reseteaza();

    // Functii de incrementare
    void incrementeazaCuvantCorect();
    void incrementeazaNivelCompletat();
    void incrementeazaGreseala();

    // Pentru afisare in meniu
    friend std::ostream& operator<<(std::ostream& os, const Statistici& stats);
};