#ifndef PICNIC_CUVANT_NIVELCRONOMETRAT_H
#define PICNIC_CUVANT_NIVELCRONOMETRAT_H

#include "Nivel.h"

// Nivel cu limita de timp: punctajul scade pe masura ce se consuma timpul.
// Are un atribut propriu (timpLimitaSecunde) inexistent in clasa de baza,
// motiv pentru care alte clase acceseaza aceasta informatie prin dynamic_cast.
class NivelCronometrat : public Nivel {
private:
    int timpLimitaSecunde;
    float timpConsumatSecunde;

    void afiseazaDetalii(std::ostream& os) const override;
    int calculeazaPunctaj(const Cuvant& cuvant) const override;
    void actualizeaza(float deltaSecunde) override;   // scade timpul, cadru cu cadru

public:
    NivelCronometrat(int id, const std::vector<char>& litere,
                      const std::vector<std::string>& cuvinte, int timpLimitaSecunde);

    std::unique_ptr<Nivel> clone() const override;

    int timpRamasSecunde() const;      // functie de nivel inalt specifica derivatei
    float fractieTimpRamas() const;    // pentru bara de progres din UI
    bool aExpiratTimpul() const;
};

#endif // PICNIC_CUVANT_NIVELCRONOMETRAT_H
