#include "NivelCronometrat.h"
#include <algorithm>

NivelCronometrat::NivelCronometrat(int nivelId, const std::vector<char>& litere,
                                    const std::vector<std::string>& cuvinte,
                                    int timpLimita)
    : Nivel(nivelId, litere, cuvinte), timpLimitaSecunde(timpLimita), timpConsumatSecunde(0.0f) {}

void NivelCronometrat::afiseazaDetalii(std::ostream& os) const {
    os << " [Cronometrat, timp ramas: " << timpRamasSecunde() << "s]";
}

int NivelCronometrat::calculeazaPunctaj(const Cuvant& cuvant) const {
    double factor = 0.5 + 0.5 * static_cast<double>(fractieTimpRamas());
    return static_cast<int>(cuvant.getScorImplicit() * factor);
}

void NivelCronometrat::actualizeaza(float deltaSecunde) {
    if (deltaSecunde > 0.0f) {
        timpConsumatSecunde += deltaSecunde;
    }
}

std::unique_ptr<Nivel> NivelCronometrat::clone() const {
    return std::make_unique<NivelCronometrat>(*this);
}

int NivelCronometrat::timpRamasSecunde() const {
    float ramas = static_cast<float>(timpLimitaSecunde) - timpConsumatSecunde;
    return ramas > 0.0f ? static_cast<int>(ramas) : 0;
}

float NivelCronometrat::fractieTimpRamas() const {
    if (timpLimitaSecunde <= 0) {
        return 1.0f;
    }
    float fractie = 1.0f - timpConsumatSecunde / static_cast<float>(timpLimitaSecunde);
    return std::clamp(fractie, 0.0f, 1.0f);
}

bool NivelCronometrat::aExpiratTimpul() const {
    return timpConsumatSecunde >= static_cast<float>(timpLimitaSecunde);
}
