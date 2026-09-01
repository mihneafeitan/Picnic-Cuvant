#ifndef PICNIC_CUVANT_EXCEPTII_H
#define PICNIC_CUVANT_EXCEPTII_H

#include <exception>
#include <string>

// Ierarhie proprie de exceptii, complet independenta de ierarhia Nivel/derivate.
// Fiecare clasa trateaza o categorie DISTINCTA de eroare din joc.

// Clasa de baza a ierarhiei de exceptii
class PicnicCuvantExceptie : public std::exception {
protected:
    std::string mesaj;

public:
    explicit PicnicCuvantExceptie(std::string mesaj);
    const char* what() const noexcept override;
    ~PicnicCuvantExceptie() override = default;
};

//  Erori legate de citirea fișierelor de date (JSON)
class ExceptieFisierDate : public PicnicCuvantExceptie {
public:
    explicit ExceptieFisierDate(const std::string& numeFisier, const std::string& detalii);
};

//  Erori legate de cuvinte invalide (nu pot fi formate din litere)
class ExceptieCuvantInvalid : public PicnicCuvantExceptie {
public:
    explicit ExceptieCuvantInvalid(const std::string& cuvant, const std::string& detalii);
};

//  Erori legate de accesarea unui nivel care nu există
class ExceptieNivelInexistent : public PicnicCuvantExceptie {
public:
    explicit ExceptieNivelInexistent(int indexCerut, int numarNiveleDisponibile);
};

#endif // PICNIC_CUVANT_EXCEPTII_H
