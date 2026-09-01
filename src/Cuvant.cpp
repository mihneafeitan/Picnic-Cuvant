#include "Cuvant.h"
#include "Exceptii.h"

Cuvant::Cuvant(std::string textCuvant) : text(std::move(textCuvant)), gasit(false) {
    if (text.empty()) {
        throw ExceptieCuvantInvalid(text, "un cuvant tinta nu poate fi gol");
    }
    scorImplicit = calculeazaScorImplicit();
}

int Cuvant::calculeazaScorImplicit() const {
    // 10 puncte per litera, plus un bonus pentru cuvinte lungi (peste 5 litere)
    int scor = static_cast<int>(text.size()) * 10;
    if (text.size() > 5) {
        scor += 15;
    }
    return scor;
}

void Cuvant::marcheazaGasit() { gasit = true; }

bool Cuvant::esteGasit() const { return gasit; }

const std::string& Cuvant::getText() const { return text; }

int Cuvant::getScorImplicit() const { return scorImplicit; }

std::ostream& operator<<(std::ostream& os, const Cuvant& cuvant) {
    os << cuvant.text << (cuvant.gasit ? " [gasit]" : " [?????]");
    return os;
}
