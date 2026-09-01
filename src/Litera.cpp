#include "Litera.h"

Litera::Litera(char valoare, int pozitie)
    : valoare(valoare), pozitie(pozitie), selectata(false) {}

void Litera::selecteaza() { selectata = true; }

void Litera::deselecteaza() { selectata = false; }

bool Litera::esteSelectata() const { return selectata; }

char Litera::getValoare() const { return valoare; }

int Litera::getPozitie() const { return pozitie; }

std::ostream& operator<<(std::ostream& os, const Litera& litera) {
    os << litera.valoare;
    if (litera.selectata) {
        os << '*';
    }
    return os;
}
