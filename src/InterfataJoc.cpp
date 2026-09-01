#include "InterfataJoc.h"
#include <algorithm>
#include <cmath>
#include <sstream>
#include "Exceptii.h"

namespace {
constexpr float PI = 3.14159265358979323846f;

sf::Text creazaText(const sf::Font& font, const std::string& continut, unsigned int marime,
                     sf::Color culoare, sf::Vector2f pozitie) {
    sf::Text text(font, continut, marime);
    text.setFillColor(culoare);
    text.setPosition(pozitie);
    return text;
}
}  // namespace

InterfataJoc::InterfataJoc(Joc jocInitial, const std::string& caleFont)
    : fereastra(sf::VideoMode({900u, 700u}), "Picnic Cuvant"),
      font(),
      joc(std::move(jocInitial)),
      culoareMesaj(sf::Color::White) {
    if (!font.openFromFile(caleFont)) {
        throw ExceptieFisierDate(caleFont, "fontul nu a putut fi incarcat");
    }
    fereastra.setFramerateLimit(60);
    mesajStare = "Formeaza un cuvant apasand literele, apoi ENTER.";
}

void InterfataJoc::ruleaza() {
    while (fereastra.isOpen()) {
        proceseazaEvenimente();
        actualizeaza();
        deseneaza();
    }
}

void InterfataJoc::proceseazaEvenimente() {
    while (const std::optional<sf::Event> eveniment = fereastra.pollEvent()) {
        if (eveniment->is<sf::Event::Closed>()) {
            fereastra.close();
        }
        else if (const auto* apasare = eveniment->getIf<sf::Event::MouseButtonPressed>()) {
                if (apasare->button == sf::Mouse::Button::Left && joc.ramanNivele()) {
                    sf::Vector2f punct(static_cast<float>(apasare->position.x),
                    static_cast<float>(apasare->position.y));
                    int index = literaLaPunct(punct);
                    if (index >= 0) {
                        bool dejaSelectata =
                            std::find(selectieCurenta.begin(), selectieCurenta.end(), index) !=
                            selectieCurenta.end();
                        if (!dejaSelectata) {
                            selectieCurenta.push_back(index);
                        }
                    }
                }
        }
        else if (const auto* tasta = eveniment->getIf<sf::Event::KeyPressed>()) {
            if (!joc.ramanNivele()) {
                continue;   // jocul s-a incheiat, nu mai raspundem la taste de joc
            }
            if (tasta->code == sf::Keyboard::Key::Enter) {
                if (joc.nivelCurent().esteNivelComplet()) {
                    golesteSelectia();
                    joc.treciLaNivelUrmator();
                    if (joc.ramanNivele()) {
                        mesajStare = "Nivel nou! Formeaza un cuvant si apasa ENTER.";
                        culoareMesaj = sf::Color::White;
                    }
                }
                else {
                    confirmaSelectie();
                }
            }
            else if (tasta->code == sf::Keyboard::Key::Backspace) {
                if (!selectieCurenta.empty()) {
                    selectieCurenta.pop_back();
                }
            }
            else if (tasta->code == sf::Keyboard::Key::Escape) {
                golesteSelectia();
            }
        }
    }
}

void InterfataJoc::actualizeaza() {
    float dt = ceasCadre.restart().asSeconds();
    if (!joc.ramanNivele()) {
        return;
    }

    joc.actualizeazaNivelCurent(dt);
    // La tema 1 exista un singur tip de nivel (NivelClasic), fara limita
    // de timp; verificarea de timp expirat o adaug la tema 2, o data cu
    // NivelCronometrat.
}

void InterfataJoc::deseneaza() {
    fereastra.clear(sf::Color(24, 28, 38));

    deseneazaAntet();
    if (joc.ramanNivele()) {
        deseneazaLitere();
        deseneazaSelectieCurenta();
        deseneazaListaCuvinte();
        deseneazaInfoSpecificaNivelului();
        treciNivelDacaEComplet();
    }
    else {
        deseneazaEcranFinal();
    }

    fereastra.display();
}

