#include <iostream>
#include <string>

#include <CLI11.hpp>

#include "Exceptii.h"
#include "GestionarSalvari.h"
#include "IncarcatorNivele.h"
#include "InterfataJoc.h"
#include "Joc.h"
#include "Jucator.h"
#include "Litera.h"
#include "NivelDificil.h"

int main(int argc, char** argv) {
    CLI::App app{"Picnic Cuvant - joc grafic de cuvinte in limba romana (10 nivele)"};

    std::string numeJucator = "Jucator";
    std::string folderDate = "data/nivele";
    std::string caleFont = "assets/DejaVuSans.ttf";
    std::string caleSalvare = "salvare.json";
    int numarNivele = 10;

    app.add_option("-n,--nume", numeJucator, "Numele jucatorului");
    app.add_option("-d,--date", folderDate, "Folderul cu fisierele JSON ale nivelelor");
    app.add_option("-f,--font", caleFont, "Calea catre fisierul de font (.ttf)");
    app.add_option("-k,--nivele", numarNivele, "Numarul de nivele de incarcat (max 10)");
    app.add_option("-s,--salvare", caleSalvare, "Calea catre fisierul de salvare a progresului");

    CLI11_PARSE(app, argc, argv);

    try {
        // daca exista o salvare anterioara, intrebam la tastatura daca vrem
        // sa continuam acel joc sau sa incepem unul nou (singurul loc din
        // program unde se citeste efectiv de la std::cin)
        bool reiaSalvare = false;
        GestionarSalvari::DateSalvare salvare{};
        if (GestionarSalvari::existaSalvare(caleSalvare)) {
            salvare = GestionarSalvari::incarca(caleSalvare);
            std::cout << "Am gasit un joc salvat pentru '" << salvare.nume << "' (nivel "
                      << (salvare.indexNivel + 1) << ", scor " << salvare.scorTotal << ").\n";
            std::cout << "Continui acel joc? (d = da / n = nu, joc nou): ";
            std::string raspuns;
            std::getline(std::cin, raspuns);
            reiaSalvare = !raspuns.empty() && (raspuns[0] == 'd' || raspuns[0] == 'D');
            if (reiaSalvare) {
                numeJucator = salvare.nume;
            } else {
                GestionarSalvari::stergeSalvarea(caleSalvare);
            }
        }

        Jucator jucator(numeJucator);
        Joc joc(jucator);

        auto nivele = IncarcatorNivele::incarcaToateNivelele(folderDate, numarNivele);
        for (auto& nivel : nivele) {
            joc.adaugaNivel(std::move(nivel));
        }

        // joc-ul catre InterfataJoc - altfel restauram un obiect a carui
        // stare nu mai ajunge nicaieri (interfata are deja propria copie)
        if (reiaSalvare) {
            joc.restaureazaProgres(salvare.indexNivel, salvare.scorTotal);
        }

        // demonstratie explicita a functiilor publice ramase neapelate altundeva
        // (cerinta: toate functiile membre publice trebuie apelate in main)
        std::cout << "Jucator: " << jucator.getNume() << ", scor initial: "
                  << jucator.getScorTotal() << "\n";
        std::cout << "Total jucatori creati: " << Jucator::getNumarJucatoriCreati() << "\n";
        std::cout << "Total obiecte Nivel active: " << Nivel::getNumarNivele() << "\n";

        Litera literaDemo('A', 0);
        literaDemo.selecteaza();
        std::cout << "Litera demo selectata? " << literaDemo.esteSelectata()
                  << ", pozitie: " << literaDemo.getPozitie() << "\n";
        literaDemo.deselecteaza();

        joc.afiseazaStareCurenta(std::cout);
        std::cout << "Scor nivel curent: " << joc.nivelCurent().getScorNivel() << "\n";

        if (const auto* dificil = dynamic_cast<const NivelDificil*>(&joc.nivelCurent())) {
            std::cout << "Nivel dificil esuat? " << dificil->aEsuat() << "\n";
        }

        InterfataJoc interfata(std::move(joc), caleFont);
        std::cout << interfata << "\n";
        interfata.ruleaza();

        // la inchiderea ferestrei, salvam progresul (sau stergem salvarea
        // daca jucatorul a terminat deja toate nivelele)
        const Joc& jocFinal = interfata.jocReferinta();
        if (jocFinal.ramanNivele()) {
            GestionarSalvari::salveaza(
                caleSalvare,
                {jocFinal.getJucator().getNume(), jocFinal.getJucator().getScorTotal(),
                 jocFinal.getIndexNivelCurent()});
            std::cout << "Progres salvat (nivel " << (jocFinal.getIndexNivelCurent() + 1)
                      << ", scor " << jocFinal.getJucator().getScorTotal() << ").\n";
        } else {
            GestionarSalvari::stergeSalvarea(caleSalvare);
            std::cout << "Felicitari, ai terminat toate nivelele! Salvarea a fost stearsa.\n";
        }

    } catch (const PicnicCuvantExceptie& eroare) {
        std::cerr << "Eroare: " << eroare.what() << "\n";
        return 1;
    }

    return 0;
}