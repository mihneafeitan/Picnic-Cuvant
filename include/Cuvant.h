#ifndef PICNIC_CUVANT_CUVANT_H
#define PICNIC_CUVANT_CUVANT_H

#include <iostream>
#include <string>

// Reprezinta un cuvant tinta dintr-un nivel (de gasit de catre jucator).
class Cuvant {
private:
    std::string text;
    int scorImplicit;   // scorul de baza, calculat din lungimea cuvantului
    bool gasit;

    int calculeazaScorImplicit() const;

public:
    explicit Cuvant(std::string text);

    void marcheazaGasit();
    bool esteGasit() const;
    const std::string& getText() const;
    int getScorImplicit() const;

    friend std::ostream& operator<<(std::ostream& os, const Cuvant& cuvant);
};

#endif // PICNIC_CUVANT_CUVANT_H
