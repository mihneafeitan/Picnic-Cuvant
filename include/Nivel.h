#ifndef PICNIC_CUVANT_NIVEL_H
#define PICNIC_CUVANT_NIVEL_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Cuvant.h"
#include "Litera.h"

// Clasa de baza abstracta a ierarhiei de nivele. Este o ierarhie proprie
// (nu deriva dintr-o clasa predefinita) si sta la baza a 4 clase derivate:
// NivelClasic, NivelCronometrat, NivelDificil si NivelBonus.
//
// Clasa este complet agnostica fata de modul de afisare (consola sau SFML):
// expune doar date "de nivel inalt" (numarLitere/literaLa, numarCuvinte/
// cuvantLa) pe care un strat de interfata grafica le poate folosi ca sa
// deseneze tabla, fara sa expuna direct vectorii interni.
class Nivel {
protected:
    int id;
    std::vector<Litera> litere;
    std::vector<Cuvant> cuvinte;
    int scorNivel;

    static int numarNivele;   // atribut static: cate obiecte Nivel (din orice derivata) exista

    // verifica, folosind frecventa literelor (STL map), daca un cuvant poate
    // fi format doar din literele disponibile pe tabla acestui nivel
    bool poateFiFormat(const std::string& cuvant) const;

    // interfata privata pur virtuala folosita de interfata publica non-virtuala
    virtual void afiseazaDetalii(std::ostream& os) const = 0;

    // functie virtuala pura specifica temei: fiecare tip de nivel
    // puncteaza diferit un cuvant gasit (nu e o simpla citire/afisare)
    virtual int calculeazaPunctaj(const Cuvant& cuvant) const = 0;

    // hook virtual (ne-pur, implementare implicita goala) apelat cand o
    // selectie a jucatorului nu corespunde niciunui cuvant tinta negasit;
    // doar NivelDificil il suprascrie, ca sa numere greselile
    virtual void laSelectieEsuata();

public:
    Nivel(int id, const std::vector<char>& literePermise, const std::vector<std::string>& cuvinteTinta);
    virtual ~Nivel();

    // constructor virtual (clonare) - necesar pentru copierea corecta
    // a obiectelor polimorfice detinute prin unique_ptr<Nivel>
    virtual std::unique_ptr<Nivel> clone() const = 0;

    // hook virtual (ne-pur) apelat o data pe cadru de catre stratul de
    // interfata, cu timpul (in secunde) scurs de la cadrul anterior;
    // implicit nu face nimic - doar NivelCronometrat il suprascrie
    virtual void actualizeaza(float deltaSecunde);

    // functie membra publica complexa: proceseaza o selectie de indici de
    // litere facuta de jucator, verifica daca formeaza un cuvant tinta
    // negasit inca si, daca da, calculeaza si adauga punctajul polimorfic
    int proceseazaSelectie(const std::vector<int>& indiciSelectati);

    bool esteNivelComplet() const;   // foloseste std::all_of (STL)
    int getId() const;
    int getScorNivel() const;

    // accesori de "nivel inalt" pentru un strat de afisare (consola/SFML):
    // NU expun vectorii interni, doar informatia minima necesara randarii
    int numarLitere() const;
    char literaLa(int index) const;
    int numarCuvinte() const;
    const Cuvant& cuvantLa(int index) const;

    // interfata publica NON-virtuala pentru afisare (apeleaza intern
    // functia privata pur virtuala afiseazaDetalii)
    void afiseaza(std::ostream& os) const;

    static int getNumarNivele();

    friend std::ostream& operator<<(std::ostream& os, const Nivel& nivel);
};

#endif // PICNIC_CUVANT_NIVEL_H
