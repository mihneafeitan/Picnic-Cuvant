#include "../include/Joc.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <filesystem>

// Cheia de decriptare
constexpr char CHEIE_SECRETA_JOC = 'Q';

Joc::Joc(const std::string& fisierNivele)
    : jucatorAreProgres(false) {
    try {
        incarcaNivele(fisierNivele);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

void Joc::incarcaNivele(const std::string& numeFisier) {
    std::ifstream fisierIn(numeFisier, std::ios::binary);
    if (!fisierIn) {
        throw std::runtime_error("EROARE FATALA: Nu am gasit fisierul " + numeFisier + "\nRuleaza .\\creator.exe in folderul 'bin'!");
    }

    std::stringstream ssDecriptat;
    char c;
    while (fisierIn.get(c)) {
        char charDecriptat = c ^ CHEIE_SECRETA_JOC;
        ssDecriptat.put(charDecriptat);
    }
    fisierIn.close();

    std::string linie;
    while (std::getline(ssDecriptat, linie)) {
        if(linie.empty()) continue; // Ignora liniile goale
        std::stringstream ssLinie(linie);
        std::string segment;
        int nrNivel;

        std::getline(ssLinie, segment, ':');
        std::stringstream ssNivel(segment);
        std::string temp;
        ssNivel >> temp >> nrNivel;

        std::getline(ssLinie, segment);

        std::vector<std::string> solutii;
        std::stringstream ssCuvinte(segment);
        while (std::getline(ssCuvinte, segment, ',')) {
            segment.erase(0, segment.find_first_not_of(" \n\r\t"));
            segment.erase(segment.find_last_not_of(" \n\r\t") + 1);
            if(!segment.empty()) {
                solutii.push_back(segment);
            }
        }
        if(!solutii.empty()) {
            toateNivelele.emplace_back(nrNivel, solutii);
        }
    }
    std::cout << "Am incarcat " << toateNivelele.size() << " nivele.\n";
}

void Joc::afiseazaMeniu() const {
    std::cout << "\nBun venit, " << jucator.getNume() << "!\n";
    std::cout << "Selecteaza o optiune:\n";

    if (jucatorAreProgres) {
        std::cout << "1. Incepe Joc (Optiune Indisponibila - progres existent)\n";
        std::cout << "2. Continua Joc (Nivelul " << jucator.getNivelCurent() << ")\n";
    } else {
        std::cout << "1. Incepe Joc\n";
        std::cout << "2. Continua Joc (Optiune Indisponibila - jucator nou)\n";
    }
    std::cout << "3. Afiseaza Statistici\n";
    std::cout << "4. Exit\n";

    std::cout << "Alegerea ta: ";
}

void Joc::afiseazaProgresNivelCurent() const {
    const Nivel& nivelActual = toateNivelele.at(jucator.getNivelCurent() - 1);
    const auto& toateSolutiile = nivelActual.getNivelSolutii();
    const auto& cuvinteGasite = jucator.getCuvinteGhicite();

    for (size_t i = 0; i < toateSolutiile.size(); ++i) {
        const std::string& solutia = toateSolutiile[i];

        if (cuvinteGasite.count(solutia)) {
            std::cout << i + 1 << ". " << solutia << "\n";
        } else {
            std::cout << i + 1 << ". ";
            for (size_t j = 0; j < solutia.length(); ++j) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }
}

void Joc::ruleaza() {
    std::filesystem::create_directory("saves");
    std::filesystem::create_directory("stats");
    std::cout << "Bun venit la Picnic Cuvant!\n";
    std::cout << "Introdu numele jucatorului: ";
    std::string nume;
    std::cin >> nume;

    jucator.seteazaNume(nume.c_str());
    jucatorAreProgres = jucator.incarcaProgres();
    statistici.incarca(jucator.getNume());

    int alegere = 0;
    while (alegere != 4) {
        afiseazaMeniu();
        std::cin >> alegere;

        switch (alegere) {
            case 1:
                if (jucatorAreProgres) {
                    std::cout << "Optiune indisponibila.\n";
                } else {
                    std::cout << "Incepem un joc nou...\n";
                    jucator.reseteazaJoc();
                    statistici.reseteaza();
                    jucator.salveazaProgres();
                    jucatorAreProgres = true;
                    ruleazaSesiuneDeJoc();
                }
                break;
            case 2:
                if (jucatorAreProgres) {
                    std::cout << "Continuam jocul...\n";
                    ruleazaSesiuneDeJoc();
                } else {
                    std::cout << "Optiune indisponibila.\n";
                }
                break;

            case 3:
                std::cout << "\n--- Statistici pentru " << jucator.getNume() << " ---\n";
                std::cout << statistici; // Apeleaza operatorul << supraincarcat
                break;
            case 4:
                std::cout << "La revedere!\n";
                break;

            default:
                std::cout << "Alegere invalida.\n";
        }
    }
}

void Joc::ruleazaSesiuneDeJoc() {
    bool aIesitUtilizatorul = false;

    while (jucator.getNivelCurent() <= static_cast<int>(toateNivelele.size())) {

        aIesitUtilizatorul = joacaUnNivel();

        if (aIesitUtilizatorul) {
            jucator.salveazaProgres();
            statistici.salveaza();
            std::cout << "Progres salvat.\n";
            break; // Iesim din bucla si ne intoarcem la meniul principal
        }

        jucator.salveazaProgres(); // Salvam progresul la finalul fiecarui nivel
        statistici.salveaza();
    }

    if (!aIesitUtilizatorul) {
        std::cout << "\n*** FELICITARI, " << jucator.getNume() << "! ***\n";
        std::cout << "Ai terminat toate nivelele disponibile!\n";
        jucator.reseteazaJoc();
        statistici.reseteaza();
        jucator.salveazaProgres();
        jucatorAreProgres = false;
    }
}

bool Joc::joacaUnNivel() {
    const Nivel& nivelActual = toateNivelele.at(jucator.getNivelCurent() - 1);

    std::cout << nivelActual; // Afiseaza "Nivelul X", "Litere: ..."

    std::string incercare;
    while (true) {
        afiseazaProgresNivelCurent();
        std::cout << "\nIntrodu cuvantul (sau 'exit' pentru meniu): ";
        std::cin >> incercare;

        std::transform(incercare.begin(), incercare.end(), incercare.begin(), ::toupper);

        if (incercare == "EXIT") {
            return true; // Semnalam ca utilizatorul a iesit
        }

        int rezultatGhicire = jucator.ghicesteCuvant(incercare, nivelActual);

        if (rezultatGhicire == 1) { // Ghicit corect
            std::cout << "Corect!\n";
            statistici.incrementeazaCuvantCorect();
            if (jucator.aTerminatNivelul(nivelActual)) {
                afiseazaProgresNivelCurent();
                std::cout << "\nFelicitari, ati completat nivelul " << nivelActual.getNrNivel() << ".\n";
                statistici.incrementeazaNivelCompletat();
                jucator.completeazaNivelul();
                return false; // Semnalam ca nivelul e complet
            }
        } else if (rezultatGhicire == 0) { // Deja gasit
            std::cout << "Cuvant deja gasit.\n";
        } else { // Nu e in lista
            std::cout << "Cuvantul nu se gaseste in lista.\n";
            statistici.incrementeazaGreseala();
        }
    }
}