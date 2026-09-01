#ifndef PICNIC_CUVANT_NIVELDIFICIL_H
#define PICNIC_CUVANT_NIVELDIFICIL_H

#include "Nivel.h"

// Nivel dificil: jucatorul are un numar limitat de greseli permise, dar
// primeste un bonus de punctaj pentru fiecare cuvant gasit corect.
class NivelDificil : public Nivel {
private:
    int greseliMaxime;
    int greseliCurente;

    void afiseazaDetalii(std::ostream& os) const override;
    int calculeazaPunctaj(const Cuvant& cuvant) const override;
    void laSelectieEsuata() override;

public:
    NivelDificil(int id, const std::vector<char>& litere,
                 const std::vector<std::string>& cuvinte, int greseliMaxime);

    std::unique_ptr<Nivel> clone() const override;

    int greseliRamase() const;      // functie de nivel inalt specifica derivatei
    bool aEsuat() const;
};

#endif // PICNIC_CUVANT_NIVELDIFICIL_H
