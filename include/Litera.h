#ifndef PICNIC_CUVANT_LITERA_H
#define PICNIC_CUVANT_LITERA_H

#include <iostream>

// Reprezinta o singura piesa de litera de pe tabla de joc a unui nivel.
class Litera {
private:
    char valoare;
    int pozitie;      // pozitia (indexul) piesei pe tabla nivelului
    bool selectata;    // daca litera este in prezent "apasata" de jucator

public:
    Litera(char valoare, int pozitie);

    void selecteaza();
    void deselecteaza();
    bool esteSelectata() const;
    char getValoare() const;
    int getPozitie() const;

    friend std::ostream& operator<<(std::ostream& os, const Litera& litera);
};

#endif // PICNIC_CUVANT_LITERA_H
