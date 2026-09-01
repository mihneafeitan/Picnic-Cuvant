#include "Jucator.h"
#include <algorithm>
#include <sstream>

int Jucator::numarJucatoriCreati = 0;

Jucator::Jucator(std::string numeJucator) : nume(std::move(numeJucator)), scorTotal(0) {
    ++numarJucatoriCreati;
}

Jucator::~Jucator() {
    --numarJucatoriCreati;
}

void Jucator::adaugaPuncte(int puncte) {
    if (puncte > 0) {
        scorTotal += puncte;
    }
}

void Jucator::finalizeazaNivel(int idNivel) {
    // evitam duplicatele in istoric folosind un algoritm STL
    bool existaDeja = std::find(nivelurileFinalizate.begin(), nivelurileFinalizate.end(), idNivel)
                       != nivelurileFinalizate.end();
    if (!existaDeja) {
        nivelurileFinalizate.push_back(idNivel);
    }
}

std::string Jucator::obtineRezumat() const {
    std::ostringstream out;
    out << nume << " - scor total: " << scorTotal
        << ", nivele finalizate: " << nivelurileFinalizate.size();
    return out.str();
}

const std::string& Jucator::getNume() const { return nume; }

int Jucator::getScorTotal() const { return scorTotal; }

int Jucator::getNumarJucatoriCreati() { return numarJucatoriCreati; }

std::ostream& operator<<(std::ostream& os, const Jucator& jucator) {
    os << "Jucator[" << jucator.obtineRezumat() << "]";
    return os;
}
