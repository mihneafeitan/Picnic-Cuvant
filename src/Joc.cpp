#include "Joc.h"
#include <utility>
#include "Exceptii.h"

Joc::Joc(Jucator jucatorInitial) : jucator(std::move(jucatorInitial)), indexNivelCurent(0) {}

Joc::Joc(const Joc& altul)
    : jucator(altul.jucator), indexNivelCurent(altul.indexNivelCurent) {
    nivele.reserve(altul.nivele.size());
    for (const auto& nivel : altul.nivele) {
        nivele.push_back(nivel->clone());   // constructor virtual (clone)
    }
}

void swap(Joc& primul, Joc& altul) noexcept {
    using std::swap;
    swap(primul.jucator, altul.jucator);
    swap(primul.nivele, altul.nivele);
    swap(primul.indexNivelCurent, altul.indexNivelCurent);
}

Joc& Joc::operator=(Joc altul) {   // copy-and-swap
    swap(*this, altul);
    return *this;
}

Joc::~Joc() = default;

void Joc::adaugaNivel(std::unique_ptr<Nivel> nivel) {
    nivele.push_back(std::move(nivel));
}

int Joc::joacaCuvant(const std::vector<int>& indiciSelectati) {
    if (indexNivelCurent < 0 || static_cast<std::size_t>(indexNivelCurent) >= nivele.size()) {
        throw ExceptieNivelInexistent(indexNivelCurent, static_cast<int>(nivele.size()));
    }

    Nivel* curent = nivele[static_cast<std::size_t>(indexNivelCurent)].get();
    int puncte = curent->proceseazaSelectie(indiciSelectati);
    jucator.adaugaPuncte(puncte);

    if (curent->esteNivelComplet()) {
        jucator.finalizeazaNivel(curent->getId());
    }
    return puncte;
}

void Joc::treciLaNivelUrmator() {
    if (!ramanNivele()) {
        throw ExceptieNivelInexistent(indexNivelCurent + 1, static_cast<int>(nivele.size()));
    }
    ++indexNivelCurent;
}

bool Joc::ramanNivele() const {
    return static_cast<std::size_t>(indexNivelCurent) < nivele.size();
}

void Joc::actualizeazaNivelCurent(float deltaSecunde) {
    if (ramanNivele()) {
        nivele[static_cast<std::size_t>(indexNivelCurent)]->actualizeaza(deltaSecunde);
    }
}

const Jucator& Joc::getJucator() const { return jucator; }

int Joc::getNumarNiveleTotale() const { return static_cast<int>(nivele.size()); }

int Joc::getIndexNivelCurent() const { return indexNivelCurent; }

const Nivel& Joc::nivelCurent() const {
    if (!ramanNivele()) {
        throw ExceptieNivelInexistent(indexNivelCurent, static_cast<int>(nivele.size()));
    }
    return *nivele[static_cast<std::size_t>(indexNivelCurent)];
}

void Joc::afiseazaStareCurenta(std::ostream& os) const {
    if (!ramanNivele()) {
        os << "Jocul s-a incheiat. " << jucator << '\n';
        return;
    }

    Nivel* curent = nivele[static_cast<std::size_t>(indexNivelCurent)].get();
    os << *curent << '\n';
    // downcast-uri catre derivate specifice (NivelCronometrat/NivelDificil)
    // se adauga la Tema 2
}

std::ostream& operator<<(std::ostream& os, const Joc& joc) {
    os << joc.jucator << ", nivel curent: " << (joc.indexNivelCurent + 1) << "/"
       << joc.nivele.size();
    return os;
}
