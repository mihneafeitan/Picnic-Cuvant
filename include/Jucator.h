#pragma once
#include <string>
#include <set>
#include <ostream>

class Nivel;

class Jucator {
private:
    char* nume;
    int nivelCurent;
    std::set<std::string> cuvinteGhiciteNivelCurent;

    void alocaSiCopiazaNume(const char* numeNou);

public:

    explicit Jucator(const char* numeJucator = "Necunoscut");
    ~Jucator();
    Jucator(const Jucator& altul);
    Jucator& operator=(const Jucator& altul);

    void seteazaNume(const char* numeNou);
    std::string getNume() const;
    int getNivelCurent() const;
    const std::set<std::string>& getCuvinteGhicite() const;

    bool salveazaProgres() const;
    bool incarcaProgres();

    void completeazaNivelul();
    void reseteazaJoc();
    
    int ghicesteCuvant(const std::string& cuvant, const Nivel& nivel);

    bool aTerminatNivelul(const Nivel& n) const; 

    friend std::ostream& operator<<(std::ostream& os, const Jucator& j);
};