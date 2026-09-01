#include "Exceptii.h"

PicnicCuvantExceptie::PicnicCuvantExceptie(std::string mesaj) : mesaj(std::move(mesaj)) {}

const char* PicnicCuvantExceptie::what() const noexcept {
    return mesaj.c_str();
}

ExceptieFisierDate::ExceptieFisierDate(const std::string& numeFisier, const std::string& detalii)
    : PicnicCuvantExceptie("Fisier de date invalid [" + numeFisier + "]: " + detalii) {}

ExceptieCuvantInvalid::ExceptieCuvantInvalid(const std::string& cuvant, const std::string& detalii)
    : PicnicCuvantExceptie("Cuvant invalid [" + cuvant + "]: " + detalii) {}

ExceptieNivelInexistent::ExceptieNivelInexistent(int indexCerut, int numarNiveleDisponibile)
    : PicnicCuvantExceptie(
          "Nivelul cu indexul " + std::to_string(indexCerut) +
          " nu exista (nivele disponibile: " + std::to_string(numarNiveleDisponibile) + ")") {}
