#include "NivelClasic.h"

NivelClasic::NivelClasic(int nivelId, const std::vector<char>& litere,
                          const std::vector<std::string>& cuvinte)
    : Nivel(nivelId, litere, cuvinte) {}

void NivelClasic::afiseazaDetalii(std::ostream& os) const {
    os << " [Clasic]";
}

int NivelClasic::calculeazaPunctaj(const Cuvant& cuvant) const {
    return cuvant.getScorImplicit();
}

std::unique_ptr<Nivel> NivelClasic::clone() const {
    return std::make_unique<NivelClasic>(*this);
}