void InterfataJoc::deseneazaAntet() {
    auto titlu = creazaText(font, "PICNIC CUVANT", 32, sf::Color(255, 210, 90), {30.f, 15.f});
    fereastra.draw(titlu);

    std::ostringstream info;
    if (joc.ramanNivele()) {
        info << "Nivel " << (joc.getIndexNivelCurent() + 1) << "/" << joc.getNumarNiveleTotale();
    }
    else {
        info << "Joc incheiat";
    }
    auto textNivel = creazaText(font, info.str(), 20, sf::Color(180, 200, 220), {30.f, 60.f});
    fereastra.draw(textNivel);

    auto textScor = creazaText(font, joc.getJucator().obtineRezumat(), 18, sf::Color(150, 220, 150),
                                {680.f, 20.f});
    fereastra.draw(textScor);
}

void InterfataJoc::deseneazaLitere() {
    int total = joc.nivelCurent().numarLitere();
    for (int i = 0; i < total; ++i) {
        sf::Vector2f pozitie = pozitieLitera(i, total);
        bool selectata =
            std::find(selectieCurenta.begin(), selectieCurenta.end(), i) != selectieCurenta.end();

        sf::CircleShape cerc(RAZA_LITERA);
        cerc.setOrigin({RAZA_LITERA, RAZA_LITERA});
        cerc.setPosition(pozitie);
        cerc.setFillColor(selectata ? sf::Color(255, 196, 60) : sf::Color(58, 66, 90));
        cerc.setOutlineThickness(2.f);
        cerc.setOutlineColor(sf::Color(210, 215, 230));
        fereastra.draw(cerc);

        std::string litera(1, joc.nivelCurent().literaLa(i));
        sf::Text text(font, litera, 26);
        text.setFillColor(selectata ? sf::Color::Black : sf::Color::White);
        sf::FloatRect margini = text.getLocalBounds();
        text.setOrigin({margini.position.x + margini.size.x / 2.f,
                         margini.position.y + margini.size.y / 2.f});
        text.setPosition(pozitie);
        fereastra.draw(text);
    }
}

void InterfataJoc::deseneazaSelectieCurenta() {
    sf::RectangleShape cutie({600.f, 46.f});
    cutie.setPosition({30.f, 600.f});
    cutie.setFillColor(sf::Color(38, 44, 60));
    cutie.setOutlineThickness(1.f);
    cutie.setOutlineColor(sf::Color(90, 100, 130));
    fereastra.draw(cutie);

    std::string cuvantCurent;
    for (int index : selectieCurenta) {
        cuvantCurent.push_back(joc.nivelCurent().literaLa(index));
    }
    if (cuvantCurent.empty()) {
        cuvantCurent = "...";
    }
    auto text = creazaText(font, cuvantCurent, 26, sf::Color::White, {42.f, 608.f});
    fereastra.draw(text);

    auto mesaj = creazaText(font, mesajStare, 16, culoareMesaj, {30.f, 655.f});
    fereastra.draw(mesaj);

    auto ajutor = creazaText(font, "ENTER confirma | BACKSPACE sterge o litera | ESC goleste",
                              14, sf::Color(140, 150, 170), {440.f, 660.f});
    fereastra.draw(ajutor);
}

void InterfataJoc::deseneazaListaCuvinte() {
    auto titlu = creazaText(font, "Cuvinte de gasit:", 18, sf::Color(200, 210, 230), {680.f, 60.f});
    fereastra.draw(titlu);

    int total = joc.nivelCurent().numarCuvinte();
    for (int i = 0; i < total; ++i) {
        const Cuvant& cuvant = joc.nivelCurent().cuvantLa(i);
        std::string afisat;
        sf::Color culoare = sf::Color(120, 130, 150);
        if (cuvant.esteGasit()) {
            afisat = cuvant.getText();
            culoare = sf::Color(120, 220, 140);
        } else {
            afisat = std::string(cuvant.getText().size(), '_');
        }
        auto text = creazaText(font, afisat, 18, culoare, {680.f, 90.f + i * 28.f});
        fereastra.draw(text);
    }
}

