#include "include/Joc.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        Joc picnicCuvant("nivele.dat");
        picnicCuvant.ruleaza();

    } catch (const std::exception& e) {
        std::cerr << "O eroare critica a oprit jocul: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
