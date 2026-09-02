#ifndef PICNIC_CUVANT_JOC_H
#define PICNIC_CUVANT_JOC_H

#include <iostream>
#include <memory>
#include <vector>
#include "Jucator.h"
#include "Nivel.h"

// Clasa "orchestrator" a jocului: detine jucatorul si toate nivelele
// (prin pointeri de baza catre ierarhia Nivel). Este SINGURA clasa din
// proiect cu constructor de copiere / operator= / destructor definite
// explicit (copy-and-swap), pentru ca detine resurse polimorfice unice.
class Joc {
private:
    Jucator jucator;
    std::vector<std::unique_ptr<Nivel>> nivele;
    int indexNivelCurent;

public:
    explicit Joc(Jucator jucator);

    // regula celor 3: constructor de copiere, operator=, destructor
    Joc(const Joc& altul);
    Joc& operator=(Joc altul);   // copy-and-swap (parametru luat prin valoare)
    ~Joc();

    friend void swap(Joc& primul, Joc& altul) noexcept;

    void adaugaNivel(std::unique_ptr<Nivel> nivel);

    // apeleaza functii virtuale prin pointerul de baza catre nivelul curent
    int joacaCuvant(const std::vector<int>& indiciSelectati);
    void treciLaNivelUrmator();
    void restaureazaProgres(int indexNivelTinta, int scorSalvat);   // pentru reluarea unei salvari
    bool ramanNivele() const;
    void actualizeazaNivelCurent(float deltaSecunde);   // deleaga la Nivel::actualizeaza

    const Jucator& getJucator() const;
    int getNumarNiveleTotale() const;
    int getIndexNivelCurent() const;

    // acces read-only, controlat, la nivelul curent - necesar unui strat de
    // interfata (consola sau grafica) care trebuie sa stie ce sa deseneze,
    // fara sa expuna direct vectorul intern de unique_ptr
    const Nivel& nivelCurent() const;

    // afiseaza starea curenta si, prin dynamic_cast, informatii
    // suplimentare specifice tipului concret al nivelului curent
    void afiseazaStareCurenta(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Joc& joc);
};

#endif // PICNIC_CUVANT_JOC_H