void InterfataJoc::deseneazaInfoSpecificaNivelului() {
    // la tema 1 exista un singur tip de nivel (NivelClasic), fara informatii
    // suplimentare de afisat aici. downcast-urile cu sens catre derivatele
    // NivelCronometrat / NivelDificil / NivelBonus se adauga la Tema 2.
    (void)joc.nivelCurent();
}

void InterfataJoc::deseneazaEcranFinal() {
    auto text = creazaText(font, "Ai terminat toate nivelele!", 28, sf::Color(255, 215, 90),
                            {180.f, 300.f});
    fereastra.draw(text);
    auto rezumat = creazaText(font, joc.getJucator().obtineRezumat(), 22, sf::Color::White,
                               {180.f, 350.f});
    fereastra.draw(rezumat);
}

sf::Vector2f InterfataJoc::pozitieLitera(int index, int totalLitere) const {
    float unghi = -PI / 2.f + static_cast<float>(index) * (2.f * PI / static_cast<float>(totalLitere));
    return {CENTRU_X + RAZA_CERC_LITERE * std::cos(unghi),
            CENTRU_Y + RAZA_CERC_LITERE * std::sin(unghi)};
}

int InterfataJoc::literaLaPunct(sf::Vector2f punct) const {
    if (!joc.ramanNivele()) {
        return -1;
    }
    int total = joc.nivelCurent().numarLitere();
    for (int i = 0; i < total; ++i) {
        sf::Vector2f centru = pozitieLitera(i, total);
        float dx = punct.x - centru.x;
        float dy = punct.y - centru.y;
        if (std::sqrt(dx * dx + dy * dy) <= RAZA_LITERA) {
            return i;
        }
    }
    return -1;
}

void InterfataJoc::confirmaSelectie() {
    if (selectieCurenta.empty()) {
        return;
    }
    try {
        int puncte = joc.joacaCuvant(selectieCurenta);
        if (puncte > 0) {
            mesajStare = "Cuvant gasit! +" + std::to_string(puncte) + " puncte";
            culoareMesaj = sf::Color(120, 220, 140);
        } else {
            mesajStare = "Nu e un cuvant tinta (sau a fost deja gasit).";
            culoareMesaj = sf::Color(220, 120, 120);
        }
    } catch (const PicnicCuvantExceptie& eroare) {
        mesajStare = std::string("Eroare: ") + eroare.what();
        culoareMesaj = sf::Color(220, 120, 120);
    }
    golesteSelectia();
}

void InterfataJoc::golesteSelectia() { selectieCurenta.clear(); }

void InterfataJoc::treciNivelDacaEComplet() {
    if (!joc.ramanNivele()) {
        return;
    }
    if (joc.nivelCurent().esteNivelComplet()) {
        // suprapunem un mesaj si asteptam ENTER pentru a trece mai departe;
        // simplu si predictibil: trecem automat dupa ce jucatorul apasa ENTER
        // din bucla de evenimente (esteNivelComplet ramane true pana atunci)
        sf::RectangleShape fundal({900.f, 700.f});
        fundal.setFillColor(sf::Color(0, 0, 0, 150));
        fereastra.draw(fundal);

        auto text = creazaText(font, "Nivel complet! Apasa ENTER pentru urmatorul nivel.", 22,
                                sf::Color(255, 230, 140), {150.f, 330.f});
        fereastra.draw(text);
    }
}
std::ostream& operator<<(std::ostream& os, const InterfataJoc& interfata) {
    os << "InterfataJoc[fereastra " << interfata.fereastra.getSize().x << "x"
       << interfata.fereastra.getSize().y << ", " << interfata.joc << "]";
    return os;
}