#include "NivelDificil.h"

NivelDificil::NivelDificil(int nivelId, const std::vector<char>& litere,
                            const std::vector<std::string>& cuvinte, int greseliMax)
    : Nivel(nivelId, litere, cuvinte), greseliMaxime(greseliMax), greseliCurente(0) {}

void NivelDificil::afiseazaDetalii(std::ostream& os) const {
    os << " [Dificil, greseli ramase: " << greseliRamase() << "]";
}

int NivelDificil::calculeazaPunctaj(const Cuvant& cuvant) const {
    // bonus de 50% fata de scorul implicit, ca recompensa pentru dificultate
    return static_cast<int>(cuvant.getScorImplicit() * 1.5);
}

void NivelDificil::laSelectieEsuata() {
    ++greseliCurente;
}

std::unique_ptr<Nivel> NivelDificil::clone() const {
    return std::make_unique<NivelDificil>(*this);
}

int NivelDificil::greseliRamase() const {
    int ramase = greseliMaxime - greseliCurente;
    return ramase > 0 ? ramase : 0;
}

bool NivelDificil::aEsuat() const {
    return greseliCurente >= greseliMaxime;
}
