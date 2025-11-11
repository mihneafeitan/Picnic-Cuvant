#include "../include/Litere.h"
#include <cctype>
#include <iostream>

void Litere::adaugaLitereDinCuvant(const std::string& cuvant) {
    for (char c : cuvant) {
        litere.insert(toupper(c));
    }
}

std::ostream& operator<<(std::ostream& os, const Litere& l) {
    for (char c : l.litere) {
        os << c << " ";
    }
    return os;
}