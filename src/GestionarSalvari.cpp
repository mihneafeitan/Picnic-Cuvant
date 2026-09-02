#include "GestionarSalvari.h"
#include <cstdio>
#include <fstream>
#include "Exceptii.h"
#include <json.hpp>

namespace GestionarSalvari {

bool existaSalvare(const std::string& caleFisier) {
    std::ifstream fisier(caleFisier);
    return fisier.good();
}

DateSalvare incarca(const std::string& caleFisier) {
    std::ifstream fisier(caleFisier);
    if (!fisier.is_open()) {
        throw ExceptieFisierDate(caleFisier, "fisierul de salvare nu a putut fi deschis");
    }

    nlohmann::json continut;
    try {
        fisier >> continut;
    } catch (const nlohmann::json::parse_error& eroare) {
        throw ExceptieFisierDate(caleFisier, std::string("JSON invalid - ") + eroare.what());
    }

    try {
        DateSalvare date;
        date.nume = continut.at("nume").get<std::string>();
        date.scorTotal = continut.at("scorTotal").get<int>();
        date.indexNivel = continut.at("indexNivel").get<int>();
        return date;
    } catch (const nlohmann::json::out_of_range& eroare) {
        throw ExceptieFisierDate(caleFisier, std::string("camp lipsa - ") + eroare.what());
    }
}

void salveaza(const std::string& caleFisier, const DateSalvare& date) {
    nlohmann::json continut;
    continut["nume"] = date.nume;
    continut["scorTotal"] = date.scorTotal;
    continut["indexNivel"] = date.indexNivel;

    std::ofstream fisier(caleFisier);
    if (!fisier.is_open()) {
        throw ExceptieFisierDate(caleFisier, "fisierul de salvare nu a putut fi creat");
    }
    fisier << continut.dump(2);
}

void stergeSalvarea(const std::string& caleFisier) {
    std::remove(caleFisier.c_str());
}

}  // namespace GestionarSalvari
