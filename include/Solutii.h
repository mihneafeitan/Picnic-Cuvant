#pragma once
#include <vector>
#include <string>

class Solutii {
private:
    std::vector<std::string> cuvinte;

public:
    Solutii(const std::vector<std::string>& solutii);
    bool esteSolutie(const std::string& incercare) const;
    int getNumarSolutii() const;
    const std::vector<std::string>& getToateSolutiile() const;
};