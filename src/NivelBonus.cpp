#include "NivelBonus.h"
#include <algorithm>
#include <cctype>

NivelBonus::NivelBonus(int nivelId, const std::vector<char>& litere,
                        const std::vector<std::string>& cuvinte, char literaBonusValoare)
    : Nivel(nivelId, litere, cuvinte),
      literaBonus(static_cast<char>(std::toupper(static_cast<unsigned char>(literaBonusValoare)))) {}

void NivelBonus::afiseazaDetalii(std::ostream& os) const {
    os << " [Bonus, litera bonus: '" << literaBonus << "' -> puncte duble]";
}

int NivelBonus::calculeazaPunctaj(const Cuvant& cuvant) const {
    bool contineLiteraBonus =
        cuvant.getText().find(literaBonus) != std::string::npos;
    return contineLiteraBonus ? cuvant.getScorImplicit() * 2 : cuvant.getScorImplicit();
}

std::unique_ptr<Nivel> NivelBonus::clone() const {
    return std::make_unique<NivelBonus>(*this);
}

char NivelBonus::getLiteraBonus() const { return literaBonus; }
