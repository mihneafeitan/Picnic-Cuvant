#include "Nivel.h"
#include <algorithm>
#include <map>
#include "Exceptii.h"

int Nivel::numarNivele = 0;

Nivel::Nivel(int nivelId, const std::vector<char>& literePermise,
             const std::vector<std::string>& cuvinteTinta)
    : id(nivelId), scorNivel(0) {
    litere.reserve(literePermise.size());
    for (std::size_t i = 0; i < literePermise.size(); ++i) {
        litere.emplace_back(literePermise[i], static_cast<int>(i));
    }

    cuvinte.reserve(cuvinteTinta.size());
    for (const auto& text : cuvinteTinta) {
        Cuvant cuvant(text);   // poate arunca ExceptieCuvantInvalid daca textul e gol
        if (!poateFiFormat(cuvant.getText())) {
            throw ExceptieCuvantInvalid(
                text, "nu poate fi format din literele nivelului " + std::to_string(nivelId));
        }
        cuvinte.push_back(std::move(cuvant));
    }

    ++numarNivele;
}

Nivel::~Nivel() {
    --numarNivele;
}

bool Nivel::poateFiFormat(const std::string& cuvant) const {
    std::map<char, int> frecventaDisponibila;
    for (const auto& litera : litere) {
        ++frecventaDisponibila[litera.getValoare()];
    }

    std::map<char, int> frecventaNecesara;
    for (char c : cuvant) {
        ++frecventaNecesara[c];
    }

    for (const auto& pereche : frecventaNecesara) {
        if (frecventaDisponibila[pereche.first] < pereche.second) {
            return false;
        }
    }
    return true;
}

void Nivel::actualizeaza(float /*deltaSecunde*/) {
    // implicit nu face nimic; doar NivelCronometrat suprascrie
}

int Nivel::proceseazaSelectie(const std::vector<int>& indiciSelectati) {
    if (indiciSelectati.empty()) {
        return 0;
    }

    std::string cuvantFormat;
    cuvantFormat.reserve(indiciSelectati.size());
    for (int index : indiciSelectati) {
        if (index < 0 || static_cast<std::size_t>(index) >= litere.size()) {
            throw ExceptieCuvantInvalid(
                cuvantFormat, "index de litera invalid: " + std::to_string(index));
        }
        cuvantFormat.push_back(litere[static_cast<std::size_t>(index)].getValoare());
    }

    auto it = std::find_if(cuvinte.begin(), cuvinte.end(), [&](const Cuvant& c) {
        return c.getText() == cuvantFormat && !c.esteGasit();
    });

    if (it == cuvinte.end()) {
        laSelectieEsuata();
        return 0;
    }

    it->marcheazaGasit();
    int puncte = calculeazaPunctaj(*it);   // apel polimorfic, specific fiecarei derivate
    scorNivel += puncte;
    return puncte;
}

bool Nivel::esteNivelComplet() const {
    return std::all_of(cuvinte.begin(), cuvinte.end(),
                        [](const Cuvant& c) { return c.esteGasit(); });
}

int Nivel::getId() const { return id; }

int Nivel::getScorNivel() const { return scorNivel; }

int Nivel::numarLitere() const { return static_cast<int>(litere.size()); }

char Nivel::literaLa(int index) const {
    if (index < 0 || static_cast<std::size_t>(index) >= litere.size()) {
        throw ExceptieCuvantInvalid("", "index de litera in afara intervalului: " + std::to_string(index));
    }
    return litere[static_cast<std::size_t>(index)].getValoare();
}

int Nivel::numarCuvinte() const { return static_cast<int>(cuvinte.size()); }

const Cuvant& Nivel::cuvantLa(int index) const {
    if (index < 0 || static_cast<std::size_t>(index) >= cuvinte.size()) {
        throw ExceptieCuvantInvalid("", "index de cuvant in afara intervalului: " + std::to_string(index));
    }
    return cuvinte[static_cast<std::size_t>(index)];
}

void Nivel::afiseaza(std::ostream& os) const {
    os << "Nivel " << id << " (" << cuvinte.size() << " cuvinte, scor curent " << scorNivel << ")";
    afiseazaDetalii(os);
    os << "\n  Litere: ";
    for (const auto& litera : litere) {
        os << litera << ' ';
    }
    os << "\n  Cuvinte: ";
    for (const auto& cuvant : cuvinte) {
        os << cuvant << "  ";
    }
}

int Nivel::getNumarNivele() { return numarNivele; }

void Nivel::laSelectieEsuata() {
    // implicit nu face nimic; NivelDificil suprascrie
}

std::ostream& operator<<(std::ostream& os, const Nivel& nivel) {
    nivel.afiseaza(os);
    return os;
}
