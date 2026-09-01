#include <iostream>
#include <string>

#include <CLI11.hpp>

#include "Litera.h"
#include "Exceptii.h"
#include "IncarcatorNivele.h"
#include "InterfataJoc.h"
#include "Joc.h"
#include "Jucator.h"

int main(int argc, char** argv) {
    CLI::App app{"Picnic Cuvant - joc grafic de cuvinte in limba romana (10 nivele)"};

    std::string numeJucator = "Jucator";
    std::string folderDate = "data/nivele";
    std::string caleFont = "assets/DejaVuSans.ttf";
    int numarNivele = 2;   // la Tema 1 exista doar 2 nivele demo (tip CLASIC)

    app.add_option("-n,--nume", numeJucator, "Numele jucatorului");
    app.add_option("-d,--date", folderDate, "Folderul cu fisierele JSON ale nivelelor");
    app.add_option("-f,--font", caleFont, "Calea catre fisierul de font (.ttf)");
    app.add_option("-k,--nivele", numarNivele, "Numarul de nivele de incarcat (max 10)");

    CLI11_PARSE(app, argc, argv);

    try {
        Jucator jucator(numeJucator);
        Joc joc(jucator);

        auto nivele = IncarcatorNivele::incarcaToateNivelele(folderDate, numarNivele);
        for (auto& nivel : nivele) {
            joc.adaugaNivel(std::move(nivel));
        }

        InterfataJoc interfata(std::move(joc), caleFont);
        std::cout << "Jucator: " << jucator.getNume() << ", scor initial: " << jucator.getScorTotal() << "\n";
        std::cout << "Total jucatori creati: " << Jucator::getNumarJucatoriCreati() << "\n";
        std::cout << "Total obiecte Nivel active: " << Nivel::getNumarNivele() << "\n";

        Litera literaDemo('A', 0);
        literaDemo.selecteaza();
        std::cout << "Litera demo selectata? " << literaDemo.esteSelectata() << ", pozitie: " << literaDemo.getPozitie() << "\n";
        literaDemo.deselecteaza();

        joc.afiseazaStareCurenta(std::cout);
        std::cout << "Scor nivel curent: " << joc.nivelCurent().getScorNivel() << "\n";
        interfata.ruleaza();

    } catch (const PicnicCuvantExceptie& eroare) {
        std::cerr << "Eroare: " << eroare.what() << "\n";
        return 1;
    }

    return 0;
}
