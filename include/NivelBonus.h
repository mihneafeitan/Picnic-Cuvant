#ifndef PICNIC_CUVANT_NIVELBONUS_H
#define PICNIC_CUVANT_NIVELBONUS_H

#include "Nivel.h"

// Nivel bonus: contine o litera speciala ("litera bonus"); orice cuvant
// gasit care contine acea litera primeste punctaj dublu.
class NivelBonus : public Nivel {
private:
    char literaBonus;

    void afiseazaDetalii(std::ostream& os) const override;
    int calculeazaPunctaj(const Cuvant& cuvant) const override;

public:
    NivelBonus(int id, const std::vector<char>& litere,
               const std::vector<std::string>& cuvinte, char literaBonus);

    std::unique_ptr<Nivel> clone() const override;

    char getLiteraBonus() const;   // functie specifica derivatei
};

#endif // PICNIC_CUVANT_NIVELBONUS_H
