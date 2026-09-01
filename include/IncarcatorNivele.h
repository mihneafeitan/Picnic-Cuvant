#ifndef PICNIC_CUVANT_INCARCATORNIVELE_H
#define PICNIC_CUVANT_INCARCATORNIVELE_H

#include <memory>
#include <string>
#include <vector>
#include "Nivel.h"

// Citeste fisierele de date (JSON) ale nivelelor de pe disc, folosind
// biblioteca externa nlohmann/json, si construieste obiectul derivat
// corect (NivelClasic / NivelCronometrat / NivelDificil / NivelBonus)
// in functie de campul "tip" din fiecare fisier.
namespace IncarcatorNivele {

// incarca un singur nivel dintr-un fisier JSON; arunca ExceptieFisierDate
// daca fisierul lipseste, e malformat, sau are un tip necunoscut
std::unique_ptr<Nivel> incarcaUnNivel(const std::string& caleFisier);

// incarca, in ordine, nivelele numarNivele001.json ... din folderul dat
std::vector<std::unique_ptr<Nivel>> incarcaToateNivelele(const std::string& folder, int numarNivele);

}  // namespace IncarcatorNivele

#endif // PICNIC_CUVANT_INCARCATORNIVELE_H
