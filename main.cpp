#include "include/Joc.h"
#include <iostream>
#include <stdexcept> // Pentru std::exception

int main() {
    try {
        // Pornim jocul folosind fisierul CRIPTAT
        // CMake va copia 'nivele.dat' in folderul 'bin/'
        Joc picnicCuvant("nivele.dat");
        picnicCuvant.ruleaza();

    } catch (const std::exception& e) {
        std::cerr << "O eroare critica a oprit jocul: " << e.what() << std::endl;
        return 1;
    }

    // Demonstratia pentru Regula celor Trei (daca e ceruta)
    // o poti adauga aici, in afara try-catch-ului principal
    // sau chiar inainte de `picnicCuvant.ruleaza();`

    return 0;
}
