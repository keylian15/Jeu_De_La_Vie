#include <iostream>
#include "Grille.hpp"

int main(int argc, char *argv[])
{
    // Initalisation des variables :
    std::string temp = ".";
    int rows = 0;
    int cols = 0;
    bool isTorus;

    // Affichage pour la config via le terminal du jeu :
    std::cout << "\t\tConfiguration des parametres du jeu :" << std::endl;

    std::cout << "=== Taille de la grille : ===" << std::endl;
    while (rows <= 0 || cols <= 0)
    {
        std::cout << "Lignes : ";
        std::cin >> rows;
        std::cout << "Colonnes : ";
        std::cin >> cols;
    }

    std::cout << "=== Type : ===\n";
    while (temp != "oui" && temp != "non")
    {
        std::cout << "Tore : (oui | non) ";
        std::cin >> temp;
    }

    isTorus = (temp == "oui");

    // Création de la Grille :
    Grille grille = Grille(rows, cols, isTorus);

    // Début du jeu :
    grille.jeu();
}

/* Pour compiler :
cmake -G "MinGW Makefiles" .
cmake --build .
.\Main.exe
*/