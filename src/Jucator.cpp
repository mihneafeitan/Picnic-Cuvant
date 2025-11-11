#include "../include/Jucator.h"
#include "../include/Nivel.h" // Necesar pentru implementare
#include <cstring>
#include <fstream>
#include <iostream>

// --- Functiile din Regula celor Trei ---
void Jucator::alocaSiCopiazaNume(const char* numeNou) {
    delete[] nume; 
    nume = new char[strlen(numeNou) + 1];
    strcpy(nume, numeNou);
}

Jucator::Jucator(const char* numeJucator) : nivelCurent(1) {
    nume = new char[strlen(numeJucator) + 1];
    strcpy(nume, numeJucator);
}

Jucator::~Jucator() {
    delete[] nume;
}

Jucator::Jucator(const Jucator& altul) {
    nume = new char[strlen(altul.nume) + 1];
    strcpy(nume, altul.nume);
    nivelCurent = altul.nivelCurent;
    cuvinteGhiciteNivelCurent = altul.cuvinteGhiciteNivelCurent;
}

Jucator& Jucator::operator=(const Jucator& altul) {
    if (this != &altul) { 
        delete[] nume; 
        nume = new char[strlen(altul.nume) + 1];
        strcpy(nume, altul.nume);
        nivelCurent = altul.nivelCurent;
        cuvinteGhiciteNivelCurent = altul.cuvinteGhiciteNivelCurent;
    }
    return *this;
}
// --- Sfarsit Regula celor Trei ---

void Jucator::seteazaNume(const char* numeNou) {
    alocaSiCopiazaNume(numeNou);
}

std::string Jucator::getNume() const {
    return std::string(nume);
}

int Jucator::getNivelCurent() const {
    return nivelCurent;
}

const std::set<std::string>& Jucator::getCuvinteGhicite() const {
    return cuvinteGhiciteNivelCurent;
}

bool Jucator::salveazaProgres() const {
    std::string numeFisier = getNume() + ".save";
    std::ofstream fisierOut(numeFisier);
    if (!fisierOut) {
        return false;
    }
    fisierOut << nivelCurent;
    fisierOut.close();
    return true;
}

bool Jucator::incarcaProgres() {
    std::string numeFisier = getNume() + ".save";
    std::ifstream fisierIn(numeFisier);
    if (!fisierIn) {
        return false; 
    }
    fisierIn >> nivelCurent;
    fisierIn.close();
    return true;
}

void Jucator::completeazaNivelul() {
    nivelCurent++;
    cuvinteGhiciteNivelCurent.clear(); // Important: reseteaza cuvintele
}

void Jucator::reseteazaJoc() {
    nivelCurent = 1;
    cuvinteGhiciteNivelCurent.clear();
}

int Jucator::ghicesteCuvant(const std::string& cuvant, const Nivel& nivel) {
    if (!nivel.esteSolutie(cuvant)) {
        return -1; // Nu e solutie
    }
    if (cuvinteGhiciteNivelCurent.count(cuvant)) {
        return 0; // Deja ghicit
    }
    cuvinteGhiciteNivelCurent.insert(cuvant);
    return 1; // Ghicit acum
}

bool Jucator::aTerminatNivelul(const Nivel& n) const {
    return cuvinteGhiciteNivelCurent.size() == static_cast<size_t>(n.getNumarSolutii());
}

std::ostream& operator<<(std::ostream& os, const Jucator& j) {
    os << "Jucator: " << j.nume;
    return os;
}