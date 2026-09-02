#ifndef PICNIC_CUVANT_CLASAMENT_H
#define PICNIC_CUVANT_CLASAMENT_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Pastreaza cele mai bune scoruri obtinute vreodata, persistate intr-un
// fisier JSON separat (independent de fisierul de "salvare" al unui joc
// in desfasurare). Compune o lista de perechi (nume, scor) si stie sa se
// incarce/salveze/afiseze singura.
class Clasament {
private:
    static constexpr std::size_t MAX_INTRARI = 5;

    std::string caleFisier;
    std::vector<std::pair<std::string, int>> intrari;   // sortate descrescator dupa scor

    void sorteazaSiTaie();   // functie privata: sorteaza si pastreaza doar primele MAX_INTRARI

public:
    explicit Clasament(std::string caleFisier);

    void incarca();          // citeste din fisier (daca exista); arunca ExceptieFisierDate la JSON corupt
    void salveaza() const;   // scrie in fisier

    // functie publica netriviala: adauga un scor nou, resorteaza clasamentul
    // si intoarce true daca scorul a intrat efectiv in top (nu doar l-a adaugat orbeste)
    bool adaugaScor(const std::string& nume, int scor);

    bool esteGol() const;

    // accesori de "nivel inalt" pentru un strat de afisare (SFML), la fel
    // ca Nivel::numarLitere()/literaLa() - fara sa expuna vectorul intern
    std::size_t numarIntrari() const;
    const std::pair<std::string, int>& intrareLa(std::size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const Clasament& clasament);
};

#endif // PICNIC_CUVANT_CLASAMENT_H
