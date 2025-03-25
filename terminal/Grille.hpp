// #ifdef Grille_hpp
// #define Grille_hpp

#include <iostream>
#include <vector>

class Grille
{
private:
    int rows, cols;                         // Dimension de la grille.
    std::vector<std::vector<int>> grid;     // Grille actuelle.
    std::vector<std::vector<int>> nextGrid; // Grille pour stocker l'étape suivante.
    std::vector<std::vector<int>> voisins;  // Grille pour stocker les voisins.

    bool isTorus; // Mode Tore ou non.

public:
    Grille(int rows, int cols, bool isTorus); // Constructeur
    void initialiser();                       // Initialiseur
    void initialiserVide();                   // Initialiseur Morte
    void initialiserPlein();                  // Initialiseur Vivante
    void initialiserDamier();                 // Initialiseur Damier
    void initialiserAleatoire();              // Initialiseur Aléatoire
    void initialiserListe();                  // Initialiseur Liste
    void afficher();                          // Afficheur
    void resetVoisins();                      // Initialiseur Voisins
    void compterVoisins();                    // Compteur Voisin
    void nextGen();                           // Generateur de la gen suivante
    void donnerStat();                        // Donneur Statistiques
    void jeu();                               // Déroulement du jeu
};

// #endif