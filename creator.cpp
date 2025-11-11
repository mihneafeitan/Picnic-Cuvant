#include <iostream>
#include <fstream>


// Cheia noastra secreta.
constexpr char CHEIE_SECRETA = 'Q'; // 'Q' de la 'Cuvant'

int main() {
    std::ifstream fisierIn("nivele.txt");
    std::ofstream fisierOut("nivele.dat", std::ios::binary);

    if (!fisierIn) {
        std::cerr << "EROARE: Nu am gasit nivele.txt\n";
        return 1;
    }

    std::cout << "Se pregatesc nivelele (criptare) -> nivele.dat...\n";
    char c;
    while (fisierIn.get(c)) {
        char charCriptat = c ^ CHEIE_SECRETA;
        fisierOut.put(charCriptat);
    }

    fisierIn.close();
    fisierOut.close();
    std::cout << "Gata! 'nivele.dat' a fost creat cu succes.\n";
    return 0;
}