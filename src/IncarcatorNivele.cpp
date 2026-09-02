#include "IncarcatorNivele.h"
#include <fstream>
#include <sstream>
#include "Exceptii.h"
#include "NivelClasic.h"
#include "NivelCronometrat.h"
#include "NivelBonus.h"
#include "NivelDificil.h"
#include <json.hpp>   // biblioteca externa nlohmann/json (folosita pentru stocare/citire)

namespace IncarcatorNivele {

namespace {

std::vector<char> extrageLitere(const nlohmann::json& j) {
    std::vector<char> litere;
    for (const auto& element : j.at("litere")) {
        std::string s = element.get<std::string>();
        if (!s.empty()) {
            litere.push_back(s[0]);
        }
    }
    return litere;
}

std::vector<std::string> extrageCuvinte(const nlohmann::json& j) {
    std::vector<std::string> cuvinte;
    for (const auto& element : j.at("cuvinte")) {
        cuvinte.push_back(element.get<std::string>());
    }
    return cuvinte;
}

}  // namespace

std::unique_ptr<Nivel> incarcaUnNivel(const std::string& caleFisier) {
    std::ifstream fisier(caleFisier);
    if (!fisier.is_open()) {
        throw ExceptieFisierDate(caleFisier, "fisierul nu a putut fi deschis");
    }

    nlohmann::json continut;
    try {
        fisier >> continut;
    } catch (const nlohmann::json::parse_error& eroare) {
        throw ExceptieFisierDate(caleFisier, std::string("JSON invalid - ") + eroare.what());
    }

    try {
        int id = continut.at("id").get<int>();
        std::string tip = continut.at("tip").get<std::string>();
        std::vector<char> litere = extrageLitere(continut);
        std::vector<std::string> cuvinte = extrageCuvinte(continut);

        if (tip == "CLASIC") {
            return std::make_unique<NivelClasic>(id, litere, cuvinte);
        }
        if (tip == "CRONOMETRAT") {
            int timpLimita = continut.at("timpLimitaSecunde").get<int>();
            return std::make_unique<NivelCronometrat>(id, litere, cuvinte, timpLimita);
        }
        if (tip == "DIFICIL") {
            int greseliMaxime = continut.at("greseliMaxime").get<int>();
            return std::make_unique<NivelDificil>(id, litere, cuvinte, greseliMaxime);
        }
        if (tip == "BONUS") {
            std::string literaBonus = continut.at("literaBonus").get<std::string>();
            char litera = literaBonus.empty() ? ' ' : literaBonus[0];
            return std::make_unique<NivelBonus>(id, litere, cuvinte, litera);
        }

        throw ExceptieFisierDate(caleFisier, "tip de nivel necunoscut: " + tip);
    } catch (const nlohmann::json::out_of_range& eroare) {
        throw ExceptieFisierDate(caleFisier, std::string("camp lipsa - ") + eroare.what());
    }
}

std::vector<std::unique_ptr<Nivel>> incarcaToateNivelele(const std::string& folder, int numarNivele) {
    std::vector<std::unique_ptr<Nivel>> nivele;
    nivele.reserve(static_cast<std::size_t>(numarNivele));

    for (int i = 1; i <= numarNivele; ++i) {
        std::ostringstream numeFisier;
        numeFisier << folder << "/nivel" << (i < 10 ? "0" : "") << i << ".json";
        nivele.push_back(incarcaUnNivel(numeFisier.str()));
    }
    return nivele;
}

}  // namespace IncarcatorNivele
