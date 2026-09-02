#ifndef PICNIC_CUVANT_INTERFATAJOC_H
#define PICNIC_CUVANT_INTERFATAJOC_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Clasament.h"
#include "Joc.h"

// Strat de interfata grafica (SFML): deseneaza tabla de litere a nivelului
// curent, citeste click-urile de mouse si le traduce in apeluri catre
// Joc::joacaCuvant, si afiseaza scorul/cuvintele/starea nivelului.
//
// Este complet separata de logica jocului (Joc, Nivel si derivatele lui nu
// stiu nimic despre SFML) - InterfataJoc COMPUNE un obiect Joc (cerinta de
// compunere din Tema 1) si il foloseste doar prin interfata lui publica.
class InterfataJoc {
private:
    sf::RenderWindow fereastra;
    sf::Font font;
    Joc joc;
    Clasament clasament;
    bool scorInregistratInClasament = false;

    std::vector<int> selectieCurenta;   // indicii literelor apasate pentru cuvantul curent
    std::string mesajStare;
    sf::Color culoareMesaj;
    sf::Clock ceasCadre;

    // constante de layout (private - detalii de implementare a randarii)
    static constexpr float RAZA_CERC_LITERE = 190.f;
    static constexpr float RAZA_LITERA = 34.f;
    static constexpr float CENTRU_X = 330.f;
    static constexpr float CENTRU_Y = 380.f;

    void proceseazaEvenimente();
    void actualizeaza();
    void deseneaza();

    void deseneazaAntet();
    void deseneazaLitere();
    void deseneazaSelectieCurenta();
    void deseneazaListaCuvinte();
    void deseneazaInfoSpecificaNivelului();   // foloseste dynamic_cast pt. info specifica derivatei
    void deseneazaEcranFinal();

    sf::Vector2f pozitieLitera(int index, int totalLitere) const;
    int literaLaPunct(sf::Vector2f punct) const;   // -1 daca niciuna

    void confirmaSelectie();
    void golesteSelectia();
    void treciNivelDacaEComplet();

public:
    InterfataJoc(Joc jocInitial, const std::string& caleFont,
                 const std::string& caleClasament = "clasament.json");

    void ruleaza();   // bucla principala a ferestrei

    const Joc& jocReferinta() const;   // acces read-only, pentru salvarea progresului dupa inchidere

    friend std::ostream& operator<<(std::ostream& os, const InterfataJoc& interfata);
};

#endif // PICNIC_CUVANT_INTERFATAJOC_H
