#pragma once
#include <set>
#include <string>
#include <ostream>

class Litere {
private:
    std::set<char> litere;

public:
    Litere() = default;
    void adaugaLitereDinCuvant(const std::string& cuvant);
    friend std::ostream& operator<<(std::ostream& os, const Litere& l);
};