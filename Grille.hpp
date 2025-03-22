#ifndef GRILLE_HPP
#define GRILLE_HPP

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
    int remplissage;

public:
    Grille(int rows, int cols);  // Constructeur
    void initialiser();          // Initialiseur
    void initialiserVide();      // Initialiseur Morte
    void initialiserPlein();     // Initialiseur Vivante
    void initialiserDamier();    // Initialiseur Damier
    void initialiserAleatoire(); // Initialiseur Aléatoire
    void resetVoisins();         // Initialiseur Voisins
    void compterVoisins();       // Compteur Voisin
    void nextGen();              // Generateur de la gen suivante
    std::vector<std::vector<int>> getState() const;
    int getRowCount();
    void setRowCount(int rows);
    void setColCount(int cels);
    int getCell(int x, int y);
    int getColCount();
    void setCell(int x, int y, int type);
    bool getTorus();
    void setTorus(bool isTorus);
    int getRemplissage();
    void setRemplissage(int remplissage);
};

#endif
