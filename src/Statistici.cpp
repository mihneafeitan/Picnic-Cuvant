#include "../include/Statistici.h"
#include <fstream> // Pentru citire/scriere in fisiere
#include <iostream>

// Constructorul initializeaza totul cu 0
Statistici::Statistici()
    : numeFisierJucator(""),
      cuvinteCorecteTotal(0),
      niveleCompletateTotal(0),
      greseliTotal(0) {}

void Statistici::incarca(const std::string& numeJucator) {
    this->numeFisierJucator = "stats/" + numeJucator + ".stats";

    std::ifstream fisierIn(this->numeFisierJucator);
    if (fisierIn) {
        // Daca fisierul exista, citim datele
        fisierIn >> cuvinteCorecteTotal;
        fisierIn >> niveleCompletateTotal;
        fisierIn >> greseliTotal;
        fisierIn.close();
    } else {
        // Daca fisierul nu exista, il cream cu valorile default (0)
        salveaza();
    }
}

void Statistici::salveaza() const {
    if (numeFisierJucator.empty()) {
        return; // Nu salvam daca nu a fost setat un jucator
    }

    std::ofstream fisierOut(this->numeFisierJucator);
    if (fisierOut) {
        fisierOut << cuvinteCorecteTotal << "\n";
        fisierOut << niveleCompletateTotal << "\n";
        fisierOut << greseliTotal << "\n";
        fisierOut.close();
    } else {
        std::cerr << "Eroare: Nu s-au putut salva statisticile in " << numeFisierJucator << "\n";
    }
}

void Statistici::reseteaza() {
    cuvinteCorecteTotal = 0;
    niveleCompletateTotal = 0;
    greseliTotal = 0;
    // Salvam imediat starea resetata
    salveaza();
}

void Statistici::incrementeazaCuvantCorect() {
    cuvinteCorecteTotal++;
}

void Statistici::incrementeazaNivelCompletat() {
    niveleCompletateTotal++;
}

void Statistici::incrementeazaGreseala() {
    greseliTotal++;
}

// Supraincarcarea operatorului << pentru afisare usoara
std::ostream& operator<<(std::ostream& os, const Statistici& stats) {
    os << "  Cuvinte corecte (total): " << stats.cuvinteCorecteTotal << "\n";
    os << "  Nivele completate (total): " << stats.niveleCompletateTotal << "\n";
    os << "  Greseli (total): " << stats.greseliTotal << "\n";
    return os;
}