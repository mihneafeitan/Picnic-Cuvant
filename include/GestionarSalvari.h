#ifndef PICNIC_CUVANT_GESTIONARSALVARI_H
#define PICNIC_CUVANT_GESTIONARSALVARI_H

#include <string>

// Se ocupa de salvarea/incarcarea progresului jocului intr-un fisier JSON,
// ca jucatorul sa poata continua de unde a ramas la o rulare urmatoare.
// Namespace cu functii libere (stil similar cu IncarcatorNivele), fara
// stare proprie - opereaza direct pe fisierul de pe disc.
namespace GestionarSalvari {

// datele minime necesare ca sa poti relua un joc: cine juca, cu ce scor
// acumulat, si la ce index de nivel ramasese
struct DateSalvare {
    std::string nume;
    int scorTotal;
    int indexNivel;
};

bool existaSalvare(const std::string& caleFisier);

// arunca ExceptieFisierDate daca fisierul e corupt/ilizibil
DateSalvare incarca(const std::string& caleFisier);

void salveaza(const std::string& caleFisier, const DateSalvare& date);

void stergeSalvarea(const std::string& caleFisier);

}  // namespace GestionarSalvari

#endif // PICNIC_CUVANT_GESTIONARSALVARI_H
