#ifndef PICNIC_CUVANT_NIVELCLASIC_H
#define PICNIC_CUVANT_NIVELCLASIC_H

#include "Nivel.h"

// Nivel standard, fara constrangeri suplimentare: punctajul este cel de baza.
class NivelClasic : public Nivel {
private:
    void afiseazaDetalii(std::ostream& os) const override;
    int calculeazaPunctaj(const Cuvant& cuvant) const override;

public:
    NivelClasic(int id, const std::vector<char>& litere, const std::vector<std::string>& cuvinte);

    std::unique_ptr<Nivel> clone() const override;
};

#endif // PICNIC_CUVANT_NIVELCLASIC_H
