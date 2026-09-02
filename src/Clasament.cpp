#include "Clasament.h"
#include <algorithm>
#include <fstream>
#include "Exceptii.h"
#include <json.hpp>

Clasament::Clasament(std::string cale) : caleFisier(std::move(cale)) {}

void Clasament::sorteazaSiTaie() {
    std::sort(intrari.begin(), intrari.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;   // descrescator dupa scor
    });
    if (intrari.size() > MAX_INTRARI) {
        intrari.resize(MAX_INTRARI);
    }
}

void Clasament::incarca() {
    std::ifstream fisier(caleFisier);
    if (!fisier.is_open()) {
        return;   // nu exista inca niciun clasament salvat - pornim de la unul gol
    }

    nlohmann::json continut;
    try {
        fisier >> continut;
    } catch (const nlohmann::json::parse_error& eroare) {
        throw ExceptieFisierDate(caleFisier, std::string("JSON invalid - ") + eroare.what());
    }

    intrari.clear();
    try {
        for (const auto& element : continut.at("clasament")) {
            intrari.emplace_back(element.at("nume").get<std::string>(), element.at("scor").get<int>());
        }
    } catch (const nlohmann::json::out_of_range& eroare) {
        throw ExceptieFisierDate(caleFisier, std::string("camp lipsa - ") + eroare.what());
    }
    sorteazaSiTaie();
}

void Clasament::salveaza() const {
    nlohmann::json continut;
    nlohmann::json listaJson = nlohmann::json::array();
    for (const auto& intrare : intrari) {
        listaJson.push_back({{"nume", intrare.first}, {"scor", intrare.second}});
    }
    continut["clasament"] = listaJson;

    std::ofstream fisier(caleFisier);
    if (!fisier.is_open()) {
        throw ExceptieFisierDate(caleFisier, "fisierul de clasament nu a putut fi creat");
    }
    fisier << continut.dump(2);
}

bool Clasament::adaugaScor(const std::string& nume, int scor) {
    intrari.emplace_back(nume, scor);
    sorteazaSiTaie();

    return std::any_of(intrari.begin(), intrari.end(), [&](const auto& intrare) {
        return intrare.first == nume && intrare.second == scor;
    });
}

bool Clasament::esteGol() const { return intrari.empty(); }

std::size_t Clasament::numarIntrari() const { return intrari.size(); }

const std::pair<std::string, int>& Clasament::intrareLa(std::size_t index) const {
    return intrari.at(index);   // arunca std::out_of_range daca indexul e invalid
}

std::ostream& operator<<(std::ostream& os, const Clasament& clasament) {
    os << "=== CLASAMENT (top " << Clasament::MAX_INTRARI << ") ===\n";
    if (clasament.intrari.empty()) {
        os << "  (inca nu exista scoruri)\n";
        return os;
    }
    int loc = 1;
    for (const auto& intrare : clasament.intrari) {
        os << "  " << loc << ". " << intrare.first << " - " << intrare.second << " puncte\n";
        ++loc;
    }
    return os;
}
