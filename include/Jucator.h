#ifndef PICNIC_CUVANT_JUCATOR_H
#define PICNIC_CUVANT_JUCATOR_H

#include <iostream>
#include <string>
#include <vector>

// Reprezinta jucatorul: nume, scor total si istoricul nivelelor finalizate.
class Jucator {
private:
    std::string nume;
    int scorTotal;
    std::vector<int> nivelurileFinalizate;

    static int numarJucatoriCreati;   // atribut static: cati Jucatori s-au creat in total

public:
    explicit Jucator(std::string nume);
    ~Jucator();

    void adaugaPuncte(int puncte);
    void finalizeazaNivel(int idNivel);
    std::string obtineRezumat() const;   // functie de nivel inalt (in loc de multi getteri)

    const std::string& getNume() const;
    int getScorTotal() const;

    static int getNumarJucatoriCreati();   // functie statica

    friend std::ostream& operator<<(std::ostream& os, const Jucator& jucator);
};

#endif // PICNIC_CUVANT_JUCATOR_H
